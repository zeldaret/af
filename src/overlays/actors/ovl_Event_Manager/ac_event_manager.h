#ifndef AC_EVENT_MANAGER_H
#define AC_EVENT_MANAGER_H

#include "ultra64.h"
#include "m_actor.h"
#include "unk.h"

struct Event_Manager;

typedef struct Event_Manager {
    /* 0x000 */ Actor actor;
    /* 0x174 */ UNK_TYPE1 unk_174[0xDC];
} Event_Manager; // size = 0x250

#endif
