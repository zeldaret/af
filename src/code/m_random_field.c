#include "global.h"
#include "m_common_data.h"
#include "m_random_field.h"
#include "m_field_make.h"
#include "m_field_info.h"
#include "m_scene_table.h"
#include "m_malloc.h"
#include "gamealloc.h"
#include "game.h"

// Original name unknown.
void mRF_Malloc(Game* game, size_t size) {
    if (game != NULL) {
        gamealloc_malloc(&game->alloc, size);

        return;
    }

    zelda_malloc(size);
}

// Original name unknown.
void mRF_Free(Game* game, void* ptr) {
    if (ptr != NULL) {
        if (game != NULL) {
            gamealloc_free(&game->alloc, ptr);

            return;
        }

        zelda_free(ptr);
    }
}

extern s32 D_8010C6C4_jp;

// Original name unknown.
s32* func_800BCC20_jp(void) {
    return &D_8010C6C4_jp;
}

extern s32 D_8010C6C8_jp;

// Original name unknown.
s32* func_800BCC30_jp(void) {
    return &D_8010C6C8_jp;
}

// TODO: import data
#if 0
u32 mRF_block_info[mFM_BLOCK_TYPE_NUM] = {
    /* 0x00 */ mRF_BLOCKKIND_BORDER,
    /* 0x01 */ mRF_BLOCKKIND_BORDER,
    /* 0x02 */ mRF_BLOCKKIND_BORDER,
    /* 0x03 */ mRF_BLOCKKIND_BORDER,
    /* 0x04 */ mRF_BLOCKKIND_BORDER,
    /* 0x05 */ mRF_BLOCKKIND_BORDER,
    /* 0x06 */ mRF_BLOCKKIND_BORDER,
    /* 0x07 */ mRF_BLOCKKIND_BORDER,
    /* 0x08 */ mRF_BLOCKKIND_BORDER,
    /* 0x09 */ mRF_BLOCKKIND_RAILROAD | mRF_BLOCKKIND_TUNNEL,
    /* 0x0a */ mRF_BLOCKKIND_RAILROAD | mRF_BLOCKKIND_TUNNEL,
    /* 0x0b */ mRF_BLOCKKIND_STATION | mRF_BLOCKKIND_RAILROAD,
    /* 0x0c */ mRF_BLOCKKIND_RAILROAD | mRF_BLOCKKIND_DUMP,
    /* 0x0d */ mRF_BLOCKKIND_RIVER | mRF_BLOCKKIND_RAILROAD,
    /* 0x0e */ mRF_BLOCKKIND_PLAYER,
    /* 0x0f */ mRF_BLOCKKIND_CLIFF | mRF_BLOCKKIND_CLIFF0,
    /* 0x10 */ mRF_BLOCKKIND_CLIFF | mRF_BLOCKKIND_CLIFF1,
    /* 0x11 */ mRF_BLOCKKIND_CLIFF | mRF_BLOCKKIND_CLIFF2,
    /* 0x12 */ mRF_BLOCKKIND_CLIFF | mRF_BLOCKKIND_CLIFF3,
    /* 0x13 */ mRF_BLOCKKIND_CLIFF | mRF_BLOCKKIND_CLIFF4,
    /* 0x14 */ mRF_BLOCKKIND_CLIFF | mRF_BLOCKKIND_CLIFF5,
    /* 0x15 */ mRF_BLOCKKIND_CLIFF | mRF_BLOCKKIND_CLIFF6,
    /* 0x16 */ mRF_BLOCKKIND_CLIFF | mRF_BLOCKKIND_RIVER | mRF_BLOCKKIND_WATERFALL | mRF_BLOCKKIND_RIVER0 |
        mRF_BLOCKKIND_CLIFF0,
    /* 0x17 */ mRF_BLOCKKIND_CLIFF | mRF_BLOCKKIND_RIVER | mRF_BLOCKKIND_WATERFALL | mRF_BLOCKKIND_RIVER1 |
        mRF_BLOCKKIND_CLIFF0,
    /* 0x18 */ mRF_BLOCKKIND_CLIFF | mRF_BLOCKKIND_RIVER | mRF_BLOCKKIND_RIVER0 | mRF_BLOCKKIND_CLIFF2,
    /* 0x19 */ mRF_BLOCKKIND_CLIFF | mRF_BLOCKKIND_RIVER | mRF_BLOCKKIND_RIVER0 | mRF_BLOCKKIND_CLIFF3,
    /* 0x1a */ mRF_BLOCKKIND_CLIFF | mRF_BLOCKKIND_RIVER | mRF_BLOCKKIND_WATERFALL | mRF_BLOCKKIND_RIVER0 |
        mRF_BLOCKKIND_CLIFF4,
    /* 0x1b */ mRF_BLOCKKIND_CLIFF | mRF_BLOCKKIND_RIVER | mRF_BLOCKKIND_RIVER0 | mRF_BLOCKKIND_CLIFF5,
    /* 0x1c */ mRF_BLOCKKIND_CLIFF | mRF_BLOCKKIND_RIVER | mRF_BLOCKKIND_RIVER0 | mRF_BLOCKKIND_CLIFF6,
    /* 0x1d */ mRF_BLOCKKIND_CLIFF | mRF_BLOCKKIND_RIVER | mRF_BLOCKKIND_RIVER1 | mRF_BLOCKKIND_CLIFF0,
    /* 0x1e */ mRF_BLOCKKIND_CLIFF | mRF_BLOCKKIND_RIVER | mRF_BLOCKKIND_WATERFALL | mRF_BLOCKKIND_RIVER1 |
        mRF_BLOCKKIND_CLIFF1,
    /* 0x1f */ mRF_BLOCKKIND_CLIFF | mRF_BLOCKKIND_RIVER | mRF_BLOCKKIND_WATERFALL | mRF_BLOCKKIND_RIVER1 |
        mRF_BLOCKKIND_CLIFF2,
    /* 0x20 */ mRF_BLOCKKIND_CLIFF | mRF_BLOCKKIND_RIVER | mRF_BLOCKKIND_RIVER1 | mRF_BLOCKKIND_CLIFF3,
    /* 0x21 */ mRF_BLOCKKIND_CLIFF | mRF_BLOCKKIND_RIVER | mRF_BLOCKKIND_RIVER1 | mRF_BLOCKKIND_CLIFF4,
    /* 0x22 */ mRF_BLOCKKIND_CLIFF | mRF_BLOCKKIND_RIVER | mRF_BLOCKKIND_RIVER2 | mRF_BLOCKKIND_CLIFF0,
    /* 0x23 */ mRF_BLOCKKIND_CLIFF | mRF_BLOCKKIND_RIVER | mRF_BLOCKKIND_RIVER2 | mRF_BLOCKKIND_CLIFF3,
    /* 0x24 */ mRF_BLOCKKIND_CLIFF | mRF_BLOCKKIND_RIVER | mRF_BLOCKKIND_RIVER2 | mRF_BLOCKKIND_CLIFF4,
    /* 0x25 */ mRF_BLOCKKIND_CLIFF | mRF_BLOCKKIND_RIVER | mRF_BLOCKKIND_WATERFALL | mRF_BLOCKKIND_RIVER2 |
        mRF_BLOCKKIND_CLIFF5,
    /* 0x26 */ mRF_BLOCKKIND_CLIFF | mRF_BLOCKKIND_RIVER | mRF_BLOCKKIND_WATERFALL | mRF_BLOCKKIND_RIVER2 |
        mRF_BLOCKKIND_CLIFF6,
    /* 0x27 */ mRF_BLOCKKIND_NONE,
    /* 0x28 */ mRF_BLOCKKIND_RIVER | mRF_BLOCKKIND_RIVER0,
    /* 0x29 */ mRF_BLOCKKIND_RIVER | mRF_BLOCKKIND_RIVER1,
    /* 0x2a */ mRF_BLOCKKIND_RIVER | mRF_BLOCKKIND_RIVER2,
    /* 0x2b */ mRF_BLOCKKIND_RIVER | mRF_BLOCKKIND_RIVER3,
    /* 0x2c */ mRF_BLOCKKIND_RIVER | mRF_BLOCKKIND_RIVER4,
    /* 0x2d */ mRF_BLOCKKIND_RIVER | mRF_BLOCKKIND_RIVER5,
    /* 0x2e */ mRF_BLOCKKIND_RIVER | mRF_BLOCKKIND_RIVER6,
    /* 0x2f */ mRF_BLOCKKIND_RIVER | mRF_BLOCKKIND_BRIDGE | mRF_BLOCKKIND_RIVER0,
    /* 0x30 */ mRF_BLOCKKIND_RIVER | mRF_BLOCKKIND_BRIDGE | mRF_BLOCKKIND_RIVER1,
    /* 0x31 */ mRF_BLOCKKIND_RIVER | mRF_BLOCKKIND_BRIDGE | mRF_BLOCKKIND_RIVER2,
    /* 0x32 */ mRF_BLOCKKIND_RIVER | mRF_BLOCKKIND_BRIDGE | mRF_BLOCKKIND_RIVER3,
    /* 0x33 */ mRF_BLOCKKIND_RIVER | mRF_BLOCKKIND_BRIDGE | mRF_BLOCKKIND_RIVER4,
    /* 0x34 */ mRF_BLOCKKIND_RIVER | mRF_BLOCKKIND_BRIDGE | mRF_BLOCKKIND_RIVER5,
    /* 0x35 */ mRF_BLOCKKIND_RIVER | mRF_BLOCKKIND_BRIDGE | mRF_BLOCKKIND_RIVER6,
    /* 0x36 */ mRF_BLOCKKIND_CLIFF | mRF_BLOCKKIND_SLOPE | mRF_BLOCKKIND_CLIFF0,
    /* 0x37 */ mRF_BLOCKKIND_CLIFF | mRF_BLOCKKIND_SLOPE | mRF_BLOCKKIND_CLIFF1,
    /* 0x38 */ mRF_BLOCKKIND_CLIFF | mRF_BLOCKKIND_SLOPE | mRF_BLOCKKIND_CLIFF2,
    /* 0x39 */ mRF_BLOCKKIND_CLIFF | mRF_BLOCKKIND_SLOPE | mRF_BLOCKKIND_CLIFF3,
    /* 0x3a */ mRF_BLOCKKIND_CLIFF | mRF_BLOCKKIND_SLOPE | mRF_BLOCKKIND_CLIFF4,
    /* 0x3b */ mRF_BLOCKKIND_CLIFF | mRF_BLOCKKIND_SLOPE | mRF_BLOCKKIND_CLIFF5,
    /* 0x3c */ mRF_BLOCKKIND_CLIFF | mRF_BLOCKKIND_SLOPE | mRF_BLOCKKIND_CLIFF6,
    /* 0x3d */ mRF_BLOCKKIND_CLIFF | mRF_BLOCKKIND_BORDER,
    /* 0x3e */ mRF_BLOCKKIND_CLIFF | mRF_BLOCKKIND_BORDER,
    /* 0x3f */ mRF_BLOCKKIND_MARINE,
    /* 0x40 */ mRF_BLOCKKIND_RIVER | mRF_BLOCKKIND_MARINE | mRF_BLOCKKIND_CLIFF0,
    /* 0x41 */ mRF_BLOCKKIND_SHOP,
    /* 0x42 */ mRF_BLOCKKIND_SHRINE,
    /* 0x43 */ mRF_BLOCKKIND_POSTOFFICE,
    /* 0x44 */ mRF_BLOCKKIND_POLICE,
    /* 0x45 */ mRF_BLOCKKIND_RIVER | mRF_BLOCKKIND_POOL | mRF_BLOCKKIND_RIVER0,
    /* 0x46 */ mRF_BLOCKKIND_RIVER | mRF_BLOCKKIND_POOL | mRF_BLOCKKIND_RIVER1,
    /* 0x47 */ mRF_BLOCKKIND_RIVER | mRF_BLOCKKIND_POOL | mRF_BLOCKKIND_RIVER2,
    /* 0x48 */ mRF_BLOCKKIND_RIVER | mRF_BLOCKKIND_POOL | mRF_BLOCKKIND_RIVER3,
    /* 0x49 */ mRF_BLOCKKIND_RIVER | mRF_BLOCKKIND_POOL | mRF_BLOCKKIND_RIVER4,
    /* 0x4a */ mRF_BLOCKKIND_RIVER | mRF_BLOCKKIND_POOL | mRF_BLOCKKIND_RIVER5,
    /* 0x4b */ mRF_BLOCKKIND_RIVER | mRF_BLOCKKIND_POOL | mRF_BLOCKKIND_RIVER6,
    /* 0x4c */ mRF_BLOCKKIND_BORDER,
    /* 0x4d */ mRF_BLOCKKIND_RIVER | mRF_BLOCKKIND_BORDER | mRF_BLOCKKIND_RIVER0,
    /* 0x4e */ mRF_BLOCKKIND_CLIFF | mRF_BLOCKKIND_BORDER | mRF_BLOCKKIND_CLIFF0,
    /* 0x4f */ mRF_BLOCKKIND_RAILROAD | mRF_BLOCKKIND_BORDER,
    /* 0x50 */ mRF_BLOCKKIND_MARINE | mRF_BLOCKKIND_BORDER,
    /* 0x51 */ mRF_BLOCKKIND_MARINE | mRF_BLOCKKIND_BORDER,
    /* 0x52 */ mRF_BLOCKKIND_RIVER | mRF_BLOCKKIND_BRIDGE | mRF_BLOCKKIND_MARINE | mRF_BLOCKKIND_RIVER0,
    /* 0x53 */ mRF_BLOCKKIND_NONE,
};


