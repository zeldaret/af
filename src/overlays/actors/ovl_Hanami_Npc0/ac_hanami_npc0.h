#ifndef AC_HANAMI_NPC0_H
#define AC_HANAMI_NPC0_H

#include "ultra64.h"
#include "m_actor.h"
#include "unk.h"

struct PlayState;
struct Hanami_Npc0;

typedef void (*Hanami_Npc0ActionFunc)(struct Hanami_Npc0*, struct PlayState*);

typedef struct Hanami_Npc0 {
    /* 0x000 */ Actor actor;
    /* 0x174 */ UNK_TYPE1 unk_174[0x7D4];
} Hanami_Npc0; // size = 0x948

#endif
