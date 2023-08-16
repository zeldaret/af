#ifndef AC_NPC_MAJIN_H
#define AC_NPC_MAJIN_H

#include "ultra64.h"
#include "m_actor.h"
#include "unk.h"

struct Npc_Majin2;

typedef struct Npc_Majin2 {
    /* 0x000 */ Actor actor;
    /* 0x174 */ UNK_TYPE1 unk_174[0x7DC];
} Npc_Majin2; // size = 0x950

#endif
