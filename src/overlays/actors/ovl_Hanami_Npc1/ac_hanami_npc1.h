#ifndef AC_HANAMI_NPC1_H
#define AC_HANAMI_NPC1_H

#include "ultra64.h"
#include "m_actor.h"
#include "unk.h"

struct Game_Play;
struct Hanami_Npc1;

typedef void (*Hanami_Npc1ActionFunc)(struct Hanami_Npc1*, struct Game_Play*);

typedef struct Hanami_Npc1 {
    /* 0x000 */ Actor actor;
    /* 0x174 */ UNK_TYPE1 unk_174[0x7D0];
} Hanami_Npc1; // size = 0x944

#endif
