#ifndef AC_EV_DOKUTU_H
#define AC_EV_DOKUTU_H

#include "ultra64.h"
#include "m_actor.h"
#include "unk.h"

struct PlayState;
struct Ev_Dokutu;

typedef void (*Ev_DokutuActionFunc)(struct Ev_Dokutu*, struct PlayState*);

typedef struct Ev_Dokutu {
    /* 0x000 */ Actor actor;
    /* 0x174 */ UNK_TYPE1 unk_174[0x7D8];
} Ev_Dokutu; // size = 0x94C

#endif
