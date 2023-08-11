#ifndef M_COMMON_DATA_H
#define M_COMMON_DATA_H

#include "ultra64.h"
#include "m_snowman.h"

typedef struct {
    /* 0x0000 */ u8 unk_0[0xF41C];
    /* 0xF41C */ SnowmanData snowmanData[SNOWMAN_SAVE_COUNT];
    /* 0xF428 */ u8 unk_F428[0x485];
    /* 0xF8AD */ u8 snowmanYear;
    /* 0xF8AE */ u8 snowmanMonth;
    /* 0xF8AF */ u8 snowmanDay;
    /* 0xF8B0 */ u8 snowmanHour;
    /* 0xF8B1 */ u8 unk_F8B1[0x74F];
} Save; // size = 0x10000

typedef struct CommonData {
    /* 0x00000 */ Save save;
    /* 0x10000 */ u8 unk_10000; // named "game_started" in AC GCN decomp
    /* 0x10001 */ u8 unk_10001[0x3];
    /* 0x10004 */ s32 unk_10004; // named "last_scene_no" in AC GCN decomp
    /* 0x10008 */ u8 unk_10008[0x104];
    /* 0x1010C */ s32 unk_1010C;
    /* 0x10110 */ u8 unk_10110[0x3B];
    /* 0x1014B */ u8 unk_1014B; // named "wipeType" in AC GCN decomp
    /* 0x1014C */ u8 unk_1014C[0x600];
    /* 0x1074C */ s32 unk_1074C;
    /* 0x10750 */ u8 unk_10750[0x66];
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
