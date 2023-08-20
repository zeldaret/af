#ifndef M_COMMON_DATA_H
#define M_COMMON_DATA_H

#include "ultra64.h"
#include "unk.h"

struct Actor;
struct ActorOverlay;
struct struct_801161E8_jp;
struct PlayState_unk_0110;
struct CommonData_unk_1004C_unk_14_arg0;
struct PlayState;
struct StructureClip;

typedef enum Season {
    /* 0 */ SPRING,
    /* 1 */ SUMMER,
    /* 2 */ FALL,
    /* 3 */ WINTER
} Season;

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

typedef UNK_RET (*CommonData_unk_10080_unk_4)(struct PlayState*, UNK_TYPE, UNK_TYPE);

typedef struct CommonData_unk_10080 {
    /* 0x00 */ UNK_TYPE1 unk_00[0x4];
    /* 0x04 */ CommonData_unk_10080_unk_4 unk_4;
} CommonData_unk_10080; // size >= 0x10

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

typedef void (*CommonData_100E4_Func)(struct PlayState*);

typedef struct CommonData {
    /* 0x00000 */ u8 unk00000[0x14];
    /* 0x00014 */ s32 unk_00014;
    /* 0x00018 */ u8 unk00018[0xFFE8];
    /* 0x10000 */ u8 unk_10000; // named "game_started" in AC GCN decomp
    /* 0x10001 */ u8 unk_10001;
    /* 0x10002 */ u8 unk10002[0x1];
    /* 0x10003 */ u8 unk_10003;
    /* 0x10004 */ s32 unk_10004; // named "last_scene_no" in AC GCN decomp
    /* 0x10008 */ UNK_TYPE1 unk_10008[0x44];
    /* 0x1004C */ CommonData_unk_1004C *unk_1004C;
    /* 0x10050 */ UNK_TYPE1 unk_10050[0x30];
    /* 0x10080 */ CommonData_unk_10080 *unk_10080;
    /* 0x10084 */ UNK_TYPE1 unk_10084[0x14];
    /* 0x10098 */ struct StructureClip* structureClip;
    /* 0x1009C */ UNK_TYPE1 unk_1009C[0x48];
    /* 0x100E4 */ CommonData_100E4_Func* unk_100E4;
    /* 0x100E8 */ u8 unk100E8[0x24];
    /* 0x1010C */ u32 season;
    /* 0x10110 */ u8 unk10110[0x8];
    /* 0x10118 */ s32 now_sec;
    /* 0x1011C */ u8 unk1011C[0x3];
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
    /* 0x1014C */ UNK_TYPE1 unk_1014C[0x2];
    /* 0x1014E */ s16 unk_1014E;
    /* 0x10150 */ UNK_TYPE1 unk_10150[0x664];
    /* 0x107B4 */ UNK_TYPE1 unk_107B4[0x2];
    /* 0x107B6 */ s16 unk_107B6; // named "demo_profile" in AC GCN decomp (though it's an array of two s16s in that game)
    /* 0x107B8 */ u8 unk107B8[0x2C];
    /* 0x107E4 */ s16 unk_107E4;
    /* 0x107E6 */ u8 unk107E6[0x29C];
    /* 0x10A82 */ s16 unk_10A82;
    /* 0x10A84 */ u8 unk10A84[0x2C];
    /* 0x10AB0 */ u8 unk_10AB0; // named "pad_connected" in AC GCN decomp
    /* 0x10AB1 */ UNK_TYPE1 unk_10AB1[0x7];
} CommonData; // size = 0x10AB8

void common_data_reinit(void);
void common_data_init(void);
void common_data_clear(void);

extern CommonData common_data;

#endif
