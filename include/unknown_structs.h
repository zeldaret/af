#ifndef UNKNOWN_STRUCTS_H
#define UNKNOWN_STRUCTS_H

#include "ultra64.h"
#include "libc/stdint.h"
#include "libc/stdbool.h"
#include "unk.h"
#include "other_types.h"

typedef struct Clip_unk_040_unk_14_arg0 {
    /* 0x00 */ s16 unk_00;
    /* 0x00 */ s16 unk_02;
    /* 0x04 */ UNK_TYPE1 unk_04[0x60];
} Clip_unk_040_unk_14_arg0; // size >= 0x64, maybe less, guessed from stack usage

typedef struct ShadowData {
    /* 0x00 */ u32 numberOfVertices;
    /* 0x04 */ u8* vertexFixFlagTable;
    /* 0x08 */ f32 size;
    /* 0x0C */ Vtx* vertices;
    /* 0x10 */ Gfx* model;
} ShadowData; // size = 0x14

typedef struct struct_809AEFA4 {
    /* 0x00 */ UNK_PTR unk_00;
    /* 0x04 */ UNK_PTR unk_04;
    /* 0x08 */ UNK_TYPE unk_08;
    /* 0x0C */ UNK_PTR unk_0C;
    /* 0x10 */ UNK_PTR unk_10;
    /* 0x14 */ UNK_PTR unk_14;
} struct_809AEFA4; // size >= 0x18

// Maybe same struct as mMl?
typedef struct struct_func_8085CE18_jp_arg4 {
    /* 0x00 */ UNK_TYPE1 unk_00[0x24];
    /* 0x24 */ u16 unk_24;
    /* 0x26 */ u8 unk_26;
} struct_func_8085CE18_jp_arg4; // size >= 0x28

#endif
