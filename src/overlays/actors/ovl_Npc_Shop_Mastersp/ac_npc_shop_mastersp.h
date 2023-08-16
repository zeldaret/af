#ifndef AC_NPC_SHOP_MASTERSP_H
#define AC_NPC_SHOP_MASTERSP_H

#include "ultra64.h"
#include "m_actor.h"
#include "unk.h"

struct Npc_Shop_Mastersp;

typedef struct Npc_Shop_Mastersp {
    /* 0x000 */ Actor actor;
    /* 0x174 */ UNK_TYPE1 unk_174[0x824];
} Npc_Shop_Mastersp; // size = 0x998

#endif
