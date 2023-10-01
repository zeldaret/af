#ifndef AC_YATAI_H
#define AC_YATAI_H

#include "ultra64.h"
#include "m_actor.h"
#include "unk.h"

struct Game_Play;
struct Yatai;

typedef void (*YataiActionFunc)(struct Yatai*, struct Game_Play*);

typedef struct Yatai {
    /* 0x000 */ Actor actor;
    /* 0x174 */ UNK_TYPE1 unk_174[0x164];
} Yatai; // size = 0x2D8

#endif
