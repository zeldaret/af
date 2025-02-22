
COMPILER_DIR := $(dir $(which $(CROSS)gcc))
AS := $(CROSS)gcc -x assembler-with-cpp
CC := $(CROSS)gcc
AR_OLD := $(CROSS)ar

WARNINGS := -Wall -Wextra -Wno-format-security -Wno-unused-function -Wno-unused-parameter -Wno-unused-variable -Wno-builtin-declaration-mismatch
WARNINGS += -Wno-int-conversion -Wno-incompatible-pointer-types -Wno-implicit-function-declaration # TODO: Try adjusting code to remove these
CFLAGS := -G 0 -c -nostdinc -march=vr4300 -mfix4300 -mabi=32 -mno-abicalls -mdivide-breaks -fno-PIC -fno-common -ffreestanding -fbuiltin -fno-builtin-sinf -fno-builtin-cosf -funsigned-char $(WARNINGS)
CFLAGS += -fno-strict-aliasing # TODO: Try adjusting code to remove this
ASFLAGS := -w -nostdinc -c -G 0 -march=vr4300 -mgp32 -mfp32 -DMIPSEB -D_LANGUAGE_ASSEMBLY -D_MIPS_SIM=1 -D_ULTRA64
CPPFLAGS = -DMODERN_CC -D_MIPS_SZLONG=32 -D__USE_ISOC99 $(GBIDEFINE) $(VERSION_DEFINE) $(DEBUGFLAG)
IINC = -I . -I $(WORKING_DIR)/include -I $(WORKING_DIR)/include/compiler/modern_gcc -I $(WORKING_DIR)/include/PR
MIPS_VERSION := -mips3
ASOPTFLAGS :=

ifeq ($(findstring _d,$(TARGET)),_d)
OPTFLAGS := -Og -ggdb3 -ffast-math -fno-unsafe-math-optimizations
else
OPTFLAGS := -Os -ggdb3 -ffast-math -fno-unsafe-math-optimizations
endif
