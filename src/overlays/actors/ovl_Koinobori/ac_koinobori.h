#ifndef AC_KOINOBORI_H
#define AC_KOINOBORI_H

#include "ultra64.h"
#include "m_actor.h"
#include "unk.h"
#include "c_keyframe.h"
#include "overlays/actors/ovl_Structure/ac_structure.h"

struct Game_Play;
struct Koinobori;

typedef void (*KoinoboriActionFunc)(struct Koinobori*, struct Game_Play*);

typedef struct Koinobori {
    /* 0x000 */ StructureActor structureActor;
} Koinobori; // size = 0x2D8

#endif
