#ifndef AC_COUNTDOWN_NPC1_H
#define AC_COUNTDOWN_NPC1_H

#include "ultra64.h"
#include "m_actor.h"
#include "unk.h"

struct Game_Play;
struct Countdown_Npc1;

typedef void (*Countdown_Npc1ActionFunc)(struct Countdown_Npc1*, struct Game_Play*);

typedef struct Countdown_Npc1 {
    /* 0x000 */ Actor actor;
    /* 0x174 */ UNK_TYPE1 unk_174[0x7E0];
} Countdown_Npc1; // size = 0x954

#endif
