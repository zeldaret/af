#ifndef AC_NPC_GUIDE_H
#define AC_NPC_GUIDE_H

#include "ultra64.h"
#include "m_actor.h"
#include "unk.h"

struct Game_Play;
struct Npc_Guide;

typedef void (*Npc_GuideActionFunc)(struct Npc_Guide*, struct Game_Play*);

typedef struct Npc_Guide {
    /* 0x000 */ Actor actor;
    /* 0x174 */ UNK_TYPE1 unk_174[0x800];
} Npc_Guide; // size = 0x974

#endif
