#ifndef AC_NPC_SUPER_MASTER_H
#define AC_NPC_SUPER_MASTER_H

#include "ultra64.h"
#include "m_actor.h"
#include "unk.h"

struct Game_Play;
struct Npc_Super_Master;

typedef void (*Npc_Super_MasterActionFunc)(struct Npc_Super_Master*, struct Game_Play*);

typedef struct Npc_Super_Master {
    /* 0x000 */ Actor actor;
    /* 0x174 */ UNK_TYPE1 unk_174[0x7F8];
} Npc_Super_Master; // size = 0x96C

#endif
