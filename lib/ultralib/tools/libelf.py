#!/usr/bin/env python3
#
#   MIPS ELF library
#

import struct

from mdebug import EcoffHDRR, EcoffFdr, EcoffPdr, EcoffLiner, EcoffSymr

# =====================================================================================================
# Utility
# =====================================================================================================

def align_as(value, align):
    if align == 0:
        return value
    while (value % align != 0):
        value += 1
    return value

# =====================================================================================================
# ELF Identity
# =====================================================================================================

# Offsets into e_ident
EI_MAG0         = 0x00 # Magic char 0 , 0x7F
EI_MAG1         = 0x01 # Magic char 1 , 0x45
EI_MAG2         = 0x02 # Magic char 2 , 0x4C
EI_MAG3         = 0x03 # Magic char 3 , 0x46
EI_CLASS        = 0x04 # 
EI_DATA         = 0x05 # 
EI_VERSION      = 0x06 # 
EI_OSABI        = 0x07 # 
EI_ABIVERSION   = 0x08 # 
EI_PAD          = 0x09 # 
EI_NIDENT       = 0x10 # 

# Values for e_ident[EI_DATA]
EI_DATA_LE      = 1 # little endian
EI_DATA_BE      = 2 # big endian

EI_DATA_V = {
    EI_DATA_LE : 'Little Endian',
    EI_DATA_BE : 'Big Endian'
}

# Values for e_ident[EI_CLASS]
EI_CLASS_32     = 1 # 32-bit 
EI_CLASS_64     = 2 # 64-bit

EI_CLASS_V = {
    EI_CLASS_32 : 'ELF32',
    EI_CLASS_64 : 'ELF64'
}

# Values for e_ident[EI_OSABI]
EI_OSABI_V = {
    0x00 : 'UNIX / System V',
    0x01 : 'HP-UX',
    0x02 : 'NetBSD',
    0x03 : 'Linux',
    0x04 : 'GNU Hurd',
    0x06 : 'Solaris',
    0x07 : 'AIX',
    0x08 : 'IRIX',
    0x09 : 'FreeBSD',
    0x0A : 'Tru64',
    0x0B : 'Novell Modesto',
    0x0C : 'OpenBSD',
    0x0D : 'OpenVMS',
    0x0E : 'NonStop Kernel',
    0x0F : 'AROS',
    0x10 : 'Fenix OS',
    0x11 : 'CloudABI',
    0x12 : 'Stratus Technologies OpenVOS'
}

# =====================================================================================================
# ELF Types
# =====================================================================================================

ET_NONE   = 0x0000 # 
ET_REL    = 0x0001 # relocatable
ET_EXEC   = 0x0002 # 
ET_DYN    = 0x0003 # 
ET_CORE   = 0x0004 # 
ET_LOOS   = 0xFE00 # 
ET_HIOS   = 0xFEFF # 
ET_LOPROC = 0xFF00 # 
ET_HIPROC = 0xFFFF # 

E_TYPE = {
    ET_NONE   : 'ET_NONE',
    ET_REL    : 'ET_REL',
    ET_EXEC   : 'ET_EXEC',
    ET_DYN    : 'ET_DYN',
    ET_CORE   : 'ET_CORE',
    ET_LOOS   : 'ET_LOOS',
    ET_HIOS   : 'ET_HIOS',
    ET_LOPROC : 'ET_LOPROC',
    ET_HIPROC : 'ET_HIPROC'
}

# =====================================================================================================
# ELF Machines
# =====================================================================================================

EM_UNSPECIFIED     = 0x00
EM_ATNT_WE_32100   = 0x01
EM_SPARC           = 0x02
EM_X86             = 0x03
EM_MOTOROLA_68000  = 0x04
EM_MOTOROLA_88000  = 0x05
EM_INTEL_MCU       = 0x06
EM_INTEL_80860     = 0x07
EM_MIPS            = 0x08
EM_IBM_SYSTEM_370  = 0x09
EM_MIPS_RS3000_LE  = 0x0A
EM_RESERVED_xB     = 0x0B
EM_RESERVED_xC     = 0x0C
EM_RESERVED_xD     = 0x0D
EM_HEWLETT_PACKARD = 0x0E
EM_RESERVED_xF     = 0x0F
EM_INTEL_80960     = 0x13
EM_POWERPC         = 0x14
EM_POWERPC_64      = 0x15
EM_5390            = 0x16
EM_ARM             = 0x28
EM_SUPERH          = 0x2A
EM_IA64            = 0x32
EM_AMD64           = 0x3E
EM_TMS320C6000     = 0x8C
EM_ARM64           = 0xB7
EM_RISC_V          = 0xF3

E_MACHINE = {
    EM_UNSPECIFIED     : 'Unspecified',
    EM_ATNT_WE_32100   : 'AT&T WE 32100',
    EM_SPARC           : 'SPARC',
    EM_X86             : 'x86',
    EM_MOTOROLA_68000  : 'Motorola 68000 (M68K)',
    EM_MOTOROLA_88000  : 'Motorola 88000 (M88K)',
    EM_INTEL_MCU       : 'Intel MCU',
    EM_INTEL_80860     : 'Intel 80860',
    EM_MIPS            : 'MIPS',
    EM_IBM_SYSTEM_370  : 'IBM_System/370',
    EM_MIPS_RS3000_LE  : 'MIPS RS3000 Little-endian',
    EM_RESERVED_xB     : 'Reserved',
    EM_RESERVED_xC     : 'Reserved',
    EM_RESERVED_xD     : 'Reserved',
    EM_HEWLETT_PACKARD : 'Hewlett-Packard PA-RISC',
    EM_RESERVED_xF     : 'Reserved',
    EM_INTEL_80960     : 'Intel 80960',
    EM_POWERPC         : 'PowerPC',
    EM_POWERPC_64      : 'PowerPC (64-bit)',
    EM_5390            : 'S390, including S390x',
    EM_ARM             : 'ARM (up to ARMv7/Aarch32)',
    EM_IA64            : 'SuperH',
    EM_IA64            : 'IA-64',
    EM_AMD64           : 'amd64',
    EM_TMS320C6000     : 'TMS320C6000 Family',
    EM_ARM64           : 'ARM 64-bits (ARMv8/Aarch64)',
    EM_RISC_V          : 'RISC-V'
}

