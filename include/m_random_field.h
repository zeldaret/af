#ifndef M_RANDOM_FIELD_H
#define M_RANDOM_FIELD_H

#include "ultra64.h"

#define mRF_BLOCKKIND_NONE (0 << 0)
#define mRF_BLOCKKIND_PLAYER (1 << 0)
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
#define mRF_BLOCKKIND_MARINE (1 << 11)
#define mRF_BLOCKKIND_BORDER (1 << 12)
#define mRF_BLOCKKIND_TUNNEL (1 << 13)
#define mRF_BLOCKKIND_SLOPE (1 << 14)
#define mRF_BLOCKKIND_POOL (1 << 15)
#define mRF_BLOCKKIND_DUMP (1 << 16)
#define mRF_BLOCKKIND_MUSEUM (1 << 17)
#define mRF_BLOCKKIND_18 (1 << 18)
#define mRF_BLOCKKIND_TAILORS (1 << 19)
#define mRF_BLOCKKIND_OCEAN (1 << 20)
#define mRF_BLOCKKIND_ISLAND (1 << 21)
#define mRF_BLOCKKIND_OFFING (1 << 22)
#define mRF_BLOCKKIND_RIVER0 (1 << 23)
#define mRF_BLOCKKIND_RIVER1 (1 << 24)
#define mRF_BLOCKKIND_RIVER2 (1 << 25)
#define mRF_BLOCKKIND_RIVER3 (1 << 26)
#define mRF_BLOCKKIND_RIVER4 (1 << 27)
#define mRF_BLOCKKIND_RIVER5 (1 << 28)
#define mRF_BLOCKKIND_RIVER6 (1 << 29)
#define mRF_BLOCKKIND_DOCK (1 << 30)
#define mRF_BLOCKKIND_ISLAND_LEFT (1 << 31)

#define mRF_BLOCK_TYPE_MAX 108 // TODO: this is likely a giant enum lol
#define mRF_DIRECT_ERROR 100

typedef enum mRF_GATE{
  /* 0 */ mRF_GATE_NONE,
  /* 1 */ mRF_GATE1_TYPE0,
  /* 2 */ mRF_GATE1_TYPE1,
  /* 3 */ mRF_GATE2_TYPE0,
  /* 4 */ mRF_GATE2_TYPE1,
  /* 5 */ mRF_GATE3_TYPE0,
  
  /* 6 */ mRF_GATE_TYPE_NUM
} mRF_GATE;

typedef enum mRF_DIRECT{
  /* 0 */ mRF_DIRECT_NORTH,
  /* 1 */ mRF_DIRECT_WEST,
  /* 2 */ mRF_DIRECT_SOUTH,
  /* 3 */ mRF_DIRECT_EAST,

  /* 4 */ mRF_DIRECT_NUM
} mRF_DIRECT;

typedef enum mRF_RIVER{
  /* 0 */ mRF_RIVER0,
  /* 1 */ mRF_RIVER1,
  /* 2 */ mRF_RIVER2,
  /* 3 */ mRF_RIVER3,
  /* 4 */ mRF_RIVER4,
  /* 5 */ mRF_RIVER5,
  /* 6 */ mRF_RIVER6,

  /* 7 */ mRF_RIVER_NUM
} mRF_RIVER;

typedef enum mRF_FIELD{
  /* 0 */ mRF_FIELD_STEP1,  /* first level */
  /* 1 */ mRF_FIELD_STEP2,  /* second level*/
  /* 2 */ mRF_FIELD_STEP3,  /* third level */
  /* 3 */ mRF_FIELD_STEP4,  /* fourth level */
 
  /* 4 */ mRF_FIELD_STEP_NUM
} mRF_FIELD;

typedef struct mRF_gate_c {
  /* 0x00 */ s32 ut0;
  /* 0x04 */ s32 ut1;
} mRF_gate_c;

#endif
