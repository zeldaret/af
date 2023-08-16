#ifndef AC_EV_YOMISE_H
#define AC_EV_YOMISE_H

#include "ultra64.h"
#include "m_actor.h"
#include "unk.h"

struct Ev_Yomise;

typedef struct Ev_Yomise {
    /* 0x000 */ Actor actor;
    /* 0x174 */ UNK_TYPE1 unk_174[0x7E0];
} Ev_Yomise; // size = 0x954

#endif