#define GATE_UT(z, x) ((((z) & 0xF) << 4) | ((x) & 0xF))
#define GATE(z0, x0, z1, x1) { GATE_UT(z0, x0), GATE_UT(z1, x1) }

RandomFieldGate gate1_type0_up[1] = { GATE(0, 7, 1, 7) };
RandomFieldGate gate1_type0_lt[1] = { GATE(7, 0, 7, 1) };
RandomFieldGate gate1_type0_dn[1] = { GATE(15, 7, 14, 7) };
RandomFieldGate gate1_type0_rt[1] = { GATE(7, 15, 7, 14) };

RandomFieldGate gate1_type1_up[1] = { GATE(0, 7, 1, 7) };
RandomFieldGate gate1_type1_lt[1] = { GATE(9, 0, 9, 1) };
RandomFieldGate gate1_type1_dn[1] = { GATE(15, 7, 14, 7) };
RandomFieldGate gate1_type1_rt[1] = { GATE(9, 15, 9, 14) };

RandomFieldGate gate2_type0_up[2] = { GATE(0, 5, 1, 5), GATE(0, 12, 1, 12) };
RandomFieldGate gate2_type0_lt[2] = { GATE(5, 0, 5, 1), GATE(12, 0, 12, 1) };
RandomFieldGate gate2_type0_dn[2] = { GATE(15, 5, 14, 5), GATE(15, 12, 14, 12) };
RandomFieldGate gate2_type0_rt[2] = { GATE(5, 15, 5, 14), GATE(12, 15, 12, 14) };