# =====================================================================================================
# Program Types
# =====================================================================================================

PT_NULL    = 0x00000000 # Program header table entry unused
PT_LOAD    = 0x00000001 # Loadable segment
PT_DYNAMIC = 0x00000002 # Dynamic linking information
PT_INTERP  = 0x00000003 # Interpreter information
PT_NOTE    = 0x00000004 # Auxiliary information
PT_SHLIB   = 0x00000005 # Reserved
PT_PHDR    = 0x00000006 # Segment containing the program header table itself
PT_TLS     = 0x00000007 # Thread-Local storage template
PT_LOOS    = 0x60000000 # Inclusive reserved range for processor-specific semantics
PT_HIOS    = 0x6FFFFFFF # ^
PT_LOPROC  = 0x70000000 # Inclusive reserved range for processor-specific semantics
PT_HIPROC  = 0x7FFFFFFF # ^

P_TYPE = {
    PT_NULL    : 'PT_NULL'   ,
    PT_LOAD    : 'PT_LOAD'   ,
    PT_DYNAMIC : 'PT_DYNAMIC',
    PT_INTERP  : 'PT_INTERP' ,
    PT_NOTE    : 'PT_NOTE'   ,
    PT_SHLIB   : 'PT_SHLIB'  ,
    PT_PHDR    : 'PT_PHDR'   ,
    PT_TLS     : 'PT_TLS'    ,
    PT_LOOS    : 'PT_LOOS'   ,
    PT_HIOS    : 'PT_HIOS'   ,
    PT_LOPROC  : 'PT_LOPROC' ,
    PT_HIPROC  : 'PT_HIPROC'
}

# =====================================================================================================
# Program Flags     ( May be platform specific ! )
# =====================================================================================================

PF_E = 1 << 0 # Execute
PF_W = 1 << 1 # Write
PF_R = 1 << 2 # Read

# =====================================================================================================
# Symbol Info
# =====================================================================================================

# Symbol Types

ST_NOTYPE  = 0
ST_OBJECT  = 1
ST_FUNC    = 2
ST_SECTION = 3
ST_FILE    = 4

SYM_TYPE = {
    ST_NOTYPE  : 'NOTYPE',
    ST_OBJECT  : 'OBJECT',
    ST_FUNC    : 'FUNC',
    ST_SECTION : 'SECTION',
    ST_FILE    : 'FILE'
}

# Symbol Bind

SB_LOCAL  = 0
SB_GLOBAL = 1
SB_WEAK   = 2

SYM_BIND = {
    SB_LOCAL  : 'LOCAL',
    SB_GLOBAL : 'GLOBAL',
    SB_WEAK   : 'WEAK'
}

# Symbol Visibility

SV_DEFAULT = 0

SYM_VIS = {
    SV_DEFAULT : 'DEFAULT'
}

# NDX

SHN_UND       = 0x0000
SHN_ABS       = 0xFFF1
SHN_COMMON    = 0xFFF2
SHN_XINDEX    = 0xFFFF
SHN_LORESERVE = 0xFF00

SYM_NDX = {
    SHN_UND       : 'UND',
    SHN_ABS       : 'ABS',
    SHN_COMMON    : 'COMMON',
    SHN_XINDEX    : 'XINDEX',
    SHN_LORESERVE : 'LORESERVE'
}

# =====================================================================================================
# Relocation Type
# =====================================================================================================

# EM_MIPS
R_MIPS_32   = 2 #  Write the 32 bit address of the symbol
R_MIPS_26   = 4 # Write the 26 bit address of the symbol divided by four (for relocating branch instructions). Fail if address won't fit
R_MIPS_HI16 = 5 # Write the high 16 bits of the address of the symbol
R_MIPS_LO16 = 6 # Write the low 16 bits of the address of the symbol

# EM_POWERPC
R_PPC_NONE        = 0   # Do nothing. Skip this entry
R_PPC_ADDR32      = 1   # Write the 32 bit address of the symbol
R_PPC_ADDR24      = 2   # Write the 24 bit address of the symbol divided by four shifted up 2 bits to the 32 bit value (for relocating branch instructions). Fail if address won't fit
R_PPC_ADDR16      = 3   # Write the 16 bit address of the symbol. Fail if address more than 16 bits
R_PPC_ADDR16_LO   = 4   # Write the low 16 bits of the address of the symbol
R_PPC_ADDR16_HI   = 5   # Write the high 16 bits of the address of the symbol
R_PPC_ADDR16_HA   = 6   # Write the high 16 bits of the address of the symbol plus 0x8000
R_PPC_ADDR14      = 7   # Write the 14 bits of the address of the symbol divided by four shifted up 2 bits to the 32 bit value (for relocating conditional branch instructions). Fail if address won't fit
R_PPC_REL24       = 10  # Write the 24 bit address of the symbol minus the address of the relocation divided by four shifted up 2 bits to the 32 bit value (for relocating relative branch instructions). Fail if address won't fit
R_PPC_REL14       = 11  # Write the 14 bit address of the symbol minus the address of the relocation divided by four shifted up 2 bits to the 32 bit value (for relocating conditional relative branch instructions). Fail if address won't fit
R_PPC_EMB_SDA21   = 109 # Small Data Area

# Gamecube/Wii custom relocations
R_DOLPHIN_NOP     = 201 # Do nothing. Skip this entry. Carry the address of the symbol to the next entry
R_DOLPHIN_SECTION = 202 # Change which section relocations are being applied to. Set the offset into the section to 0
R_DOLPHIN_END     = 203 # Stop parsing the relocation table
R_DOLPHIN_MRKREF  = 204 # Unknown

