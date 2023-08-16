#ifndef AC_NPC_MAJIN5_H
#define AC_NPC_MAJIN5_H

#include "ultra64.h"
#include "m_actor.h"
#include "unk.h"

struct Npc_Majin5;

typedef struct Npc_Majin5 {
    /* 0x000 */ Actor actor;
    /* 0x174 */ UNK_TYPE1 unk_174[0x7C4];
} Npc_Majin5; // size = 0x938

#endif
