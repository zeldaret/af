#ifndef AC_SHOP_UMBRELLA_H
#define AC_SHOP_UMBRELLA_H

#include "ultra64.h"
#include "m_actor.h"
#include "unk.h"

struct Shop_Umbrella;

typedef struct Shop_Umbrella {
    /* 0x000 */ Actor actor;
    /* 0x174 */ UNK_TYPE1 unk_174[0x1C];
} Shop_Umbrella; // size = 0x190

#endif
