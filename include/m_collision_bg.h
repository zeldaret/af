#ifndef M_COLLISION_BG_H
#define M_COLLISION_BG_H

#include "ultra64.h"
#include "z64math.h"
#include "unk.h"

struct Actor;
struct PosRot;

// TODO: focus further investigation on attributes WATER, 30, HOLE, WAVE, 59-63, and NONE
enum BackgroundAttribute {
    /* 000 */ mCoBG_ATTRIBUTE_GRASS0,
    /* 001 */ mCoBG_ATTRIBUTE_GRASS1,
    /* 002 */ mCoBG_ATTRIBUTE_GRASS2,
    /* 003 */ mCoBG_ATTRIBUTE_GRASS3,
    /* 004 */ mCoBG_ATTRIBUTE_SOIL0,
    /* 005 */ mCoBG_ATTRIBUTE_SOIL1,
    /* 006 */ mCoBG_ATTRIBUTE_SOIL2,
    /* 007 */ mCoBG_ATTRIBUTE_STONE, // stone path (not individual rocks)
    /* 008 */ mCoBG_ATTRIBUTE_FLOOR, // seems to occupy all units in bottom row
    /* 009 */ mCoBG_ATTRIBUTE_BUSH,

    /* 010 */ mCoBG_ATTRIBUTE_HOLE, // unconfirmed (from ac-decomp)
    /* 011 */ mCoBG_ATTRIBUTE_WAVE, // unconfirmed (from ac-decomp)

    /* 012 */ mCoBG_ATTRIBUTE_WATER, // only used in small pond?
    /* 013 */ mCoBG_ATTRIBUTE_WATERFALL,
    /* 014 */ mCoBG_ATTRIBUTE_RIVER_N,
    /* 015 */ mCoBG_ATTRIBUTE_RIVER_NW,
    /* 016 */ mCoBG_ATTRIBUTE_RIVER_W,
    /* 017 */ mCoBG_ATTRIBUTE_RIVER_SW,
    /* 018 */ mCoBG_ATTRIBUTE_RIVER_S,
    /* 019 */ mCoBG_ATTRIBUTE_RIVER_SE,
    /* 020 */ mCoBG_ATTRIBUTE_RIVER_E,
    /* 021 */ mCoBG_ATTRIBUTE_RIVER_NE,

    /* 022 */ mCoBG_ATTRIBUTE_SAND,
    /* 023 */ mCoBG_ATTRIBUTE_WOOD,        // fences (train tracks/dump), large signs, bridge edges
    /* 024 */ mCoBG_ATTRIBUTE_SEA,         // only seems to appear in row with beach
    /* 025 */ mCoBG_ATTRIBUTE_SHALLOW0_NW, // shallower diagonal sea shallows, sea to SE
    /* 026 */ mCoBG_ATTRIBUTE_SHALLOW0_NE, // shallower diagonal sea shallows, sea to SW

    /* 027 */ mCoBG_ATTRIBUTE_BRIDGE_NW,  // diagonal bridge, river to NW
    /* 028 */ mCoBG_ATTRIBUTE_BRIDGE_END, // "bridge" unit that ends above water (i.e. a pier)
    /* 029 */ mCoBG_ATTRIBUTE_BRIDGE_SE,  // diagonal bridge, river to SE
    /* 030 */ mCoBG_ATTRIBUTE_30,
    /* 031 */ mCoBG_ATTRIBUTE_BRIDGE_C, // diagonal bridge's central unit
    /* 032 */ mCoBG_ATTRIBUTE_BRIDGE_N, // horizontal bridge, river/tracks to north (stone?)
    /* 033 */ mCoBG_ATTRIBUTE_BRIDGE_E, // vertical bridge/steps, river/grass to east
    /* 034 */ mCoBG_ATTRIBUTE_BRIDGE_W, // vertical bridge/steps, river/grass to west
    /* 035 */ mCoBG_ATTRIBUTE_BRIDGE_S, // horizontal bridge, river to south

    /* 036 */ mCoBG_ATTRIBUTE_SHALLOW1_S,  // deeper horizontal sea shallows, sea to south
    /* 037 */ mCoBG_ATTRIBUTE_SHALLOW1_NW, // deeper diagonal sea shallows, sea to SE
    /* 038 */ mCoBG_ATTRIBUTE_SHALLOW1_NE, // deeper diagonal sea shallows, sea to SW

