#ifndef AC_T_HANABI_H
#define AC_T_HANABI_H

#include "ultra64.h"
#include "m_actor.h"
#include "unk.h"

struct PlayState;
struct T_Hanabi;

typedef void (*T_HanabiActionFunc)(struct T_Hanabi*, struct PlayState*);

typedef struct T_Hanabi {
    /* 0x000 */ Actor actor;
    /* 0x174 */ UNK_TYPE1 unk_174[0x5C];
} T_Hanabi; // size = 0x1D0

#endif
