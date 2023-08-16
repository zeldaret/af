#ifndef AC_EV_KABUPEDDLER_H
#define AC_EV_KABUPEDDLER_H

#include "ultra64.h"
#include "m_actor.h"
#include "unk.h"

struct Ev_KabuPeddler;

typedef struct Ev_KabuPeddler {
    /* 0x000 */ Actor actor;
    /* 0x174 */ UNK_TYPE1 unk_174[0x7D4];
} Ev_KabuPeddler; // size = 0x948

#endif