    /* 039 */ mCoBG_ATTRIBUTE_BANK_SE, // diagonal riverbank, river to NW
    /* 040 */ mCoBG_ATTRIBUTE_BANK_NE, // diagonal riverbank, river to SW
    /* 041 */ mCoBG_ATTRIBUTE_BANK_NW, // diagonal riverbank, river to SE
    /* 042 */ mCoBG_ATTRIBUTE_BANK_SW, // diagonal riverbank, river to NE
    /* 043 */ mCoBG_ATTRIBUTE_BANK_N,  // horizontal riverbank, river to north
    /* 044 */ mCoBG_ATTRIBUTE_BANK_W,  // vertical riverbank, river to east
    /* 045 */ mCoBG_ATTRIBUTE_BANK_E,  // vertical riverbank, river to west
    /* 046 */ mCoBG_ATTRIBUTE_BANK_S,  // horizontal riverbank, river to south

    /* 047 */ mCoBG_ATTRIBUTE_CLIFF_S, // vertical cliff edge, valley to north (only in south tunnel wall?)
    /* 048 */ mCoBG_ATTRIBUTE_CLIFF_W, // vertical cliff edge, valley to west
    /* 049 */ mCoBG_ATTRIBUTE_CLIFF_E, // vertical cliff edge, valley to west
    /* 050 */ mCoBG_ATTRIBUTE_CLIFF_N, // horizontal cliff edge, valley to south (also appears in north tunnel wall)

    /* 051 */ mCoBG_ATTRIBUTE_TUNNEL_E_S, // east tunnel entrance, south corner
    /* 052 */ mCoBG_ATTRIBUTE_TUNNEL_E_N, // east tunnel entrance, north corner
    /* 053 */ mCoBG_ATTRIBUTE_TUNNEL_W_N, // west tunnel entrance, north corner
    /* 054 */ mCoBG_ATTRIBUTE_TUNNEL_W_S, // west tunnel entrance, south corner

    /* 055 */ mCoBG_ATTRIBUTE_CLIFF_SE, // diagonal cliff edge, valley to NW
    /* 056 */ mCoBG_ATTRIBUTE_CLIFF_NE, // diagonal cliff edge, valley to SW
    /* 057 */ mCoBG_ATTRIBUTE_CLIFF_NW, // diagonal cliff edge, valley to SE
    /* 058 */ mCoBG_ATTRIBUTE_CLIFF_SW, // diagonal cliff edge, valley to NE

    /* 059 */ mCoBG_ATTRIBUTE_BANK_WN,  // corner riverbank, river/pond to north and west (need more data)
    /* 060 */ mCoBG_ATTRIBUTE_BANK_UNK, // corner riverbank, unsure (found at beach on mini cliff with SAND to west,
                                        // BANK_NE to east, BANK_E to north, SHALLOW1_NW to south)

    /* 061 */ mCoBG_ATTRIBUTE_61,
    /* 062 */ mCoBG_ATTRIBUTE_62,
    /* 063 */ mCoBG_ATTRIBUTE_63, // appears very sparingly at soil-grass boundaries

    /* 100 */ mCoBG_ATTRIBUTE_NONE = 100, // unconfirmed (from ac-decomp)
};

// offset table
typedef struct mCoBG_unkStruct2 {
    /* 0x00 */ u8 unk0;
    /* 0x01 */ s8 unk1;
    /* 0x02 */ s8 unk2;
    /* 0x03 */ s8 unk3;
    /* 0x04 */ s8 unk4;
    /* 0x05 */ s8 unk5;
    /* 0x06 */ s8 unk6;
} mCoBG_unkStruct2; // size = 0x7

// clang-format off
// collision bg data
typedef struct mCoBG_unkStruct {
    /* 0x0 */ u32 unk0 : 1; // [31] shape
    /* 0x0 */ u32 unk1 : 5; // [30:25] center
    /* 0x0 */ u32 unk2 : 5; // [25:20] top_left
    /* 0x0 */ u32 unk3 : 5; // [20:15] bot_left
    /* 0x0 */ u32 unk4 : 5; // [15:10] top_right
    /* 0x0 */ u32 unk5 : 5; // [10:5] bot_right
    /* 0x0 */ u32 unitAttribute : 6; // [5:0] unit_attribute
} mCoBG_unkStruct; // size = 0x4
// clang-format on

