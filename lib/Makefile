MAKEFLAGS += --no-builtin-rules


# Set prefix to mips binutils binaries (mips-linux-gnu-ld => 'mips-linux-gnu-') - Change at your own risk!
# In nearly all cases, not having 'mips-linux-gnu-*' binaries on the PATH is indicative of missing dependencies
MIPS_BINUTILS_PREFIX ?= mips-linux-gnu-

### Output ###

BUILD_DIR := ../build/lib


#### Setup ####

MAKE = make

UNAME_S := $(shell uname -s)
ifeq ($(OS),Windows_NT)
$(error Native Windows is currently unsupported for building this repository, use WSL instead c:)
else ifeq ($(UNAME_S),Linux)
	DETECTED_OS := linux
else ifeq ($(UNAME_S),Darwin)
	DETECTED_OS := macos
	MAKE := gmake
endif

#### Tools ####
ifneq ($(shell type $(MIPS_BINUTILS_PREFIX)ld >/dev/null 2>/dev/null; echo $$?), 0)
	$(error Please install or build $(MIPS_BINUTILS_PREFIX))
endif

export COMPILER_PATH := ../tools/ido/$(DETECTED_OS)/5.3
CC         := ../tools/ido/$(DETECTED_OS)/5.3/cc


IINC       := -Iultralib/include -Iultralib/include/ido -Iultralib/include/PR -Iultralib/src

OPTFLAGS        := -O2
ASOPTFLAGS      := -O1
MIPS_VERSION    := -mips2 -non_shared -32
CFLAGS          := -Wab,-r4300_mul -G 0 -nostdinc -Xcpluscomm -fullwarn
ASFLAGS         := -Wab,-r4300_mul -G 0 -nostdinc
WARNINGS        := -woff 516,649,838,712
COMMON_DEFINES  := -D_MIPS_SZLONG=32
GBI_DEFINES     := -DF3DEX_GBI_2
RELEASE_DEFINES := -DNDEBUG -D_FINALROM

#### Files ####

SRC_DIRS      := $(shell find ultralib/src -type d \
					-not -path "ultralib/src/audio" \
					-not -path "ultralib/src/error" \
					-not -path "ultralib/src/gio" \
					-not -path "ultralib/src/gt" \
					-not -path "ultralib/src/host" \
					-not -path "ultralib/src/log" \
					-not -path "ultralib/src/rg" \
					-not -path "ultralib/src/rmon" \
					-not -path "ultralib/src/sched" \
					-not -path "ultralib/src/voice")

