#ifndef AC_DUMM_H
#define AC_DUMM_H

#include "ultra64.h"
#include "m_actor.h"
#include "unk.h"

struct Game_Play;
struct Dummy;

typedef void (*DummyActionFunc)(struct Dummy*, struct Game_Play*);

typedef struct Dummy {
    /* 0x000 */ Actor actor;
} Dummy; // size = 0x174

#endif
