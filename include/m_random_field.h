#ifndef M_RANDOM_FIELD_H
#define M_RANDOM_FIELD_H

#include "ultra64.h"

#define mRF_BLOCKKIND_SHRINE (1 << 2)

#define mRF_BLOCK_TYPE_MAX 108 // TODO: this is likely a giant enum lol
#define mRF_DIRECT_ERROR 100

typedef enum mRF_DIRECT{
  /* 0 */ mRF_DIRECT_NORTH,
  /* 1 */ mRF_DIRECT_WEST,
  /* 2 */ mRF_DIRECT_SOUTH,
  /* 3 */ mRF_DIRECT_EAST,

  /* 4 */ mRF_DIRECT_NUM
} mRF_DIRECT;

typedef struct mRF_gate_c {
  /* 0x00 */ s32 ut0;
  /* 0x04 */ s32 ut1;
} mRF_gate_c;

#endif
