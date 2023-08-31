#ifndef UNKNOWN_STRUCTS_H
#define UNKNOWN_STRUCTS_H

#include "ultra64.h"
#include "libc/stdint.h"
#include "libc/stdbool.h"
#include "unk.h"
#include "other_types.h"

typedef struct Struct_8010EAA0 {
    /* 0x00 */ RomOffset unk_00;
    /* 0x04 */ RomOffset unk_04;
    /* 0x08 */ char unk08[0xB];
    /* 0x13 */ u8 unk_13;
} Struct_8010EAA0;  // size = 0x14

typedef struct struct_801161E8_jp {
    /* 0x0 */ UNK_TYPE1 unk_0[0x8];
} struct_801161E8_jp; // size <= 0x8

typedef struct CommonData_unk_1004C_unk_14_arg0 {
    /* 0x00 */ s16 unk_00;
    /* 0x00 */ s16 unk_02;
    /* 0x04 */ UNK_TYPE1 unk_04[0x60];
} CommonData_unk_1004C_unk_14_arg0; // size >= 0x64, maybe less, guessed from stack usage

typedef struct Game_Play_unk_0110 {
    /* 0x00 */ s16 unk_00;
    /* 0x02 */ UNK_TYPE1 unk_02[0x2];
    /* 0x04 */ void* segment;
    /* 0x08 */ UNK_TYPE1 unk_08[0x48];
    /* 0x50 */ s16 unk_50;
    /* 0x52 */ UNK_TYPE1 unk_52[0x2];
} Game_Play_unk_0110; // size = 0x54

typedef struct struct_809AEFA4 {
    /* 0x00 */ UNK_PTR unk_0;
    /* 0x04 */ UNK_PTR unk_4;
    /* 0x08 */ UNK_TYPE unk_8;
    /* 0x0C */ UNK_PTR unk_C;
    /* 0x10 */ UNK_PTR unk_10;
    /* 0x14 */ UNK_PTR unk_14;
} struct_809AEFA4; // size >= 0x18

#endif
