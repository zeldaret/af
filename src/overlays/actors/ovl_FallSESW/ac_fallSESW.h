#ifndef AC_FALLSESW_H
#define AC_FALLSESW_H

#include "ultra64.h"
#include "m_actor.h"
#include "unk.h"

struct Game_Play;
struct FallSESW;

typedef void (*FallSESWActionFunc)(struct FallSESW*, struct Game_Play*);

typedef struct FallSESW {
    /* 0x000 */ Actor actor;
    /* 0x174 */ UNK_TYPE1 unk_174[0x164];
} FallSESW; // size = 0x2D8

#endif
