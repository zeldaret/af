#ifndef AC_T_TUMBLER_H
#define AC_T_TUMBLER_H

#include "ultra64.h"
#include "m_actor.h"
#include "unk.h"

struct PlayState;
struct T_Tumbler;

typedef void (*T_TumblerActionFunc)(struct T_Tumbler*, struct PlayState*);

typedef struct T_Tumbler {
    /* 0x000 */ Actor actor;
    /* 0x174 */ UNK_TYPE1 unk_174[0x5C];
} T_Tumbler; // size = 0x1D0

#endif
