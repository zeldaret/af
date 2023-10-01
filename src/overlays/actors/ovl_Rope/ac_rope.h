#ifndef AC_ROPE_H
#define AC_ROPE_H

#include "ultra64.h"
#include "m_actor.h"
#include "unk.h"

struct Game_Play;
struct Rope;

typedef void (*RopeActionFunc)(struct Rope*, struct Game_Play*);

typedef struct Rope {
    /* 0x000 */ Actor actor;
} Rope; // size = 0x174

#endif
