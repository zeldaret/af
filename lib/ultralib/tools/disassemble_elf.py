#!/usr/bin/env python3
#
#   ELF disassembler that attempts to be matching
#

import argparse, struct, sys

from libelf import *
from mdebug import *
from mips_isa import *
from util import *

def debug_log(msg):
    print(msg, file=sys.stderr)

class MipsDisasm:
    """
    """

    def __init__(self, elf_file) -> None:
        self.elf_file = elf_file
        mdebug_section = elf_file.find_section_by_type(SHT_MIPS_DEBUG)
        if mdebug_section is not None:
            self.mdebug = mdebug_section
            self.has_mdebug = True
        else:
            self.has_mdebug = False
        self.cur_file = None
        self.comment_section_pos = 1
        self.section_local_labels = {}

    def add_section_local_label(self, section, offset):
        if section not in self.section_local_labels:
            self.section_local_labels.update({section : set()})
        self.section_local_labels[section].add(offset)

    def advance_file(self):
        seen_cur_file = False
        for sym in self.elf_file.symtab.symbol_entries:
            if sym.type == ST_FILE:
                if seen_cur_file or self.cur_file is None:
                    self.cur_file = sym
                    break
                elif self.cur_file == sym:
                    seen_cur_file = True
        return self.cur_file is not None

    def disassemble_all_sections(self):
        print(MipsDisasm.asm_prelude())

        # debug_log("Name        Type         Addr     Off    Size   ES Flg Lk Inf    Al")
        for section in self.elf_file.sections:
            local_labels = self.section_local_labels.get(section.name, None)
            # debug_log(section)
            if section.name in ['', '.strtab', '.shstrtab', '.symtab', '.reginfo', '.comment', '.note', '.options', '.mdebug', '.gptab.data', '.gptab.bss'] or \
                (section.sh_type == SHT_REL or section.sh_type == SHT_RELA):
                continue
            if section.sh_size == 0:
                continue
            print("")
            print(MipsDisasm.begin_section(section))
            if section.is_executable():
                self.disassemble_exec(section)
            elif section.sh_type == SHT_PROGBITS:
                # TODO kmc as doesn't support incbin, byte array this
                # print(f".incbin \"libultra.a\", 0x{section.sh_offset:08X}, 0x{section.sh_size:X}")
                first = True
                for i,b in enumerate(section.data):
                    if local_labels is not None and i in local_labels:
                        if not first:
                            print("")
                        print(f".{section.name[1].upper()}_{i:08X}:")
                        print("    .byte ", end='')
                        first = True
                    elif first:
                        print("    .byte ", end='')
                    if not first:
                        print(", ", end='')
                    print(f"0x{int(b):02X}", end='')
                    first = False
                print("")
            elif section.sh_type == SHT_NOBITS:
                print(f".skip 0x{section.sh_size:X}")
            else:
                assert False, f"Unhandled section: {section.name}"
                # debug_log("/// UNHANDLED ///")

    def pass_section(self, section):
        pass

    @staticmethod
    def asm_prelude():
        return f""".include "macro.inc"
#include "regdef.h"

// assembler directives
.set noat      // allow manual use of $at
.set noreorder // don't insert nops after branches"""

    @staticmethod
    def begin_section(section):
        section_flags = section.flags_str().lower().replace(' ', '')
        if section_flags != "":
            section_flags = f", \"{section_flags}\""
        section_type = ""
        if section.sh_type == SHT_PROGBITS:
            section_type = ", @progbits"
        elif section.sh_type == SHT_NOBITS:
            section_type = ", @nobits"
        if section_type != "" and section_flags == "":
            section_flags = ", \"\""

        return f""".section {section.name}{section_flags}{section_type}
.balign {section.sh_addralign}
"""

    def get_label_name(self, addr, pdr=None, optional=False):
        if pdr is not None:
            sym = pdr.lookup_sym(addr, EcoffSt.LABEL)
            if sym is not None:
                return sym.name
        if not optional:
            return f".L{addr:08X}"
        else:
            return None

    def get_comment_string(self, start):
        comment_section = self.elf_file.find_section_by_name(".comment")
        end = comment_section.data.find(b'\0', start)
        if end == -1:
            return None, None
        comment = comment_section.data[start:end].decode("ASCII")
        return comment, end + 1

    def print_end(self, vaddr, eof):
        ends = eof.get(vaddr, None)
        if ends is not None:
            for sym in ends:
                print(f"    .type {sym.name}, @{'function' if sym.type == ST_FUNC else 'object'}")
                if sym.st_size != 0:
                    print(f"    .size {sym.name}, . - {sym.name}")
                print(f"  .end {sym.name}\n")

    def disassemble_exec(self, section):
        raw_insns = as_word_list(section.data)
        insns = [decode_insn(raw, section.sh_addr + j * 4) for j,raw in enumerate(raw_insns)]

        # enumerate branch labels
        branch_labels = set()

        for i,insn in enumerate(insns):
            if insn.id in MIPS_BRANCH_INSNS or insn.id == MIPS_INS_J:
                branch_labels.add(insn.target if insn.id == MIPS_INS_J else insn.offset)

        eof = {} # vaddr : name
        def add_end(vaddr, sym):
            if vaddr not in eof:
                eof[vaddr] = set()
            eof[vaddr].add(sym)

        cur_fdr = None
        cur_pdr = None
        for i,insn in enumerate(insns):
            mnemonic = insn.mnemonic
            op_str = insn.op_str

            # Update mdebug info
            src_inf = ""
            if self.has_mdebug:
                # Get new fdr if there is one
                fdr = self.mdebug.fdr_foraddr(i * 4, extensions=('.c', '.s'))
                if fdr is not None:
                    # debug_log(fdr.name)
                    cur_fdr = fdr

                # Get new pdr if there is one
                if cur_fdr is not None:
                    pdr = cur_fdr.pdr_foraddr(i * 4)
                    if pdr is not None:
                        # debug_log(pdr)
                        cur_pdr = pdr

                # Line numbers
                if cur_pdr is not None:
                    asm_line = i - cur_pdr.addr//4
                    if asm_line < len(cur_pdr.lines):
                        src_inf = f" {cur_pdr.lines[asm_line]:4}"
                    else:
                        src_inf = " PADDING"

            # Symbols for this address
            syms = section.get_sym(i * 4)
            # if len(syms) != 0:
            #     debug_log("\n".join([str(sym) for sym in syms]))

            # Print end
            self.print_end(insn.vaddr, eof)

            # Print symbol
            for sym in syms:
                if sym.name == "gcc2_compiled.":
                    print(f"// compiler generated")
                    if self.cur_file is None:
                        print(f".version \"01.01\"")
                    if self.advance_file():
                        print(f".file 1 \"{self.cur_file.name}\"")

                    comment_string = None
                    while comment_string != "\"GCC: (GNU) 2.7.2\"":
                        comment_string, self.comment_section_pos = self.get_comment_string(self.comment_section_pos)
                        if comment_string is None:
                            break
                        print(f".ident \"{comment_string}\"")

                if sym.bind == SB_GLOBAL:
                    print(f"glabel {sym.name}")
                else:
                    print(f"{sym.name}:")

                if sym.st_size != 0:
                    print(f"  .ent {sym.name}")
                    add_end(insn.vaddr + sym.st_size, sym)
                else:
                    print(f"    .type {sym.name}, @{'function' if sym.type == ST_FUNC else 'object'}\n")

            # Print branch labels
            lbl = self.get_label_name(insn.vaddr, pdr=cur_pdr, optional=not insn.vaddr in branch_labels)
            if lbl is not None:
                print(f"{lbl}:")

            # Relocations for this address
            rels = section.get_rel(i * 4)
            assert len(rels) < 2 # There should never be more than 1 relocation for a single address, right?
            # if len(rels) != 0:
            #     debug_log("\n".join([str(rel) for rel in rels]))

            # Apply relocation
            if len(rels) != 0:
                rel = rels[0]
                if rel.rel_type == R_MIPS_26:
                    if insn.id == MIPS_INS_JAL:
                        op_str = rel.relocated_symbol.name
                        if op_str == ".text" and cur_fdr is not None:
                            pdr = cur_fdr.pdr_foraddr(insn.target)
                            if pdr is not None:
                                op_str = pdr.name
                    elif insn.id != MIPS_INS_J: # Branch labels for j instructions are also R_MIPS_26 relocations
                        assert False , f"Got unexpected R_MIPS_26 relocation {insn.id}"
                elif rel.rel_type == R_MIPS_HI16:
                    assert insn.id in [MIPS_INS_LUI]
                    rel_name = rel.relocated_symbol.name
                    if rel.relocated_symbol.type == ST_SECTION:
                        rel_name = f".{rel_name[1].upper()}_00000000"
                        if cur_fdr is not None:
                            pass

                    op_str = f"{insn.abi.gpr_names[insn.rt]}, %hi({rel_name})"
                elif rel.rel_type == R_MIPS_LO16:
                    # Ideally this should be in the elf code so the relocations don't look identical
                    addend = insn.imm
                    rel_name = rel.relocated_symbol.name
                    if rel.relocated_symbol.type == ST_SECTION:
                        rel_name = f".{rel_name[1].upper()}_{addend:08X}"
                        self.add_section_local_label(rel.relocated_symbol.name, addend)
                        addend = 0
                    addend_str = f" + 0x{addend:X}" if addend != 0 else ""

                    if insn.id == MIPS_INS_ADDIU:
                        op_str = f"{insn.abi.gpr_names[insn.rt]}, {insn.abi.gpr_names[insn.rs]}, %lo({rel_name}{addend_str})"
                    elif insn.id in MIPS_LOAD_STORE_INSNS:
                        if insn.id in MIPS_FP_LOAD_STORE_INSNS:
                            op_str = f"{insn.abi.cop1_names[insn.ft]}, "
                        else:
                            op_str = f"{insn.abi.gpr_names[insn.rt]}, "
                        op_str += f"%lo({rel_name}{addend_str})({insn.abi.gpr_names[insn.base]})"
                    else:
                        assert False
                else:
                    assert False

            # Apply branch labels
            if insn.id in MIPS_BRANCH_INSNS:
                op_str_parts = []
                for field in insn.fields:
                    if field == 'offset':
                        op_str_parts.append(self.get_label_name(insn.offset, cur_pdr))
                    else:
                        op_str_parts.append(insn.format_field(field))
                op_str = ", ".join(op_str_parts)
            elif insn.id == MIPS_INS_J:
                op_str = self.get_label_name(insn.target, cur_pdr)

            print(f"/* {section.sh_offset + i * 4:06X} {insn.vaddr:08X} {insn.raw:08X}{src_inf} */  {mnemonic:12}{op_str:35}".rstrip())
        self.print_end(section.sh_addr + section.sh_size, eof)

def main():
    parser = argparse.ArgumentParser(description="Disassemble relocatable ELF object.")
    parser.add_argument("filepath",     help="path to the ELF file")
    # TODO unimplemented optionals
    parser.add_argument("--compiler",   help="original compiler that produced the ELF (IDO or GCC, IDO default)", default="IDO")
    parser.add_argument("--strenc",     help="string encoding, default is EUC-JP for IDO and SJIS for GCC")
    args = parser.parse_args()

    elf_file = None
    with open(args.filepath, "rb") as elf:
        elf_file = ElfFile(bytearray(elf.read()))

    disassembler = MipsDisasm(elf_file)
    disassembler.disassemble_all_sections()

if __name__ == '__main__':
    main()
