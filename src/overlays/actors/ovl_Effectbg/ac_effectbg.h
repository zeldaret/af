#ifndef AC_EFFECTBG_H
#define AC_EFFECTBG_H

#include "ultra64.h"
#include "m_actor.h"
#include "unk.h"

struct Game_Play;
struct Effectbg;

typedef void (*EffectbgActionFunc)(struct Effectbg*, struct Game_Play*);

typedef struct Effectbg {
    /* 0x000 */ Actor actor;
    /* 0x174 */ UNK_TYPE1 unk_174[0xB7C];
} Effectbg; // size = 0xCF0

#endif
