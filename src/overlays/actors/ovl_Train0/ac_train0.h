#ifndef AC_TRAIN0_H
#define AC_TRAIN0_H

#include "ultra64.h"
#include "m_actor.h"
#include "unk.h"

struct PlayState;
struct Train0;

typedef void (*Train0ActionFunc)(struct Train0*, struct PlayState*);

typedef struct Train0 {
    /* 0x000 */ Actor actor;
    /* 0x174 */ UNK_TYPE1 unk_174[0x164];
} Train0; // size = 0x2D8

#endif
