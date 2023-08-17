#ifndef AC_SET_NPC_MANAGER_H
#define AC_SET_NPC_MANAGER_H

#include "ultra64.h"
#include "m_actor.h"
#include "unk.h"

struct Game_Play;
struct Set_Npc_Manager;

typedef void (*Set_Npc_ManagerActionFunc)(struct Set_Npc_Manager*, struct Game_Play*);

typedef struct Set_Npc_Manager {
    /* 0x000 */ Actor actor;
    /* 0x174 */ UNK_TYPE1 unk_174[0x234];
} Set_Npc_Manager; // size = 0x3A8

#endif
