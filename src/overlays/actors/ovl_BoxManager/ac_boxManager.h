#ifndef AC_BOXMANAGER_H
#define AC_BOXMANAGER_H

#include "ultra64.h"
#include "m_actor.h"
#include "unk.h"

struct PlayState;
struct BoxManager;

typedef void (*BoxManagerActionFunc)(struct BoxManager*, struct PlayState*);

typedef struct BoxManager {
    /* 0x000 */ Actor actor;
    /* 0x174 */ UNK_TYPE1 unk_174[0x84];
} BoxManager; // size = 0x1F8

#endif
