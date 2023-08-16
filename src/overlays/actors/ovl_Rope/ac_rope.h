#ifndef AC_ROPE_H
#define AC_ROPE_H

#include "ultra64.h"
#include "m_actor.h"
#include "unk.h"

struct PlayState;
struct Rope;

typedef void (*RopeActionFunc)(struct Rope*, struct PlayState*);

typedef struct Rope {
    /* 0x000 */ Actor actor;
} Rope; // size = 0x174

#endif
