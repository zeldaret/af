#ifndef AC_FUUSEN_H
#define AC_FUUSEN_H

#include "ultra64.h"
#include "m_actor.h"
#include "unk.h"

struct PlayState;
struct Fuusen;

typedef void (*FuusenActionFunc)(struct Fuusen*, struct PlayState*);

typedef struct Fuusen {
    /* 0x000 */ Actor actor;
    /* 0x174 */ UNK_TYPE1 unk_174[0x2D4];
} Fuusen; // size = 0x448

#endif
