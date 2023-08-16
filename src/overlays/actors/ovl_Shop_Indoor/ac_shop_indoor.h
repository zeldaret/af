#ifndef AC_SHOP_INDOOR_H
#define AC_SHOP_INDOOR_H

#include "ultra64.h"
#include "m_actor.h"
#include "unk.h"

struct PlayState;
struct Shop_Indoor;

typedef void (*Shop_IndoorActionFunc)(struct Shop_Indoor*, struct PlayState*);

typedef struct Shop_Indoor {
    /* 0x000 */ Actor actor;
    /* 0x174 */ UNK_TYPE1 unk_174[0x38];
} Shop_Indoor; // size = 0x1AC

#endif
