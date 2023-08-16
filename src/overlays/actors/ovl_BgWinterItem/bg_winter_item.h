#ifndef BG_WINTER_ITEM_H
#define BG_WINTER_ITEM_H

#include "ultra64.h"
#include "m_actor.h"
#include "unk.h"

struct PlayState;
struct BgWinterItem;

typedef void (*BgWinterItemActionFunc)(struct BgWinterItem*, struct PlayState*);

typedef struct BgWinterItem {
    /* 0x00000 */ Actor actor;
    /* 0x00174 */ UNK_TYPE1 unk_00174[0x12D2C];
} BgWinterItem; // size = 0x12EA0

#endif
