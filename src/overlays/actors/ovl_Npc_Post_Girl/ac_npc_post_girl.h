#ifndef AC_NPC_POST_GIRL_H
#define AC_NPC_POST_GIRL_H

#include "ultra64.h"
#include "m_actor.h"
#include "unk.h"

struct Npc_Post_Girl;

typedef struct Npc_Post_Girl {
    /* 0x000 */ Actor actor;
    /* 0x174 */ UNK_TYPE1 unk_174[0x7E4];
} Npc_Post_Girl; // size = 0x958

#endif
