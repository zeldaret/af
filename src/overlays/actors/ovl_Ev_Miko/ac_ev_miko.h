#ifndef AC_EV_MIKO_H
#define AC_EV_MIKO_H

#include "ultra64.h"
#include "m_actor.h"
#include "unk.h"

struct Game_Play;
struct Ev_Miko;

typedef void (*Ev_MikoActionFunc)(struct Ev_Miko*, struct Game_Play*);

typedef struct Ev_Miko {
    /* 0x000 */ Actor actor;
    /* 0x174 */ UNK_TYPE1 unk_174[0x7D4];
} Ev_Miko; // size = 0x948

#endif
