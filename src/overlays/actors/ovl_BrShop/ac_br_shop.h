#ifndef AC_BR_SHOP_H
#define AC_BR_SHOP_H

#include "ultra64.h"
#include "m_actor.h"
#include "unk.h"

struct PlayState;
struct BrShop;

typedef void (*BrShopActionFunc)(struct BrShop*, struct PlayState*);

typedef struct BrShop {
    /* 0x000 */ Actor actor;
    /* 0x174 */ UNK_TYPE1 unk_174[0x164];
} BrShop; // size = 0x2D8

#endif
