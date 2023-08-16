#ifndef AC_COUNTDOWN_NPC0_H
#define AC_COUNTDOWN_NPC0_H

#include "ultra64.h"
#include "m_actor.h"
#include "unk.h"

struct Countdown_Npc0;

typedef struct Countdown_Npc0 {
    /* 0x000 */ Actor actor;
    /* 0x174 */ UNK_TYPE1 unk_174[0x7D0];
} Countdown_Npc0; // size = 0x944

#endif
