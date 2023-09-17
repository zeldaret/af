#ifndef AC_FALLS_H
#define AC_FALLS_H

#include "ultra64.h"
#include "m_actor.h"
#include "unk.h"

struct Game_Play;
struct FallS;

typedef void (*FallSActionFunc)(struct FallS*, struct Game_Play*);

typedef struct FallS {
    /* 0x000 */ Actor actor;
    /* 0x174 */ UNK_TYPE1 unk_174[0x164];
} FallS; // size = 0x2D8

#endif
