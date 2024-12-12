#ifndef M_RANDOM_FIELD_H
#define M_RANDOM_FIELD_H

#include "ultra64.h"


#define RANDOM_FIELD_BLOCKKIND_SHRINE (1 << 2)

#define RANDOM_FIELD_BLOCK_TYPE_MAX 108 
#define RANDOM_FIELD_DIRECT_ERROR 100

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

typedef enum RandomFieldDirection {
  /* 0 */ RANDOM_FIELD_DIRECT_NORTH,
  /* 1 */ RANDOM_FIELD_DIRECT_WEST,
  /* 2 */ RANDOM_FIELD_DIRECT_SOUTH,
  /* 3 */ RANDOM_FIELD_DIRECT_EAST,

  /* 4 */ RANDOM_FIELD_DIRECT_NUM
} RandomFieldDirection;

typedef struct RandomFieldGate {
  /* 0x00 */ s32 ut0;
  /* 0x04 */ s32 ut1;
} RandomFieldGate;

#define mRF_BLOCKKIND_NONE (0 << 0)
#define mRF_BLOCKKIND_PLAYER (1 << 0) // Player houses
#define mRF_BLOCKKIND_SHOP (1 << 1)
#define mRF_BLOCKKIND_SHRINE (1 << 2)
#define mRF_BLOCKKIND_POLICE (1 << 3)
#define mRF_BLOCKKIND_POSTOFFICE (1 << 4)
#define mRF_BLOCKKIND_STATION (1 << 5)
#define mRF_BLOCKKIND_CLIFF (1 << 6)
#define mRF_BLOCKKIND_RIVER (1 << 7)
#define mRF_BLOCKKIND_WATERFALL (1 << 8)
#define mRF_BLOCKKIND_BRIDGE (1 << 9)
#define mRF_BLOCKKIND_RAILROAD (1 << 10)
#define mRF_BLOCKKIND_MARINE (1 << 11) // Beach
#define mRF_BLOCKKIND_BORDER (1 << 12)
#define mRF_BLOCKKIND_TUNNEL (1 << 13)
#define mRF_BLOCKKIND_SLOPE (1 << 14)
#define mRF_BLOCKKIND_POOL (1 << 15) // The large pond, not the small pools
#define mRF_BLOCKKIND_DUMP (1 << 16)
#define mRF_BLOCKKIND_RIVER0 (1 << 17) // Flows south
#define mRF_BLOCKKIND_RIVER1 (1 << 18) // Flows east
#define mRF_BLOCKKIND_RIVER2 (1 << 19) // Flows west
#define mRF_BLOCKKIND_RIVER3 (1 << 20) // Flows south then east
#define mRF_BLOCKKIND_RIVER4 (1 << 21) // Flows east then south
#define mRF_BLOCKKIND_RIVER5 (1 << 22) // Flows south then west
#define mRF_BLOCKKIND_RIVER6 (1 << 23) // Flows west then south
#define mRF_BLOCKKIND_CLIFF0 (1 << 24) // Cliff that goes horizontally in an arc across entire block
#define mRF_BLOCKKIND_CLIFF1 (1 << 25) // Bottom part of cliff which juts out, valley on right
#define mRF_BLOCKKIND_CLIFF2 (1 << 26) // Cliff that goes vertically across entire block, valley on right
#define mRF_BLOCKKIND_CLIFF3 (1 << 27) // Top part of cliff which juts out, valley on right
#define mRF_BLOCKKIND_CLIFF4 (1 << 28) // Top part of cliff which juts out, valley on left
#define mRF_BLOCKKIND_CLIFF5 (1 << 29) // Cliff that goes vertically across entire block, valley on left
#define mRF_BLOCKKIND_CLIFF6 (1 << 30) // Bottom part of cliff that juts out, valley on left
#define mRF_BLOCKKIND_31 (1 << 31) // Not used in `mRF_block_info`

// void func_800BCBA0_jp();
// void func_800BCBDC_jp();
// void func_800BCC20_jp();
// void func_800BCC30_jp();
// void func_800BCC40_jp();
// void func_800BCCFC_jp();
s32 mRF_Type2BlockInfo(u8 type);
// void func_800BCDFC_jp();
// void func_800BCE80_jp();
// void func_800BCEA4_jp();
// void func_800BCF64_jp();
// void func_800BCFA4_jp();
RandomFieldGate* mRF_BlockTypeDirect2GateData(s32*, u8, s32);
// void func_800BD02C_jp();
// void func_800BD1E4_jp();

#endif
