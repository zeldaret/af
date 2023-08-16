#ifndef AC_NPC_POST_MAN_H
#define AC_NPC_POST_MAN_H

#include "ultra64.h"
#include "m_actor.h"
#include "unk.h"

struct Npc_Post_Man;

typedef struct Npc_Post_Man {
    /* 0x000 */ Actor actor;
    /* 0x174 */ UNK_TYPE1 unk_174[0x7D8];
} Npc_Post_Man; // size = 0x94C

#endif
