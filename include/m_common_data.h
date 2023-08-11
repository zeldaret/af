#ifndef M_COMMON_DATA_H
#define M_COMMON_DATA_H

#include "ultra64.h"
#include "unk.h"

typedef struct CommonData {
    /* 0x00000 */ u8 unk_00000[0x10000];
    /* 0x10000 */ u8 unk_10000; // named "game_started" in AC GCN decomp
    /* 0x10001 */ u8 unk_10001[0x3];
    /* 0x10004 */ s32 unk_10004; // named "last_scene_no" in AC GCN decomp
    /* 0x10008 */ u8 unk_10008[0x143];
    /* 0x1014B */ u8 unk_1014B; // named "wipeType" in AC GCN decomp
    /* 0x1014C */ UNK_TYPE1 unk_1014C[0x2];
    /* 0x1014E */ s16 unk_1014E;
    /* 0x10150 */ UNK_TYPE1 unk_10150[0x664];
    /* 0x107B4 */ UNK_TYPE1 unk_107B4[0x2];
    /* 0x107B6 */ s16 unk_107B6; // named "demo_profile" in AC GCN decomp (though it's an array of two s16s in that game)
    /* 0x107B8 */ u8 unk_107B8[0x2F8];
    /* 0x10AB0 */ u8 unk_10AB0; // named "pad_connected" in AC GCN decomp
    /* 0x10AB1 */ u8 unk_10AB1[0x7];
} CommonData; // size = 0x10AB8

void common_data_reinit(void);
void common_data_init(void);
void common_data_clear(void);

extern CommonData common_data;

#endif
