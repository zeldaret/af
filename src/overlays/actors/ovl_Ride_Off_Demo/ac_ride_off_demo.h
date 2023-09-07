#ifndef AC_RIDE_OFF_DEMO_H
#define AC_RIDE_OFF_DEMO_H

#include "ultra64.h"
#include "m_actor.h"
#include "unk.h"

struct Game_Play;
struct Ride_Off_Demo;

typedef void (*Ride_Off_DemoActionFunc)(struct Ride_Off_Demo*, struct Game_Play*);

typedef struct Ride_Off_Demo {
    /* 0x000 */ Actor actor;
    /* 0x174 */ UNK_TYPE1 unk_174[0x18];
} Ride_Off_Demo; // size = 0x18C

#endif
