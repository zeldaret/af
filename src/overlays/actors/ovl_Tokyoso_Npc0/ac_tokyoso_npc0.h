#ifndef AC_TOKYOSO_NPC0_H
#define AC_TOKYOSO_NPC0_H

#include "ultra64.h"
#include "m_actor.h"
#include "unk.h"

struct PlayState;
struct Tokyoso_Npc0;

typedef void (*Tokyoso_Npc0ActionFunc)(struct Tokyoso_Npc0*, struct PlayState*);

typedef struct Tokyoso_Npc0 {
    /* 0x000 */ Actor actor;
    /* 0x174 */ UNK_TYPE1 unk_174[0x7DC];
} Tokyoso_Npc0; // size = 0x950

#endif
