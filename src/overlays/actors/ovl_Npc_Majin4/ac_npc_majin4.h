#ifndef AC_NPC_MAJIN4_H
#define AC_NPC_MAJIN4_H

#include "ultra64.h"
#include "m_actor.h"
#include "unk.h"

struct Npc_Majin4;

typedef struct Npc_Majin4 {
    /* 0x000 */ Actor actor;
    /* 0x174 */ UNK_TYPE1 unk_174[0x7E0];
} Npc_Majin4; // size = 0x954

#endif
