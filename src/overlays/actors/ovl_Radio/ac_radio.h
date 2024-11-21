#ifndef AC_RADIO_H
#define AC_RADIO_H

#include "m_actor.h"
#include "overlays/actors/ovl_Structure/ac_structure.h"

struct Game_Play;
struct Radio;

typedef enum RadioProcess {
    RADIO_PROCESS_ANIMATE,
} RadioProcess;

typedef void (*RadioActionFunc)(struct Radio*, struct Game_Play*);

/* only a handfull of `StructureActor`'s fields are actually employed:
 * - 0x2A0, process: an action / process function
 * - 0x2B4, unk_2B4: corresponding action / process index
 * - 0x2B8, unk_2B8: timer
 */
typedef struct Radio {
    /* 0x000 */ StructureActor structureActor;
} Radio; // size = 0x2D8

#define RADIO_HOME(this) (this->structureActor.actor.home)
#define RADIO_WORLD(this) (this->structureActor.actor.world)

#define RADIO_PROCESS(this) (this->structureActor.process)
#define RADIO_PROCESS_INDEX(this) (this->structureActor.unk_2B4)
#define RADIO_TIMER(this) (this->structureActor.unk_2B8)

#endif