RELOC_TYPE = {
    EM_MIPS : {
        R_MIPS_32   : 'R_MIPS_32',
        R_MIPS_26   : 'R_MIPS_26',
        R_MIPS_HI16 : 'R_MIPS_HI16',
        R_MIPS_LO16 : 'R_MIPS_LO16'
    },
    EM_POWERPC : {
        R_PPC_NONE        : 'R_PPC_NONE',
        R_PPC_ADDR32      : 'R_PPC_ADDR32',
        R_PPC_ADDR24      : 'R_PPC_ADDR24',
        R_PPC_ADDR16      : 'R_PPC_ADDR16',
        R_PPC_ADDR16_LO   : 'R_PPC_ADDR16_LO',
        R_PPC_ADDR16_HI   : 'R_PPC_ADDR16_HI',
        R_PPC_ADDR16_HA   : 'R_PPC_ADDR16_HA',
        R_PPC_ADDR14      : 'R_PPC_ADDR14',
        8                 : 'R_PPC_ADDR14',
        9                 : 'R_PPC_ADDR14',
        R_PPC_REL24       : 'R_PPC_REL24',
        R_PPC_REL14       : 'R_PPC_REL14',
        12                : 'R_PPC_REL14',
        13                : 'R_PPC_REL14',
        R_PPC_EMB_SDA21   : 'R_PPC_EMB_SDA21',
        R_DOLPHIN_NOP     : 'R_DOLPHIN_NOP',
        R_DOLPHIN_SECTION : 'R_DOLPHIN_SECTION',
        R_DOLPHIN_END     : 'R_DOLPHIN_END',
        R_DOLPHIN_MRKREF  : 'R_DOLPHIN_MRKREF'
    }
}

# =====================================================================================================
# Section Types
# =====================================================================================================

SHT_NULL          = 0x00000000 # Section header table entry unused
SHT_PROGBITS      = 0x00000001 # Program data
SHT_SYMTAB        = 0x00000002 # Symbol table
SHT_STRTAB        = 0x00000003 # String table
SHT_RELA          = 0x00000004 # Relocation entries with addends
SHT_HASH          = 0x00000005 # Symbol hash table
SHT_DYNAMIC       = 0x00000006 # Dynamic linking information
SHT_NOTE          = 0x00000007 # Notes
SHT_NOBITS        = 0x00000008 # Program space with no data (bss)
SHT_REL           = 0x00000009 # Relocation entries, no addends
SHT_SHLIB         = 0x0000000A # Reserved
SHT_DYNSYM        = 0x0000000B # Dynamic linker symbol table
SHT_INIT_ARRAY    = 0x0000000E # Array of constructors
SHT_FINI_ARRAY    = 0x0000000F # Array of destructors
SHT_PREINIT_ARRAY = 0x00000010 # Array of pre-constructors
SHT_GROUP         = 0x00000011 # Section group
SHT_SYMTAB_SHNDX  = 0x00000012 # Extended section indices
SHT_NUM           = 0x00000013 # Number of defined types.
SHT_LOOS          = 0x60000000 # Start OS-specific.

# MIPS specific
SHT_MIPS_DEBUG    = 0x70000005 # .mdebug
SHT_MIPS_REGINFO  = 0x70000006 # .reginfo
SHT_MIPS_OPTIONS  = 0x7000000D # .options

SH_TYPE = {
    SHT_NULL          : 'SHT_NULL',
    SHT_PROGBITS      : 'SHT_PROGBITS',
    SHT_SYMTAB        : 'SHT_SYMTAB',
    SHT_STRTAB        : 'SHT_STRTAB',
    SHT_RELA          : 'SHT_RELA',
    SHT_HASH          : 'SHT_HASH',
    SHT_DYNAMIC       : 'SHT_DYNAMIC',
    SHT_NOTE          : 'SHT_NOTE',
    SHT_NOBITS        : 'SHT_NOBITS',
    SHT_REL           : 'SHT_REL',
    SHT_SHLIB         : 'SHT_SHLIB',
    SHT_DYNSYM        : 'SHT_DYNSYM',
    SHT_INIT_ARRAY    : 'SHT_INIT_ARRAY',
    SHT_FINI_ARRAY    : 'SHT_FINI_ARRAY',
    SHT_PREINIT_ARRAY : 'SHT_PREINIT_ARRAY',
    SHT_GROUP         : 'SHT_GROUP',
    SHT_SYMTAB_SHNDX  : 'SHT_SYMTAB_SHNDX',
    SHT_NUM           : 'SHT_NUM',
    SHT_LOOS          : 'SHT_LOOS',

    SHT_MIPS_DEBUG    : 'SHT_MIPS_DEBUG',
    SHT_MIPS_REGINFO  : 'SHT_MIPS_REGINFO',
    SHT_MIPS_OPTIONS  : 'SHT_MIPS_OPTIONS',
}

# =====================================================================================================
# Section Flags
# =====================================================================================================

SHF_WRITE            = 1 << 0 # Writable
SHF_ALLOC            = 1 << 1 # Occupies memory during execution
SHF_EXECINSTR        = 1 << 2 # Executable
SHF_MERGE            = 1 << 4 # Might be merged
SHF_STRINGS          = 1 << 5 # Contains null-terminated strings
SHF_INFO_LINK        = 1 << 6 # 'sh_info' contains SHT index
SHF_LINK_ORDER       = 1 << 7 # Preserve order after combining
SHF_OS_NONCONFORMING = 1 << 8 # Non-standard OS specific handling required
SHF_GROUP            = 1 << 9 # Section is member of a group
SHF_TLS              = 1 << 10 # Section hold thread-local data

SHF_MASKOS           = 0x0ff00000 # OS-specific
SHF_MASKPROC         = 0xf0000000 # Processor-specific
SHF_ORDERED          = 0x04000000 # Special ordering requirement (Solaris)
SHF_EXCLUDE          = 0x08000000 # Section is excluded unless referenced or allocated (Solaris)

