#ifndef AC_MBG_H
#define AC_MBG_H

#include "ultra64.h"
#include "m_actor.h"
#include "unk.h"

struct PlayState;
struct Mbg;

typedef void (*MbgActionFunc)(struct Mbg*, struct PlayState*);

typedef struct Mbg {
    /* 0x000 */ Actor actor;
    /* 0x174 */ UNK_TYPE1 unk_174[0x3C];
} Mbg; // size = 0x1B0

#endif