RandomFieldGate gate2_type1_up[2] = { GATE(0, 2, 1, 2), GATE(0, 11, 1, 11) };
RandomFieldGate gate2_type1_lt[2] = { GATE(2, 0, 2, 1), GATE(11, 0, 11, 1) };
RandomFieldGate gate2_type1_dn[2] = { GATE(15, 2, 14, 2), GATE(15, 11, 14, 11) };
RandomFieldGate gate2_type1_rt[2] = { GATE(2, 15, 2, 14), GATE(11, 15, 11, 14) };

RandomFieldGate gate3_type0_up[3] = { GATE(0, 2, 1, 2), GATE(0, 8, 1, 8), GATE(0, 12, 1, 12) };
RandomFieldGate gate3_type0_lt[3] = { GATE(2, 0, 2, 1), GATE(8, 0, 8, 1), GATE(12, 0, 12, 1) };
RandomFieldGate gate3_type0_dn[3] = { GATE(15, 2, 14, 2), GATE(15, 8, 14, 8), GATE(15, 12, 14, 12) };
RandomFieldGate gate3_type0_rt[3] = { GATE(2, 15, 2, 14), GATE(8, 15, 8, 14), GATE(12, 15, 12, 14) };

RandomFieldGate* RandomFieldGateorrect_info[mRF_GATE_TYPE_NUM][RANDOM_FIELD_DIRECT_NUM] = {
  { NULL, NULL, NULL, NULL },
  { gate1_type0_up, gate1_type0_lt, gate1_type0_dn, gate1_type0_rt },
  { gate1_type1_up, gate1_type1_lt, gate1_type1_dn, gate1_type1_rt },
  { gate2_type0_up, gate2_type0_lt, gate2_type0_dn, gate2_type0_rt },
  { gate2_type1_up, gate2_type1_lt, gate2_type1_dn, gate2_type1_rt },
  { gate3_type0_up, gate3_type0_lt, gate3_type0_dn, gate3_type0_rt },
};

