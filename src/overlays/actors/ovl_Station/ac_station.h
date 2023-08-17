#ifndef AC_STATION_H
#define AC_STATION_H

#include "ultra64.h"
#include "m_actor.h"
#include "unk.h"

struct Game_Play;
struct Station;

typedef void (*StationActionFunc)(struct Station*, struct Game_Play*);

typedef struct Station {
    /* 0x000 */ Actor actor;
    /* 0x174 */ UNK_TYPE1 unk_174[0x164];
} Station; // size = 0x2D8

#endif
