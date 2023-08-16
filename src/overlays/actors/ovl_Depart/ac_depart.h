#ifndef AC_DEPART_H
#define AC_DEPART_H

#include "ultra64.h"
#include "m_actor.h"
#include "unk.h"

struct PlayState;
struct Depart;

typedef void (*DepartActionFunc)(struct Depart*, struct PlayState*);

typedef struct Depart {
    /* 0x000 */ Actor actor;
    /* 0x174 */ UNK_TYPE1 unk_174[0x164];
} Depart; // size = 0x2D8

#endif
