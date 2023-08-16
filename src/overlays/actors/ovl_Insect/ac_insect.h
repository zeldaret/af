#ifndef AC_INSECT_H
#define AC_INSECT_H

#include "ultra64.h"
#include "m_actor.h"
#include "unk.h"

struct PlayState;
struct Insect;

typedef void (*InsectActionFunc)(struct Insect*, struct PlayState*);

typedef struct Insect {
    /* 0x000 */ Actor actor;
    /* 0x174 */ UNK_TYPE1 unk_174[0x784];
} Insect; // size = 0x8F8

#endif
