#ifndef AC_T_CRACKER_H
#define AC_T_CRACKER_H

#include "ultra64.h"
#include "m_actor.h"
#include "unk.h"

struct Game_Play;
struct T_Cracker;

typedef void (*T_CrackerActionFunc)(struct T_Cracker*, struct Game_Play*);

typedef struct T_Cracker {
    /* 0x000 */ Actor actor;
    /* 0x174 */ UNK_TYPE1 unk_174[0x5C];
} T_Cracker; // size = 0x1D0

#endif
