#ifndef AC_HOUSE_GOKI_H
#define AC_HOUSE_GOKI_H

#include "m_actor.h"
#include "unk.h"

struct Game_Play;
struct House_Goki;

typedef void (*House_GokiActionFunc)(struct House_Goki*, struct Game_Play*);

typedef struct House_Goki {
    /* 0x000 */ Actor actor;
    /* 0x174 */ UNK_TYPE1 unk_174[0x190 - 0x174];
    /* 0x174 */ s32 unk_190;
    /* 0x194 */ UNK_TYPE1 unk_194[0x19C - 0x194];
} House_Goki; // size = 0x19C

#endif
