#ifndef AC_UKI_H
#define AC_UKI_H

#include "ultra64.h"
#include "m_actor.h"
#include "unk.h"

struct Uki;

typedef struct Uki {
    /* 0x000 */ Actor actor;
    /* 0x174 */ UNK_TYPE1 unk_174[0x144];
} Uki; // size = 0x2B8

#endif
