#ifndef AC_NPC_POLICE_H
#define AC_NPC_POLICE_H

#include "ultra64.h"
#include "m_actor.h"
#include "unk.h"

struct Npc_Police;

typedef struct Npc_Police {
    /* 0x000 */ Actor actor;
    /* 0x174 */ UNK_TYPE1 unk_174[0x7D8];
} Npc_Police; // size = 0x94C

#endif
