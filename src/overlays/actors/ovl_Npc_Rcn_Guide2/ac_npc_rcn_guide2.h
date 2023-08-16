#ifndef AC_NPC_RCN_GUIDE2_H
#define AC_NPC_RCN_GUIDE2_H

#include "ultra64.h"
#include "m_actor.h"
#include "unk.h"

struct Npc_Rcn_Guide2;

typedef struct Npc_Rcn_Guide2 {
    /* 0x000 */ Actor actor;
    /* 0x174 */ UNK_TYPE1 unk_174[0x7EC];
} Npc_Rcn_Guide2; // size = 0x960

#endif
