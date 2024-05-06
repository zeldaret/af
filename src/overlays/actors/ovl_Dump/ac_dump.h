#ifndef AC_DUMP_H
#define AC_DUMP_H

#include "ultra64.h"
#include "m_actor.h"
#include "unk.h"
#include "overlays/actors/ovl_Structure/ac_structure.h"

struct Game_Play;
struct Dump;

typedef enum DumpProcess {
    DUM_PROCESS_WAIT,
} DumpProcess;

typedef void (*DumpActionFunc)(struct Dump*, struct Game_Play*);

typedef struct Dump {
    /* 0x000 */ StructureActor structureActor;
} Dump; // size = 0x2D8

#endif
