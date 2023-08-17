#ifndef AC_RESERVE_H
#define AC_RESERVE_H

#include "ultra64.h"
#include "m_actor.h"
#include "unk.h"

struct Game_Play;
struct Reserve;

typedef void (*ReserveActionFunc)(struct Reserve*, struct Game_Play*);

typedef struct Reserve {
    /* 0x000 */ Actor actor;
    /* 0x174 */ UNK_TYPE1 unk_174[0x164];
} Reserve; // size = 0x2D8

#endif
