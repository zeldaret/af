COMPARE ?= 1
MODERN_LD ?= 0
MODERN_GCC ?= 0

ifneq ($(MODERN_LD),0)
COMPARE := 0
endif

# One of:
# libgultra_rom, libgultra_d, libgultra
# libultra_rom, libultra_d, libultra
TARGET ?= libgultra_rom
VERSION ?= L
CROSS ?= mips-linux-gnu-

ifeq ($(findstring libgultra,$(TARGET)),libgultra)
COMPILER := gcc
else ifeq ($(findstring libultra,$(TARGET)),libultra)
COMPILER := ido
else
$(error Invalid Target)
endif

ifneq ($(MODERN_GCC),0)
COMPILER := modern_gcc
COMPARE := 0
MODERN_LD := 0
endif

BASE_DIR := extracted/$(VERSION)/$(TARGET)
BASE_AR := base/$(VERSION)/$(TARGET).a
BUILD_ROOT := build
BUILD_DIR := $(BUILD_ROOT)/$(VERSION)/$(TARGET)
BUILD_AR := $(BUILD_DIR)/$(TARGET).a

WORKING_DIR := $(shell pwd)

CPP := cpp -P
AR := $(CROSS)ar

VERSION_DEFINE := -DBUILD_VERSION=VERSION_$(VERSION) -DBUILD_VERSION_STRING=\"2.0$(VERSION)\"

ifeq ($(findstring _d,$(TARGET)),_d)
DEBUGFLAG := -D_DEBUG
else
DEBUGFLAG := -DNDEBUG
endif

ifeq ($(COMPILER),gcc)
-include makefiles/gcc.mk
else ifeq ($(COMPILER),ido)
-include makefiles/ido.mk
else ifeq ($(COMPILER),modern_gcc)
-include makefiles/modern_gcc.mk
else
$(error Invalid Compiler)
endif

export COMPILER_PATH := $(COMPILER_DIR)

ifeq ($(findstring _rom,$(TARGET)),_rom)
CPPFLAGS += -D_FINALROM
endif

