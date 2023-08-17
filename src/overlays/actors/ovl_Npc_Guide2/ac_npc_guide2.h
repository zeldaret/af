#ifndef AC_NPC_GUIDE2_H
#define AC_NPC_GUIDE2_H

#include "ultra64.h"
#include "m_actor.h"
#include "unk.h"

struct PlayState;
struct Npc_Guide2;

typedef void (*Npc_Guide2ActionFunc)(struct Npc_Guide2*, struct PlayState*);

typedef struct Npc_Guide2 {
    /* 0x000 */ Actor actor;
    /* 0x174 */ UNK_TYPE1 unk_174[0x800];
} Npc_Guide2; // size = 0x974

#endif
