#ifndef AC_POLICE_BOX_H
#define AC_POLICE_BOX_H

#include "ultra64.h"
#include "m_actor.h"
#include "unk.h"

struct PlayState;
struct Police_Box;

typedef void (*Police_BoxActionFunc)(struct Police_Box*, struct PlayState*);

typedef struct Police_Box {
    /* 0x000 */ Actor actor;
    /* 0x174 */ UNK_TYPE1 unk_174[0x164];
} Police_Box; // size = 0x2D8

#endif
