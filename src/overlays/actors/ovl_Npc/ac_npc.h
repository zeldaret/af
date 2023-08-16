#ifndef AC_NPC_H
#define AC_NPC_H

#include "ultra64.h"
#include "m_actor.h"
#include "unk.h"

struct Npc;

typedef struct Npc {
    /* 0x000 */ Actor actor;
    /* 0x174 */ UNK_TYPE1 unk_174[0x7C8];
} Npc; // size = 0x93C

#endif
