#ifndef AC_NPC_DEPART_MASTER_H
#define AC_NPC_DEPART_MASTER_H

#include "ultra64.h"
#include "m_actor.h"
#include "unk.h"

struct PlayState;
struct Npc_Depart_Master;

typedef void (*Npc_Depart_MasterActionFunc)(struct Npc_Depart_Master*, struct PlayState*);

typedef struct Npc_Depart_Master {
    /* 0x000 */ Actor actor;
    /* 0x174 */ UNK_TYPE1 unk_174[0x7F8];
} Npc_Depart_Master; // size = 0x96C

#endif
