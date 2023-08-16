#ifndef AC_TURI_NPC0_H
#define AC_TURI_NPC0_H

#include "ultra64.h"
#include "m_actor.h"
#include "unk.h"

struct PlayState;
struct Turi_Npc0;

typedef void (*Turi_Npc0ActionFunc)(struct Turi_Npc0*, struct PlayState*);

typedef struct Turi_Npc0 {
    /* 0x000 */ Actor actor;
    /* 0x174 */ UNK_TYPE1 unk_174[0x7CC];
} Turi_Npc0; // size = 0x940

#endif
