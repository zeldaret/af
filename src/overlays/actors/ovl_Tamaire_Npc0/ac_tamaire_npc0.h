#ifndef AC_TAMAIRE_NPC0_H
#define AC_TAMAIRE_NPC0_H

#include "ultra64.h"
#include "m_actor.h"
#include "unk.h"

struct Game_Play;
struct Tamaire_Npc0;

typedef void (*Tamaire_Npc0ActionFunc)(struct Tamaire_Npc0*, struct Game_Play*);

typedef struct Tamaire_Npc0 {
    /* 0x000 */ Actor actor;
    /* 0x174 */ UNK_TYPE1 unk_174[0x7DC];
} Tamaire_Npc0; // size = 0x950

#endif