SRC_DIRS := $(shell find src -type d)
C_FILES  := $(foreach dir,$(SRC_DIRS),$(wildcard $(dir)/*.c))
S_FILES  := $(foreach dir,$(SRC_DIRS),$(wildcard $(dir)/*.s))

# Versions J and below used the C matrix math implementations
MGU_MATRIX_FILES := mtxcatf normalize scale translate
ifneq ($(filter $(VERSION),D E F G H I J),)
S_FILES := $(filter-out $(addprefix src/mgu/,$(MGU_MATRIX_FILES:=.s)),$(S_FILES))
else
C_FILES := $(filter-out $(addprefix src/gu/,$(MGU_MATRIX_FILES:=.c)),$(C_FILES))
endif

C_O_FILES := $(foreach f,$(C_FILES:.c=.o),$(BUILD_DIR)/$f)
S_O_FILES := $(foreach f,$(S_FILES:.s=.o),$(BUILD_DIR)/$f)
O_FILES   := $(S_O_FILES) $(C_O_FILES)
# Because we patch the object file timestamps, we can't use them as the targets since they'll always be older than the C file
# Therefore instead we use marker files that have actual timestamps as the dependencies for the archive
C_MARKER_FILES := $(C_O_FILES:.o=.marker)
S_MARKER_FILES := $(S_O_FILES:.o=.marker)
S_MARKER_FILES := $(filter-out $(MDEBUG_FILES),$(S_MARKER_FILES))
MARKER_FILES   := $(C_MARKER_FILES) $(S_MARKER_FILES) $(MDEBUG_FILES)

ifneq ($(COMPARE),0)
COMPARE_OBJ = cmp $(BASE_DIR)/$(@F:.marker=.o) $(@:.marker=.o) && echo "$(@:.marker=.o): OK"
COMPARE_AR = cmp $(BASE_AR) $@ && echo "$@: OK"
ifeq ($(COMPILER),ido)
COMPARE_OBJ = $(CROSS)objcopy -p --strip-debug $(WORKING_DIR)/$(@:.marker=.o) $(WORKING_DIR)/$(@:.marker=.cmp.o) && \
              cmp $(BASE_DIR)/.cmp/$(@F:.marker=.cmp.o) $(WORKING_DIR)/$(@:.marker=.cmp.o) && echo "$(@:.marker=.o): OK"
COMPARE_AR = echo "$@: Cannot compare archive currently"
endif
else
COMPARE_OBJ :=
COMPARE_AR :=
AR_OLD := $(AR)
endif

BASE_OBJS := $(wildcard $(BASE_DIR)/*.o)

# Check to make sure the current version has been set up
ifneq ($(COMPARE),0)
ifeq ($(BASE_OBJS),)
# Ignore this check if the user is currently running setup, clean or distclean
ifeq ($(filter $(MAKECMDGOALS),setup clean distclean),)
$(error Current version ($(TARGET) 2.0$(VERSION)) has not been setup!)
endif
endif
endif

AR_OBJECTS := $(shell cat base/$(VERSION)/$(TARGET).txt)
# If the version and target doesn't have a text file yet, resort back to using the base archive to get objects
ifeq ($(AR_OBJECTS),)
AR_OBJECTS := $(shell ar t $(BASE_AR))
endif


# Try to find a file corresponding to an archive file in src/ or the base directory, prioritizing src then the original file
AR_ORDER = $(foreach f,$(AR_OBJECTS),$(shell find $(BUILD_DIR)/src $(BASE_DIR) -iname $f -type f -print -quit))
MATCHED_OBJS = $(filter-out $(BASE_DIR)/%,$(AR_ORDER))
UNMATCHED_OBJS = $(filter-out $(MATCHED_OBJS),$(AR_ORDER))
NUM_OBJS = $(words $(AR_ORDER))
NUM_OBJS_MATCHED = $(words $(MATCHED_OBJS))
NUM_OBJS_UNMATCHED = $(words $(UNMATCHED_OBJS))

$(shell mkdir -p $(BASE_DIR) src $(foreach dir,$(SRC_DIRS),$(BUILD_DIR)/$(dir)))

.PHONY: all clean distclean setup
all: $(BUILD_AR)

$(BUILD_AR): $(MARKER_FILES)
	$(AR_OLD) rcs $@ $(AR_ORDER)
ifneq ($(COMPARE),0)
# patch archive creation time and individual files' ownership & permissions
	dd bs=1 skip=24 seek=24 count=12 conv=notrunc if=$(BASE_AR) of=$@ status=none
	python3 tools/patch_ar_meta.py $@ $(BASE_AR) $(PATCH_AR_FLAGS)
	@$(COMPARE_AR)
	@echo "Matched: $(NUM_OBJS_MATCHED)/$(NUM_OBJS)"
endif

clean:
	$(RM) -rf $(BUILD_DIR)

distclean:
	$(MAKE) -C tools distclean
	$(RM) -rf extracted/ $(BUILD_ROOT)

setup:
	$(MAKE) -C tools
ifneq ($(COMPARE),0)
	cd $(BASE_DIR) && $(AR) xo $(WORKING_DIR)/$(BASE_AR)
	chmod -R +rw $(BASE_DIR)
ifeq ($(COMPILER),ido)
	export CROSS=$(CROSS) && ./tools/strip_debug.sh $(BASE_DIR)
endif
endif

$(BUILD_DIR)/$(BASE_DIR)/%.marker: $(BASE_DIR)/%.o
	cp $< $(@:.marker=.o)
ifneq ($(COMPARE),0)
# change file timestamps to match original
	@touch -r $(BASE_DIR)/$(@F:.marker=.o) $(@:.marker=.o)
	@$(COMPARE_OBJ)
	@touch $@
endif

GBIDEFINE := -DF3DEX_GBI

$(BUILD_DIR)/src/gu/parse_gbi.marker: GBIDEFINE := -DF3D_GBI
$(BUILD_DIR)/src/gu/us2dex_emu.marker: GBIDEFINE :=
$(BUILD_DIR)/src/gu/us2dex2_emu.marker: GBIDEFINE :=
$(BUILD_DIR)/src/sp/sprite.marker: GBIDEFINE := -DF3D_GBI
$(BUILD_DIR)/src/sp/spriteex.marker: GBIDEFINE :=
$(BUILD_DIR)/src/sp/spriteex2.marker: GBIDEFINE :=
$(BUILD_DIR)/src/voice/%.marker: OPTFLAGS += -DLANG_JAPANESE -I$(WORKING_DIR)/src -I$(WORKING_DIR)/src/voice
$(BUILD_DIR)/src/voice/%.marker: CC := $(WORKING_DIR)/tools/compile_sjis.py -D__CC=$(CC) -D__BUILD_DIR=$(BUILD_DIR)

$(C_MARKER_FILES): $(BUILD_DIR)/%.marker: %.c
	cd $(<D) && $(CC) $(CFLAGS) $(MIPS_VERSION) $(CPPFLAGS) $(OPTFLAGS) $(<F) $(IINC) -o $(WORKING_DIR)/$(@:.marker=.o)
ifneq ($(COMPARE),0)
# check if this file is in the archive; patch corrupted bytes and change file timestamps to match original if so
	@$(if $(findstring $(BASE_DIR)/$(@F:.marker=.o), $(BASE_OBJS)), \
	 python3 tools/fix_objfile.py $(@:.marker=.o) $(BASE_DIR)/$(@F:.marker=.o) $(STRIP) && \
	 $(COMPARE_OBJ) && \
	 touch -r $(BASE_DIR)/$(@F:.marker=.o) $(@:.marker=.o), \
	 echo "Object file $(@F:.marker=.o) is not in the current archive" \
	)
endif
ifneq ($(MODERN_LD),0)
	tools/set_o32abi_bit.py $(WORKING_DIR)/$(@:.marker=.o)
	$(CROSS)strip $(WORKING_DIR)/$(@:.marker=.o) -N asdasdasdasd
	$(CROSS)objcopy --remove-section .mdebug $(WORKING_DIR)/$(@:.marker=.o)
endif
# create or update the marker file
	@touch $@

$(S_MARKER_FILES): $(BUILD_DIR)/%.marker: %.s
	cd $(<D) && $(AS) $(ASFLAGS) $(MIPS_VERSION) $(CPPFLAGS) $(ASOPTFLAGS) $(<F) $(IINC) -o $(WORKING_DIR)/$(@:.marker=.o)
ifneq ($(COMPARE),0)
# check if this file is in the archive; patch corrupted bytes and change file timestamps to match original if so
	@$(if $(findstring $(BASE_DIR)/$(@F:.marker=.o), $(BASE_OBJS)), \
	 python3 tools/fix_objfile.py $(@:.marker=.o) $(BASE_DIR)/$(@F:.marker=.o) $(STRIP) && \
	 $(COMPARE_OBJ) && \
	 touch -r $(BASE_DIR)/$(@F:.marker=.o) $(@:.marker=.o), \
	 echo "Object file $(@F:.marker=.o) is not in the current archive" \
	)
endif
ifneq ($(MODERN_LD),0)
	tools/set_o32abi_bit.py $(WORKING_DIR)/$(@:.marker=.o)
	$(CROSS)strip $(WORKING_DIR)/$(@:.marker=.o) -N asdasdasdasd
	$(CROSS)objcopy --remove-section .mdebug $(WORKING_DIR)/$(@:.marker=.o)
endif
# create or update the marker file
	@touch $@

# Rule for building files that require specific file paths in the mdebug section
$(MDEBUG_FILES): $(BUILD_DIR)/src/%.marker: src/%.s
	cp $(<:.marker=.s) $(dir $@)
	mkdir -p $(@:.marker=)
	export USR_INCLUDE=$(WORKING_DIR)/include && cd $(@:.marker=) && $(AS) $(ASFLAGS) $(CPPFLAGS) ../$(<F) -I/usr/include -o $(notdir $(<:.s=.o))
	mv $(@:.marker=)/$(<F:.s=.o) $(@:.marker=)/..
ifneq ($(COMPARE),0)
# check if this file is in the archive; patch corrupted bytes and change file timestamps to match original if so
	@$(if $(findstring $(BASE_DIR)/$(@F:.marker=.o), $(BASE_OBJS)), \
	 python3 tools/fix_objfile.py $(@:.marker=.o) $(BASE_DIR)/$(@F:.marker=.o) && \
	 $(COMPARE_OBJ) && \
	 touch -r $(BASE_DIR)/$(@F:.marker=.o) $(@:.marker=.o), \
	 echo "Object file $(@F:.marker=.o) is not in the current archive" \
	)
endif
ifneq ($(MODERN_LD),0)
	tools/set_o32abi_bit.py $(WORKING_DIR)/$(@:.marker=.o)
	$(CROSS)strip $(WORKING_DIR)/$(@:.marker=.o) -N asdasdasdasd
	$(CROSS)objcopy --remove-section .mdebug $(WORKING_DIR)/$(@:.marker=.o)
endif
# create or update the marker file
	@touch $@

# Disable built-in rules
.SUFFIXES:
print-% : ; $(info $* is a $(flavor $*) variable set to [$($*)]) @true
