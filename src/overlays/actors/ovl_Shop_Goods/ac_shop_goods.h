#ifndef AC_SHOP_GOODS_H
#define AC_SHOP_GOODS_H

#include "ultra64.h"
#include "m_actor.h"
#include "unk.h"

struct Game_Play;
struct Shop_Goods;

typedef void (*Shop_GoodsActionFunc)(struct Shop_Goods*, struct Game_Play*);

typedef struct Shop_Goods {
    /* 0x000 */ Actor actor;
    /* 0x174 */ UNK_TYPE1 unk_174[0xCC];
} Shop_Goods; // size = 0x240

#endif
