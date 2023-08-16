#ifndef AC_BALL_H
#define AC_BALL_H

#include "ultra64.h"
#include "m_actor.h"
#include "unk.h"

struct PlayState;
struct Ball;

typedef void (*BallActionFunc)(struct Ball*, struct PlayState*);

typedef struct Ball {
    /* 0x000 */ Actor actor;
    /* 0x174 */ UNK_TYPE1 unk_174[0x98];
} Ball; // size = 0x20C

#endif
