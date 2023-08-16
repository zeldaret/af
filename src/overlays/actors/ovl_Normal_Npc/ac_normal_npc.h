#ifndef AC_NORMAL_NPC_H
#define AC_NORMAL_NPC_H

#include "ultra64.h"
#include "m_actor.h"
#include "unk.h"

struct Normal_Npc;

typedef struct Normal_Npc {
    /* 0x000 */ Actor actor;
    /* 0x174 */ UNK_TYPE1 unk_174[0x7C4];
} Normal_Npc; // size = 0x938

#endif
