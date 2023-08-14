#ifndef M_SCENE_H
#define M_SCENE_H

#include "ultra64.h"
#include "z64math.h"

typedef struct ActorEntry {
    /* 0x0 */ s16 id;
    /* 0x2 */ Vec3s pos;
    /* 0x8 */ Vec3s rot;
    /* 0xE */ s16 params;
} ActorEntry; // size = 0x10

#endif
