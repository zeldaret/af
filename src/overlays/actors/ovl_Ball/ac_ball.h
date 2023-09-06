#ifndef AC_BALL_H
#define AC_BALL_H

#include "ultra64.h"
#include "m_actor.h"
#include "m_collision_obj.h"
#include "unk.h"

struct Game_Play;
struct Ball;

typedef void (*BallActionFunc)(struct Ball*, struct Game_Play*);

typedef struct Ball {
    /* 0x000 */ Actor actor;
    /* 0x174 */ ClObjPipe collider;
    /* 0x180 */ UNK_TYPE1 unk_180[0x8C];
} Ball; // size = 0x20C

#endif
