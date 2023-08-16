#ifndef AC_HATUMODE_NPC0_H
#define AC_HATUMODE_NPC0_H

#include "ultra64.h"
#include "m_actor.h"
#include "unk.h"

struct Hatumode_Npc0;

typedef struct Hatumode_Npc0 {
    /* 0x000 */ Actor actor;
    /* 0x174 */ UNK_TYPE1 unk_174[0x7DC];
} Hatumode_Npc0; // size = 0x950

#endif
