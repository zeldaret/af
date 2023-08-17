#ifndef BG_POST_ITEM_H
#define BG_POST_ITEM_H

#include "ultra64.h"
#include "m_actor.h"
#include "unk.h"

struct Game_Play;
struct BgPostItem;

typedef void (*BgPostItemActionFunc)(struct BgPostItem*, struct Game_Play*);

typedef struct BgPostItem {
    /* 0x000 */ Actor actor;
    /* 0x174 */ UNK_TYPE1 unk_174[0x4];
} BgPostItem; // size = 0x178

#endif
