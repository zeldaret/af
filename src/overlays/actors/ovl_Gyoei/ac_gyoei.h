#ifndef AC_GYOEI_H
#define AC_GYOEI_H

#include "ultra64.h"
#include "m_actor.h"
#include "unk.h"

struct Gyoei;

typedef struct Gyoei {
    /* 0x000 */ Actor actor;
    /* 0x174 */ UNK_TYPE1 unk_174[0x4C8];
} Gyoei; // size = 0x63C

#endif
