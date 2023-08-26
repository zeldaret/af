#ifndef M_RANDOM_FIELD_H
#define M_RANDOM_FIELD_H

#include "ultra64.h"

#define RANDOM_FIELD_BLOCKKIND_SHRINE (1 << 2)

#define RANDOM_FIELD_BLOCK_TYPE_MAX 108 // TODO: this is likely a giant enum lol
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

#endif
