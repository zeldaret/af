#ifndef AC_EV_DOZAEMON_H
#define AC_EV_DOZAEMON_H

#include "ultra64.h"
#include "m_actor.h"
#include "unk.h"

struct Game_Play;
struct Ev_Dozaemon;

typedef void (*Ev_DozaemonActionFunc)(struct Ev_Dozaemon*, struct Game_Play*);

typedef struct Ev_Dozaemon {
    /* 0x000 */ Actor actor;
    /* 0x174 */ UNK_TYPE1 unk_174[0x7D8];
} Ev_Dozaemon; // size = 0x94C

#endif
