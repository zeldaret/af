#ifndef EF_EFFECT_CONTROL_H
#define EF_EFFECT_CONTROL_H

#include "ultra64.h"
#include "m_actor.h"
#include "unk.h"

struct Game_Play;
struct Effect_Control;

typedef void (*Effect_ControlActionFunc)(struct Effect_Control*, struct Game_Play*);

typedef struct Effect_Control {
    /* 0x000 */ Actor actor;
    /* 0x174 */ UNK_TYPE1 unk_174[0x48];
} Effect_Control; // size = 0x1BC

#endif
