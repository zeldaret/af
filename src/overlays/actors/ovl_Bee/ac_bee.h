#ifndef AC_BEE_H
#define AC_BEE_H

#include "ultra64.h"
#include "m_actor.h"
#include "unk.h"

struct PlayState;
struct Bee;

typedef void (*BeeActionFunc)(struct Bee*, struct PlayState*);

typedef struct Bee {
    /* 0x000 */ Actor actor;
    /* 0x174 */ UNK_TYPE1 unk_174[0x2DC];
} Bee; // size = 0x450

#endif
