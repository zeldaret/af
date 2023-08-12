#ifndef UNKNOWN_STRUCTS_H
#define UNKNOWN_STRUCTS_H

#include "ultra64.h"
#include "libc/stdint.h"
#include "libc/stdbool.h"
#include "unk.h"

typedef struct struct_801161E8_jp {
    /* 0x0 */ UNK_TYPE1 unk_0[0x8];
} struct_801161E8_jp; // size <= 0x8

typedef struct CommonData_unk_1004C_unk_14_arg0 {
    /* 0x00 */ UNK_TYPE1 unk_00[0x64];
} CommonData_unk_1004C_unk_14_arg0; // size >= 0x64

typedef struct PlayState_unk_0110 {
    /* 0x00 */ UNK_TYPE1 unk_00[0x4];
    /* 0x04 */ void* unk_04;
    /* 0x08 */ UNK_TYPE1 unk_08[0x48];
    /* 0x50 */ s16 unk_50;
    /* 0x52 */ UNK_TYPE1 unk_52[0x2];
} PlayState_unk_0110; // size = 0x54

#endif
