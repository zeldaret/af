#ifndef BG_POLICE_ITEM_H
#define BG_POLICE_ITEM_H

#include "ultra64.h"
#include "m_actor.h"
#include "unk.h"

struct Game_Play;
struct BgPoliceItem;

typedef void (*BgPoliceItemActionFunc)(struct BgPoliceItem*, struct Game_Play*);

typedef struct BgPoliceItem {
    /* 0x0000 */ Actor actor;
    /* 0x0174 */ UNK_TYPE1 unk_0174[0x44C0];
} BgPoliceItem; // size = 0x4634

#endif
