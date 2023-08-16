#ifndef AC_HOUSE_GOKI_H
#define AC_HOUSE_GOKI_H

#include "ultra64.h"
#include "m_actor.h"
#include "unk.h"

struct PlayState;
struct House_Goki;

typedef void (*House_GokiActionFunc)(struct House_Goki*, struct PlayState*);

typedef struct House_Goki {
    /* 0x000 */ Actor actor;
    /* 0x174 */ UNK_TYPE1 unk_174[0x28];
} House_Goki; // size = 0x19C

#endif
