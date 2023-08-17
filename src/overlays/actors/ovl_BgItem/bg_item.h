#ifndef BG_ITEM_H
#define BG_ITEM_H

#include "ultra64.h"
#include "m_actor.h"
#include "unk.h"

struct PlayState;
struct BgItem;

typedef void (*BgItemActionFunc)(struct BgItem*, struct PlayState*);

typedef struct BgItem {
    /* 0x00000 */ Actor actor;
    /* 0x00174 */ UNK_TYPE1 unk_00174[0x12D34];
} BgItem; // size = 0x12EA8

#endif
