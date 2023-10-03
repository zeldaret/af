#ifndef EF_LAMP_LIGHT_H
#define EF_LAMP_LIGHT_H

#include "ultra64.h"
#include "m_actor.h"
#include "unk.h"
#include "m_lights.h"

struct Game_Play;
struct Lamp_Light;

typedef void (*Lamp_LightActionFunc)(struct Lamp_Light*, struct Game_Play*);

typedef struct Lamp_Light {
    /* 0x000 */ Actor actor;
    /* 0x174 */ s32 unk_174;
    /* 0x178 */ Lights unk_178;
    /* 0x188 */ LightNode* unk_188;
} Lamp_Light; // size = 0x18C

#endif
