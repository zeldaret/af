#ifndef AC_EV_PUMPKIN_H
#define AC_EV_PUMPKIN_H

#include "ultra64.h"
#include "m_actor.h"
#include "unk.h"

struct Ev_Pumpkin;

typedef struct Ev_Pumpkin {
    /* 0x000 */ Actor actor;
    /* 0x174 */ UNK_TYPE1 unk_174[0x7D4];
} Ev_Pumpkin; // size = 0x948

#endif
