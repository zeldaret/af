#ifndef M_FIELD_MAKE_H
#define M_FIELD_MAKE_H

#include "ultra64.h"
#include "unk.h"
#include "m_collision_bg.h"

struct Game;

#define BLOCK_X_NUM 7
#define BLOCK_Z_NUM 8
#define BLOCK_TOTAL_NUM (BLOCK_X_NUM * BLOCK_Z_NUM)

#define FG_BLOCK_X_NUM (BLOCK_X_NUM - 2) /* 5 */
#define FG_BLOCK_Z_NUM (BLOCK_Z_NUM - 2) /* 6 */
#define FG_BLOCK_TOTAL_NUM (FG_BLOCK_X_NUM * FG_BLOCK_Z_NUM)

#define UT_BASE_NUM 16
#define UT_X_NUM UT_BASE_NUM /* Spaces per block (acre) in x direction */
#define UT_Z_NUM UT_BASE_NUM /* Spaces per block (acre) in z direction */
#define UT_TOTAL_NUM (UT_X_NUM * UT_Z_NUM)

/*
 * Naming convention for `RIVER`/`POOL`: directions indicated are flow of river
 * (e.g. `RIVER_SOUTH` indicates a river that flows south through entire block,
 * `RIVER_WEST_SOUTH` indicates a river that flows west and then south, etc.)
 *
 * Naming convention for `CLIFF`: direction indicated is side with valley
 * (e.g. `CORNER_RIGHT_TOP` indicates the top part of a corner cliff
 * with the valley on the right). However, directions for border cliffs simply
 * indicate the side of the map.
 */
