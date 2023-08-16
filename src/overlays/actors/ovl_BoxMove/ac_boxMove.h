#ifndef AC_BOXMOVE_H
#define AC_BOXMOVE_H

#include "ultra64.h"
#include "m_actor.h"
#include "unk.h"

struct BoxMove;

typedef struct BoxMove {
    /* 0x000 */ Actor actor;
    /* 0x174 */ UNK_TYPE1 unk_174[0x118];
} BoxMove; // size = 0x28C

#endif
