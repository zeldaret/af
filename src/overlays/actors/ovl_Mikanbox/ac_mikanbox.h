#ifndef AC_MIKANBOX_H
#define AC_MIKANBOX_H

#include "ultra64.h"
#include "m_actor.h"
#include "unk.h"

struct Mikanbox;

typedef struct Mikanbox {
    /* 0x000 */ Actor actor;
    /* 0x174 */ UNK_TYPE1 unk_174[0x164];
} Mikanbox; // size = 0x2D8

#endif
