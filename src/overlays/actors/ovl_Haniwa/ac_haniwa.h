#ifndef AC_HANIWA_H
#define AC_HANIWA_H

#include "ultra64.h"
#include "m_actor.h"
#include "unk.h"

struct Game_Play;
struct Haniwa;

typedef void (*HaniwaActionFunc)(struct Haniwa*, struct Game_Play*);

typedef struct Haniwa {
    /* 0x000 */ Actor actor;
    /* 0x174 */ UNK_TYPE1 unk_174[0x114];
} Haniwa; // size = 0x288

#endif
