#ifndef AC_RADIO_H
#define AC_RADIO_H

#include "m_actor.h"
#include "overlays/actors/ovl_Structure/ac_structure.h"

struct Game_Play;
struct Radio;

typedef enum RadioProcess {
    RADIO_PROCESS_WAIT,
} RadioProcess;

typedef void (*RadioActionFunc)(struct Radio*, struct Game_Play*);

typedef struct Radio {
    /* 0x000 */ StructureActor structureActor;
} Radio; // size = 0x2D8

#endif
