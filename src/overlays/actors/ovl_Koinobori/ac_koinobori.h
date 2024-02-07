#ifndef AC_KOINOBORI_H
#define AC_KOINOBORI_H

#include "ultra64.h"
#include "m_actor.h"
#include "unk.h"
#include "c_keyframe.h"

struct Game_Play;
struct Koinobori;

typedef void (*KoinoboriActionFunc)(struct Koinobori*, struct Game_Play*);

typedef struct Koinobori {
    /* 0x000 */ Actor actor;
    /* 0x174 */ s32 unk174;
    /* 0x178 */ SkeletonInfoR skeletonInfo;
    /* 0x1E8 */ s32 unk1E8;
    /* 0x1EC */ s_xyz jointTable[15];
    /* 0x246 */ s_xyz morphTable[15];
    /* 0x2A0 */ KoinoboriActionFunc unk2A0;
    /* 0x2A4 */ UNK_TYPE1 unk2A4[0x10];
    /* 0x2B4 */ UNK_TYPE unk2B4;
    /* 0x2B8 */ UNK_TYPE1 unk2B8[0x4];
    /* 0x2BC */ UNK_TYPE unk2BC;
    /* 0x2C0 */ UNK_TYPE1 unk2C0[0x8];
    /* 0x2C8 */ f32 unk2C8;
    /* 0x2CC */ f32 unk2CC;
    /* 0x2D0 */ f32 unk2D0;
    /* 0x2D4 */ UNK_TYPE1 unk2D4[0x4];
} Koinobori; // size = 0x2D8

#endif
