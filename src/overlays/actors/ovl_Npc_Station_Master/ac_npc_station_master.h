#ifndef AC_NPC_STATION_MASTER_H
#define AC_NPC_STATION_MASTER_H

#include "ultra64.h"
#include "m_actor.h"
#include "unk.h"

struct Game_Play;
struct Npc_Station_Master;

typedef void (*Npc_Station_MasterActionFunc)(struct Npc_Station_Master*, struct Game_Play*);

typedef struct Npc_Station_Master {
    /* 0x000 */ Actor actor;
    /* 0x174 */ UNK_TYPE1 unk_174[0x7DC];
} Npc_Station_Master; // size = 0x950

#endif
