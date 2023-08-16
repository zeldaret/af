#ifndef AC_NPC2_H
#define AC_NPC2_H

#include "ultra64.h"
#include "m_actor.h"
#include "unk.h"

struct Npc2;

typedef struct Npc2 {
    /* 0x000 */ Actor actor;
    /* 0x174 */ UNK_TYPE1 unk_174[0x8D0];
} Npc2; // size = 0xA44

#endif
