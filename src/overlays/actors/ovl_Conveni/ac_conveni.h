#ifndef AC_CONVENI_H
#define AC_CONVENI_H

#include "ultra64.h"
#include "m_actor.h"
#include "unk.h"

struct Conveni;

typedef struct Conveni {
    /* 0x000 */ Actor actor;
    /* 0x174 */ UNK_TYPE1 unk_174[0x164];
} Conveni; // size = 0x2D8

#endif
