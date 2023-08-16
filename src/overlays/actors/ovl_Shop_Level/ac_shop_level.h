#ifndef AC_SHOP_LEVEL_H
#define AC_SHOP_LEVEL_H

#include "ultra64.h"
#include "m_actor.h"
#include "unk.h"

struct Shop_Level;

typedef struct Shop_Level {
    /* 0x000 */ Actor actor;
    /* 0x174 */ UNK_TYPE1 unk_174[0x8];
} Shop_Level; // size = 0x17C

#endif