// Order of gate types for each block is north, west, south, east.
// Provided indices correspond to block type, not struct size
u8 mRF_gate_info2[mFM_BLOCK_TYPE_NUM][RANDOM_FIELD_DIRECT_NUM] = {
    /* 0x00 */ {
        mRF_GATE_NONE,
        mRF_GATE_NONE,
        mRF_GATE_NONE,
        mRF_GATE_NONE
    },
    /* 0x01 */ {
        mRF_GATE_NONE,
        mRF_GATE_NONE,
        mRF_GATE_NONE,
        mRF_GATE_NONE
    },
    /* 0x02 */ {
        mRF_GATE_NONE,
        mRF_GATE_NONE,
        mRF_GATE_NONE,
        mRF_GATE_NONE
    },
    /* 0x03 */ {
        mRF_GATE_NONE,
        mRF_GATE_NONE,
        mRF_GATE_NONE,
        mRF_GATE_NONE
    },
    /* 0x04 */ {
        mRF_GATE_NONE,
        mRF_GATE_NONE,
        mRF_GATE_NONE,
        mRF_GATE_NONE
    },
    /* 0x05 */ {
        mRF_GATE_NONE,
        mRF_GATE_NONE,
        mRF_GATE_NONE,
        mRF_GATE_NONE
    },
    /* 0x06 */ {
        mRF_GATE_NONE,
        mRF_GATE_NONE,
        mRF_GATE_NONE,
        mRF_GATE_NONE
    },
    /* 0x07 */ {
        mRF_GATE_NONE,
        mRF_GATE_NONE,
        mRF_GATE_NONE,
        mRF_GATE_NONE
    },
    /* 0x08 */ {
        mRF_GATE_NONE,
        mRF_GATE_NONE,
        mRF_GATE_NONE,
        mRF_GATE_NONE
    },
    /* 0x09 */ {
        mRF_GATE_NONE,
        mRF_GATE_NONE,
        mRF_GATE_NONE,
        mRF_GATE_NONE
    },
    /* 0x0a */ {
        mRF_GATE_NONE,
        mRF_GATE_NONE,
        mRF_GATE_NONE,
        mRF_GATE_NONE
    },
    /* 0x0b */ {
        mRF_GATE_NONE,
        mRF_GATE1_TYPE1,
        mRF_GATE1_TYPE0,
        mRF_GATE1_TYPE1
    },
    /* 0x0c */ {
        mRF_GATE_NONE,
        mRF_GATE1_TYPE1,
        mRF_GATE1_TYPE0,
        mRF_GATE1_TYPE1
    },
    /* 0x0d */ {
        mRF_GATE_NONE,
        mRF_GATE1_TYPE1,
        mRF_GATE2_TYPE1,
        mRF_GATE1_TYPE1
    },
    /* 0x0e */ {
        mRF_GATE1_TYPE0,
        mRF_GATE1_TYPE0,
        mRF_GATE1_TYPE0,
        mRF_GATE1_TYPE0
    },
    /* 0x0f */ {
        mRF_GATE1_TYPE0,
        mRF_GATE2_TYPE0,
        mRF_GATE1_TYPE0,
        mRF_GATE2_TYPE0
    },
    /* 0x10 */ {
        mRF_GATE2_TYPE0,
        mRF_GATE2_TYPE0,
        mRF_GATE1_TYPE0,
        mRF_GATE1_TYPE0
    },
    /* 0x11 */ {
        mRF_GATE2_TYPE0,
        mRF_GATE1_TYPE0,
        mRF_GATE2_TYPE0,
        mRF_GATE1_TYPE0
    },
    /* 0x12 */ {
        mRF_GATE1_TYPE0,
        mRF_GATE1_TYPE0,
        mRF_GATE2_TYPE0,
        mRF_GATE2_TYPE0
    },
    /* 0x13 */ {
        mRF_GATE1_TYPE0,
        mRF_GATE2_TYPE0,
        mRF_GATE2_TYPE0,
        mRF_GATE1_TYPE0
    },
    /* 0x14 */ {
        mRF_GATE2_TYPE0,
        mRF_GATE1_TYPE0,
        mRF_GATE2_TYPE0,
        mRF_GATE1_TYPE0
    },
    /* 0x15 */ {
        mRF_GATE2_TYPE0,
        mRF_GATE1_TYPE0,
        mRF_GATE1_TYPE0,
        mRF_GATE2_TYPE0
    },
    /* 0x16 */ {
        mRF_GATE2_TYPE1,
        mRF_GATE2_TYPE0,
        mRF_GATE2_TYPE1,
        mRF_GATE2_TYPE0
    },
    /* 0x17 */ {
        mRF_GATE3_TYPE0,
        mRF_GATE2_TYPE0,
        mRF_GATE2_TYPE1,
        mRF_GATE1_TYPE0
    },
    /* 0x18 */ {
        mRF_GATE3_TYPE0,
        mRF_GATE1_TYPE0,
        mRF_GATE3_TYPE0,
        mRF_GATE1_TYPE0
    },
    /* 0x19 */ {
        mRF_GATE2_TYPE1,
        mRF_GATE1_TYPE0,
        mRF_GATE3_TYPE0,
        mRF_GATE2_TYPE0
    },
    /* 0x1a */ {
        mRF_GATE2_TYPE1,
        mRF_GATE2_TYPE0,
        mRF_GATE3_TYPE0,
        mRF_GATE1_TYPE0
    },
    /* 0x1b */ {
        mRF_GATE3_TYPE0,
        mRF_GATE1_TYPE0,
        mRF_GATE3_TYPE0,
        mRF_GATE1_TYPE0
    },
    /* 0x1c */ {
        mRF_GATE3_TYPE0,
        mRF_GATE1_TYPE0,
        mRF_GATE2_TYPE1,
        mRF_GATE2_TYPE0
    },
    /* 0x1d */ {
        mRF_GATE1_TYPE0,
        mRF_GATE3_TYPE0,
        mRF_GATE1_TYPE0,
        mRF_GATE3_TYPE0
    },
    /* 0x1e */ {
        mRF_GATE2_TYPE0,
        mRF_GATE3_TYPE0,
        mRF_GATE1_TYPE0,
        mRF_GATE2_TYPE1
    },
    /* 0x1f */ {
        mRF_GATE2_TYPE0,
        mRF_GATE2_TYPE1,
        mRF_GATE2_TYPE0,
        mRF_GATE2_TYPE1
    },
    /* 0x20 */ {
        mRF_GATE1_TYPE0,
        mRF_GATE2_TYPE1,
        mRF_GATE2_TYPE0,
        mRF_GATE3_TYPE0
    },
    /* 0x21 */ {
        mRF_GATE1_TYPE0,
        mRF_GATE3_TYPE0,
        mRF_GATE2_TYPE0,
        mRF_GATE2_TYPE1
    },
    /* 0x22 */ {
        mRF_GATE1_TYPE0,
        mRF_GATE3_TYPE0,
        mRF_GATE1_TYPE0,
        mRF_GATE3_TYPE0
    },
    /* 0x23 */ {
        mRF_GATE1_TYPE0,
        mRF_GATE2_TYPE1,
        mRF_GATE2_TYPE0,
        mRF_GATE3_TYPE0
    },
    /* 0x24 */ {
        mRF_GATE1_TYPE0,
        mRF_GATE3_TYPE0,
        mRF_GATE2_TYPE0,
        mRF_GATE2_TYPE1
    },
    /* 0x25 */ {
        mRF_GATE2_TYPE0,
        mRF_GATE2_TYPE1,
        mRF_GATE2_TYPE0,
        mRF_GATE2_TYPE1
    },
    /* 0x26 */ {
        mRF_GATE2_TYPE0,
        mRF_GATE2_TYPE1,
        mRF_GATE1_TYPE0,
        mRF_GATE3_TYPE0
    },
    /* 0x27 */ {
        mRF_GATE1_TYPE0,
        mRF_GATE1_TYPE0,
        mRF_GATE1_TYPE0,
        mRF_GATE1_TYPE0
    },
    /* 0x28 */ {
        mRF_GATE2_TYPE1,
        mRF_GATE1_TYPE0,
        mRF_GATE2_TYPE1,
        mRF_GATE1_TYPE0
    },
    /* 0x29 */ {
        mRF_GATE1_TYPE0,
        mRF_GATE2_TYPE1,
        mRF_GATE1_TYPE0,
        mRF_GATE2_TYPE1
    },
    /* 0x2a */ {
        mRF_GATE1_TYPE0,
        mRF_GATE2_TYPE1,
        mRF_GATE1_TYPE0,
        mRF_GATE2_TYPE1
    },
    /* 0x2b */ {
        mRF_GATE2_TYPE1,
        mRF_GATE1_TYPE0,
        mRF_GATE1_TYPE0,
        mRF_GATE2_TYPE1
    },
    /* 0x2c */ {
        mRF_GATE1_TYPE0,
        mRF_GATE2_TYPE1,
        mRF_GATE2_TYPE1,
        mRF_GATE1_TYPE0
    },
    /* 0x2d */ {
        mRF_GATE2_TYPE1,
        mRF_GATE2_TYPE1,
        mRF_GATE1_TYPE0,
        mRF_GATE1_TYPE0
    },
    /* 0x2e */ {
        mRF_GATE1_TYPE0,
        mRF_GATE1_TYPE0,
        mRF_GATE2_TYPE1,
        mRF_GATE2_TYPE1
    },
    /* 0x2f */ {
        mRF_GATE2_TYPE1,
        mRF_GATE1_TYPE0,
        mRF_GATE2_TYPE1,
        mRF_GATE1_TYPE0
    },
    /* 0x30 */ {
        mRF_GATE1_TYPE0,
        mRF_GATE2_TYPE1,
        mRF_GATE1_TYPE0,
        mRF_GATE2_TYPE1
    },
    /* 0x31 */ {
        mRF_GATE1_TYPE0,
        mRF_GATE2_TYPE1,
        mRF_GATE1_TYPE0,
        mRF_GATE2_TYPE1
    },
    /* 0x32 */ {
        mRF_GATE2_TYPE1,
        mRF_GATE1_TYPE0,
        mRF_GATE1_TYPE0,
        mRF_GATE2_TYPE1
    },
    /* 0x33 */ {
        mRF_GATE1_TYPE0,
        mRF_GATE2_TYPE1,
        mRF_GATE2_TYPE1,
        mRF_GATE1_TYPE0
    },
    /* 0x34 */ {
        mRF_GATE2_TYPE1,
        mRF_GATE2_TYPE1,
        mRF_GATE1_TYPE0,
        mRF_GATE1_TYPE0
    },
    /* 0x35 */ {
        mRF_GATE1_TYPE0,
        mRF_GATE1_TYPE0,
        mRF_GATE2_TYPE1,
        mRF_GATE2_TYPE1
    },
    /* 0x36 */ {
        mRF_GATE1_TYPE0,
        mRF_GATE2_TYPE0,
        mRF_GATE1_TYPE0,
        mRF_GATE2_TYPE0
    },
    /* 0x37 */ {
        mRF_GATE2_TYPE0,
        mRF_GATE2_TYPE0,
        mRF_GATE1_TYPE0,
        mRF_GATE1_TYPE0
    },
    /* 0x38 */ {
        mRF_GATE2_TYPE0,
        mRF_GATE1_TYPE0,
        mRF_GATE2_TYPE0,
        mRF_GATE1_TYPE0
    },
    /* 0x39 */ {
        mRF_GATE1_TYPE0,
        mRF_GATE1_TYPE0,
        mRF_GATE2_TYPE0,
        mRF_GATE2_TYPE0
    },
    /* 0x3a */ {
        mRF_GATE1_TYPE0,
        mRF_GATE2_TYPE0,
        mRF_GATE2_TYPE0,
        mRF_GATE1_TYPE0
    },
    /* 0x3b */ {
        mRF_GATE2_TYPE0,
        mRF_GATE1_TYPE0,
        mRF_GATE2_TYPE0,
        mRF_GATE1_TYPE0
    },
    /* 0x3c */ {
        mRF_GATE2_TYPE0,
        mRF_GATE1_TYPE0,
        mRF_GATE1_TYPE0,
        mRF_GATE2_TYPE0
    },
    /* 0x3d */ {
        mRF_GATE_NONE,
        mRF_GATE_NONE,
        mRF_GATE_NONE,
        mRF_GATE_NONE
    },
    /* 0x3e */ {
        mRF_GATE_NONE,
        mRF_GATE_NONE,
        mRF_GATE_NONE,
        mRF_GATE_NONE
    },
    /* 0x3f */ {
        mRF_GATE1_TYPE0,
        mRF_GATE1_TYPE0,
        mRF_GATE_NONE,
        mRF_GATE1_TYPE0
    },
    /* 0x40 */ {
        mRF_GATE2_TYPE1,
        mRF_GATE1_TYPE0,
        mRF_GATE_NONE,
        mRF_GATE1_TYPE0
    },
    /* 0x41 */ {
        mRF_GATE1_TYPE0,
        mRF_GATE1_TYPE1,
        mRF_GATE1_TYPE0,
        mRF_GATE1_TYPE1
    },
    /* 0x42 */ {
        mRF_GATE1_TYPE0,
        mRF_GATE1_TYPE0,
        mRF_GATE1_TYPE0,
        mRF_GATE1_TYPE0
    },
    /* 0x43 */ {
        mRF_GATE1_TYPE0,
        mRF_GATE1_TYPE1,
        mRF_GATE1_TYPE0,
        mRF_GATE1_TYPE1
    },
    /* 0x44 */ {
        mRF_GATE1_TYPE0,
        mRF_GATE1_TYPE0,
        mRF_GATE1_TYPE0,
        mRF_GATE1_TYPE0
    },
    /* 0x45 */ {
        mRF_GATE2_TYPE1,
        mRF_GATE1_TYPE0,
        mRF_GATE2_TYPE1,
        mRF_GATE1_TYPE0
    },
    /* 0x46 */ {
        mRF_GATE1_TYPE0,
        mRF_GATE2_TYPE1,
        mRF_GATE1_TYPE0,
        mRF_GATE2_TYPE1
    },
    /* 0x47 */ {
        mRF_GATE1_TYPE0,
        mRF_GATE2_TYPE1,
        mRF_GATE1_TYPE0,
        mRF_GATE2_TYPE1
    },
    /* 0x48 */ {
        mRF_GATE2_TYPE1,
        mRF_GATE1_TYPE0,
        mRF_GATE1_TYPE0,
        mRF_GATE2_TYPE1
    },
    /* 0x49 */ {
        mRF_GATE1_TYPE0,
        mRF_GATE2_TYPE1,
        mRF_GATE2_TYPE1,
        mRF_GATE1_TYPE0
    },
    /* 0x4a */ {
        mRF_GATE2_TYPE1,
        mRF_GATE2_TYPE1,
        mRF_GATE1_TYPE0,
        mRF_GATE1_TYPE0
    },
    /* 0x4b */ {
        mRF_GATE1_TYPE0,
        mRF_GATE1_TYPE0,
        mRF_GATE2_TYPE1,
        mRF_GATE2_TYPE1
    },
    /* 0x4c */ {
        mRF_GATE_NONE,
        mRF_GATE_NONE,
        mRF_GATE_NONE,
        mRF_GATE_NONE
    },
    /* 0x4d */ {
        mRF_GATE_NONE,
        mRF_GATE_NONE,
        mRF_GATE_NONE,
        mRF_GATE_NONE
    },
    /* 0x4e */ {
        mRF_GATE_NONE,
        mRF_GATE_NONE,
        mRF_GATE_NONE,
        mRF_GATE_NONE
    },
    /* 0x4f */ {
        mRF_GATE_NONE,
        mRF_GATE_NONE,
        mRF_GATE_NONE,
        mRF_GATE_NONE
    },
    /* 0x50 */ {
        mRF_GATE_NONE,
        mRF_GATE_NONE,
        mRF_GATE_NONE,
        mRF_GATE_NONE
    },
    /* 0x51 */ {
        mRF_GATE_NONE,
        mRF_GATE_NONE,
        mRF_GATE_NONE,
        mRF_GATE_NONE
    },
    /* 0x52 */ {
        mRF_GATE2_TYPE1,
        mRF_GATE1_TYPE0,
        mRF_GATE_NONE,
        mRF_GATE1_TYPE0
    },
    /* 0x53 */ {
        mRF_GATE_NONE,
        mRF_GATE_NONE,
        mRF_GATE_NONE,
        mRF_GATE_NONE
    }
};
#endif

