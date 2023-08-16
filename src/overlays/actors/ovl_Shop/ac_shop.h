#ifndef AC_SHOP_H
#define AC_SHOP_H

#include "ultra64.h"
#include "m_actor.h"
#include "unk.h"

struct Shop;

typedef struct Shop {
    /* 0x000 */ Actor actor;
    /* 0x174 */ UNK_TYPE1 unk_174[0x164];
} Shop; // size = 0x2D8

#endif
