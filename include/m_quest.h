#ifndef M_QUEST_H
#define M_QUEST_H

#include "ultra64.h"

/* 'Not Saved' Quest */
typedef struct mQst_not_saved_c {
  /* 0x00 */ s32 work;
  /* 0x04 */ u8 h;
} mQst_not_saved_c; // size = 0x5

typedef struct mQst_delivery_c {
  /* 0x00 */ char unk00[0x24];
} mQst_delivery_c; // size = 0x24

typedef struct mQst_errand_c {
  /* 0x00 */ char unk00[0x50];
} mQst_errand_c; // size = 0x50

#endif
