#ifndef AC_RADIO_H
#define AC_RADIO_H

#include "ultra64.h"
#include "m_actor.h"
#include "unk.h"

struct Radio;

typedef struct Radio {
    /* 0x000 */ Actor actor;
    /* 0x174 */ UNK_TYPE1 unk_174[0x164];
} Radio; // size = 0x2D8

#endif
