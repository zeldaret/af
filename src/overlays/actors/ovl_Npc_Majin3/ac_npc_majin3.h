#ifndef AC_NPC_MAJIN3_H
#define AC_NPC_MAJIN3_H

#include "ultra64.h"
#include "m_actor.h"
#include "unk.h"

struct PlayState;
struct Npc_Majin3;

typedef void (*Npc_Majin3ActionFunc)(struct Npc_Majin3*, struct PlayState*);

typedef struct Npc_Majin3 {
    /* 0x000 */ Actor actor;
    /* 0x174 */ UNK_TYPE1 unk_174[0x7E4];
} Npc_Majin3; // size = 0x958

#endif
