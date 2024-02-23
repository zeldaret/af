#ifndef AC_T_KEITAI_H
#define AC_T_KEITAI_H

#include "ultra64.h"
#include "c_keyframe.h"
#include "m_actor.h"
#include "overlays/actors/ovl_Tools/ac_tools.h"
#include "unk.h"

struct Game_Play;
struct T_Keitai;

typedef void (*T_KeitaiActionFunc)(struct T_Keitai*);

typedef struct T_Keitai {
    /* 0x000 */ ToolActor toolActor;
    /* 0x1C0 */ UNK_TYPE1 unk_1C0[0x8];
    /* 0x1C8 */ T_KeitaiActionFunc process;
    /* 0x1CC */ s32 processIndex;
    /* 0x1D0 */ SkeletonInfoR skeletonInfo;
    /* 0x240 */ s_xyz jointTable[4];
    /* 0x258 */ s_xyz morphTable[4];
    /* 0x270 */ void* segment;
} T_Keitai; // size = 0x274

#endif
