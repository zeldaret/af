#ifndef AC_GARAGARA_H
#define AC_GARAGARA_H

#include "ultra64.h"
#include "m_actor.h"
#include "unk.h"

struct Garagara;

typedef struct Garagara {
    /* 0x000 */ Actor actor;
    /* 0x174 */ UNK_TYPE1 unk_174[0x284];
} Garagara; // size = 0x3F8

#endif
