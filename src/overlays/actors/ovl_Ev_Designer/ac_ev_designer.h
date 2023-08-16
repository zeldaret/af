#ifndef AC_EV_DESIGNER_H
#define AC_EV_DESIGNER_H

#include "ultra64.h"
#include "m_actor.h"
#include "unk.h"

struct PlayState;
struct Ev_Designer;

typedef void (*Ev_DesignerActionFunc)(struct Ev_Designer*, struct PlayState*);

typedef struct Ev_Designer {
    /* 0x000 */ Actor actor;
    /* 0x174 */ UNK_TYPE1 unk_174[0x7E4];
} Ev_Designer; // size = 0x958

#endif
