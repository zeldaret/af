#ifndef AC_NPC_POLICE2_H
#define AC_NPC_POLICE2_H

#include "ultra64.h"
#include "m_actor.h"
#include "unk.h"

struct Npc_Police2;

typedef struct Npc_Police2 {
    /* 0x000 */ Actor actor;
    /* 0x174 */ UNK_TYPE1 unk_174[0x7D4];
} Npc_Police2; // size = 0x948

#endif
