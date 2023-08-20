#ifndef AC_GOZA_H
#define AC_GOZA_H

#include "ultra64.h"
#include "m_actor.h"
#include "unk.h"

struct Game_Play;
struct Goza;

typedef void (*GozaActionFunc)(struct Goza*, struct Game_Play*);

typedef struct Goza {
    /* 0x000 */ Actor actor;
    /* 0x174 */ UNK_TYPE1 unk_174[0x164];
} Goza; // size = 0x2D8

#endif
