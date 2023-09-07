#ifndef BG_CHERRY_ITEM_H
#define BG_CHERRY_ITEM_H

#include "ultra64.h"
#include "m_actor.h"
#include "unk.h"

struct Game_Play;
struct BgCherryItem;

typedef void (*BgCherryItemActionFunc)(struct BgCherryItem*, struct Game_Play*);

typedef struct BgCherryItem {
    /* 0x00000 */ Actor actor;
    /* 0x00174 */ UNK_TYPE1 unk_00174[0x12D34];
} BgCherryItem; // size = 0x12EA8

#endif
