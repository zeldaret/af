#ifndef AC_SHOP_DESIGN_H
#define AC_SHOP_DESIGN_H

#include "ultra64.h"
#include "m_actor.h"
#include "unk.h"

struct Game_Play;
struct Shop_Design;

typedef void (*Shop_DesignActionFunc)(struct Shop_Design*, struct Game_Play*);

typedef struct Shop_Design {
    /* 0x000 */ Actor actor;
    /* 0x174 */ UNK_TYPE1 unk_174[0x18];
} Shop_Design; // size = 0x18C

#endif