SH_FLAG = {
    SHF_WRITE            : 'SHF_WRITE',
    SHF_ALLOC            : 'SHF_ALLOC',
    SHF_EXECINSTR        : 'SHF_EXECINSTR',
    SHF_MERGE            : 'SHF_MERGE',
    SHF_STRINGS          : 'SHF_STRINGS',
    SHF_INFO_LINK        : 'SHF_INFO_LINK',
    SHF_LINK_ORDER       : 'SHF_LINK_ORDER',
    SHF_OS_NONCONFORMING : 'SHF_OS_NONCONFORMING',
    SHF_GROUP            : 'SHF_GROUP',
    SHF_TLS              : 'SHF_TLS',
    SHF_MASKOS           : 'SHF_MASKOS',
    SHF_MASKPROC         : 'SHF_MASKPROC',
    SHF_ORDERED          : 'SHF_ORDERED',
    SHF_EXCLUDE          : 'SHF_EXCLUDE'
}

# =====================================================================================================
# ELF Header
# =====================================================================================================

ELF32_BIG_STRUCT    = '>HHIIIIIHHHHHH'
ELF32_LITTLE_STRUCT = '<HHIIIIIHHHHHH'
ELF64_BIG_STRUCT    = '>HHLLLLIHHHHHH'
ELF64_LITTLE_STRUCT = '<HHLLLLIHHHHHH'

class ElfHeader:
    """
    Describes the ELF header
    typedef struct {
        unsigned char   e_ident[EI_NIDENT];
        Elf32_Half      e_type;
        Elf32_Half      e_machine;
        Elf32_Word      e_version;
        Elf32_Addr      e_entry;
        Elf32_Off       e_phoff;
        Elf32_Off       e_shoff;
        Elf32_Word      e_flags;
        Elf32_Half      e_ehsize;
        Elf32_Half      e_phentsize;
        Elf32_Half      e_phnum;
        Elf32_Half      e_shentsize;
        Elf32_Half      e_shnum;
        Elf32_Half      e_shstrndx;
    } Elf32_Ehdr;

x00 x00 4   4   EI_MAG0         0x7F
                EI_MAG1         0x45
                EI_MAG2         0x4C
                EI_MAG3         0x46

x04 x04 1   1   EI_CLASS        1 : 32-bit , 2 : 64-bit

x05 x05 1   1   EI_DATA         1 : little-endian , 2 : big-endian

x06 x06 1   1   EI_VERSION      1

x07 x07 1   1   EI_OSABI        see EI_OSABI_V

x08 x08 1   1   EI_ABIVERSION   

x09 x09 7   7   EI_PAD          0

x10 x10 2   2   e_type          see E_TYPE

x12 x12 2   2   e_machine       see E_MACHINE

x14 x14 4   4   e_version       1

x18 x18 4   8   e_entry         ptr to entrypoint

x1C x20 4   8   e_phoff         ptr to program header table

x20 x28 4   8   e_shoff         ptr to section header table

x24 x30 4   4   e_flags         arch-specific flags

x28 x34 2   2   e_ehsize        header size (64 : 64-bit, 52 : 32-bit)

x2A x36 2   2   e_phentsize     size of a program header table entry

x2C x38 2   2   e_phnum         number of entries in the program header table

x2E x3A 2   2   e_shentsize     size of a section header table entry

x30 x3C 2   2   e_shnum         number of entries in the section header table

x32 x3E 2   2   e_shstrndx      index of the section header table entry containing section names

x34 x40         END
    """

    def __init__(self, data):
        self.from_bin(data)
        assert self.e_ident[EI_CLASS] == EI_CLASS_32
        assert self.e_ident[EI_DATA] == EI_DATA_BE
        #assert self.e_type == ET_REL # why?
        #assert self.e_machine == 8 # MIPS I Architecture
        #assert self.e_phoff == 0 # no program header
        assert self.e_shoff != 0 # section header present
        assert self.e_shstrndx != SHN_UND # must have section names

    def from_bin(self, data):
        assert data[0:4] == b'\x7fELF', "not an ELF file"

        self.e_ident = data[EI_MAG0:EI_NIDENT]
        self.e_type, self.e_machine, self.e_version, self.e_entry, \
            self.e_phoff, self.e_shoff, self.e_flags, self.e_ehsize, \
                self.e_phentsize, self.e_phnum, self.e_shentsize, self.e_shnum, \
                    self.e_shstrndx = struct.unpack(ELF32_BIG_STRUCT, data[EI_NIDENT:])

    def to_bin(self):
        return self.e_ident + struct.pack(ELF32_BIG_STRUCT, self.e_type,
                self.e_machine, self.e_version, self.e_entry, self.e_phoff,
                self.e_shoff, self.e_flags, self.e_ehsize, self.e_phentsize,
                self.e_phnum, self.e_shentsize, self.e_shnum, self.e_shstrndx)

    def __str__(self):
        out = "ELF Header:\n"
        out += f"Magic:                             {' '.join([f'{m:02X}' for m in self.e_ident[EI_MAG0:EI_MAG3+1]])}\n"
        out += f"Class:                             {EI_CLASS_V[self.e_ident[EI_CLASS]]}\n"
        out += f"Data:                              {EI_DATA_V[self.e_ident[EI_DATA]]}\n"
        out += f"Version:                           {self.e_ident[EI_VERSION]}\n"
        out += f"OS/ABI:                            {EI_OSABI_V[self.e_ident[EI_OSABI]]}\n"
        out += f"ABI Version:                       {self.e_ident[EI_ABIVERSION]}\n"
        out += f"Type:                              {E_TYPE[self.e_type].replace('ET_','')}\n"
        out += f"Machine:                           {E_MACHINE[self.e_machine]}\n"
        out += f"Version:                           {self.e_version}\n"
        out += f"Entrypoint:                        0x{self.e_entry:08X}\n" # TODO 08 or 16 depending on bitness
        out += f"Start of program headers:          0x{self.e_phoff:08X}\n"
        out += f"Start of section headers:          0x{self.e_shoff:08X}\n"
        out += f"Flags:                             0x{self.e_flags:08X}\n" # TODO flags prettyprint
        out += f"Size of this header:               0x{self.e_ehsize:08X}\n"
        out += f"Size of program headers:           0x{self.e_phentsize:08X}\n"
        out += f"Number of program headers:         {self.e_phnum}\n"
        out += f"Size of section headers:           0x{self.e_shentsize:08X}\n"
        out += f"Number of section headers:         {self.e_shnum}\n"
        out += f"Section header string table index: {self.e_shstrndx}"
        return out

