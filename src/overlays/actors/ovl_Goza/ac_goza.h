#ifndef AC_GOZA_H
#define AC_GOZA_H

#include "ultra64.h"
#include "m_actor.h"
#include "unk.h"
#include "overlays/actors/ovl_Structure/ac_structure.h"

struct Game_Play;
struct Goza;

typedef void (*GozaActionFunc)(struct Goza*, struct Game_Play*);

typedef struct Goza {
    /* 0x000 */ StructureActor structureActor;
} Goza; // size = 0x2D8

#endif
