#ifndef AC_BUGGY_H
#define AC_BUGGY_H

#include "ultra64.h"
#include "m_actor.h"
#include "unk.h"

struct PlayState;
struct Buggy;

typedef void (*BuggyActionFunc)(struct Buggy*, struct PlayState*);

typedef struct Buggy {
    /* 0x000 */ Actor actor;
    /* 0x174 */ UNK_TYPE1 unk_174[0x164];
} Buggy; // size = 0x2D8

#endif