// TODO: import data
#if 0
const char* D_8010C6CC_jp[] = {
  "BGFGｼｮｷｶ",
  "ｶﾜｶﾞｹｾｲｾｲ",
  "ｳﾐｾｲｾｲ",
  "ﾊｼｻｶｾｲｾｲ",
  "ｺｳﾊﾞﾝﾋﾛﾊﾞｾｲｾｲ",
  "ﾐｾﾕｳﾋﾞﾝｷｮｸｾｲｾｲ",
  "ｲｹｾｲｾ",
  "ﾍﾞｰｽｾｯﾃｲ",
  "ｳﾐﾆｶﾜｾｲｾｲ",
  "ﾌﾞﾛｯｸｾﾝﾀｸ",
  "ﾗﾝﾀﾞﾑｶﾝﾘｮｳ"
}
#endif

#if 0
extern s32 D_8010C6C4_jp;
extern s32 D_8010C6C8_jp;
extern char* D_8010C6CC_jp[];

void mRF_PrintDebug(gfxprint* gfxprint) {
    gfxprint_color(gfxprint, 200, 200, 250, 255);
    gfxprint_locate8x8(gfxprint, 3, 21);
    gfxprint_printf(gfxprint, "RandomTry %d", D_8010C6C8_jp);
    gfxprint_color(gfxprint, 200, 200, 250, 255);
    gfxprint_locate8x8(gfxprint, 3, 22);
    gfxprint_printf(gfxprint, "RandomStep %s", D_8010C6CC_jp[D_8010C6C4_jp]);
}
#elif 0
extern s32 D_8010C6C4_jp;
extern s32 D_8010C6C8_jp;
extern u8* D_8010C6CC_jp[];
extern s8 RO_STR_80117694_jp;
extern s8 RO_STR_801176A4_jp;

