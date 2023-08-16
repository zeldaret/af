#ifndef AC_MY_ROOM_H
#define AC_MY_ROOM_H

#include "ultra64.h"
#include "m_actor.h"
#include "unk.h"

struct My_Room;

typedef struct My_Room {
    /* 0x000 */ Actor actor;
    /* 0x174 */ UNK_TYPE1 unk_174[0x36C];
} My_Room; // size = 0x4E0

#endif
