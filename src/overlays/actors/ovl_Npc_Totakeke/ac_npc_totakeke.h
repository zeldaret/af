#ifndef AC_NPC_TOTAKEKE_H
#define AC_NPC_TOTAKEKE_H

#include "ultra64.h"
#include "m_actor.h"
#include "unk.h"

struct Npc_Totakeke;

typedef struct Npc_Totakeke {
    /* 0x000 */ Actor actor;
    /* 0x174 */ UNK_TYPE1 unk_174[0x7DC];
} Npc_Totakeke; // size = 0x950

#endif
