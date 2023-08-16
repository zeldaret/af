#ifndef AC_INTRO_DEMO_H
#define AC_INTRO_DEMO_H

#include "ultra64.h"
#include "m_actor.h"
#include "unk.h"

struct Intro_Demo;

typedef struct Intro_Demo {
    /* 0x000 */ Actor actor;
    /* 0x174 */ UNK_TYPE1 unk_174[0x38];
} Intro_Demo; // size = 0x1AC

#endif
