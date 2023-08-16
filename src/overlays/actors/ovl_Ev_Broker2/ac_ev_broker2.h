#ifndef AC_EV_BROKER2_H
#define AC_EV_BROKER2_H

#include "ultra64.h"
#include "m_actor.h"
#include "unk.h"

struct Ev_Broker2;

typedef struct Ev_Broker2 {
    /* 0x000 */ Actor actor;
    /* 0x174 */ UNK_TYPE1 unk_174[0x7D8];
} Ev_Broker2; // size = 0x94C

#endif
