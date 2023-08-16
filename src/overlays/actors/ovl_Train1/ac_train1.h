#ifndef AC_TRAIN1_H
#define AC_TRAIN1_H

#include "ultra64.h"
#include "m_actor.h"
#include "unk.h"

struct Train1;

typedef struct Train1 {
    /* 0x000 */ Actor actor;
    /* 0x174 */ UNK_TYPE1 unk_174[0x164];
} Train1; // size = 0x2D8

#endif
