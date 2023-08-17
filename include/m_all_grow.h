#ifndef M_ALL_GROW_H
#define M_ALL_GROW_H

#include "ultra64.h"

#define mAGrw_DUMP_WIDTH 4
#define mAGrw_DUMP_HEIGHT 4

typedef enum mAGrw_XMAS_PROC {
  /* 0 */ mAGrw_XMAS_PROC_CLEAR,
  /* 1 */ mAGrw_XMAS_PROC_SET,

  /* 2 */ mAGrw_XMAS_PROC_NUM
} mAGrw_XMAS_PROC;

typedef enum mAGrw_FRUIT {
  /* 0 */ mAGrw_FRUIT_APPLE,
  /* 1 */ mAGrw_FRUIT_CHERRY,
  /* 2 */ mAGrw_FRUIT_PEAR,
  /* 3 */ mAGrw_FRUIT_PEACH,
  /* 4 */ mAGrw_FRUIT_ORANGE,

  /* 5 */ mAGrw_FRUIT_NUM
} mAGrw_FRUIT;

#define mAGrw_XMAS_LIGHTS_MAX_BLOCK 3
#define mAGrw_CEDAR_BLOCK_Z_MIN 0
#define mAGrw_CEDAR_BLOCK_Z_MAX 3 // [min, max)

#endif
