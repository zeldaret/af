#ifndef AC_TOUDAI_H
#define AC_TOUDAI_H

#include "ultra64.h"
#include "m_actor.h"
#include "unk.h"

struct Toudai;

typedef struct Toudai {
    /* 0x000 */ Actor actor;
    /* 0x174 */ UNK_TYPE1 unk_174[0x164];
} Toudai; // size = 0x2D8

#endif
