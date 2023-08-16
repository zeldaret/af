#ifndef OVL_NPC_MAJIN_H
#define OVL_NPC_MAJIN_H

#include "ultra64.h"
#include "m_actor.h"
#include "unk.h"

struct PlayState;
struct Npc_Majin;

typedef void (*Npc_MajinActionFunc)(struct Npc_Majin*, struct PlayState*);

typedef struct Npc_Majin {
    /* 0x000 */ Actor actor;
    /* 0x174 */ UNK_TYPE1 unk_174[0x7D8];
} Npc_Majin; // size = 0x94C

#endif
