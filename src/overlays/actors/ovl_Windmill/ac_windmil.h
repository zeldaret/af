#ifndef AC_WINDMIL_H
#define AC_WINDMIL_H

#include "ultra64.h"
#include "m_actor.h"
#include "unk.h"

struct Game_Play;
struct Windmill;

typedef void (*WindmillActionFunc)(struct Windmill*, struct Game_Play*);

typedef struct Windmill {
    /* 0x000 */ Actor actor;
    /* 0x174 */ UNK_TYPE1 unk_174[0x164];
} Windmill; // size = 0x2D8

#endif
