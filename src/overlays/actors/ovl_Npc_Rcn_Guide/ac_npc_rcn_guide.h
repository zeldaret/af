#ifndef AC_NPC_RCN_GUIDE_H
#define AC_NPC_RCN_GUIDE_H

#include "ultra64.h"
#include "m_actor.h"
#include "unk.h"

struct Game_Play;
struct Npc_Rcn_Guide;

typedef void (*Npc_Rcn_GuideActionFunc)(struct Npc_Rcn_Guide*, struct Game_Play*);

typedef struct Npc_Rcn_Guide {
    /* 0x000 */ Actor actor;
    /* 0x174 */ UNK_TYPE1 unk_174[0x7E4];
} Npc_Rcn_Guide; // size = 0x958

#endif
