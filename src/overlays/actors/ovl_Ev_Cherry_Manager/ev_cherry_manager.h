#ifndef EV_CHERRY_MANAGER_H
#define EV_CHERRY_MANAGER_H

#include "ultra64.h"
#include "m_actor.h"
#include "unk.h"

struct Game_Play;
struct Ev_Cherry_Manager;

typedef void (*Ev_Cherry_ManagerActionFunc)(struct Ev_Cherry_Manager*, struct Game_Play*);

typedef struct Ev_Cherry_Manager {
    /* 0x000 */ Actor actor;
} Ev_Cherry_Manager; // size = 0x174

#endif