typedef enum FieldMakeBlockType {
    /* 0x00 */ mFM_BLOCK_TYPE_BORDER_CLIFF_TOP,
    /* 0x01 */ mFM_BLOCK_TYPE_BORDER_CLIFF_RIVER,
    /* 0x02 */ mFM_BLOCK_TYPE_BORDER_CLIFF_LEFT,
    /* 0x03 */ mFM_BLOCK_TYPE_3, // Unused (no entries in `data_combi_table`)
    /* 0x04 */ mFM_BLOCK_TYPE_BORDER_CLIFF_RIGHT,
    /* 0x05 */ mFM_BLOCK_TYPE_BORDER_CLIFF_CORNER_TOP_LEFT,
    /* 0x06 */ mFM_BLOCK_TYPE_6, // Unused (no entries in `data_combi_table`)
    /* 0x07 */ mFM_BLOCK_TYPE_7, // Unused (no entries in `data_combi_table`)
    /* 0x08 */ mFM_BLOCK_TYPE_BORDER_CLIFF_CORNER_TOP_RIGHT,
    /* 0x09 */ mFM_BLOCK_TYPE_BORDER_CLIFF_TUNNEL_LEFT,
    /* 0x0A */ mFM_BLOCK_TYPE_BORDER_CLIFF_TUNNEL_RIGHT,
    /* 0x0B */ mFM_BLOCK_TYPE_TRACKS_STATION,
    /* 0x0C */ mFM_BLOCK_TYPE_TRACKS_DUMP,
    /* 0x0D */ mFM_BLOCK_TYPE_TRACKS_RIVER,
    /* 0x0E */ mFM_BLOCK_TYPE_PLAYER_HOUSE,
    /* 0x0F */ mFM_BLOCK_TYPE_CLIFF_HORIZONTAL,
    /* 0x10 */ mFM_BLOCK_TYPE_CLIFF_CORNER_RIGHT_BOTTOM,
    /* 0x11 */ mFM_BLOCK_TYPE_CLIFF_VERTICAL_RIGHT,
    /* 0x12 */ mFM_BLOCK_TYPE_CLIFF_CORNER_RIGHT_TOP,
    /* 0x13 */ mFM_BLOCK_TYPE_CLIFF_CORNER_LEFT_TOP,
    /* 0x14 */ mFM_BLOCK_TYPE_CLIFF_VERTICAL_LEFT,
    /* 0x15 */ mFM_BLOCK_TYPE_CLIFF_CORNER_LEFT_BOTTOM,
    /* 0x16 */ mFM_BLOCK_TYPE_WATERFALL_SOUTH_CLIFF_HORIZONTAL,
    /* 0x17 */ mFM_BLOCK_TYPE_WATERFALL_SOUTH_CLIFF_CORNER_RIGHT_BOTTOM,
    /* 0x18 */ mFM_BLOCK_TYPE_RIVER_SOUTH_CLIFF_VERTICAL_RIGHT,
    /* 0x19 */ mFM_BLOCK_TYPE_RIVER_SOUTH_CLIFF_CORNER_RIGHT_TOP,
    /* 0x1A */ mFM_BLOCK_TYPE_WATERFALL_SOUTH_CLIFF_CORNER_LEFT_TOP,
    /* 0x1B */ mFM_BLOCK_TYPE_RIVER_SOUTH_CLIFF_VERTICAL_LEFT,
    /* 0x1C */ mFM_BLOCK_TYPE_RIVER_SOUTH_CLIFF_CORNER_LEFT_BOTTOM,
    /* 0x1D */ mFM_BLOCK_TYPE_RIVER_EAST_CLIFF_HORIZONTAL, // Correct according to ACSE, should be verified in-game
    /* 0x1E */ mFM_BLOCK_TYPE_WATERFALL_EAST_CLIFF_CORNER_RIGHT_BOTTOM,
    /* 0x1F */ mFM_BLOCK_TYPE_WATERFALL_EAST_CLIFF_VERTICAL_RIGHT,
    /* 0x20 */ mFM_BLOCK_TYPE_RIVER_EAST_CLIFF_CORNER_RIGHT_TOP,
    /* 0x21 */ mFM_BLOCK_TYPE_RIVER_EAST_CLIFF_CORNER_LEFT_TOP,
    /* 0x22 */ mFM_BLOCK_TYPE_RIVER_WEST_CLIFF_HORIZONTAL,
    /* 0x23 */ mFM_BLOCK_TYPE_RIVER_WEST_CLIFF_CORNER_RIGHT_TOP,
    /* 0x24 */ mFM_BLOCK_TYPE_RIVER_WEST_CLIFF_CORNER_LEFT_TOP,
    /* 0x25 */ mFM_BLOCK_TYPE_WATERFALL_WEST_CLIFF_VERTICAL_LEFT,
    /* 0x26 */ mFM_BLOCK_TYPE_WATERFALL_WEST_CLIFF_CORNER_LEFT_BOTTOM,
    /* 0x27 */ mFM_BLOCK_TYPE_FLAT, // Grassy field
    /* 0x28 */ mFM_BLOCK_TYPE_RIVER_SOUTH,
    /* 0x29 */ mFM_BLOCK_TYPE_RIVER_EAST,
    /* 0x2A */ mFM_BLOCK_TYPE_RIVER_WEST,
    /* 0x2B */ mFM_BLOCK_TYPE_RIVER_SOUTH_EAST,
    /* 0x2C */ mFM_BLOCK_TYPE_RIVER_EAST_SOUTH,
    /* 0x2D */ mFM_BLOCK_TYPE_RIVER_SOUTH_WEST,
    /* 0x2E */ mFM_BLOCK_TYPE_RIVER_WEST_SOUTH,
    /* 0x2F */ mFM_BLOCK_TYPE_RIVER_SOUTH_BRIDGE,
    /* 0x30 */ mFM_BLOCK_TYPE_RIVER_EAST_BRIDGE,
    /* 0x31 */ mFM_BLOCK_TYPE_RIVER_WEST_BRIDGE,
    /* 0x32 */ mFM_BLOCK_TYPE_RIVER_SOUTH_EAST_BRIDGE,
    /* 0x33 */ mFM_BLOCK_TYPE_RIVER_EAST_SOUTH_BRIDGE,
    /* 0x34 */ mFM_BLOCK_TYPE_RIVER_SOUTH_WEST_BRIDGE,
    /* 0x35 */ mFM_BLOCK_TYPE_RIVER_WEST_SOUTH_BRIDGE,
    /* 0x36 */ mFM_BLOCK_TYPE_SLOPE_HORIZONTAL,
    /* 0x37 */ mFM_BLOCK_TYPE_SLOPE_CORNER_RIGHT_BOTTOM,
    /* 0x38 */ mFM_BLOCK_TYPE_SLOPE_VERTICAL_RIGHT,
    /* 0x39 */ mFM_BLOCK_TYPE_SLOPE_CORNER_RIGHT_TOP,
    /* 0x3A */ mFM_BLOCK_TYPE_SLOPE_CORNER_LEFT_TOP,
    /* 0x3B */ mFM_BLOCK_TYPE_SLOPE_VERTICAL_LEFT,
    /* 0x3C */ mFM_BLOCK_TYPE_SLOPE_CORNER_LEFT_BOTTOM,
    /* 0x3D */ mFM_BLOCK_TYPE_BORDER_CLIFF_TRANSITION_LEFT,
    /* 0x3E */ mFM_BLOCK_TYPE_BORDER_CLIFF_TRANSITION_RIGHT,
    /* 0x3F */ mFM_BLOCK_TYPE_BEACH,
    /* 0x40 */ mFM_BLOCK_TYPE_BEACH_RIVER,
    /* 0x41 */ mFM_BLOCK_TYPE_SHOP,
    /* 0x42 */ mFM_BLOCK_TYPE_SHRINE,
    /* 0x43 */ mFM_BLOCK_TYPE_POST_OFFICE,
    /* 0x44 */ mFM_BLOCK_TYPE_POLICE_BOX,
    /* 0x45 */ mFM_BLOCK_TYPE_POOL_SOUTH,
    /* 0x46 */ mFM_BLOCK_TYPE_POOL_EAST,
    /* 0x47 */ mFM_BLOCK_TYPE_POOL_WEST,
    /* 0x48 */ mFM_BLOCK_TYPE_POOL_SOUTH_EAST,
    /* 0x49 */ mFM_BLOCK_TYPE_POOL_EAST_SOUTH,
    /* 0x4A */ mFM_BLOCK_TYPE_POOL_SOUTH_WEST,
    /* 0x4B */ mFM_BLOCK_TYPE_POOL_WEST_SOUTH,
    /* 0x4C */ mFM_BLOCK_TYPE_76,
    /* 0x4D */ mFM_BLOCK_TYPE_77,
    /* 0x4E */ mFM_BLOCK_TYPE_78,
    /* 0x4F */ mFM_BLOCK_TYPE_79,
    /* 0x50 */ mFM_BLOCK_TYPE_BORDER_CLIFF_OCEAN_LEFT,
    /* 0x51 */ mFM_BLOCK_TYPE_BORDER_CLIFF_OCEAN_RIGHT,
    /* 0x52 */ mFM_BLOCK_TYPE_BEACH_RIVER_BRIDGE,
    /* 0x53 */ mFM_BLOCK_TYPE_OCEAN,

    /* 0x54 */ mFM_BLOCK_TYPE_NUM,

    /* 0xFF */ mFM_BLOCK_TYPE_NONE = 0xFF
} FieldMakeBlockType;

