#ifndef AC_TUNAHIKI_NPC1_H
#define AC_TUNAHIKI_NPC1_H

#include "ultra64.h"
#include "m_actor.h"
#include "unk.h"

struct Tunahiki_Npc1;

typedef struct Tunahiki_Npc1 {
    /* 0x000 */ Actor actor;
    /* 0x174 */ UNK_TYPE1 unk_174[0x7D8];
} Tunahiki_Npc1; // size = 0x94C

#endif
