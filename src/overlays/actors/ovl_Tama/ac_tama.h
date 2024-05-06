#ifndef AC_TAMA_H
#define AC_TAMA_H

#include "ultra64.h"
#include "m_actor.h"
#include "unk.h"
#include "c_keyframe.h"
#include "overlays/actors/ovl_Structure/ac_structure.h"

struct Game_Play;
struct Tama;

typedef enum TamaProcess {
    TAM_PROCESS_WAIT,
} TamaProcess;

typedef void (*TamaActionFunc)(struct Tama*, struct Game_Play*);

typedef struct Tama {
    /* 0x000 */ StructureActor structureActor;
} Tama; // size = 0x2D8

#endif
