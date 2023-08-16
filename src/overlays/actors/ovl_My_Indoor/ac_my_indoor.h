#ifndef AC_MY_INDOOR_H
#define AC_MY_INDOOR_H

#include "ultra64.h"
#include "m_actor.h"
#include "unk.h"

struct My_Indoor;

typedef struct My_Indoor {
    /* 0x000 */ Actor actor;
    /* 0x174 */ UNK_TYPE1 unk_174[0x44];
} My_Indoor; // size = 0x1B8

#endif
