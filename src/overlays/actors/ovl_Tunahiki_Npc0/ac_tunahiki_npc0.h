#ifndef AC_TUNAHIKI_NPC0_H
#define AC_TUNAHIKI_NPC0_H

#include "ultra64.h"
#include "m_actor.h"
#include "unk.h"

struct PlayState;
struct Tunahiki_Npc0;

typedef void (*Tunahiki_Npc0ActionFunc)(struct Tunahiki_Npc0*, struct PlayState*);

typedef struct Tunahiki_Npc0 {
    /* 0x000 */ Actor actor;
    /* 0x174 */ UNK_TYPE1 unk_174[0x7DC];
} Tunahiki_Npc0; // size = 0x950

#endif
