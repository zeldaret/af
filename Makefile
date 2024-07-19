# Build options can be changed by modifying the makefile or by building with 'make SETTING=value'.
# It is also possible to override the settings in Defaults in a file called .make_options as 'SETTING=value'.

-include .make_options

MAKEFLAGS += --no-builtin-rules

# Ensure the build fails if a piped command fails
SHELL = /bin/bash
.SHELLFLAGS = -o pipefail -c

# OS Detection
ifeq ($(OS),Windows_NT)
$(error Native Windows is currently unsupported for building this repository, use WSL instead c:)
else
  UNAME_S := $(shell uname -s)
  ifeq ($(UNAME_S),Linux)
    DETECTED_OS = linux
    MAKE = make
    AR = ar
    VENV_BIN_DIR = bin
  endif
  ifeq ($(UNAME_S),Darwin)
    DETECTED_OS = macos
    MAKE = gmake
    AR = gar
    VENV_BIN_DIR = bin
  endif
endif

#### Defaults ####
# Target game version. Currently only the following version is supported:
#   jp   N64 Japan (default)
VERSION ?= jp
# If COMPARE is 1, check the output md5sum after building
COMPARE ?= 1
# If NON_MATCHING is 1, define the NON_MATCHING C flag when building
NON_MATCHING ?= 0
# if WERROR is 1, pass -Werror to CC_CHECK, so warnings would be treated as errors
WERROR ?= 0
# Keep .mdebug section in build
KEEP_MDEBUG ?= 0
# Check code syntax with host compiler
RUN_CC_CHECK ?= 1
CC_CHECK_COMP ?= gcc
# Dump build object files
OBJDUMP_BUILD ?= 0
# Number of threads to compress with
N_THREADS ?= $(shell nproc)
# Not meant to be used by normal users. Toggles some options to improve the use of the warning checker system
WARNINGS_CHECK ?= 0
# Disassembles matched functions and migrated data as well
FULL_DISASM ?= 0
# Python virtual environment
VENV ?= .venv
# Python interpreter
PYTHON ?= $(VENV)/$(VENV_BIN_DIR)/python3
# Emulator w/ flags
N64_EMULATOR ?=
# Set prefix to mips binutils binaries (mips-linux-gnu-ld => 'mips-linux-gnu-') - Change at your own risk!
# In nearly all cases, not having 'mips-linux-gnu-*' binaries on the PATH is indicative of missing dependencies
MIPS_BINUTILS_PREFIX ?= mips-linux-gnu-

TARGET  := animalforest

BASEROM_DIR := baseroms/$(VERSION)
BASEROM     := $(BASEROM_DIR)/baserom.z64
BASEROMD    := $(BASEROM_DIR)/baserom-decompressed.z64

ULTRALIB_VERSION     := L
ULTRALIB_TARGET      := libultra_rom

### Output ###

BUILD_DIR := build
ROM       := $(BUILD_DIR)/$(TARGET)-$(VERSION).z64
ROMC      := $(ROM:.z64=-compressed.z64)
ELF       := $(ROM:.z64=.elf)
MAP       := $(ROM:.z64=.map)
LDSCRIPT  := $(ROM:.z64=.ld)


#### Setup ####

BUILD_DEFINES ?=

ifeq ($(VERSION),jp)
  BUILD_DEFINES   += -DVERSION_JP=1
else
ifeq ($(VERSION),cn)
  BUILD_DEFINES   += -DVERSION_CN=1 -DBBPLAYER=1
else
$(error Invalid VERSION variable detected. Please use either 'jp' or 'cn')
endif
endif


ifeq ($(NON_MATCHING),1)
  BUILD_DEFINES   += -DNON_MATCHING -DAVOID_UB
  COMPARE  := 0
endif

MAKE = make
CPPFLAGS += -fno-dollars-in-identifiers -P
LDFLAGS  := --no-check-sections --accept-unknown-input-arch --emit-relocs

