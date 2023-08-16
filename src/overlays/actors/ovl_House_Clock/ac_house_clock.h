#ifndef AC_HOUSE_CLOCK_H
#define AC_HOUSE_CLOCK_H

#include "ultra64.h"
#include "m_actor.h"
#include "unk.h"

struct PlayState;
struct House_Clock;

typedef void (*House_ClockActionFunc)(struct House_Clock*, struct PlayState*);

typedef struct House_Clock {
    /* 0x000 */ Actor actor;
    /* 0x174 */ UNK_TYPE1 unk_174[0x444];
} House_Clock; // size = 0x5B8

#endif
