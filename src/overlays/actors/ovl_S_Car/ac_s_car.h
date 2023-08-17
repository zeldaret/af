#ifndef AC_S_CAR_H
#define AC_S_CAR_H

#include "ultra64.h"
#include "m_actor.h"
#include "unk.h"

struct PlayState;
struct S_Car;

typedef void (*S_CarActionFunc)(struct S_Car*, struct PlayState*);

typedef struct S_Car {
    /* 0x000 */ Actor actor;
    /* 0x174 */ UNK_TYPE1 unk_174[0x164];
} S_Car; // size = 0x2D8

#endif
