#ifndef AC_RADIO_H
#define AC_RADIO_H

#include "ultra64.h"
#include "m_actor.h"
#include "unk.h"
#include "overlays/actors/ovl_Structure/ac_structure.h"

struct Game_Play;
struct Radio;

typedef enum RadioProcess {
    RADIO_PROCESS_ANIMATE,
} RadioProcess;

typedef void (*RadioActionFunc)(struct Radio*, struct Game_Play*);

/* it can use `struct StructureActor`, but only a handfull of fields actually make sense
 * - 0x2A0: an action / process function
 * - 0x2B4: corresponding action / process id
 * - 0x2B8: timer
 */
typedef struct Radio {
    /* 0x000 */ Actor actor;
    /* 0x174 */ UNK_TYPE1 unk_174[0x2A0 - 0x174];
    /* 0x2A0 */ RadioActionFunc process;
    /* 0x174 */ UNK_TYPE1 unk_2A4[0x2B4 - 0x2A4];
    /* 0x2B4 */ s32 processId;
    /* 0x2B8 */ s32 timer;
    /* 0x2BC */ UNK_TYPE1 unk_2BC[0x2D8 - 0x2BC];
} Radio; // size = 0x2D8

#endif