# =====================================================================================================
# Program Header
# =====================================================================================================

PROGHDR32_BIG_STRUCT    = '>IIIIIIII'
PROGHDR32_LITTLE_STRUCT = '<IIIIIIII'
PROGHDR64_BIG_STRUCT    = '>IILLLLLL'
PROGHDR64_LITTLE_STRUCT = '<IILLLLLL'

class ProgramHeader:
    """
    Describes the Program Header

    typedef union {
        struct {
            Elf32_Word p_type;
            Elf32_Off  p_offset;
            Elf32_Addr p_vaddr;
            Elf32_Addr p_paddr;
            Elf32_Word p_filesz;
            Elf32_Word p_memsz;
            Elf32_Word p_flags;
            Elf32_Word p_align;
        } Elf64_Phdr;
        struct {
            Elf64_Word  p_type;
            Elf64_Word  p_flags;
            Elf64_Off   p_offset;
            Elf64_Addr  p_vaddr;
            Elf64_Addr  p_paddr;
            Elf64_DWord p_filesz;
            Elf64_DWord p_memsz;
            Elf64_DWord p_align;
        } Elf64_Phdr;
    } Elf_Phdr

x00 x00 4   4   p_type      see P_TYPE

--- x04 -   4   p_flags     Segment-dependent flags (64)

x04 x08 4   8   p_offset    Offset of the segment in the file image

x08 x10 4   8   p_vaddr     Virtual address of the segment in memory

x0C x18 4   8   p_paddr     Physical address of the segment in memory if applicable

x10 x20 4   8   p_filesz    Size in bytes of the segment in the file image

x14 x28 4   8   p_memsz     Size in bytes of the segment in memory

x18 --- 4   -   p_flags     Segment-dependent flags (32)

x1C x30 4   8   p_align     0 or 1 : No alignment , 2^x : Align 2^x

x20 x38         END
    """

    def __init__(self, data, arch):
        self.arch = arch
        self.from_bin(data)

    def from_bin(self, data):
        if self.arch == EI_CLASS_32: # flags are located differently based on 32 bit or 64 bit due to alignment
            self.p_type,  self.p_offset, self.p_vaddr, self.p_paddr, \
                self.p_filesz, self.p_memsz, self.p_flags, self.p_align = struct.unpack(PROGHDR32_BIG_STRUCT, data)
        else:
            self.p_type, self.p_flags, self.p_offset, self.p_vaddr, \
                self.p_paddr, self.p_filesz, self.p_memsz, self.p_align = struct.unpack(PROGHDR32_BIG_STRUCT, data)

    def to_bin(self):
        if self.arch == EI_CLASS_32:
            return struct.pack(PROGHDR32_BIG_STRUCT, self.p_type,  self.p_offset, self.p_vaddr, self.p_paddr, \
                self.p_filesz, self.p_memsz, self.p_flags, self.p_align)
        else:
            return struct.pack(PROGHDR32_LITTLE_STRUCT, self.p_type, self.p_flags, self.p_offset, self.p_vaddr, \
                self.p_paddr, self.p_filesz, self.p_memsz, self.p_align)

    def is_readable(self):
        return (self.p_flags & PF_R) == PF_R

    def is_writable(self):
        return (self.p_flags & PF_W) == PF_W

    def is_executable(self):
        return (self.p_flags & PF_E) == PF_E

    def __str__(self):
        out = f"  {P_TYPE[self.p_type].replace('PT_','')}       "
        out += f"0x{self.p_offset:06X} "
        out += f"0x{self.p_vaddr:08X} "
        out += f"0x{self.p_paddr:08X} "
        out += f"0x{self.p_filesz:05X} "
        out += f"0x{self.p_memsz:05X} "

        out += "R" if self.is_readable() else " "
        out += "W" if self.is_writable() else " "
        out += "E" if self.is_executable() else " "
        out += " "

        out += f"0x{self.p_align:02X}"
        return out

# =====================================================================================================
# Symbol
# =====================================================================================================

class Symbol:
    """
    typedef struct {
        Elf32_Word      st_name;
        Elf32_Addr      st_value;
        Elf32_Word      st_size;
        unsigned char   st_info;
        unsigned char   st_other;
        Elf32_Half      st_shndx;
    } Elf32_Sym;
    """

    def __init__(self, data, elf_file, name=None):
        self.st_name, self.st_value, self.st_size, st_info, self.st_other, self.st_shndx = struct.unpack('>IIIBBH', data)
        assert self.st_shndx != SHN_XINDEX, "too many sections (SHN_XINDEX not supported)"
        self.bind = st_info >> 4
        self.type = st_info & 0xF
        self.visibility = self.st_other & 3
        self.parent_section = elf_file.sections[self.st_shndx] if self.st_shndx < SHN_LORESERVE else None

        self.name = name
        if self.type == ST_SECTION:
            self.name = elf_file.shstrtab.lookup_str(self.parent_section.sh_name)
        if self.name == None:
            self.name = elf_file.symtab.strtab.lookup_str(self.st_name)

    @staticmethod
    def from_parts(st_name, st_value, st_size, st_info, st_other, st_shndx, strtab, name):
        header = struct.pack('>IIIBBH', st_name, st_value, st_size, st_info, st_other, st_shndx)
        return Symbol(header, strtab, name)

    def to_bin(self):
        st_info = (self.bind << 4) | self.type
        return struct.pack('>IIIBBH', self.st_name, self.st_value, self.st_size, st_info, self.st_other, self.st_shndx)

    def section_offset(self):
        return self.st_value - self.parent_section.sh_addr

    def padded_size_n(self, n):
        return align_as(self.st_size, n)

    def padded_size(self):
        return self.padded_size_n(self.parent_section.sh_addralign)

    def __str__(self):
        #    Num:    Value  Size Type    Bind   Vis      Ndx Name
        ndx = '  ' + (SYM_NDX[self.st_shndx] if self.st_shndx in SYM_NDX.keys() else self.parent_section.name)
        out = f"{self.st_value:08X} {self.st_size:06X} {SYM_TYPE[self.type]:7} {SYM_BIND[self.bind]:6} {SYM_VIS[self.visibility]:7} {ndx:12} {self.name}"
        return out

