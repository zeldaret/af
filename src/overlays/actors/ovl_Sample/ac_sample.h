#ifndef AC_SAMPLE_H
#define AC_SAMPLE_H

#include "ultra64.h"
#include "m_actor.h"
#include "unk.h"

struct Game_Play;
struct Sample;

typedef void (*SampleActionFunc)(struct Sample*, struct Game_Play*);

typedef struct Sample {
    /* 0x000 */ Actor actor;
    /* 0x174 */ UNK_TYPE1 unk_174[0xF8];
} Sample; // size = 0x26C

#endif
