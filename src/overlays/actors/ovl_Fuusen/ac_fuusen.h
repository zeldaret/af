#ifndef AC_FUUSEN_H
#define AC_FUUSEN_H

#include "ultra64.h"
#include "m_actor.h"
#include "unk.h"
#include "c_keyframe.h"

struct Game_Play;
struct Fuusen;

typedef void (*FuusenInitFunc)(struct Fuusen*, struct Game_Play*);
typedef void (*FuusenActionFunc)(struct Actor*, struct Game_Play*);

typedef enum FuusenProcess {
    FSN_PROCESS_BIRTH,
    FSN_PROCESS_MOVING,
    FSN_PROCESS_WOOD_STOP,
    FSN_PROCESS_ESCAPE,
} FuusenProcess;

typedef enum FuusenRand {
    FSN_RAND_X,
    FSN_RAND_Z,
} FuusenRand;

typedef struct Fuusen {
    Actor actor;
    FuusenActionFunc process;
    void* segment;
    s32 processNum;
    u32 colorIndex;
    s32 escapeTimer;
    s32 birthTimer;
    s32 unk_18C;
    s32 shouldLookUp;
    s32 dataIndex;
    s16 heightAmplitudeCounter;
    f32 windPower;
    f32 heightOffset;
    u8 unk_1A4;
    SkeletonInfoR skeletonInfo; // 0x1A8
    s_xyz jointTable[0x4]; // 0x218
    s_xyz morphTable[0x4]; // 0x230
    Mtx mtx[2][4];
} Fuusen; // size = 0x448

#endif
