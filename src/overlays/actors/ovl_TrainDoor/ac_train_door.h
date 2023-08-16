#ifndef AC_TRAIN_DOOR_H
#define AC_TRAIN_DOOR_H

#include "ultra64.h"
#include "m_actor.h"
#include "unk.h"

struct TrainDoor;

typedef struct TrainDoor {
    /* 0x000 */ Actor actor;
    /* 0x174 */ UNK_TYPE1 unk_174[0xD0];
} TrainDoor; // size = 0x244

#endif
