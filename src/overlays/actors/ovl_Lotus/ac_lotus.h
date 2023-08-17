#ifndef AC_LOTUS_H
#define AC_LOTUS_H

#include "ultra64.h"
#include "m_actor.h"
#include "unk.h"

struct PlayState;
struct Lotus;

typedef void (*LotusActionFunc)(struct Lotus*, struct PlayState*);

typedef struct Lotus {
    /* 0x000 */ Actor actor;
    /* 0x174 */ UNK_TYPE1 unk_174[0x164];
} Lotus; // size = 0x2D8

#endif
