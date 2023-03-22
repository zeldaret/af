# Build options can be changed by modifying the makefile or by building with 'make SETTING=value'.
# It is also possible to override the settings in Defaults in a file called .make_options as 'SETTING=value'.

-include .make_options

MAKEFLAGS += --no-builtin-rules

#### Defaults ####

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
CC_CHECK_COMP ?= clang
# Dump build object files
OBJDUMP_BUILD ?= 1

# Set prefix to mips binutils binaries (mips-linux-gnu-ld => 'mips-linux-gnu-') - Change at your own risk!
# In nearly all cases, not having 'mips-linux-gnu-*' binaries on the PATH is indicative of missing dependencies
MIPS_BINUTILS_PREFIX ?= mips-linux-gnu-


VERSION ?= jp

BASEROM              := baserom.$(VERSION).z64
BASEROM_UNCOMPRESSED := baserom_uncompressed.$(VERSION).z64
TARGET               := animalforest


### Output ###

BUILD_DIR := build
ROM       := $(BUILD_DIR)/$(TARGET)_uncompressed.$(VERSION).z64
ELF       := $(BUILD_DIR)/$(TARGET).$(VERSION).elf
LD_MAP    := $(BUILD_DIR)/$(TARGET).$(VERSION).map
LD_SCRIPT := linker_scripts/$(VERSION)/$(TARGET).ld
ROMC      := $(BUILD_DIR)/$(TARGET).$(VERSION).z64


#### Setup ####

BUILD_DEFINES ?=

ifeq ($(VERSION),jp)
	BUILD_DEFINES   += -DVERSION_US=1
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

UNAME_S := $(shell uname -s)
ifeq ($(OS),Windows_NT)
	DETECTED_OS := windows
else ifeq ($(UNAME_S),Linux)
	DETECTED_OS := linux
else ifeq ($(UNAME_S),Darwin)
	DETECTED_OS := mac
	MAKE := gmake
	CPPFLAGS += -xc++
endif

#### Tools ####
ifneq ($(shell type $(MIPS_BINUTILS_PREFIX)ld >/dev/null 2>/dev/null; echo $$?), 0)
$(error Please install or build $(MIPS_BINUTILS_PREFIX))
endif

# TODO
CC              :=

AS              := $(MIPS_BINUTILS_PREFIX)as
LD              := $(MIPS_BINUTILS_PREFIX)ld
OBJCOPY         := $(MIPS_BINUTILS_PREFIX)objcopy
OBJDUMP         := $(MIPS_BINUTILS_PREFIX)objdump
GCC             := $(MIPS_BINUTILS_PREFIX)gcc
CPP             := $(MIPS_BINUTILS_PREFIX)cpp
STRIP           := $(MIPS_BINUTILS_PREFIX)strip
ICONV           := iconv

SPLAT           ?= tools/splat/split.py
SPLAT_YAML      ?= $(TARGET).$(VERSION).yaml



IINC       := -Iinclude -Ibin/$(VERSION) -I.

# Check code syntax with host compiler
CHECK_WARNINGS := -Wall -Wextra -Wimplicit-fallthrough -Wno-unknown-pragmas -Wno-missing-braces -Wno-sign-compare -Wno-uninitialized
# Have CC_CHECK pretend to be a MIPS compiler
MIPS_BUILTIN_DEFS := -D_MIPS_ISA_MIPS2=2 -D_MIPS_ISA=_MIPS_ISA_MIPS2 -D_ABIO32=1 -D_MIPS_SIM=_ABIO32 -D_MIPS_SZINT=32 -D_MIPS_SZPTR=32
ifneq ($(RUN_CC_CHECK),0)
#	The -MMD flags additionaly creates a .d file with the same name as the .o file.
	CC_CHECK          := $(CC_CHECK_COMP)
	CC_CHECK_FLAGS    := -MMD -MP -fno-builtin -fsyntax-only -funsigned-char -fdiagnostics-color -std=gnu89 -m32 -DNON_MATCHING -DAVOID_UB -DCC_CHECK=1
	ifneq ($(WERROR), 0)
		CHECK_WARNINGS += -Werror
	endif
else
	CC_CHECK          := @:
endif


CFLAGS          += -nostdinc -fno-PIC -G 0 -mgp32 -mfp32 -fno-common -funsigned-char

