#ifndef AC_EV_BROKER_H
#define AC_EV_BROKER_H

#include "ultra64.h"
#include "m_actor.h"
#include "unk.h"

struct PlayState;
struct Ev_Broker;

typedef void (*Ev_BrokerActionFunc)(struct Ev_Broker*, struct PlayState*);

typedef struct Ev_Broker {
    /* 0x000 */ Actor actor;
    /* 0x174 */ UNK_TYPE1 unk_174[0x7DC];
} Ev_Broker; // size = 0x950

#endif
