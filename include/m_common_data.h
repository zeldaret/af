#ifndef M_COMMON_DATA_H
#define M_COMMON_DATA_H

#include "ultra64.h"

struct PlayState;

typedef struct CommonData10138_Sub {
    /* 0x00 */ char unk00[0x3];
    /* 0x03 */ u8 unk_03;
    /* 0x04 */ char unk04[0x1];
    /* 0x05 */ u8 unk_05;
    /* 0x06 */ u16 unk_06;
    /* 0x08 */ u8 unk_08;
} CommonData10138_Sub; // size >= 0xC

typedef struct CommonData10138 {
    /* 0x000 */ char unk000[0xA86];
    /* 0xA86 */ CommonData10138_Sub unk_A86;
} CommonData10138; // size >= 0xA90

typedef struct CommonData {
    /* 0x00000 */ u8 unk00000[0x14];
    /* 0x00014 */ s32 unk_00014;
    /* 0x00018 */ u8 unk00018[0xFFE8];
    /* 0x10000 */ u8 unk_10000; // named "game_started" in AC GCN decomp
    /* 0x10001 */ u8 unk_10001;
    /* 0x10002 */ u8 unk10002[0x1];
    /* 0x10003 */ u8 unk_10003;
    /* 0x10004 */ s32 unk_10004; // named "last_scene_no" in AC GCN decomp
    /* 0x10008 */ u8 unk10008[0xDC];
    /* 0x100E4 */ void (**unk_100E4)(struct PlayState*);
    /* 0x100E8 */ u8 unk100E8[0x37];
    /* 0x1011F */ u8 unk_1011F;
    /* 0x10120 */ u8 unk10120[0x1];
    /* 0x10121 */ u8 unk_10121;
    /* 0x10122 */ u16 unk_10122;
    /* 0x10124 */ u8 unk10124[0x14];
    /* 0x10138 */ CommonData10138* unk_10138;
    /* 0x1013C */ u8 unk1013C[0xD];
    /* 0x10149 */ u8 unk_10149;
    /* 0x1014A */ u8 unk_1014A;
    /* 0x1014B */ u8 unk_1014B; // named "wipeType" in AC GCN decomp
    /* 0x1014C */ u8 unk1014C[0x66A];
    /* 0x107B6 */ s16 unk_107B6; // named "demo_profile" in AC GCN decomp (though it's an array of two s16s in that game)
    /* 0x107B8 */ u8 unk107B8[0x2C];
    /* 0x107E4 */ s16 unk_107E4;
    /* 0x107E6 */ u8 unk107E6[0x29C];
    /* 0x10A82 */ s16 unk_10A82;
    /* 0x10A84 */ u8 unk10A84[0x2C];
    /* 0x10AB0 */ u8 unk_10AB0; // named "pad_connected" in AC GCN decomp
    /* 0x10AB1 */ u8 unk10AB1[0x7];
} CommonData; // size = 0x10AB8

void common_data_reinit(void);
void common_data_init(void);
void common_data_clear(void);

extern CommonData common_data;

#endif
