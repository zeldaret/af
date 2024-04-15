#ifndef AC_BALL_H
#define AC_BALL_H

#include "ultra64.h"
#include "m_actor.h"
#include "m_collision_obj.h"
#include "unk.h"
#include "c_keyframe.h"

struct Game_Play;
struct Ball;

#define BALL_208_FLAG_1 (1 << 0)
#define BALL_208_FLAG_2 (1 << 1)
#define BALL_208_FLAG_4 (1 << 2)
#define BALL_208_FLAG_8 (1 << 3)

typedef enum BallType {
    BALL_TYPE_B,
    BALL_TYPE_D,
    BALL_TYPE_S,
} BallType;

typedef void (*BallActionFunc)(struct Ball*, struct Game_Play*);

typedef struct Ball {
    /* 0x000 */ Actor actor;
    /* 0x174 */ ClObjPipe collider;
    /* 0x190 */ UNK_TYPE1 unk_190[0x40];
    /* 0x1D0 */ xyz_t bgPos;
    /* 0x1DC */ Actor* colliderActor;
    /* 0x1E0 */ BallActionFunc process;
    /* 0x1E4 */ void* segment;
    /* 0x1E8 */ f32 height;
    /* 0x1EC */ f32 maxSpeed;
    /* 0x1F0 */ f32 acceleration;
    /* 0x1F4 */ f32 speed;
    /* 0x1F8 */ s32 type;
    /* 0x1FC */ s16 waterTimer;
    /* 0x1FE */ UNK_TYPE1 unk_1FE[0x2];
    /* 0x200 */ s_xyz ballRot;
    /* 0x206 */ s16 bounceTimer;
    /* 0x208 */ s16 unk_208;
    /* 0x20A */ s16 unk_20A;
} Ball; // size 0x20C

#endif
