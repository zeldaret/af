#ifndef AC_EV_GYPSY_H
#define AC_EV_GYPSY_H

#include "ultra64.h"
#include "m_actor.h"
#include "unk.h"

struct Game_Play;
struct Ev_Gypsy;

typedef void (*Ev_GypsyActionFunc)(struct Ev_Gypsy*, struct Game_Play*);

typedef struct Ev_Gypsy {
    /* 0x000 */ Actor actor;
    /* 0x174 */ UNK_TYPE1 unk_174[0x7D4];
} Ev_Gypsy; // size = 0x948

#endif
