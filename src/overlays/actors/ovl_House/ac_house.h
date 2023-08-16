#ifndef AC_HOUSE_H
#define AC_HOUSE_H

#include "ultra64.h"
#include "m_actor.h"
#include "unk.h"

struct House;

typedef struct House {
    /* 0x000 */ Actor actor;
    /* 0x174 */ UNK_TYPE1 unk_174[0x164];
} House; // size = 0x2D8

#endif