# =====================================================================================================
# Relocation
# =====================================================================================================

class Relocation:
    """
    typedef struct {
        Elf32_Word  r_offset;
        struct {
            Elf32_Word  sym_index : 24;
            Elf32_Word  rel_type  : 8;
        } r_info;
        Elf32_Word  r_addend;
    } Elf32_Reloc;
    """

    def __init__(self, data, elf_file, target_section, sh_type):
        self.sh_type = sh_type
        if sh_type == SHT_REL:
            self.r_offset, self.r_info = struct.unpack('>II', data)
            self.r_addend = 0
        else:
            self.r_offset, self.r_info, self.r_addend = struct.unpack('>III', data)
        self.sym_index = self.r_info >> 8
        self.rel_type = self.r_info & 0xff
        self.relocated_symbol = elf_file.symtab.symbol_entries[self.sym_index]
        self.elf_machine = elf_file.elf_header.e_machine
        self.target_section = target_section
        # TODO obtain the addend if the target section is executable

    def to_bin(self):
        self.r_info = (self.sym_index << 8) | self.rel_type
        if self.sh_type == SHT_REL:
            return struct.pack('>II', self.r_offset, self.r_info)
        else:
            return struct.pack('>III', self.r_offset, self.r_info, self.r_addend)

    def relocated_symbol_in_section(self, symtab, section):
        return symtab.lookup_symbol_in_section(symtab.symbol_entries[self.sym_index].st_value, section)

    def __str__(self):
        relocated_symbol = self.relocated_symbol
        #   Offset      Info Type             Sym.Value   Sym. Name + Addend
        # 80135560  00091201 R_MY_RELOC_TYPE  800f39e0   ...data.0 + 0
        out = f"{self.r_offset:08X}  {self.r_info:08X} {RELOC_TYPE[self.elf_machine][self.rel_type]:17} {relocated_symbol.st_value:08X}   {relocated_symbol.name} + 0x{self.r_addend:X}"
        return out

# =====================================================================================================
# Section
# =====================================================================================================

class Section:
    """
    Describes a section

    typedef struct {
        Elf32_Word   sh_name;
        Elf32_Word   sh_type;
        Elf32_Word   sh_flags;
        Elf32_Addr   sh_addr;
        Elf32_Off    sh_offset;
        Elf32_Word   sh_size;
        Elf32_Word   sh_link;
        Elf32_Word   sh_info;
        Elf32_Word   sh_addralign;
        Elf32_Word   sh_entsize;
    } Elf32_Shdr;

x00 x00 4   4   sh_name         Offset to string in the .shstrtab section representing this section's name

x04 x04 4   4   sh_type         See SH_TYPE

x08 x08 4   8   sh_flags        See SH_FLAG

x0C x10 4   8   sh_addr         Virtual address of the section in memory (for loaded sections)

x10 x18 4   8   sh_offset       Offset of the section in the file image

x14 x20 4   8   sh_size         Size in bytes of the section in the file image

x18 x28 4   4   sh_link         Contains the section index of an associated section. This field is used for several purposes depending on section type

x1C x2C 4   4   sh_info         Contains extra information about the section. This field is used for several purposes, depending on section type

x20 x30 4   8   sh_addralign    Contains the required alignment of the section. This field must be a power of two

x24 x38 4   8   sh_entsize      Contains the size, in bytes, of each entry, for sections that contain fixed-size entries. Zero otherwise

x28 x40         END
    """

    def __init__(self, header, elf_file, index):
        self.late_init_done = False
        self.sh_name, self.sh_type, \
            self.sh_flags, self.sh_addr, \
                self.sh_offset, self.sh_size, \
                    self.sh_link, self.sh_info, \
                        self.sh_addralign, self.sh_entsize = struct.unpack('>IIIIIIIIII', header)
        assert not self.sh_flags & SHF_LINK_ORDER
        if self.sh_entsize != 0:
            assert self.sh_size % self.sh_entsize == 0
        if self.sh_type in [SHT_NULL, SHT_NOBITS]:
            self.data = None
        else:
            self.data = elf_file.data[self.sh_offset:][:self.sh_size]
        self.index = index
        self.relocated_by = []
        self.elf_file = elf_file

    def late_init(self):
        self.late_init_done = True

    @staticmethod
    def from_parts(sh_name, sh_type, sh_flags, sh_link, sh_info, sh_addralign, sh_entsize, sh_addr, sh_offset, data, index):
        header = struct.pack('>IIIIIIIIII', sh_name, sh_type, sh_flags, sh_addr, sh_offset, \
            len(data), sh_link, sh_info, sh_addralign, sh_entsize)
        return Section(header, data, index)

    def to_bin(self):
        if self.sh_type not in [SHT_NULL, SHT_NOBITS]:
            self.sh_size = len(self.data)
        header = struct.pack('>IIIIIIIIII', self.sh_name, self.sh_type, self.sh_flags, self.sh_addr, self.sh_offset, self.sh_size, self.sh_link, self.sh_info, self.sh_addralign, self.sh_entsize)
        return header, self.data

    def get_rel(self, addr):
        relocs = []
        for reloc_section in self.relocated_by:
            reloc = reloc_section.find_reloc(addr)
            if reloc is not None:
                relocs.append(reloc)
        return relocs

    def get_sym(self, addr):
        symtab = self.elf_file.symtab
        symbols = []
        for symbol in symtab.symbol_entries:
            if symbol.st_value == addr and symbol.st_shndx == self.index and symbol.type != ST_SECTION:
                symbols.append(symbol)
        return symbols

    def is_rel(self):
        return self.sh_type == SHT_REL or self.sh_type == SHT_RELA

    def is_allocable(self):
        return (self.sh_flags & SHF_ALLOC) == SHF_ALLOC

    def is_executable(self):
        return (self.sh_flags & SHF_EXECINSTR) == SHF_EXECINSTR

    def is_writable(self):
        return (self.sh_flags & SHF_WRITE) == SHF_WRITE

    def padded_size(self):
        return align_as(self.sh_size, self.sh_addralign)

    def padded_size_4(self):
        return align_as(self.sh_size, 4)

    def flags_str(self):
        flags = ""
        flags += "W" if self.is_writable() else " "
        flags += "A" if self.is_allocable() else " "
        flags += "X" if self.is_executable() else " "
        return flags

    def __str__(self):
        s_type = SH_TYPE[self.sh_type].replace('SHT_','') if self.sh_type in SH_TYPE.keys() else str(self.sh_type)
        out = f"{self.name:12}{s_type:12} "
        out += f"{self.sh_addr:08X} "
        out += f"{self.sh_offset:06X} "
        out += f"{self.sh_size:06X} "
        out += f"{self.sh_entsize:2X} "
        out += f"{self.flags_str():3} "
        out += f"{self.sh_link:2} "
        out += f"{self.sh_info:3} "
        out += f"{self.sh_addralign:5X} "
        return out

