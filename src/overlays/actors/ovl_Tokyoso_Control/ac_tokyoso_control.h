#ifndef AC_TOKYOSO_CONTROL_H
#define AC_TOKYOSO_CONTROL_H

#include "ultra64.h"
#include "m_actor.h"
#include "unk.h"

struct Tokyoso_Control;

typedef struct Tokyoso_Control {
    /* 0x000 */ Actor actor;
    /* 0x174 */ UNK_TYPE1 unk_174[0x34];
} Tokyoso_Control; // size = 0x1A8

#endif
