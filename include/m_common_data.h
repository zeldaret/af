#ifndef M_COMMON_DATA_H
#define M_COMMON_DATA_H

#include "ultra64.h"
#include "unk.h"

struct Actor;
struct ActorOverlay;
struct struct_801161E8_jp;
struct PlayState_unk_0110;
struct CommonData_unk_1004C_unk_14_arg0;


typedef UNK_RET (*CommonData_unk_1004C_unk_04)(struct ActorOverlay*, const struct struct_801161E8_jp*, size_t, s32);
typedef UNK_RET (*CommonData_unk_1004C_unk_08)(void);

// TODO: figure out if this is a generic memory allocation or if it is Actor specific
typedef UNK_PTR (*CommonData_unk_1004C_unk_0C)(size_t, const struct struct_801161E8_jp*, s32);

typedef UNK_RET (*CommonData_unk_1004C_unk_10)(struct Actor*);
typedef UNK_RET (*CommonData_unk_1004C_unk_14)(struct CommonData_unk_1004C_unk_14_arg0*, u16);

typedef UNK_RET (*CommonData_unk_1004C_unk_EC)(struct PlayState_unk_0110*, s16, s16);
typedef UNK_RET (*CommonData_unk_1004C_unk_F0)(struct PlayState_unk_0110*, struct Actor*);
typedef s32 (*CommonData_unk_1004C_unk_F4)(struct PlayState_unk_0110*, struct Actor*);

typedef struct CommonData_unk_1004C {
    /* 0x00 */ UNK_TYPE1 unk_00[0x4];
    /* 0x04 */ CommonData_unk_1004C_unk_04 unk_04;
    /* 0x08 */ CommonData_unk_1004C_unk_08 unk_08;
    /* 0x0C */ CommonData_unk_1004C_unk_0C unk_0C;
    /* 0x10 */ CommonData_unk_1004C_unk_10 unk_10;
    /* 0x14 */ CommonData_unk_1004C_unk_14 unk_14;
    /* 0x18 */ UNK_TYPE1 unk_18[0xD4];
    /* 0xEC */ CommonData_unk_1004C_unk_EC unk_EC;
    /* 0xF0 */ CommonData_unk_1004C_unk_F0 unk_F0;
    /* 0xF4 */ CommonData_unk_1004C_unk_F4 unk_F4;
} CommonData_unk_1004C; // size >= 0xF8

typedef UNK_RET (*CommonData_unk_10098_unk_4)(struct ActorOverlay*, size_t);
typedef UNK_RET (*CommonData_unk_10098_unk_8)(void);

// TODO: figure out if this is a generic memory allocation or if it is Actor specific
typedef UNK_PTR (*CommonData_unk_10098_unk_0C)(void);

typedef UNK_RET (*CommonData_unk_10098_unk_10)(struct Actor*);

typedef struct CommonData_unk_10098 {
    /* 0x00 */ UNK_TYPE1 unk_00[0x4];
    /* 0x04 */ CommonData_unk_10098_unk_4 unk_4;
    /* 0x08 */ CommonData_unk_10098_unk_8 unk_08;
    /* 0x0C */ CommonData_unk_10098_unk_0C unk_0C;
    /* 0x10 */ CommonData_unk_10098_unk_10 unk_10;
} CommonData_unk_10098; // size >= 0x10


typedef struct CommonData {
    /* 0x00000 */ UNK_TYPE1 unk_00000[0x10000];
    /* 0x10000 */ u8 unk_10000; // named "game_started" in AC GCN decomp
    /* 0x10001 */ UNK_TYPE1 unk_10001[0x3];
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
    /* 0x107B8 */ UNK_TYPE1 unk_107B8[0x2F8];
    /* 0x10AB0 */ u8 unk_10AB0; // named "pad_connected" in AC GCN decomp
    /* 0x10AB1 */ UNK_TYPE1 unk_10AB1[0x7];
} CommonData; // size = 0x10AB8

void common_data_reinit(void);
void common_data_init(void);
void common_data_clear(void);

extern CommonData common_data;

#endif
