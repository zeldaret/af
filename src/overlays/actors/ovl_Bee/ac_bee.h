#ifndef AC_BEE_H
#define AC_BEE_H

#include "ultra64.h"
#include "m_actor.h"
#include "unk.h"
#include "c_keyframe.h"

struct Game_Play;
struct Bee;

typedef enum BeeProcess {
    BEE_PROCESS_APPEAR,
    BEE_PROCESS_1,
    BEE_PROCESS_DISAPPEAR,
} BeeProcess;

typedef enum BeeState {
    BEE_STATE_0,
    BEE_STATE_1,
    BEE_STATE_2,
} BeeState;

typedef struct Clip_unk_07C_unk_0_arg0 {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ xyz_t unk_04;
    /* 0x10 */ s32 unk_10;
    /* 0x14 */ struct Game_Play* unk_14;
} Clip_unk_07C_unk_0_arg0; // size >= 0x18

typedef void (*BeeActionFunc)(struct Bee*, struct Game_Play*);

typedef struct Bee {
    /* 0x000 */ Actor actor;
    /* 0x174 */ BeeActionFunc process;
    /* 0x178 */ void* segment;
    /* 0x17C */ s32 processNum;
    /* 0x180 */ SkeletonInfoR skeletonInfo;
    /* 0x1F0 */ s_xyz jointTable[4];
    /* 0x208 */ s_xyz morphTable[4];
    /* 0x220 */ Mtx mtx[2][4];
    /* 0x420 */ xyz_t targetScale;
    /* 0x42C */ f32 targetSpeed;
    /* 0x430 */ f32 shapeFactor;
    /* 0x434 */ f32 targetHeight;
    /* 0x438 */ s32 alpha;
    /* 0x43C */ s16 heightAmplitudeCounter;
    /* 0x43E */ s16 rotStep;
    /* 0x440 */ s16 texScrollCounter1;
    /* 0x442 */ s16 texScrollCounter2;
    /* 0x444 */ s16 targetRotStep;
    /* 0x446 */ u8 state;
    /* 0x448 */ u32 unk_448;
    /* 0x000 */ UNK_TYPE1 unk_44C[0x4];
} Bee; // size 0x450

#endif
