#ifndef AC_TAMAIRE_NPC1_H
#define AC_TAMAIRE_NPC1_H

#include "ultra64.h"
#include "m_actor.h"
#include "unk.h"

struct Tamaire_Npc1;

typedef struct Tamaire_Npc1 {
    /* 0x000 */ Actor actor;
    /* 0x174 */ UNK_TYPE1 unk_174[0x7E4];
} Tamaire_Npc1; // size = 0x958

#endif
