#ifndef EF_LAMP_LIGHT_H
#define EF_LAMP_LIGHT_H

#include "ultra64.h"
#include "m_actor.h"
#include "unk.h"

struct Lamp_Light;

typedef struct Lamp_Light {
    /* 0x000 */ Actor actor;
    /* 0x174 */ UNK_TYPE1 unk_174[0x18];
} Lamp_Light; // size = 0x18C

#endif