C_FILES       := $(foreach dir,$(SRC_DIRS),$(wildcard $(dir)/*.c))
S_FILES       := $(foreach dir,$(SRC_DIRS),$(wildcard $(dir)/*.s))
O_FILES       := $(foreach f,$(C_FILES:.c=.o),$(BUILD_DIR)/$f) \
                 $(foreach f,$(S_FILES:.s=.o),$(BUILD_DIR)/$f)

# create build directories
$(shell mkdir -p $(foreach dir,$(SRC_DIRS),$(BUILD_DIR)/$(dir)))

$(BUILD_DIR)/ultralib/src/debug/%.o: OPTFLAGS := -O1
$(BUILD_DIR)/ultralib/src/host/%.o: OPTFLAGS := -O1
$(BUILD_DIR)/ultralib/src/os/%.o: OPTFLAGS := -O1
$(BUILD_DIR)/ultralib/src/rmon/%.o: OPTFLAGS := -O1
$(BUILD_DIR)/ultralib/src/libc/ll.o: OPTFLAGS := -O1
$(BUILD_DIR)/ultralib/src/libc/llbit.o: OPTFLAGS := -O1
$(BUILD_DIR)/ultralib/src/libc/llcvt.o: OPTFLAGS := -O1
$(BUILD_DIR)/ultralib/src/log/%.o: OPTFLAGS := -O1

$(BUILD_DIR)/ultralib/src/libc/%.o: ASOPTFLAGS := -O2
$(BUILD_DIR)/ultralib/src/mgu/%.o: ASOPTFLAGS := -O2

$(BUILD_DIR)/ultralib/src/libc/ll.o: MIPS_VERSION := -mips3 -32 -non_shared
$(BUILD_DIR)/ultralib/src/libc/llbit.o: MIPS_VERSION := -mips3 -32 -non_shared
$(BUILD_DIR)/ultralib/src/libc/llcvt.o: MIPS_VERSION := -mips3 -32 -non_shared
$(BUILD_DIR)/ultralib/src/os/exceptasm.o: MIPS_VERSION := -mips3 -32 -non_shared


#### Main Targets ###

all: $(O_FILES)

clean:
	$(RM) -r $(BUILD_DIR)

distclean: clean

.PHONY: all clean distclean
.DEFAULT_GOAL := all
# Prevent removing intermediate files
.SECONDARY:

$(BUILD_DIR)/%.o: %.s
	$(CC) -c $(ASFLAGS) $(IINC) -I $(dir $*) $(WARNINGS) $(MIPS_VERSION) $(COMMON_DEFINES) $(RELEASE_DEFINES) $(GBI_DEFINES) $(ASOPTFLAGS) -o $@ $<
	$(MIPS_BINUTILS_PREFIX)objcopy --remove-section .mdebug $(@:.marker=.o)

$(BUILD_DIR)/%.o: %.c
	$(CC) -c $(CFLAGS) $(IINC) -I $(dir $*) $(WARNINGS) $(MIPS_VERSION) $(COMMON_DEFINES) $(RELEASE_DEFINES) $(GBI_DEFINES) $(OPTFLAGS) -o $@ $<
	$(MIPS_BINUTILS_PREFIX)objcopy --remove-section .mdebug $(@:.marker=.o)

$(BUILD_DIR)/ultralib/src/libc/ll.o: ultralib/src/libc/ll.c
	$(CC) -c $(CFLAGS) $(IINC) -I $(dir $*) $(WARNINGS) $(MIPS_VERSION) $(COMMON_DEFINES) $(RELEASE_DEFINES) $(GBI_DEFINES) $(OPTFLAGS) -o $@ $<
	python3 ../tools/set_o32abi_bit.py $@
	$(MIPS_BINUTILS_PREFIX)objcopy --remove-section .mdebug $(@:.marker=.o)

$(BUILD_DIR)/ultralib/src/libc/llbit.o: ultralib/src/libc/llbit.c
	$(CC) -c $(CFLAGS) $(IINC) -I $(dir $*) $(WARNINGS) $(MIPS_VERSION) $(COMMON_DEFINES) $(RELEASE_DEFINES) $(GBI_DEFINES) $(OPTFLAGS) -o $@ $<
	python3 ../tools/set_o32abi_bit.py $@
	$(MIPS_BINUTILS_PREFIX)objcopy --remove-section .mdebug $(@:.marker=.o)

$(BUILD_DIR)/ultralib/src/libc/llcvt.o: ultralib/src/libc/llcvt.c
	$(CC) -c $(CFLAGS) $(IINC) -I $(dir $*) $(WARNINGS) $(MIPS_VERSION) $(COMMON_DEFINES) $(RELEASE_DEFINES) $(GBI_DEFINES) $(OPTFLAGS) -o $@ $<
	python3 ../tools/set_o32abi_bit.py $@
	$(MIPS_BINUTILS_PREFIX)objcopy --remove-section .mdebug $(@:.marker=.o)

$(BUILD_DIR)/ultralib/src/os/exceptasm.o: ultralib/src/os/exceptasm.s
	$(CC) -c $(ASFLAGS) $(IINC) -I $(dir $*) $(WARNINGS) $(MIPS_VERSION) $(COMMON_DEFINES) $(RELEASE_DEFINES) $(GBI_DEFINES) $(ASOPTFLAGS) -o $@ $<
	python3 ../tools/set_o32abi_bit.py $@
	$(MIPS_BINUTILS_PREFIX)objcopy --remove-section .mdebug $(@:.marker=.o)

# Print target for debugging
print-% : ; $(info $* is a $(flavor $*) variable set to [$($*)]) @true
