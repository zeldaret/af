#ifndef AC_BROKER_DESIGN_H
#define AC_BROKER_DESIGN_H

#include "ultra64.h"
#include "m_actor.h"
#include "unk.h"

struct Game_Play;
struct Broker_Design;

typedef void (*Broker_DesignActionFunc)(struct Broker_Design*, struct Game_Play*);

typedef struct Broker_Design {
    /* 0x000 */ Actor actor;
    /* 0x174 */ UNK_TYPE1 unk_174[0x8];
} Broker_Design; // size = 0x17C

#endif
