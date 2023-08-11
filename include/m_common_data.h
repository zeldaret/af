#ifndef M_COMMON_DATA_H
#define M_COMMON_DATA_H

#include "ultra64.h"
#include "unk.h"

struct struct_801161E8_jp;
struct ActorOverlay;


typedef UNK_RET (*CommonData_unk_1004C_unk_4)(struct ActorOverlay*, const struct struct_801161E8_jp*, size_t, s32);
typedef UNK_RET (*CommonData_unk_1004C_unk_8)(void);

typedef struct CommonData_unk_1004C {
    /* 0x00 */ UNK_TYPE1 unk_00[0x4];
    /* 0x04 */ CommonData_unk_1004C_unk_4 unk_04;
    /* 0x08 */ CommonData_unk_1004C_unk_8 unk_08;
    /* 0x0C */ UNK_TYPE1 unk_0C[0x8];
    /* 0x14 */ UNK_FUN_PTR unk_14;
    /* 0x18 */ UNK_TYPE1 unk_18[0xD4];
    /* 0xEC */ UNK_FUN_PTR unk_EC;
} CommonData_unk_1004C; // size >= 0xD0

typedef UNK_RET (*CommonData_unk_10098_unk_4)(struct ActorOverlay*, size_t);
typedef UNK_RET (*CommonData_unk_10098_unk_8)(void);

typedef struct CommonData_unk_10098 {
    /* 0x0 */ UNK_TYPE1 unk_0[0x4];
    /* 0x4 */ CommonData_unk_10098_unk_4 unk_4;
    /* 0x8 */ CommonData_unk_10098_unk_8 unk_08;
} CommonData_unk_10098; // size >= 0xC


typedef struct CommonData {
    /* 0x00000 */ u8 unk_00000[0x10000];
    /* 0x10000 */ u8 unk_10000; // named "game_started" in AC GCN decomp
    /* 0x10001 */ u8 unk_10001[0x3];
    /* 0x10004 */ s32 unk_10004; // named "last_scene_no" in AC GCN decomp
    /* 0x10008 */ UNK_TYPE1 unk_10008[0x44];
    /* 0x1004C */ CommonData_unk_1004C *unk_1004C;
    /* 0x10050 */ UNK_TYPE1 unk_10050[0x48];
    /* 0x10098 */ CommonData_unk_10098 *unk_10098;
    /* 0x1009C */ UNK_TYPE1 unk_1009C[0xAC];
    /* 0x10148 */ UNK_TYPE1 unk_10148[0x3];
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