WARNINGS        := -w
ASFLAGS         := -march=vr4300 -32 -G0
COMMON_DEFINES  := -D_MIPS_SZLONG=32 -D__USE_ISOC99
GBI_DEFINES     := -DF3DEX_GBI_2
RELEASE_DEFINES := -DNDEBUG -D_FINALROM
AS_DEFINES      := -DMIPSEB -D_LANGUAGE_ASSEMBLY -D_ULTRA64
C_DEFINES       := -D_LANGUAGE_C
ENDIAN          := -EB

ifeq ($(VERSION),jp)
OPTFLAGS        := -O2
# OPTFLAGS        +=
MIPS_VERSION    := -mips3
ICONV_FLAGS     := --from-code=UTF-8 --to-code=Shift-JIS
endif
ifeq ($(VERSION),cn)
CFLAGS          += -mcpu=4300
OPTFLAGS        := -O2 -ggdb
MIPS_VERSION    := -mips2
ICONV_FLAGS     := --from-code=UTF-8 --to-code=EUC-CN
endif

# Variable to simplify C compiler invocation
C_COMPILER_FLAGS = $(CFLAGS) $(BUILD_DEFINES) $(IINC) $(WARNINGS) $(MIPS_VERSION) $(ENDIAN) $(COMMON_DEFINES) $(RELEASE_DEFINES) $(GBI_DEFINES) $(C_DEFINES) $(OPTFLAGS)

# Use relocations and abi fpr names in the dump
OBJDUMP_FLAGS := --disassemble --reloc --disassemble-zeroes -Mreg-names=32 -Mno-aliases

ifneq ($(OBJDUMP_BUILD), 0)
	OBJDUMP_CMD = $(OBJDUMP) $(OBJDUMP_FLAGS) $@ > $(@:.o=.dump.s)
	OBJCOPY_BIN = $(OBJCOPY) -O binary $@ $@.bin
else
	OBJDUMP_CMD = @:
	OBJCOPY_BIN = @:
endif


#### Files ####

$(shell mkdir -p asm bin linker_scripts/$(VERSION)/auto)

SRC_DIRS      := $(shell find src -type d)
ASM_DIRS      := $(shell find asm/$(VERSION) -type d -not -path "asm/$(VERSION)/nonmatchings/*")
BIN_DIRS      := $(shell find bin -type d)

