#ifndef AC_GYO_RELEASE_H
#define AC_GYO_RELEASE_H

#include "ultra64.h"
#include "m_actor.h"
#include "unk.h"

struct Game_Play;
struct Gyo_Release;

typedef void (*Gyo_ReleaseActionFunc)(struct Gyo_Release*, struct Game_Play*);

typedef struct Gyo_Release {
    /* 0x000 */ Actor actor;
    /* 0x174 */ UNK_TYPE1 unk_174[0x48];
} Gyo_Release; // size = 0x1BC

#endif
