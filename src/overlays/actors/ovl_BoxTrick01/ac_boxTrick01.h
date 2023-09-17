#ifndef AC_BOXTRICK01_H
#define AC_BOXTRICK01_H

#include "ultra64.h"
#include "m_actor.h"
#include "unk.h"

struct Game_Play;
struct BoxTrick01;

typedef void (*BoxTrick01ActionFunc)(struct BoxTrick01*, struct Game_Play*);

typedef struct BoxTrick01 {
    /* 0x000 */ Actor actor;
    /* 0x174 */ UNK_TYPE1 unk_174[0x8];
} BoxTrick01; // size = 0x17C

#endif
