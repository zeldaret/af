#ifndef AC_HANABI_NPC1_H
#define AC_HANABI_NPC1_H

#include "ultra64.h"
#include "m_actor.h"
#include "unk.h"

struct Game_Play;
struct Hanabi_Npc1;

typedef void (*Hanabi_Npc1ActionFunc)(struct Hanabi_Npc1*, struct Game_Play*);

typedef struct Hanabi_Npc1 {
    /* 0x000 */ Actor actor;
    /* 0x174 */ UNK_TYPE1 unk_174[0x7D8];
} Hanabi_Npc1; // size = 0x94C

#endif
