#ifndef AC_SHOP_LEVEL_H
#define AC_SHOP_LEVEL_H

#include "ultra64.h"
#include "m_actor.h"
#include "unk.h"

struct PlayState;
struct Shop_Level;

typedef void (*Shop_LevelActionFunc)(struct Shop_Level*, struct PlayState*);

typedef struct Shop_Level {
    /* 0x000 */ Actor actor;
    /* 0x174 */ UNK_TYPE1 unk_174[0x8];
} Shop_Level; // size = 0x17C

#endif
