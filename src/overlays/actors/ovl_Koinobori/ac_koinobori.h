#ifndef AC_KOINOBORI_H
#define AC_KOINOBORI_H

#include "ultra64.h"
#include "m_actor.h"
#include "unk.h"

struct Koinobori;

typedef struct Koinobori {
    /* 0x000 */ Actor actor;
    /* 0x174 */ UNK_TYPE1 unk_174[0x164];
} Koinobori; // size = 0x2D8

#endif
