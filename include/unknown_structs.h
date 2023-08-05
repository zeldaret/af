#ifndef UNKNOWN_STRUCTS_H
#define UNKNOWN_STRUCTS_H

#include "ultra64.h"
#include "libc/stdint.h"
#include "libc/stdbool.h"
#include "unk.h"

typedef struct struct_debug_mode {
    /* 0x000 */ UNK_TYPE1 unk_000[0x110];
    /* 0x110 */ s16 unk_110;
} struct_debug_mode; // size >= 0x114

#endif