ifeq ($(DETECTED_OS), macos)
  CPPFLAGS += -xc++
endif

#### Tools ####
ifneq ($(shell type $(MIPS_BINUTILS_PREFIX)ld >/dev/null 2>/dev/null; echo $$?), 0)
$(error Unable to find $(MIPS_BINUTILS_PREFIX)ld. Please install or build MIPS binutils, commonly mips-linux-gnu. (or set MIPS_BINUTILS_PREFIX if your MIPS binutils install uses another prefix))
endif


CC              := tools/ido/$(DETECTED_OS)/7.1/cc
CC_OLD          := tools/ido/$(DETECTED_OS)/5.3/cc

AS              := $(MIPS_BINUTILS_PREFIX)as
LD              := $(MIPS_BINUTILS_PREFIX)ld
OBJCOPY         := $(MIPS_BINUTILS_PREFIX)objcopy
OBJDUMP         := $(MIPS_BINUTILS_PREFIX)objdump
NM              := $(MIPS_BINUTILS_PREFIX)nm

CPP             := cpp
ICONV           := iconv
CAT             := cat

ASM_PROC        := $(PYTHON) tools/asm-processor/build.py
ASM_PROC_FLAGS  := --input-enc=utf-8 --output-enc=euc-jp --convert-statics=global-with-filename

SPLAT           := $(PYTHON) -m splat split
SPLAT_YAML      := $(TARGET)-$(VERSION).yaml

PIGMENT         := tools/pigment64/pigment64


IINC := -Iinclude -Isrc -Iassets/$(VERSION) -I. -I$(BUILD_DIR)
IINC += -Ilib/ultralib/include -Ilib/ultralib/include/PR -Ilib/ultralib/include/ido

ifeq ($(KEEP_MDEBUG),0)
  RM_MDEBUG = $(OBJCOPY) --remove-section .mdebug $@
else
  RM_MDEBUG = @:
endif

# Check code syntax with host compiler
CHECK_WARNINGS := -Wall -Wextra -Wimplicit-fallthrough -Wno-unknown-pragmas -Wno-missing-braces -Wno-sign-compare -Wno-uninitialized -Wno-unused-label -Wno-type-limits
# Have CC_CHECK pretend to be a MIPS compiler
MIPS_BUILTIN_DEFS := -DMIPSEB -D_MIPS_FPSET=16 -D_MIPS_ISA=2 -D_ABIO32=1 -D_MIPS_SIM=_ABIO32 -D_MIPS_SZINT=32 -D_MIPS_SZPTR=32
ifneq ($(RUN_CC_CHECK),0)
#   The -MMD flags additionaly creates a .d file with the same name as the .o file.
  CC_CHECK          := $(CC_CHECK_COMP)
  CC_CHECK_FLAGS    := -MMD -MP -fno-builtin -fsyntax-only -funsigned-char -fdiagnostics-color -std=gnu89 -m32 -DNON_MATCHING -DAVOID_UB -DCC_CHECK=1
  ifneq ($(WERROR), 0)
    CHECK_WARNINGS  += -Werror
  endif
else
  CC_CHECK          := @:
endif


CFLAGS          += -G 0 -non_shared -Xcpluscomm -nostdinc -Wab,-r4300_mul

WARNINGS         := -fullwarn -verbose -woff 624,649,838,712,516,513,596,564,594
ASFLAGS          := -march=vr4300 -32 -G0
GBI_DEFINES      := -DF3DEX_GBI_2
RELEASE_DEFINES  := -DNDEBUG -D_FINALROM
LIBULTRA_DEFINES := -DBUILD_VERSION=VERSION_$(ULTRALIB_VERSION)
COMMON_DEFINES   := -D_MIPS_SZLONG=32 $(GBI_DEFINES) $(RELEASE_DEFINES) $(LIBULTRA_DEFINES)
C_DEFINES        := -DLANGUAGE_C -D_LANGUAGE_C $(COMMON_DEFINES)
AS_DEFINES       := -DMIPSEB -D_LANGUAGE_ASSEMBLY -D_ULTRA64 $(COMMON_DEFINES)
ENDIAN           := -EB