class SymtabSection(Section):
    """
    Symbol Table Section
    """

    def __init__(self, header, elf_file, index):
        super().__init__(header, elf_file, index)
        assert self.sh_entsize == 16

    def late_init(self):
        if self.late_init_done:
            return
        super().late_init()
        self.strtab = self.elf_file.sections[self.sh_link]
        self.symbol_entries = []
        for i in range(0, self.sh_size, self.sh_entsize):
            self.symbol_entries.append(Symbol(self.data[i:i+self.sh_entsize], self.elf_file))

    def to_bin(self):
        header, _ = super().to_bin()
        data = bytearray()
        for sym in self.symbol_entries:
            data.extend(sym.to_bin())
        return header, data

    def find_symbol(self, name):
        for s in self.symbol_entries:
            if s.name == name:
                return (s.st_shndx, s.st_value)
        return None

    def lookup_symbol(self, vaddr):
        found = []
        for s in self.symbol_entries:
            if s.st_value == vaddr and s.type != ST_SECTION:
                found.append(s)
        if len(found) != 0:
            found.sort(reverse=True, key=(lambda s : s.type))
            return found[0]
        return None

    def lookup_symbol_for_section(self, vaddr, shndx):
        found = []
        for s in self.symbol_entries:
            if s.st_value == vaddr and s.type != ST_SECTION and s.st_shndx == shndx:
                found.append(s)
        if len(found) != 0:
            found.sort(reverse=True, key=(lambda s : s.type))
            return found[0]
        return None

    def lookup_symbol_in_section(self, vaddr, section):
        found = []
        for s in self.symbol_entries:
            if s.st_value == vaddr and s.type != ST_SECTION and s.st_shndx == section.index:
                found.append(s)
        if len(found) != 0:
            found.sort(reverse=True, key=(lambda s : s.type))
            return found[0]
        return None

    def find_symbol_in_section(self, name, section):
        pos = self.find_symbol(name)
        assert pos is not None
        assert pos[0] == section.index
        return pos[1]

    def local_symbols(self):
        return self.symbol_entries[:self.sh_info]

    def global_symbols(self):
        return self.symbol_entries[self.sh_info:]

class StrtabSection(Section):
    """
    String Table Section
    """
    def __init__(self, header, data, index):
        super().__init__(header, data, index)

    def lookup_str(self, index):
        to = self.data.find(b'\0', index)
        assert to != -1
        return self.data[index:to].decode('latin1')

class RelocationSection(Section):
    """
    Relocation Section
    """
    def __init__(self, header, data, index):
        super().__init__(header, data, index)

    def late_init(self):
        if self.late_init_done:
            return
        super().late_init()
        self.rel_target = self.elf_file.sections[self.sh_info]
        self.rel_target.relocated_by.append(self)
        self.relocations = []
        for i in range(0, self.sh_size, self.sh_entsize):
            self.relocations.append(Relocation(self.data[i:][:self.sh_entsize], self.elf_file, self.rel_target, self.sh_type))

    def to_bin(self):
        header, _ = super().to_bin()
        data = bytearray()
        for rel in self.relocations:
            data.extend(rel.to_bin())
        return header, data

    def lookup_reloc(self, vaddr):
        for r in self.relocations:
            if r.r_offset - r.r_offset % 4 == vaddr:
                return r
        return None

    def find_reloc(self, vaddr):
        for r in self.relocations:
            if r.r_offset == vaddr:
                return r
        return None

    def lookup_jtbl_reloc(self, vaddr, symtab):
        for r in self.relocations:
            r_sym = r.relocated_symbol(symtab)
            if r_sym.st_value + r.r_addend == vaddr:
                return r
        return None

