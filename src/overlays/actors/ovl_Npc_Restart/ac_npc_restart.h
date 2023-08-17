#ifndef AC_NPC_RESTART_H
#define AC_NPC_RESTART_H

#include "ultra64.h"
#include "m_actor.h"
#include "unk.h"

struct PlayState;
struct Npc_Restart;

typedef void (*Npc_RestartActionFunc)(struct Npc_Restart*, struct PlayState*);

typedef struct Npc_Restart {
    /* 0x000 */ Actor actor;
    /* 0x174 */ UNK_TYPE1 unk_174[0x7DC];
} Npc_Restart; // size = 0x950

#endif
