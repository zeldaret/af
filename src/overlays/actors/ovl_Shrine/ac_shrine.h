#ifndef AC_SHRINE_H
#define AC_SHRINE_H

#include "ultra64.h"
#include "m_actor.h"
#include "unk.h"

struct Shrine;

typedef struct Shrine {
    /* 0x000 */ Actor actor;
    /* 0x174 */ UNK_TYPE1 unk_174[0x164];
} Shrine; // size = 0x2D8

#endif
