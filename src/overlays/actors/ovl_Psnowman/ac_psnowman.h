#ifndef AC_PSNOWMAN_H
#define AC_PSNOWMAN_H

#include "ultra64.h"
#include "m_actor.h"
#include "unk.h"

struct Psnowman;

typedef struct Psnowman {
    /* 0x000 */ Actor actor;
    /* 0x174 */ UNK_TYPE1 unk_174[0x24];
} Psnowman; // size = 0x198

#endif
