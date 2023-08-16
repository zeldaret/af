#ifndef AC_COUNT02_H
#define AC_COUNT02_H

#include "ultra64.h"
#include "m_actor.h"
#include "unk.h"

struct Count02;

typedef struct Count02 {
    /* 0x000 */ Actor actor;
    /* 0x174 */ UNK_TYPE1 unk_174[0x164];
} Count02; // size = 0x2D8

#endif
