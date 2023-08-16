#ifndef AC_MIKUJI_H
#define AC_MIKUJI_H

#include "ultra64.h"
#include "m_actor.h"
#include "unk.h"

struct PlayState;
struct Mikuji;

typedef void (*MikujiActionFunc)(struct Mikuji*, struct PlayState*);

typedef struct Mikuji {
    /* 0x000 */ Actor actor;
    /* 0x174 */ UNK_TYPE1 unk_174[0x164];
} Mikuji; // size = 0x2D8

#endif
