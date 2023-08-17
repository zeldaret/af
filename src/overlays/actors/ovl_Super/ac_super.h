#ifndef AC_SUPER_H
#define AC_SUPER_H

#include "ultra64.h"
#include "m_actor.h"
#include "unk.h"

struct PlayState;
struct Super;

typedef void (*SuperActionFunc)(struct Super*, struct PlayState*);

typedef struct Super {
    /* 0x000 */ Actor actor;
    /* 0x174 */ UNK_TYPE1 unk_174[0x164];
} Super; // size = 0x2D8

#endif
