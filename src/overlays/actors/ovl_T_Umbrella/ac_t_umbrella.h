#ifndef AC_T_UMBRELLA_H
#define AC_T_UMBRELLA_H

#include "ultra64.h"
#include "m_actor.h"
#include "unk.h"

struct PlayState;
struct T_Umbrella;

typedef void (*T_UmbrellaActionFunc)(struct T_Umbrella*, struct PlayState*);

typedef struct T_Umbrella {
    /* 0x000 */ Actor actor;
    /* 0x174 */ UNK_TYPE1 unk_174[0x7C];
} T_Umbrella; // size = 0x1F0

#endif
