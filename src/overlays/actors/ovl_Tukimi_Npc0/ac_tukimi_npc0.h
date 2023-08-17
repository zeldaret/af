#ifndef AC_TUKIMI_NPC0_H
#define AC_TUKIMI_NPC0_H

#include "ultra64.h"
#include "m_actor.h"
#include "unk.h"

struct PlayState;
struct Tukimi_Npc0;

typedef void (*Tukimi_Npc0ActionFunc)(struct Tukimi_Npc0*, struct PlayState*);

typedef struct Tukimi_Npc0 {
    /* 0x000 */ Actor actor;
    /* 0x174 */ UNK_TYPE1 unk_174[0x7C4];
} Tukimi_Npc0; // size = 0x938

#endif
