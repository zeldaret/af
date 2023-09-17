#ifndef AC_ANIMAL_LOGO_H
#define AC_ANIMAL_LOGO_H

#include "ultra64.h"
#include "m_actor.h"
#include "unk.h"

struct Game_Play;
struct Animal_Logo;

typedef void (*Animal_LogoActionFunc)(struct Animal_Logo*, struct Game_Play*);

typedef struct Animal_Logo {
    /* 0x000 */ Actor actor;
    /* 0x174 */ UNK_TYPE1 unk_174[0x1B4];
} Animal_Logo; // size = 0x328

#endif
