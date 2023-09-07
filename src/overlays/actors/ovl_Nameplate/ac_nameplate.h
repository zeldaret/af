#ifndef AC_NAMEPLATE_H
#define AC_NAMEPLATE_H

#include "ultra64.h"
#include "m_actor.h"
#include "unk.h"

struct Game_Play;
struct Nameplate;

typedef void (*NameplateActionFunc)(struct Nameplate*, struct Game_Play*);

typedef struct Nameplate {
    /* 0x000 */ Actor actor;
    /* 0x174 */ UNK_TYPE1 unk_174[0x164];
} Nameplate; // size = 0x2D8

#endif
