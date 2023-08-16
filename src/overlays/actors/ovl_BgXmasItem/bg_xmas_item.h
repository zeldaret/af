#ifndef BG_XMAS_ITEM_H
#define BG_XMAS_ITEM_H

#include "ultra64.h"
#include "m_actor.h"
#include "unk.h"

struct BgXmasItem;

typedef struct BgXmasItem {
    /* 0x00000 */ Actor actor;
    /* 0x00174 */ UNK_TYPE1 unk_00174[0x13D44];
} BgXmasItem; // size = 0x13EB8

#endif
