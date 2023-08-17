#ifndef AC_DOUZOU_H
#define AC_DOUZOU_H

#include "ultra64.h"
#include "m_actor.h"
#include "unk.h"

struct Game_Play;
struct Douzou;

typedef void (*DouzouActionFunc)(struct Douzou*, struct Game_Play*);

typedef struct Douzou {
    /* 0x000 */ Actor actor;
    /* 0x174 */ UNK_TYPE1 unk_174[0x164];
} Douzou; // size = 0x2D8

#endif
