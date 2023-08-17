#ifndef AC_TOUDAI_H
#define AC_TOUDAI_H

#include "ultra64.h"
#include "m_actor.h"
#include "unk.h"
#include "z64math.h"
#include "c_keyframe.h"

struct PlayState;
struct Toudai;

typedef void (*ToudaiActionFunc)(struct Toudai*, struct PlayState*);

typedef struct Toudai {
    /* 0x000 */ Actor actor;
    /* 0x174 */ s32 unk174;
    /* 0x178 */ SkeletonInfoR skeletonInfo;
    /* 0x1E8 */ s32 unk1E8; //maybe f32?
    /* 0x1EC */ Vec3s jointTable; //todo make the right array size
    /* 0x1F2 */ UNK_TYPE1 unk1F2[0x54];
    /* 0x246 */ Vec3s morphTable; //todo make the right array size
    /* 0x24C */ UNK_TYPE1 unk24C[0x54];
    /* 0x2A0 */ ToudaiActionFunc unk2A0;
    /* 0x2A4 */ UNK_TYPE1 unk2A4[0x38];
} Toudai; // size = 0x2D8

#endif
