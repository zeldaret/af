#ifndef M_RANDOM_FIELD_H
#define M_RANDOM_FIELD_H

#include "ultra64.h"


#define RANDOM_FIELD_BLOCKKIND_SHRINE (1 << 2)

#define RANDOM_FIELD_BLOCK_TYPE_MAX 108 
#define RANDOM_FIELD_DIRECT_ERROR 100

typedef enum RandomFieldDirection {
  /* 0 */ RANDOM_FIELD_DIRECT_NORTH,
  /* 1 */ RANDOM_FIELD_DIRECT_WEST,
  /* 2 */ RANDOM_FIELD_DIRECT_SOUTH,
  /* 3 */ RANDOM_FIELD_DIRECT_EAST,

  /* 4 */ RANDOM_FIELD_DIRECT_NUM
}RandomFieldDirection;

typedef struct RandomFieldGate {
  /* 0x00 */ s32 ut0;
  /* 0x04 */ s32 ut1;
} RandomFieldGate;


#define mRF_BLOCKKIND_NONE (0 << 0)
#define mRF_BLOCKKIND_1 (1 << 0)
#define mRF_BLOCKKIND_2 (1 << 1)
#define mRF_BLOCKKIND_3 (1 << 2)
#define mRF_BLOCKKIND_4 (1 << 3)
#define mRF_BLOCKKIND_5 (1 << 4)
#define mRF_BLOCKKIND_6 (1 << 5)
#define mRF_BLOCKKIND_7 (1 << 6)
#define mRF_BLOCKKIND_8 (1 << 7)
#define mRF_BLOCKKIND_9 (1 << 8)
#define mRF_BLOCKKIND_10 (1 << 9)
#define mRF_BLOCKKIND_11 (1 << 10)
#define mRF_BLOCKKIND_12 (1 << 11)
#define mRF_BLOCKKIND_13 (1 << 12)
#define mRF_BLOCKKIND_14 (1 << 13)
#define mRF_BLOCKKIND_15 (1 << 14)
#define mRF_BLOCKKIND_16 (1 << 15)
#define mRF_BLOCKKIND_17 (1 << 16)
#define mRF_BLOCKKIND_18 (1 << 17)
#define mRF_BLOCKKIND_19 (1 << 18)
#define mRF_BLOCKKIND_20 (1 << 19)
#define mRF_BLOCKKIND_21 (1 << 20)
#define mRF_BLOCKKIND_22 (1 << 21)
#define mRF_BLOCKKIND_23 (1 << 22)
#define mRF_BLOCKKIND_24 (1 << 23)
#define mRF_BLOCKKIND_25 (1 << 24)
#define mRF_BLOCKKIND_26 (1 << 25)
#define mRF_BLOCKKIND_27 (1 << 26)
#define mRF_BLOCKKIND_28 (1 << 27)
#define mRF_BLOCKKIND_29 (1 << 28)
#define mRF_BLOCKKIND_30 (1 << 29)
#define mRF_BLOCKKIND_31 (1 << 30)
#define mRF_BLOCKKIND_32 (1 << 31)

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