extern u8* g_block_type_p;
extern u32* g_block_kind_p; // s32 in ac-decomp--if problems arise, try changing type

typedef struct Foreground {
    /* 0x000 */ u16 items[UT_Z_NUM][UT_X_NUM];
} Foreground; // size = 0x200

typedef struct FieldMakeMoveActor {
    /* 0x0 */ u16 nameId;
    /* 0x2 */ s8 utX;
    /* 0x3 */ s8 utZ;
    /* 0x4 */ s8 npcId;
    /* 0x6 */ s16 arg;
} FieldMakeMoveActor; // size = 0x8

typedef struct FieldMakeFGData {
    /* 0x000 */ u16 id;
    /* 0x002 */ u16 items[UT_Z_NUM][UT_X_NUM];
    /* 0x202 */ UNK_TYPE1 unk_202[4];
} FieldMakeFGData; // size = 0x206

typedef struct FieldMakeFGInfo {
    /* 0x00 */ u16 fgId;
    /* 0x04 */ u16* itemsPtr;
    /* 0x08 */ UNK_TYPE1 unk_08[0x8C];
} FieldMakeFGInfo; // size = 0x94

typedef struct FieldMakeBGInfo {
    /* 0x000 */ UNK_TYPE1 unk_000[0x14];
    /* 0x014 */ u32 blockKind;
    /* 0x018 */ UNK_TYPE1 unk_018[0x08];
    /* 0x020 */ mCoBG_unkStructUnion collision[UT_Z_NUM][UT_X_NUM];
    /* 0x420 */ UNK_TYPE1 unk_024[0x160];
} FieldMakeBGInfo; // size >= 0x57d

typedef struct FieldMakeBlockInfo {
    /* 0x000 */ FieldMakeBGInfo bgInfo;
    /* 0x580 */ FieldMakeFGInfo fgInfo;
} FieldMakeBlockInfo; // size = 0x614

typedef struct FieldMakeInfo {
    /* 0x000 */ u16 fieldId;
    /* 0x002 */ UNK_TYPE1 unk_000[0x146];
    /* 0x148 */ FieldMakeBlockInfo* blockInfo;
    /* 0x14C */ UNK_TYPE1 unk_14C[0x1A];
    /* 0x166 */ u8 blockXMax;
    /* 0x167 */ u8 blockZMax;
} FieldMakeInfo; // size >= 0x168

// void func_80084ED0_jp();
// void func_80084FAC_jp();
// void func_800850E4_jp();
// void func_80085178_jp();
// void func_800851C8_jp();
// void func_800853CC_jp();
// void func_80085490_jp();
// void func_8008557C_jp();
// void func_800855D0_jp();
// void func_80085918_jp();
// void func_800859F4_jp();
// void func_80085A84_jp();
// void func_80085B40_jp();
// void func_80085CC0_jp();
// void func_80085D44_jp();
// void func_80085D64_jp();
// void func_80085D94_jp();
// void func_80085FF0_jp();
// void func_8008609C_jp();
// void func_800862DC_jp();
// void func_8008640C_jp();
// void func_800865D0_jp();
// void func_800867F0_jp();
// void func_80086BD0_jp();
// void func_80086CA4_jp();
// void func_80086D44_jp();
// void func_80086DE0_jp();
// void func_80086E30_jp();
// void func_80086F08_jp();
// void func_80086FA8_jp();
void mFM_SetFieldInitData(s32, s32);
void func_80087004_jp(void);
void func_80087280_jp(void);
// void func_80087380_jp();
void mFM_SetBlockKindLoadCombi(struct Game* game);
void mFM_InitFgCombiSaveData(struct Game* game);
// void func_80087754_jp();
// void func_8008775C_jp();
// void func_80087788_jp();
// void func_800877CC_jp();
void mFM_RenewalReserve(void);
u16 mFM_GetReseveName(s32,s32);

#endif
