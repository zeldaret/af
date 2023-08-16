#ifndef AC_EV_SANTA_H
#define AC_EV_SANTA_H

#include "ultra64.h"
#include "m_actor.h"
#include "unk.h"

struct Ev_Santa;

typedef struct Ev_Santa {
    /* 0x000 */ Actor actor;
    /* 0x174 */ UNK_TYPE1 unk_174[0x7E0];
} Ev_Santa; // size = 0x954

#endif
