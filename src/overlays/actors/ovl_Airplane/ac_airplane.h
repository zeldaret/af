#ifndef AC_AIRPLANE_H
#define AC_AIRPLANE_H

#include "ultra64.h"
#include "m_actor.h"
#include "unk.h"

struct Airplane;

typedef struct Airplane {
    /* 0x000 */ Actor actor;
    /* 0x174 */ UNK_TYPE1 unk_174[0x54];
} Airplane; // size = 0x1C8

#endif
