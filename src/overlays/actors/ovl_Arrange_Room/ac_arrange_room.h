#ifndef AC_ARRANGE_ROOM_H
#define AC_ARRANGE_ROOM_H

#include "ultra64.h"
#include "m_actor.h"
#include "unk.h"

struct Arrange_Room;

typedef struct Arrange_Room {
    /* 0x000 */ Actor actor;
    /* 0x174 */ UNK_TYPE1 unk_174[0x1C];
} Arrange_Room; // size = 0x190

#endif
