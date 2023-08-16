#ifndef AC_NPC_SLEEP_OBABA_H
#define AC_NPC_SLEEP_OBABA_H

#include "ultra64.h"
#include "m_actor.h"
#include "unk.h"

struct PlayState;
struct Npc_Sleep_Obaba;

typedef void (*Npc_Sleep_ObabaActionFunc)(struct Npc_Sleep_Obaba*, struct PlayState*);

typedef struct Npc_Sleep_Obaba {
    /* 0x000 */ Actor actor;
    /* 0x174 */ UNK_TYPE1 unk_174[0x7CC];
} Npc_Sleep_Obaba; // size = 0x940

#endif
