#ifndef AC_TURI_H
#define AC_TURI_H

#include "ultra64.h"
#include "m_actor.h"
#include "unk.h"

struct Turi;

typedef struct Turi {
    /* 0x000 */ Actor actor;
    /* 0x174 */ UNK_TYPE1 unk_174[0x164];
} Turi; // size = 0x2D8

#endif
