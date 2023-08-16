#ifndef AC_KAMAKURA_H
#define AC_KAMAKURA_H

#include "ultra64.h"
#include "m_actor.h"
#include "unk.h"

struct Kamakura;

typedef struct Kamakura {
    /* 0x000 */ Actor actor;
    /* 0x174 */ UNK_TYPE1 unk_174[0x164];
} Kamakura; // size = 0x2D8

#endif
