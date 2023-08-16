#ifndef AC_NPC_MAMEDANUKI_H
#define AC_NPC_MAMEDANUKI_H

#include "ultra64.h"
#include "m_actor.h"
#include "unk.h"

struct PlayState;
struct Npc_Mamedanuki;

typedef void (*Npc_MamedanukiActionFunc)(struct Npc_Mamedanuki*, struct PlayState*);

typedef struct Npc_Mamedanuki {
    /* 0x000 */ Actor actor;
    /* 0x174 */ UNK_TYPE1 unk_174[0x7F8];
} Npc_Mamedanuki; // size = 0x96C

#endif
