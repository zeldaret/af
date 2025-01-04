COMPILER_DIR := $(WORKING_DIR)/tools/ido
AS := $(COMPILER_DIR)/cc
CC := $(COMPILER_DIR)/cc
AR_OLD := $(WORKING_DIR)/tools/ar.py
PATCH_AR_FLAGS := 40001 110 100644
STRIP =

CFLAGS := -c -Wab,-r4300_mul -G 0 -nostdinc -Xcpluscomm -fullwarn -woff 516,649,838,712
ASFLAGS := -c -Wab,-r4300_mul -G 0 -nostdinc -woff 516,649,838,712
CPPFLAGS = -D_MIPS_SZLONG=32 $(GBIDEFINE) $(VERSION_DEFINE) $(PICFLAGS) $(DEBUGFLAG)
IINC = -I $(WORKING_DIR)/include -I $(WORKING_DIR)/include/compiler/ido -I $(WORKING_DIR)/include/PR
MIPS_VERSION := -mips2 -o32
PICFLAGS := -non_shared

ifeq ($(findstring _d,$(TARGET)),_d)
OPTFLAGS := -O1 -g2
ASOPTFLAGS := -O0 -g2
else
ifneq ($(filter $(VERSION),D E F G H I),)
OPTFLAGS := -O1
else
OPTFLAGS := -O2
endif
ASOPTFLAGS := -O1
endif

ifneq ($(findstring _d,$(TARGET)),_d)
$(BUILD_DIR)/src/debug/%.marker: OPTFLAGS := -O1
$(BUILD_DIR)/src/host/%.marker: OPTFLAGS := -O1
$(BUILD_DIR)/src/os/%.marker: OPTFLAGS := -O1
$(BUILD_DIR)/src/rmon/%.marker: OPTFLAGS := -O1
$(BUILD_DIR)/src/libc/ll.marker: OPTFLAGS := -O1
$(BUILD_DIR)/src/libc/llbit.marker: OPTFLAGS := -O1
$(BUILD_DIR)/src/libc/llcvt.marker: OPTFLAGS := -O1
$(BUILD_DIR)/src/log/%.marker: OPTFLAGS := -O1

$(BUILD_DIR)/src/libc/%.marker: ASOPTFLAGS := -O2
$(BUILD_DIR)/src/mgu/%.marker: ASOPTFLAGS := -O2
endif

$(BUILD_DIR)/src/os/initialize_isv.marker: OPTFLAGS := -O2
$(BUILD_DIR)/src/libc/ll.marker: MIPS_VERSION := -mips3 -32
$(BUILD_DIR)/src/libc/llbit.marker: MIPS_VERSION := -mips3 -32
$(BUILD_DIR)/src/libc/llcvt.marker: MIPS_VERSION := -mips3 -32
$(BUILD_DIR)/src/os/exceptasm.marker: MIPS_VERSION := -mips3 -32
$(BUILD_DIR)/src/log/delay.marker: MIPS_VERSION := -mips1 -o32
$(BUILD_DIR)/src/log/delay.marker: PICFLAGS := -KPIC

ifneq ($(filter $(VERSION),D E F G H I),)
$(BUILD_DIR)/src/libc/%.marker: OPTFLAGS := -O3
$(BUILD_DIR)/src/sched/%.marker: OPTFLAGS := -O3
$(BUILD_DIR)/src/gu/%.marker: OPTFLAGS := -O3
$(BUILD_DIR)/src/mgu/%.marker: OPTFLAGS := -O3
$(BUILD_DIR)/src/sp/%.marker: OPTFLAGS := -O3
$(BUILD_DIR)/src/audio/%.marker: OPTFLAGS := -O3
$(BUILD_DIR)/src/rg/%.marker: OPTFLAGS := -O3
$(BUILD_DIR)/src/gt/%.marker: OPTFLAGS := -O3
endif