OPTFLAGS        := -O2 -g3
MIPS_VERSION    := -mips2
ICONV_FLAGS     := --from-code=UTF-8 --to-code=EUC-JP

# Use relocations and abi fpr names in the dump
OBJDUMP_FLAGS := --disassemble --reloc --disassemble-zeroes -Mreg-names=32 -Mno-aliases

ifneq ($(OBJDUMP_BUILD), 0)
  OBJDUMP_CMD = $(OBJDUMP) $(OBJDUMP_FLAGS) $@ > $(@:.o=.s)
  OBJCOPY_BIN = $(OBJCOPY) -O binary $@ $@.bin
  LIBDUMP_CMD = $(AR) xo --output $(@D) $@
else
  OBJDUMP_CMD = @:
  OBJCOPY_BIN = @:
  LIBDUMP_CMD = @:
endif

SPLAT_FLAGS ?=
ifneq ($(WARNINGS_CHECK), 0)
  SPLAT_FLAGS += --stdout-only
endif

ifneq ($(FULL_DISASM), 0)
  SPLAT_FLAGS += --disassemble-all
endif

#### Files ####

$(shell mkdir -p asm/$(VERSION) assets/$(VERSION) linker_scripts/$(VERSION)/auto)

ULTRALIB_DIR  := lib/ultralib
ULTRALIB_LIB  := $(ULTRALIB_DIR)/build/$(ULTRALIB_VERSION)/$(ULTRALIB_TARGET)/$(ULTRALIB_TARGET).a
LIBULTRA_DIR  := lib/libultra
LIBULTRA_LIB  := $(BUILD_DIR)/$(LIBULTRA_DIR)/libultra.a

SRC_DIRS      := $(shell find src -type d)
ASM_DIRS      := $(shell find asm/$(VERSION) -type d -not -path "asm/$(VERSION)/nonmatchings/*" -not -path "asm/$(VERSION)/lib/*")
ASSET_DIRS    := $(shell find assets/$(VERSION) -type d)
LIB_DIRS      := $(foreach f,$(LIBULTRA_DIR),$f)

