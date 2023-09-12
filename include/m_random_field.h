#ifndef M_RANDOM_FIELD_H
#define M_RANDOM_FIELD_H

#include "ultra64.h"


#define RANDOM_FIELD_BLOCKKIND_SHRINE (1 << 2)

#define RANDOM_FIELD_BLOCK_TYPE_MAX 108 
#define RANDOM_FIELD_DIRECT_ERROR 100

typedef enum RANDOM_FIELD_DIRECT {
  /* 0 */ RANDOM_FIELD_DIRECT_NORTH,
  /* 1 */ RANDOM_FIELD_DIRECT_WEST,
  /* 2 */ RANDOM_FIELD_DIRECT_SOUTH,
  /* 3 */ RANDOM_FIELD_DIRECT_EAST,

  /* 4 */ RANDOM_FIELD_DIRECT_NUM
} RANDOM_FIELD_DIRECT;

typedef struct RandomFieldGate {
  /* 0x00 */ s32 ut0;
  /* 0x04 */ s32 ut1;
} RandomFieldGate;

// void func_800BCBA0_jp();
// void func_800BCBDC_jp();
// void func_800BCC20_jp();
// void func_800BCC30_jp();
// void func_800BCC40_jp();
// void func_800BCCFC_jp();
// void func_800BCDCC_jp();
// void func_800BCDFC_jp();
// void func_800BCE80_jp();
// void func_800BCEA4_jp();
// void func_800BCF64_jp();
// void func_800BCFA4_jp();
RandomFieldGate* mRF_BlockTypeDirect2GateData(s32*, u8, s32);
// void func_800BD02C_jp();
// void func_800BD1E4_jp();

#endif