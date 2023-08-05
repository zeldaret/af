#ifndef UNKNOWN_STRUCTS_H
#define UNKNOWN_STRUCTS_H

#include "ultra64.h"
#include "libc/stdint.h"
#include "libc/stdbool.h"
#include "unk.h"

typedef struct struct_debug_mode {
    /* 0x000 */ UNK_TYPE1 unk_000[0xD4];
    /* 0x0D4 */ s16 unk_0D4;
    /* 0x0D6 */ UNK_TYPE1 unk_0D6[0x2];
    /* 0x0D8 */ UNK_TYPE1 unk_0D8[0x38];
    /* 0x110 */ s16 unk_110;
} struct_debug_mode; // size >= 0x114

#endif