C_FILES       := $(foreach dir,$(SRC_DIRS),$(wildcard $(dir)/*.c))
S_FILES       := $(foreach dir,$(ASM_DIRS) $(SRC_DIRS),$(wildcard $(dir)/*.s))
BIN_FILES     := $(foreach dir,$(BIN_DIRS),$(wildcard $(dir)/*.bin))
O_FILES       := $(foreach f,$(C_FILES:.c=.o),$(BUILD_DIR)/$f) \
                 $(foreach f,$(S_FILES:.s=.o),$(BUILD_DIR)/$f) \
                 $(foreach f,$(BIN_FILES:.bin=.o),$(BUILD_DIR)/$f)


# Automatic dependency files
DEP_FILES := $(O_FILES:.o=.d) \
             $(O_FILES:.o=.asmproc.d)

# create build directories
$(shell mkdir -p $(BUILD_DIR)/linker_scripts/$(VERSION) $(BUILD_DIR)/linker_scripts/$(VERSION)/auto $(foreach dir,$(SRC_DIRS) $(ASM_DIRS) $(BIN_DIRS) $(LIBULTRA_DIRS) $(LIBMUS_DIRS),$(BUILD_DIR)/$(dir)))


# directory flags

# per-file flags


#### Main Targets ###

all: uncompressed

uncompressed: $(ROM)
ifneq ($(COMPARE),0)
	@md5sum $(ROM)
	@md5sum -c $(TARGET)_uncompressed.$(VERSION).md5
endif

# TODO
# compressed: $(ROMC)
# ifneq ($(COMPARE),0)
# 	@md5sum $(ROMC)
# 	@md5sum -c $(TARGET).$(VERSION).md5
# endif

clean:
	$(RM) -r $(BUILD_DIR)/asm $(BUILD_DIR)/bin $(BUILD_DIR)/src $(ROM) $(ROMC) $(ELF)

libclean:
	$(RM) -r $(BUILD_DIR)/lib

distclean: clean
	$(RM) -r $(BUILD_DIR) asm/ bin/ .splat/
	$(RM) -r linker_scripts/$(VERSION)/auto $(LD_SCRIPT)
	$(MAKE) -C tools distclean

setup:
	$(MAKE) -C tools
	python3 tools/decompress_baserom.py

extract:
	$(RM) -r asm/$(VERSION) bin/$(VERSION)
	$(SPLAT) $(SPLAT_YAML)

diff-init: all
	$(RM) -rf expected/
	mkdir -p expected/
	cp -r $(BUILD_DIR) expected/$(BUILD_DIR)

init:
	$(MAKE) distclean
	$(MAKE) setup
	$(MAKE) extract
	$(MAKE) all
	$(MAKE) diff-init

format:
	clang-format-11 -i -style=file $(C_FILES)

tidy:
	clang-tidy-11 -p . --fix --fix-errors $(C_FILES) -- $(CC_CHECK_FLAGS) $(IINC) $(CHECK_WARNINGS) $(BUILD_DEFINES) $(COMMON_DEFINES) $(RELEASE_DEFINES) $(GBI_DEFINES) $(C_DEFINES) $(MIPS_BUILTIN_DEFS)

.PHONY: all compressed uncompressed clean distclean setup extract diff-init init format tidy
.DEFAULT_GOAL := all
# Prevent removing intermediate files
.SECONDARY:


#### Various Recipes ####

$(ROM): $(ELF)
	$(OBJCOPY) -O binary --pad-to=0x1914000 --gap-fill=0xFF $< $@

# TODO: avoid using auto/undefined
$(ELF): $(O_FILES) $(LIBULTRA_O) $(LD_SCRIPT) $(BUILD_DIR)/linker_scripts/$(VERSION)/hardware_regs.ld $(BUILD_DIR)/linker_scripts/$(VERSION)/undefined_syms.ld $(BUILD_DIR)/linker_scripts/common_undef_syms.ld $(BUILD_DIR)/linker_scripts/libultra_syms.ld $(BUILD_DIR)/linker_scripts/$(VERSION)/auto/undefined_syms_auto.ld $(BUILD_DIR)/linker_scripts/$(VERSION)/auto/undefined_funcs_auto.ld
	$(LD) $(LDFLAGS) -T $(LD_SCRIPT) \
		-T $(BUILD_DIR)/linker_scripts/$(VERSION)/hardware_regs.ld -T $(BUILD_DIR)/linker_scripts/$(VERSION)/undefined_syms.ld -T $(BUILD_DIR)/linker_scripts/common_undef_syms.ld -T $(BUILD_DIR)/linker_scripts/libultra_syms.ld \
		-T $(BUILD_DIR)/linker_scripts/$(VERSION)/auto/undefined_syms_auto.ld -T $(BUILD_DIR)/linker_scripts/$(VERSION)/auto/undefined_funcs_auto.ld \
		-Map $(LD_MAP) -o $@


$(BUILD_DIR)/%.ld: %.ld
	$(CPP) $(CPPFLAGS) $(BUILD_DEFINES) $(IINC) $< > $@

$(BUILD_DIR)/%.o: %.bin
	$(OBJCOPY) -I binary -O elf32-big $< $@

$(BUILD_DIR)/%.o: %.s
	$(CPP) $(CPPFLAGS) $(BUILD_DEFINES) $(IINC) -I $(dir $*) $(COMMON_DEFINES) $(RELEASE_DEFINES) $(GBI_DEFINES) $(AS_DEFINES) $< | $(ICONV) $(ICONV_FLAGS) | $(AS) $(ASFLAGS) $(ENDIAN) $(IINC) -I $(dir $*) -o $@
	$(OBJDUMP_CMD)

$(BUILD_DIR)/%.o: %.c
	$(CC_CHECK) $(CC_CHECK_FLAGS) $(IINC) -I $(dir $*) $(CHECK_WARNINGS) $(BUILD_DEFINES) $(COMMON_DEFINES) $(RELEASE_DEFINES) $(GBI_DEFINES) $(C_DEFINES) $(MIPS_BUILTIN_DEFS) -o $@ $<
	$(CC) $(C_COMPILER_FLAGS) -I $(dir $*) -E $< | $(ICONV) $(ICONV_FLAGS) | $(CC) -x c $(C_COMPILER_FLAGS) -I $(dir $*) -c -o $@ -
	$(OBJDUMP_CMD)
	$(RM_MDEBUG)

-include $(DEP_FILES)

# Print target for debugging
print-% : ; $(info $* is a $(flavor $*) variable set to [$($*)]) @true