C_FILES       := $(foreach dir,$(SRC_DIRS),$(wildcard $(dir)/*.c))
S_FILES       := $(foreach dir,$(ASM_DIRS) $(SRC_DIRS),$(wildcard $(dir)/*.s))
BIN_FILES     := $(foreach dir,$(ASSET_DIRS),$(wildcard $(dir)/*.bin))
O_FILES       := $(foreach f,$(C_FILES:.c=.o),$(BUILD_DIR)/$f) \
                 $(foreach f,$(S_FILES:.s=.o),$(BUILD_DIR)/$f) \
                 $(foreach f,$(BIN_FILES:.bin=.o),$(BUILD_DIR)/$f)

ASSET_PNGS := $(foreach dir,$(ASSET_DIRS),$(wildcard $(dir)/*.png))
ASSET_BINS := $(foreach f,$(ASSET_PNGS:.png=.bin),$(BUILD_DIR)/$f)
ASSET_INC_C := $(foreach f,$(ASSET_PNGS:.png=.inc.c),$(BUILD_DIR)/$f)


# Automatic dependency files
DEP_FILES := $(O_FILES:.o=.d) \
             $(O_FILES:.o=.asmproc.d)

# create build directories
$(shell mkdir -p $(BUILD_DIR)/linker_scripts/$(VERSION) $(BUILD_DIR)/linker_scripts/$(VERSION)/auto $(foreach dir,$(SRC_DIRS) $(ASM_DIRS) $(ASSET_DIRS) $(LIB_DIRS),$(BUILD_DIR)/$(dir)))


# directory flags
build/src/boot/O2/%.o: OPTFLAGS := -O2
build/src/boot/libc/%.o: OPTFLAGS := -O2
build/src/boot/libc64/%.o: OPTFLAGS := -O2
build/src/boot/libm/%.o: OPTFLAGS := -O2
build/src/boot/libu64/%.o: OPTFLAGS := -O2

# per-file flags

build/src/boot/fault.o: CFLAGS += -trapuv
build/src/boot/fault_drawer.o: CFLAGS += -trapuv

build/src/code/lbrtc/%.o: CC = $(CC_OLD)
build/src/code/lbrtc/%.o: OPTFLAGS = -O1 -g1


# cc & asm-processor
build/src/%.o: CC := $(ASM_PROC) $(ASM_PROC_FLAGS) $(CC) -- $(AS) $(ASFLAGS) --


#### Main Targets ###

all: rom compress

rom: $(ROM)
ifneq ($(COMPARE),0)
	@md5sum $(ROM)
	@md5sum -c $(BASEROM_DIR)/checksum.md5
endif

compress: $(ROMC)
ifneq ($(COMPARE),0)
	@md5sum $(ROMC)
	@md5sum -c $(BASEROM_DIR)/checksum-compressed.md5
endif

clean:
	$(RM) -r $(BUILD_DIR)

libclean:
	$(MAKE) -C lib/ultralib clean VERSION=$(ULTRALIB_VERSION) TARGET=$(ULTRALIB_TARGET)

distclean: clean libclean
	$(RM) -r $(BUILD_DIR) asm/ assets/ .splat/
	$(RM) -r linker_scripts/$(VERSION)/auto $(LDSCRIPT)
	$(MAKE) -C tools distclean

venv:
	test -d $(VENV) || python3 -m venv $(VENV)
	$(PYTHON) -m pip install -U pip
	$(PYTHON) -m pip install -U -r requirements.txt

setup:
	$(MAKE) -C tools WARNINGS_CHECK=$(WARNINGS_CHECK)
	$(PYTHON) tools/decompress_baserom.py $(VERSION)

extract:
	$(RM) -r asm/$(VERSION) assets/$(VERSION)
	$(CAT) yamls/$(VERSION)/header.yaml yamls/$(VERSION)/makerom.yaml yamls/$(VERSION)/boot.yaml yamls/$(VERSION)/code.yaml yamls/$(VERSION)/overlays.yaml yamls/$(VERSION)/assets.yaml > $(SPLAT_YAML)
	$(SPLAT) $(SPLAT_FLAGS) $(SPLAT_YAML)

lib: $(ULTRALIB_LIB)

diff-init: rom
	$(RM) -r expected/
	mkdir -p expected/
	cp -r $(BUILD_DIR) expected/$(BUILD_DIR)

init: distclean
	$(MAKE) venv
	$(MAKE) setup
	$(MAKE) extract
	$(MAKE) all
	$(MAKE) diff-init

run: $(ROM)
ifeq ($(N64_EMULATOR),)
	$(error Emulator path not set. Set N64_EMULATOR in the Makefile, .make_options, or define it as an environment variable)
endif
	$(N64_EMULATOR) $<

.PHONY: all rom compress clean libclean distclean venv setup extract lib diff-init init run
.DEFAULT_GOAL := rom
# Prevent removing intermediate files
.SECONDARY:


#### Various Recipes ####

$(ROM): $(ELF)
	$(OBJCOPY) -O binary --pad-to=0x1914000 --gap-fill=0x00 $< $@
# TODO: update rom header checksum

$(ROMC): $(ROM) $(ELF) $(BUILD_DIR)/compress_ranges.txt
	$(PYTHON) tools/compress.py --in $(ROM) --out $@ --dma-start `tools/dmadata_start.sh $(NM) $(ELF)` --compress `cat $(BUILD_DIR)/compress_ranges.txt` --threads $(N_THREADS)
	$(PYTHON) -m ipl3checksum sum --cic 6102 --update $@

$(BUILD_DIR)/compress_ranges.txt:
	$(PYTHON) tools/compress_ranges.py $(SPLAT_YAML) -o $@

# TODO: avoid using auto/undefined
$(ELF): $(O_FILES) $(LIBULTRA_LIB) $(LDSCRIPT) $(BUILD_DIR)/linker_scripts/$(VERSION)/hardware_regs.ld $(BUILD_DIR)/linker_scripts/$(VERSION)/undefined_syms.ld $(BUILD_DIR)/linker_scripts/$(VERSION)/unused_syms.ld $(BUILD_DIR)/linker_scripts/common_undef_syms.ld $(BUILD_DIR)/linker_scripts/$(VERSION)/auto/undefined_syms_auto.ld $(BUILD_DIR)/linker_scripts/$(VERSION)/auto/undefined_funcs_auto.ld
	$(LD) $(LDFLAGS) -T $(LDSCRIPT) \
		-T $(BUILD_DIR)/linker_scripts/$(VERSION)/hardware_regs.ld -T $(BUILD_DIR)/linker_scripts/$(VERSION)/undefined_syms.ld \
		-T $(BUILD_DIR)/linker_scripts/$(VERSION)/unused_syms.ld -T $(BUILD_DIR)/linker_scripts/common_undef_syms.ld \
		-T $(BUILD_DIR)/linker_scripts/$(VERSION)/auto/undefined_syms_auto.ld -T $(BUILD_DIR)/linker_scripts/$(VERSION)/auto/undefined_funcs_auto.ld \
		-Map $(MAP) $(LIBULTRA_LIB) -o $@

$(LDSCRIPT): linker_scripts/$(VERSION)/$(TARGET).ld
	cp $< $@

$(BUILD_DIR)/%.ld: %.ld
	$(CPP) $(CPPFLAGS) $(BUILD_DEFINES) $(IINC) $< > $@

$(LIBULTRA_LIB): $(ULTRALIB_LIB)
	cp $< $@
	$(LIBDUMP_CMD)

$(ULTRALIB_LIB):
	$(MAKE) -C lib/ultralib VERSION=$(ULTRALIB_VERSION) TARGET=$(ULTRALIB_TARGET) FIXUPS=1 CROSS=$(MIPS_BINUTILS_PREFIX) CC=../../$(CC_OLD) AR=$(AR)

$(BUILD_DIR)/%.o: %.bin
	$(OBJCOPY) -I binary -O elf32-big $< $@

$(BUILD_DIR)/%.o: %.s
	$(ICONV) $(ICONV_FLAGS) $< | $(AS) $(ASFLAGS) $(ENDIAN) $(IINC) -I $(dir $*) -o $@
	$(OBJDUMP_CMD)

$(BUILD_DIR)/%.o: %.c
	$(CC_CHECK) $(CC_CHECK_FLAGS) $(BUILD_DEFINES) $(IINC) -I $(dir $*) $(CHECK_WARNINGS) $(C_DEFINES) $(MIPS_BUILTIN_DEFS) -o $@ $<
	$(CC) -c $(CFLAGS) $(BUILD_DEFINES) $(IINC) $(WARNINGS) $(MIPS_VERSION) $(ENDIAN) $(C_DEFINES) $(OPTFLAGS) -o $@ $<
	$(OBJDUMP_CMD)
	$(RM_MDEBUG)

# Build C files from assets
$(BUILD_DIR)/%.inc.c: %.png
# File names are formatted as <file name>.<image format>.png
# The <image format> part is passed into pigment's format argument
	$(PIGMENT) to-bin -f $(subst .,,$(suffix $*)) --c-array -o $@ $<

# Add these as a dependency for .o files
asset_files: $(ASSET_INC_C)
$(O_FILES): | asset_files
.PHONY: asset_files

-include $(DEP_FILES)

# Print target for debugging
print-% : ; $(info $* is a $(flavor $*) variable set to [$($*)]) @true
