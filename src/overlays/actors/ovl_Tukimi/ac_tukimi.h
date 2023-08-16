#ifndef AC_TUKIMI_H
#define AC_TUKIMI_H

#include "ultra64.h"
#include "m_actor.h"
#include "unk.h"

struct PlayState;
struct Tukimi;

typedef void (*TukimiActionFunc)(struct Tukimi*, struct PlayState*);

typedef struct Tukimi {
    /* 0x000 */ Actor actor;
    /* 0x174 */ UNK_TYPE1 unk_174[0x164];
} Tukimi; // size = 0x2D8

#endif
