#ifndef AC_UKI_H
#define AC_UKI_H

#include "ultra64.h"
#include "m_actor.h"
#include "m_collision_obj.h"
#include "unk.h"

struct Game_Play;
struct Uki;

typedef void (*UkiActionFunc)(struct Uki*, struct Game_Play*);

typedef struct Uki {
    /* 0x000 */ Actor actor;
    /* 0x174 */ UNK_TYPE1 unk_174[0x4];
    /* 0x178 */ ClObjPipe collider;
    /* 0x194 */ UNK_TYPE1 unk_194[0x124];
} Uki; // size = 0x2B8

#endif