typedef union mCoBG_unkStructUnion {
    mCoBG_unkStruct data;
    u32 raw;
} mCoBG_unkStructUnion;

// collision bg wall info
typedef struct mCoBG_WallInfo {
    /* 0x0 */ s16 angleY;
    /* 0x2 */ s16 type;
} mCoBG_WallInfo; // size = 0x4

/* collision bg result data
 *
 * bits allocation:
 * | 0x0      0x1      0x2      0x3      | offset | name
 * | X_______ ________ ________ ________ | 0x00   | onGround
 * | _XXXXX__ ________ ________ ________ | 0x01   | unk1
 * | ______XX XXX_____ ________ ________ | 0x06   | hitWall
 * | ________ ___XXX__ ________ ________ | 0x0B   | unk3
 * | ________ ______X_ ________ ________ | 0x0E   | unk4
 * | ________ _______X XXXXX___ ________ | 0x0F   | unk5
 * | ________ ________ _____X__ ________ | 0x15   | unk6
 * | ________ ________ ______X_ ________ | 0x16   | inWater
 * | ________ ________ _______X ________ | 0x17   | unk8
 * | ________ ________ ________ X_______ | 0x18   | unk9
 * | ________ ________ ________ _X______ | 0x19   | unk10
 * | ________ ________ ________ __X_____ | 0x1A   | unk11
 * | ________ ________ ________ ___X____ | 0x1B   | unk12
 * | ________ ________ ________ ____XXXX | 0x1C   | unk13
 */
// clang-format off
typedef struct mCoBG_CheckResult {
    u32 onGround : 1; // on_ground
    u32 unk1     : 5; // hit_attribute_wall
    u32 hitWall  : 5; // hit_wall
    u32 unk3     : 3; // hit_wall_count
    u32 unk4     : 1; // unk_flag0
    u32 unk5     : 6; // unit_attribute
    u32 unk6     : 1; // is_on_move_bg_obj
    u32 inWater  : 1; // is_in_water
    u32 unk8     : 1; // unk_flag1
    u32 unk9     : 1; // unk_flag2
    u32 unk10    : 1; // unk_flag3
    u32 unk11    : 1; // unk_flag4
    u32 unk12    : 1; // unk_flag5
    u32 unk13    : 4; // unk_flag6
} mCoBG_CheckResult;
// clang-format on

typedef struct mCoBG_Check {
    /* 0x00 */ u8 unk0[0x11];
    /* 0x14 */ mCoBG_CheckResult colResult;
    /* 0x18 */ u8 unk18[0xC];
    /* 0x24 */ mCoBG_WallInfo wallInfo[2];
    /* 0x2C */ s16 unk2C;
} mCoBG_Check; // size = 0x30

