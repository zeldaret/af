#!/usr/bin/env python3
#
#   Fixes garbage data between sections and optionally rodata section flags
#

import argparse
from libelf import *

def fix_section_flags(elf):
    for section in elf.sections:
        # Unset Alloc flag in .rodata section
        if section.name == ".rodata":
            section.sh_flags &= ~SHF_ALLOC

def fix_garbage(elf, original):
    # Begin with the original data, and paste header and section data over it
    result = original
    if len(original) < len(elf.data):
        result.extend([0]*(len(elf.data) - len(original)))
    else:
        result = result[:len(elf.data)]

    # NOTE: This only supports the elf header, program headers, section headers and section data at this time

    # emplace elf header
    hdr = elf.elf_header.to_bin()
    result[0:len(hdr)] = hdr

    # emplace program headers
    for i,proghdr in enumerate(elf.progheaders):
        offset = elf.elf_header.e_phoff + i * elf.elf_header.e_phentsize
        result[offset:offset+elf.elf_header.e_phentsize] = proghdr.to_bin()

    # emplace section headers and section data
    for i,section in enumerate(elf.sections):
        offset = elf.elf_header.e_shoff + i * elf.elf_header.e_shentsize
        section_header, section_data = section.to_bin()
        result[offset:offset+elf.elf_header.e_shentsize] = section_header
        if section_data is not None:
            result[section.sh_offset:section.sh_offset+section.sh_size] = section_data

    return result

def main():
    parser = argparse.ArgumentParser(description="Disassemble relocatable ELF object.")
    parser.add_argument("compiled", help="path to the compiled ELF file")
    parser.add_argument("original", help="path to the original ELF file")
    parser.add_argument("--fix-section-flags", help="", action="store_true")
    args = parser.parse_args()

    elf = None
    with open(args.compiled, "rb") as elf_file:
        elf = ElfFile(bytearray(elf_file.read()))

    original = None
    with open(args.original, "rb") as original_file:
        original = bytearray(original_file.read())

    if args.fix_section_flags:
        fix_section_flags(elf)

    result_data = fix_garbage(elf, original)

    with open(args.compiled, "wb") as elf_file:
        elf_file.write(result_data)

if __name__ == '__main__':
    main()