void mRF_PrintDebug(gfxprint* gfxprint) {
    gfxprint_color(gfxprint, 200, 200, 250, 255);
    gfxprint_locate8x8(gfxprint, 3, 21);
    gfxprint_printf(gfxprint, &RO_STR_80117694_jp, D_8010C6C8_jp);
    gfxprint_color(gfxprint, 200, 200, 250, 255);
    gfxprint_locate8x8(gfxprint, 3, 22);
    gfxprint_printf(gfxprint, &RO_STR_801176A4_jp, D_8010C6CC_jp[D_8010C6C4_jp]);
}
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_random_field/mRF_PrintDebug.s")
#endif

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_random_field/func_800BCCFC_jp.s")

extern u32 mRF_block_info[];

u32 mRF_Type2BlockInfo(u8 blockType) {
  if (blockType < mFM_BLOCK_TYPE_NUM) {
    return mRF_block_info[blockType];
  }

  return mRF_BLOCKKIND_NONE;
}

/* @unused */
u8 mRF_Info2BlockType(u32 blockInfo) {
    s32 blockType = 0;

    for (blockType = 0; blockType < mFM_BLOCK_TYPE_NUM; blockType += 1) {
        if (blockInfo == mRF_block_info[blockType]) {
            return (u8) blockType;
        }
    }

    return mFM_BLOCK_TYPE_NONE;
}