// void func_80067430_jp();
// void func_800674B0_jp();
// void func_800674D8_jp();
// void func_8006755C_jp();
// void func_800675E0_jp();
// void func_80067664_jp();
// void func_800678AC_jp();
// void func_80067954_jp();
// void func_80067B48_jp();
// void func_80067B70_jp();
// void func_80067CE8_jp();
// void func_80067D98_jp();
// void func_80067EB0_jp();
// void func_80067F50_jp();
// void func_8006800C_jp();
// void func_8006806C_jp();
// void func_8006811C_jp();
// void func_8006818C_jp();
// void func_800682F4_jp();
// void func_800683F4_jp();
// void func_8006844C_jp();
// void func_8006847C_jp();
// void func_800684C8_jp();
// void func_8006851C_jp();
// void func_80068570_jp();
// void func_800685D4_jp();
// void func_80068648_jp();
// void func_800686C4_jp();
// void func_80068730_jp();
// void func_8006874C_jp();
// void func_80068768_jp();
// void func_800687B8_jp();
// void func_80068808_jp();
// void func_800688B4_jp();
// void func_800688D0_jp();
// void func_800688FC_jp();
// void func_80068934_jp();
// void func_800689A4_jp();
// void func_800689C8_jp();
// void func_800689E4_jp();
// void func_80068A50_jp();
// void func_80068BB8_jp();
// void func_80068C88_jp();
// void func_80068D10_jp();
// void func_80068F5C_jp();
// void func_80069280_jp();
// void func_80069354_jp();
// void func_800694DC_jp();
// void func_80069558_jp();
// void func_80069580_jp();
// void func_80069680_jp();
// void func_8006969C_jp();
// void func_80069750_jp();
// void func_80069778_jp();
// void func_800698C0_jp();
// void func_80069948_jp();
// void func_800699D8_jp();
// void func_80069C00_jp();
// void func_80069C4C_jp();
// void func_80069EF4_jp();
// void func_80069F20_jp();
// void func_8006A13C_jp();
// void func_8006A174_jp();
// void func_8006A490_jp();
// void func_8006A6FC_jp();
// void func_8006A760_jp();
// void func_8006A7B4_jp();
// void func_8006AA94_jp();
// void func_8006AAAC_jp();
// void func_8006AB50_jp();
// void func_8006AB9C_jp();
// void func_8006ABFC_jp();
// void func_8006AC74_jp();
// void func_8006ACF4_jp();
// void func_8006AD0C_jp();
// void func_8006AD58_jp();
// void func_8006ADA8_jp();
// void func_8006AF00_jp();
// void func_8006AF14_jp();
// void func_8006AF54_jp();
// void func_8006B1A8_jp();
// void func_8006B39C_jp();
// void func_8006B5C0_jp();
// void func_8006B664_jp();
// void func_8006B92C_jp();
s32 mCoBG_RegistMoveBg(s8* arg0, struct PosRot* arg1, xyz_t* arg2, s16* arg3, f32 arg4, s32 arg5, s32 arg6, s32 arg7,
                       s32 arg8, s32 arg9, s32 argA, f32 argB);
