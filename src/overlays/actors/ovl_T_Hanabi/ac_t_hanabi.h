#ifndef AC_T_HANABI_H
#define AC_T_HANABI_H

#include "ultra64.h"
#include "m_actor.h"
#include "overlays/actors/ovl_Tools/ac_tools.h"
#include "unk.h"

struct Game_Play;
struct T_Hanabi;

typedef void (*T_HanabiActionFunc)(struct T_Hanabi*);

typedef struct T_Hanabi {
    /* 0x000 */ ToolActor toolActor;
    /* 0x1C0 */ UNK_TYPE1 unk1C0[0x8];
    /* 0x1C8 */ T_HanabiActionFunc process;
    /* 0x1CC */ s32 processIndex;
} T_Hanabi; // size = 0x1D0

#endif
