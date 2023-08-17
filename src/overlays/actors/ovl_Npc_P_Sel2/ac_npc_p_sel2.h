#ifndef AC_NPC_P_SEL2_H
#define AC_NPC_P_SEL2_H

#include "ultra64.h"
#include "m_actor.h"
#include "unk.h"

struct PlayState;
struct Npc_P_Sel2;

typedef void (*Npc_P_Sel2ActionFunc)(struct Npc_P_Sel2*, struct PlayState*);

typedef struct Npc_P_Sel2 {
    /* 0x000 */ Actor actor;
    /* 0x174 */ UNK_TYPE1 unk_174[0x7E0];
} Npc_P_Sel2; // size = 0x954

#endif