// void func_8006BAA8_jp();
void mCoBG_CrossOffMoveBg(s32 arg0, struct Actor* actor);
void func_8006BB64_jp(void);
// void func_8006BB9C_jp();
// void func_8006BBE8_jp();
// void func_8006BBF8_jp();
// void func_8006BC20_jp();
// void func_8006BC54_jp();
// void func_8006BCB8_jp();
// void func_8006BD00_jp();
// void func_8006BE78_jp();
// void func_8006BF0C_jp();
// void func_8006C4B4_jp();
// void func_8006C5A8_jp();
// void func_8006C634_jp();
void mCoBG_CalcTimerDecalCircle(void);
// void func_8006C7B4_jp();
void func_8006C8D0_jp(void);
// void func_8006C910_jp();
// void func_8006C980_jp();
// void func_8006D3B0_jp();
// void func_8006D478_jp();
// void func_8006D65C_jp();
// void func_8006D7F4_jp();
// void func_8006D80C_jp();
// void func_8006D854_jp();
// void func_8006D9C0_jp();
// void func_8006DA1C_jp();
// void func_8006DE00_jp();
// void func_8006DF40_jp();
// void func_8006DF9C_jp();
// void func_8006DFE4_jp();
// void func_8006E0AC_jp();
// void func_8006E2DC_jp();
// void func_8006E30C_jp();
// void func_8006E374_jp();
// void func_8006E4B4_jp();
// void func_8006E548_jp();
// void func_8006E7A4_jp();
// void func_8006E8CC_jp();
// void func_8006E900_jp();
// void func_8006EA38_jp();
// void func_8006EAE8_jp();
// void func_8006EBA0_jp();
// void func_8006EDC0_jp();
// void func_8006EE70_jp();
// void func_8006EFB4_jp();
// void func_8006F250_jp();
// void func_8006F36C_jp();
// void func_8006F540_jp();
// void func_8006F62C_jp();
// void func_8006F928_jp();
// void func_8006FE98_jp();
// void func_80070290_jp();
// void func_80070590_jp();
// void func_8007071C_jp();
// void func_8007073C_jp();
// void func_8007075C_jp();
// void func_80070880_jp();
// void func_80070950_jp();
// void func_80070990_jp();
// void func_800709A8_jp();
// void func_800709E8_jp();
// void func_80070A28_jp();
// void func_80070AE4_jp();
// void func_80070C68_jp();
// void func_80070D28_jp();
// void func_80070F5C_jp();
// void func_80070FBC_jp();
// void func_80071064_jp();
// void func_800713CC_jp();
// void func_80071460_jp();
f32 mCoBG_GetShadowBgY_AngleS_FromWpos(s_xyz*, xyz_t, f32);
// void func_800715B4_jp();
// void func_80071604_jp();
// void func_80071728_jp();
// void func_8007175C_jp();
f32 mCoBG_GetBgY_AngleS_FromWpos(s_xyz* angleToGround, xyz_t wpos, f32 offsetY);
f32 mCoBG_GetBgY_OnlyCenter_FromWpos(xyz_t arg0, f32 arg1);
// void func_80071AB8_jp();
f32 mCoBG_GetBgY_OnlyCenter_FromWpos2(xyz_t arg0, f32 arg1);
void mCoBG_GetBgNorm_FromWpos(xyz_t*, xyz_t);
// void func_80071DB4_jp();
// void func_800721C8_jp();
// void func_800721E4_jp();
// void func_80072238_jp();
s32 mCoBG_Attribute2CheckPlant(u32 attribute, const xyz_t* wpos); // void func_80072264_jp();
// void func_80072340_jp();
// void func_80072398_jp();
// void func_800723C4_jp();
// void func_80072418_jp();
s32 func_8007244C_jp(u32);
// void func_8007246C_jp();
// void func_8007249C_jp();
// void func_80072530_jp();
// void func_800725C4_jp();
// void func_80072610_jp();
// void func_800727D8_jp();
// void func_80072828_jp();
// void func_80072880_jp();
// void func_800728B4_jp();
// void func_800728F4_jp();
// void func_80072938_jp();
// void func_80072990_jp();
// void func_80072B24_jp();
// void func_80072BE8_jp();
// void func_80072C60_jp();
s32 mCoBG_SearchWaterLimitDistN(UNK_TYPE* arg0, xyz_t arg1, s16 arg4, f32 arg5, s32 arg6);
// void func_80072E70_jp();
f32 mCoBG_GetBalloonGroundY(xyz_t*);
s32 mCoBG_CheckAttribute_BallRolling(s16*, xyz_t*);
// void func_800731A8_jp();
f32 mCoBG_CheckBallRollingArea(s16, xyz_t*);
// void func_800734BC_jp();
s32 mCoBG_ExistHeightGap_KeepAndNow_Detail(xyz_t);
// void func_80073680_jp();
// void func_80073718_jp();
// void func_80073784_jp();
// void func_800737D4_jp();
// void func_80073800_jp();
// void func_800738A4_jp();
// void func_80073970_jp();
void mCoBG_SetPlussOffset(xyz_t, s32, s32);
// void func_80073C38_jp();
// void func_80073CC0_jp();
void mCoBG_SetPluss5PointOffset_file(xyz_t pos, mCoBG_unkStruct2 arg1, char* file, s32 line);
// void func_80074090_jp();
// void func_80074174_jp();
// void func_800741DC_jp();
// void func_800741F4_jp();
// void func_80074208_jp();
// void func_800743EC_jp();
// void func_80074648_jp();
// void func_80074690_jp();
// void func_80074860_jp();
// void func_800749D0_jp();
// void func_800749F8_jp();
// void func_80074AA8_jp();
// void func_80074BA0_jp();
// void func_80074D88_jp();
// void func_80074EEC_jp();
// void func_8007532C_jp();
// void func_800753B8_jp();
// void func_8007584C_jp();
// void func_80075954_jp();
// void func_80075A10_jp();
// void func_80075AB4_jp();
// void func_80075B28_jp();
f32 mCoBG_GetWaterHeight_File(xyz_t, char*, s32);
// void func_8007620C_jp();
// void func_80076248_jp();
// void func_80076270_jp();
// void func_80076280_jp();
void mCoBG_GetWaterFlow(xyz_t*, u32);
s32 func_80076358_jp(u32 attribute);
// void func_8007638C_jp();
// void func_800763F0_jp();
// void func_800763FC_jp();
// void func_8007648C_jp();
// void func_800764CC_jp();
void mCoBG_BgCheckControll(xyz_t*, struct Actor*, f32, f32, s32, s32, s32);
void func_80076778_jp(s32, struct Actor*, f32, f32, s32, s32);
// void func_800768C8_jp();
// void func_80076A04_jp();

#endif