extern u8 gate_count_table[];
s32 mRF_GateType2GateCount(s32 gateType) {
    // TODO: import data
    // static u8 gate_count_table[mRF_GATE_TYPE_NUM] = {
    //   0, 1, 1, 2, 2, 3
    // };

    if (gateType < mRF_GATE_TYPE_NUM) {
        return gate_count_table[gateType];
    }

    return 0;
}

s32 mRF_SearchPond(s32* utX, s32* utZ, s32 blockX, s32 blockZ) {
  FieldMakeBGSoundSource* soundSourceInfo = mFI_GetSoundSourcePBlockNum(blockX, blockZ);

  if (soundSourceInfo != NULL) {
    s32 i;

    for (i = 0; i < mFI_NUM_SOUND_SOURCES; i++, soundSourceInfo++) {
      if (soundSourceInfo->kind == mFI_SOUND_SOURCE_POND) {
        if (mFI_Wpos2UtNum(utX, utZ, soundSourceInfo->pos)) {
          return TRUE;
        }
      }
    }
  }

  return FALSE;
}

s32 mRF_Attr2BeastRoadAttr(s32 attribute) {
  switch (attribute) {
    case mCoBG_ATTRIBUTE_0:
    case mCoBG_ATTRIBUTE_1:
      return mCoBG_ATTRIBUTE_2;

    case mCoBG_ATTRIBUTE_4:
    case mCoBG_ATTRIBUTE_5:
      return mCoBG_ATTRIBUTE_6;

    default:
      return attribute;
  }
}

