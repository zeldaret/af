#ifndef AC_TRAIN_DOOR_H
#define AC_TRAIN_DOOR_H

#include "ultra64.h"
#include "m_actor.h"
#include "c_keyframe.h"
#include "unk.h"

typedef struct TrainDoor {
    /* 0x000 */ Actor actor;
    /* 0x174 */ UNK_TYPE1 unk_174 [0x17C - 0x174];
    /* 0x17C */ SkeletonInfoR skeletonInfo;
    /* 0x1EC */ UNK_TYPE1 unk_1EC [0x210 - 0x1EC];
    /* 0x210 */ s_xyz work[4];
    /* 0x228 */ s_xyz target[4];
    /* 0x240 */ s32 idle;
}TrainDoor; // size = 0x244


#endif
