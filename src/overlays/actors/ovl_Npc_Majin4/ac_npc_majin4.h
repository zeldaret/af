#ifndef AC_NPC_MAJIN4_H
#define AC_NPC_MAJIN4_H

#include "ultra64.h"
#include "m_actor.h"
#include "unk.h"

struct PlayState;
struct Npc_Majin4;

typedef void (*Npc_Majin4ActionFunc)(struct Npc_Majin4*, struct PlayState*);

typedef struct Npc_Majin4 {
    /* 0x000 */ Actor actor;
    /* 0x174 */ UNK_TYPE1 unk_174[0x7E0];
} Npc_Majin4; // size = 0x954

#endif
