#ifndef AC_KAGO_H
#define AC_KAGO_H
#include "ultra64.h"
#include "m_actor.h"
#include "unk.h"
#include "c_keyframe.h"
#include "overlays/actors/ovl_Structure/ac_structure.h"

struct Game_Play;
struct Kago;

typedef enum KagoProcess {
    KAG_PROCESS_WAIT,
} KagoProcess;

typedef void (*KagoActionFunc)(struct Kago*, struct Game_Play*);

typedef struct Kago {
    /* 0x000 */ StructureActor structureActor;
} Kago; // size = 0x2D8

#endif
