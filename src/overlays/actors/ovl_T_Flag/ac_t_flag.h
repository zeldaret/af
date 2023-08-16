#ifndef AC_T_FLAG_H
#define AC_T_FLAG_H

#include "ultra64.h"
#include "m_actor.h"
#include "unk.h"

struct T_Flag;

typedef struct T_Flag {
    /* 0x000 */ Actor actor;
    /* 0x174 */ UNK_TYPE1 unk_174[0x68];
} T_Flag; // size = 0x1DC

#endif
