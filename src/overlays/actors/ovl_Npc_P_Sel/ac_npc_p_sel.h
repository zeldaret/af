#ifndef AC_NPC_P_SEL_H
#define AC_NPC_P_SEL_H

#include "ultra64.h"
#include "m_actor.h"
#include "unk.h"

struct Npc_P_Sel;

typedef struct Npc_P_Sel {
    /* 0x000 */ Actor actor;
    /* 0x174 */ UNK_TYPE1 unk_174[0x7E0];
} Npc_P_Sel; // size = 0x954

#endif
