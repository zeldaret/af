#ifndef AC_QUEST_MANAGER_H
#define AC_QUEST_MANAGER_H

#include "ultra64.h"
#include "m_actor.h"
#include "unk.h"

struct PlayState;
struct Quest_Manager;

typedef void (*Quest_ManagerActionFunc)(struct Quest_Manager*, struct PlayState*);

typedef struct Quest_Manager {
    /* 0x000 */ Actor actor;
    /* 0x174 */ UNK_TYPE1 unk_174[0x764];
} Quest_Manager; // size = 0x8D8

#endif
