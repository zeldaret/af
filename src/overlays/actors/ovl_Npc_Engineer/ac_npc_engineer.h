#ifndef AC_NPC_ENGINEER_H
#define AC_NPC_ENGINEER_H

#include "ultra64.h"
#include "m_actor.h"
#include "unk.h"

struct Npc_Engineer;

typedef struct Npc_Engineer {
    /* 0x000 */ Actor actor;
    /* 0x174 */ UNK_TYPE1 unk_174[0x7C4];
} Npc_Engineer; // size = 0x938

#endif
