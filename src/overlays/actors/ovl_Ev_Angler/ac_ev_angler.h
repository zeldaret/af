#ifndef AC_EV_ANGLER_H
#define AC_EV_ANGLER_H

#include "ultra64.h"
#include "m_actor.h"
#include "unk.h"

struct Ev_Angler;

typedef struct Ev_Angler {
    /* 0x000 */ Actor actor;
    /* 0x174 */ UNK_TYPE1 unk_174[0x7D8];
} Ev_Angler; // size = 0x94C

#endif
