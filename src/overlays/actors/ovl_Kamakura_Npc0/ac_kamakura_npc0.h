#ifndef AC_KAMAKURA_NPC0_H
#define AC_KAMAKURA_NPC0_H

#include "ultra64.h"
#include "m_actor.h"
#include "unk.h"

struct Kamakura_Npc0;

typedef struct Kamakura_Npc0 {
    /* 0x000 */ Actor actor;
    /* 0x174 */ UNK_TYPE1 unk_174[0x7C4];
} Kamakura_Npc0; // size = 0x938

#endif
