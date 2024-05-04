#ifndef AC_TOUDAI_H
#define AC_TOUDAI_H

#include "ultra64.h"
#include "m_actor.h"
#include "unk.h"
#include "z64math.h"
#include "c_keyframe.h"
#include "overlays/actors/ovl_Structure/ac_structure.h"

struct Toudai;
struct Game_Play;

typedef void (*ToudaiActionFunc)(struct Toudai*, struct Game_Play*);

typedef struct Toudai {
    /* 0x000 */ StructureActor structureActor;
} Toudai; // size = 0x2D8

#endif
