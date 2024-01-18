#ifndef AC_SAMPLE_H
#define AC_SAMPLE_H

#include "ultra64.h"
#include "m_actor.h"
#include "m_collision_obj.h"
#include "unk.h"
#include "c_keyframe.h"

struct Game_Play;
struct Sample;

typedef void (*SampleActionFunc)(struct Sample*, struct Game_Play*);

typedef struct Sample {
    /* 0x000 */Actor actor;
    /* 0x174 */SkeletonInfoR skeletonInfo;
    /* 0x1E4 */s_xyz workArea[8];
    /* 0x214 */s_xyz morphArea[8];
    /* 0x244 */ClObjPipe stand;
    /* 0x260 */s32 mainAction;
    /* 0x264 */s32 drawAction;
    /* 0x268 */void* segment;
} Sample; // size = 0x26C

#endif
