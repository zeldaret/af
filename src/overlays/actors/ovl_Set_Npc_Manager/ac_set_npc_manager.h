#ifndef AC_SET_NPC_MANAGER_H
#define AC_SET_NPC_MANAGER_H

#include "ultra64.h"
#include "m_actor.h"
#include "unk.h"

struct Set_Npc_Manager;

typedef struct Set_Npc_Manager {
    /* 0x000 */ Actor actor;
    /* 0x174 */ UNK_TYPE1 unk_174[0x234];
} Set_Npc_Manager; // size = 0x3A8

#endif
