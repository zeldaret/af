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
    /* 0x000 */ Actor actor;
    /* 0x174 */ FuusenActionFunc process;
    /* 0x178 */ void* segment;
    /* 0x17C */ s32 processNum;
    /* 0x180 */ u32 colorIndex;
    /* 0x184 */ s32 escapeTimer;
    /* 0x188 */ s32 birthTimer;
    /* 0x18C */ s32 unk_18C;
    /* 0x190 */ s32 shouldLookUp;
    /* 0x194 */ s32 dataIndex;
    /* 0x198 */ s16 heightAmplitudeCounter;
    /* 0x19C */ f32 windPower;
    /* 0x1A0 */ f32 heightOffset;
    /* 0x1A4 */ u8 unk_1A4;
    /* 0x1A8 */ SkeletonInfoR skeletonInfo;
    /* 0x218 */ s_xyz jointTable[0x4];
    /* 0x230 */ s_xyz morphTable[0x4];
    /* 0x248 */ Mtx mtx[2][4];
} Fuusen; // size = 0x448

#endif
