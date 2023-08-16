#ifndef AC_SHOP_MANEKIN_H
#define AC_SHOP_MANEKIN_H

#include "ultra64.h"
#include "m_actor.h"
#include "unk.h"

struct Shop_Manekin;

typedef struct Shop_Manekin {
    /* 0x000 */ Actor actor;
    /* 0x174 */ UNK_TYPE1 unk_174[0x2C];
} Shop_Manekin; // size = 0x1A0

#endif
