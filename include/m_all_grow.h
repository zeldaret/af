#ifndef M_ALL_GROW_H
#define M_ALL_GROW_H

#include "ultra64.h"

#define mAGrw_DUMP_WIDTH 4
#define mAGrw_DUMP_HEIGHT 4

enum {
  mAGrw_XMAS_PROC_CLEAR,
  mAGrw_XMAS_PROC_SET,

  mAGrw_XMAS_PROC_NUM
};

enum {
  mAGrw_FRUIT_APPLE,
  mAGrw_FRUIT_CHERRY,
  mAGrw_FRUIT_PEAR,
  mAGrw_FRUIT_PEACH,
  mAGrw_FRUIT_ORANGE,

  mAGrw_FRUIT_NUM
};

#define mAGrw_XMAS_LIGHTS_MAX_BLOCK 3
#define mAGrw_CEDAR_BLOCK_Z_MIN 0
#define mAGrw_CEDAR_BLOCK_Z_MAX 3 // [min, max)

#endif
