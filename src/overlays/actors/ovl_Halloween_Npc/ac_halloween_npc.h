#ifndef AC_HALLOWEEN_NPC_H
#define AC_HALLOWEEN_NPC_H

#include "ultra64.h"
#include "m_actor.h"
#include "unk.h"

struct Game_Play;
struct Halloween_Npc;

typedef void (*Halloween_NpcActionFunc)(struct Halloween_Npc*, struct Game_Play*);

typedef struct Halloween_Npc {
    /* 0x000 */ Actor actor;
    /* 0x174 */ UNK_TYPE1 unk_174[0x7DC];
} Halloween_Npc; // size = 0x950

#endif