class MdebugSection(Section):
    """
    MIPS Debugging Section
    """
    def __init__(self, header, elf_file, index):
        super().__init__(header, elf_file, index)
        self.parent = self.elf_file
        self.hdrr = EcoffHDRR(self.data)
 
        self.fdrs = []
        for i in range(self.hdrr.ifdMax):
            fdr = EcoffFdr.from_binary(self, i)
            self.fdrs.append(fdr)

    def late_init(self):
        if self.late_init_done:
            return
        super().late_init()
        for fdr in self.fdrs:
            fdr.late_init()

    def fdr_forname(self, filename):
        for fdr in self.fdrs:
            # remove path and file ext
            normalized_name = ".".join(fdr.name.split("/")[-1].split(".")[:-1])

            if normalized_name == filename:
                return fdr
        return None

    def fdr_foraddr(self, addr, extensions=('.c')):
        for fdr in self.fdrs:
            if fdr.adr == addr and any((fdr.name.endswith(ext) for ext in extensions)):
                return fdr
        return None

    def read_string(self, index):
        to = self.elf_file.data.find(b'\0', self.hdrr.cbSsOffset + index)
        assert to != -1
        return self.elf_file.data[self.hdrr.cbSsOffset + index:to].decode("ASCII")

    def read_ext_string(self, index):
        to = self.elf_file.data.find(b'\0', self.hdrr.cbSsExtOffset + index)
        assert to != -1
        return self.elf_file.data[self.hdrr.cbSsExtOffset + index:to].decode("ASCII")

class ReginfoSection(Section):
    """
    MIPS Register Information Section
    """
    def __init__(self, header, elf_file, index):
        super().__init__(header, elf_file, index)

# =====================================================================================================
# Elf File
# =====================================================================================================

class ElfFile:
    def __init__(self, data):
        def init_section(i):
            offset = self.elf_header.e_shoff + i * self.elf_header.e_shentsize
            section_type = struct.unpack(">I", data[offset + 4:][:4])[0]
            header_data = data[offset:][:self.elf_header.e_shentsize]

            if section_type == SHT_REL or section_type == SHT_RELA:
                return RelocationSection(header_data, self, i)
            elif section_type == SHT_SYMTAB:
                return SymtabSection(header_data, self, i)
            elif section_type == SHT_STRTAB:
                return StrtabSection(header_data, self, i)
            elif section_type == SHT_MIPS_DEBUG:
                return MdebugSection(header_data, self, i)
            elif section_type == SHT_MIPS_REGINFO:
                return ReginfoSection(header_data, self, i)
            else:
                return Section(header_data, self, i)

        self.data = data
        self.elf_header = ElfHeader(data[0:52])

        num_progheaders = self.elf_header.e_phnum
        num_sections = self.elf_header.e_shnum

        # Init program headers
        self.progheaders = []
        for i in range(num_progheaders):
            offset = self.elf_header.e_phoff + i * self.elf_header.e_phentsize
            self.progheaders.append(ProgramHeader(data[offset:][:self.elf_header.e_phentsize], self.elf_header.e_ident[EI_CLASS]))

        # Init sections
        self.sections = []
        for i in range(num_sections):
            self.sections.append(init_section(i))

        # Init shstrtab and name sections
        self.shstrtab = self.sections[self.elf_header.e_shstrndx]
        assert isinstance(self.shstrtab, StrtabSection)

        for s in self.sections:
            s.name = self.shstrtab.lookup_str(s.sh_name)

        # Init symtab
        symtab = None
        for s in self.sections:
            if s.sh_type == SHT_SYMTAB:
                assert not symtab , "Found more than one symtab section?"
                symtab = s
        self.symtab = symtab
        if self.symtab is not None:
            self.symtab.late_init()

        # Late Init sections
        for s in self.sections:
            s.late_init()

    def find_section_by_name(self, name):
        for s in self.sections:
            if s.name == name:
                return s
        return None

    def find_section_by_type(self, type):
        for s in self.sections:
            if s.sh_type == type:
                return s
        return None

### Tests

if __name__ == "__main__":
    import sys

    elf_file = None

    with open(sys.argv[1], "rb") as elf:
        elf_file = ElfFile(bytearray(elf.read()))

    # Header Info Test
    print(elf_file.elf_header)
    # Program Headers Info Test
    print("")
    print("Program Headers:")
    print("  Type      Offset   VirtAddr   PhysAddr   FileSiz MemSiz  Flg Align")
    for phdr in elf_file.progheaders:
        print(phdr)
    # Section Headers Info Test
    print("")
    print("Section Headers:")
    print("  [Nr] Name        Type         Addr     Off    Size   ES Flg Lk Inf    Al")
    for i,s in enumerate(elf_file.sections,0):
        print(f"  [{i:2}] {s}")
    # Symbols Info Test
    if elf_file.symtab is not None:
        print("")
        print(f"Symbol table '{elf_file.symtab.name}' contains {len(elf_file.symtab.symbol_entries)} entries")
        print("   Num:    Value   Size    Type   Bind     Vis   Ndx        Name")
        for i,sym in enumerate(elf_file.symtab.symbol_entries,0):
            print(f"{i:6}: {sym}")
    # Relocations Info Test
    print("")
    for s in elf_file.sections:
        if s.is_rel():
            print(f"\nRelocation section '{s.name}' at offset 0x{s.sh_offset:06X} contains {len(s.relocations)} entries:")
            print(" Offset     Info     Type            Sym.Value  Sym.Name + Addend")
            for reloc in s.relocations:
                print(f"{reloc}")
    # mdebug Info Test
    print("")
    mdebug_section = elf_file.find_section_by_type(SHT_MIPS_DEBUG)
    if mdebug_section is not None:
        """
        for fdr in mdebug_section.fdrs:
            print(fdr)
            for symr in fdr.symrs:
                print(symr)
            for pdr in fdr.pdrs:
                print(pdr)
                for symr in pdr.symrs:
                    print(symr)
                for liner in pdr.lines:
                    print(liner)
        """
        for fdr in mdebug_section.fdrs:
            print(fdr.c_str())
