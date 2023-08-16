#ifndef AC_TUKIMI_NPC1_H
#define AC_TUKIMI_NPC1_H

#include "ultra64.h"
#include "m_actor.h"
#include "unk.h"

struct Tukimi_Npc1;

typedef struct Tukimi_Npc1 {
    /* 0x000 */ Actor actor;
    /* 0x174 */ UNK_TYPE1 unk_174[0x7C8];
} Tukimi_Npc1; // size = 0x93C

#endif
