#ifndef AC_COUNTDOWN_H
#define AC_COUNTDOWN_H

#include "ultra64.h"
#include "m_actor.h"
#include "unk.h"

struct PlayState;
struct Count;

typedef void (*CountActionFunc)(struct Count*, struct PlayState*);

typedef struct Count {
    /* 0x000 */ Actor actor;
    /* 0x174 */ UNK_TYPE1 unk_174[0x164];
} Count; // size = 0x2D8

#endif