extern u8 mRF_gate_info2[mFM_BLOCK_TYPE_NUM][RANDOM_FIELD_DIRECT_NUM];

s32 mRF_BlockTypeDirect2GateType(u8 block_type, s32 direct) {
  return mRF_gate_info2[block_type][direct];
}

extern RandomFieldGate* mRF_gate_correct_info[mRF_GATE_TYPE_NUM][RANDOM_FIELD_DIRECT_NUM];

RandomFieldGate* mRF_BlockTypeDirect2GateData(s32* gateCount, u8 blockType, s32 direct) {
  s32 type = mRF_BlockTypeDirect2GateType(blockType, direct);
  s32 count = mRF_GateType2GateCount(type);

  *gateCount = count;
  return mRF_gate_correct_info[type][direct];
}

#if 0
// TODO: rename unk6 in mCoBG_unkStructUnion to unitAttribute
extern xyz_t wpos;
s32 mRF_BlockInf2CheckBeastRoad(u8 blockType, mCoBG_unkStructUnion* collisionData) {
  // fairly specific variable declaration order required for match
  s32 colUt;
  s32 gateCount; 
  s32 i;
  s32 j;
  u32 attrib;
  mCoBG_unkStructUnion* col;
  RandomFieldGate* gateP;

  s32 changedAttributeCount = 0;
  // TODO: import data
  // xyz_t wpos = { 0.0f, 0.0f, 0.0f };

  for (i = 0; i < RANDOM_FIELD_DIRECT_NUM; i++) {
    gateP = mRF_BlockTypeDirect2GateData(&gateCount, blockType, i);

    if (gateP != NULL) {
      for (j = 0; j < gateCount; j++) {
        /* process first unit */
        {
          colUt = gateP[j].ut0;
          col = collisionData + (u8)colUt;
          attrib = col->data.unk6;
          
          mFI_UtNum2CenterWpos(&wpos, colUt & 0xF, (colUt >> 4) & 0xF);

          /* only bother updating the unit attribute if the unit can grow collideable plants in it */
          if (mCoBG_Attribute2CheckPlant(attrib, &wpos) > 0) {
            col->data.unk6 = mRF_Attr2BeastRoadAttr(attrib);
            changedAttributeCount++;
          }
        }

        /* process second unit */
        {
          colUt = gateP[j].ut1;
          col = collisionData + (u8)colUt;
          attrib = col->data.unk6;
          
          mFI_UtNum2CenterWpos(&wpos, colUt & 0xF, (colUt >> 4) & 0xF);

          /* only bother updating the unit attribute if the unit can grow collideable plants in it */
          if (mCoBG_Attribute2CheckPlant(attrib, &wpos) > 0) {
            col->data.unk6 = mRF_Attr2BeastRoadAttr(attrib);
            changedAttributeCount++;
          }
        }
      }
    }
  }

  if (changedAttributeCount != 0) {
      return 0;
  }

  return 1;
}
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_random_field/mRF_BlockInf2CheckBeastRoad.s")
#endif

void mRF_CheckBeastRoad() {
  if (SAVE_GET(sceneNo) == SCENE_FG) {
    s32 blockXMax = mFI_GetBlockXMax() - 1;
    s32 blockZMax = mFI_GetBlockZMax() - 1;
    s32 blockX;
    s32 blockZ;

    for (blockZ = 1; blockZ < blockZMax; blockZ++) {
      for (blockX = 1; blockX < blockXMax; blockX++) {
        mCoBG_unkStructUnion* collisionData = mFI_GetBkNum2ColTop(blockX, blockZ);
        u8 type = mFI_BkNum2BlockType(blockX, blockZ);

        mRF_BlockInf2CheckBeastRoad(type, collisionData);
      }
    }
  }
}
