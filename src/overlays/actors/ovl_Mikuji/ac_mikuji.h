#ifndef AC_MIKUJI_H
#define AC_MIKUJI_H

#include "ultra64.h"
#include "m_actor.h"
#include "overlays/actors/ovl_Structure/ac_structure.h"

struct Game_Play;
struct Mikuji;

typedef struct Mikuji {
    /* 0x000 */ StructureActor structureActor;
} Mikuji; // size = 0x2D8

typedef void (*MikujiActionFunc)(struct Mikuji*, struct Game_Play*);

typedef enum Mikuji_Action {
    /* 0 */ MIKUJI_ACTION_WAIT,
    /* 1 */ MIKUJI_ACTION_MAX
} Mikuji_Action;

#endif
