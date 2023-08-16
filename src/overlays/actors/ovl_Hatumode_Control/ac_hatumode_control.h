#ifndef AC_HATUMODE_CONTROL_H
#define AC_HATUMODE_CONTROL_H

#include "ultra64.h"
#include "m_actor.h"
#include "unk.h"

struct Hatumode_Control;

typedef struct Hatumode_Control {
    /* 0x000 */ Actor actor;
    /* 0x174 */ UNK_TYPE1 unk_174[0x18];
} Hatumode_Control; // size = 0x18C

#endif
