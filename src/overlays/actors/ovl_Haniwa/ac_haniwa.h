#ifndef AC_HANIWA_H
#define AC_HANIWA_H

#include "ultra64.h"
#include "m_actor.h"
#include "m_collision_obj.h"
#include "unk.h"

struct Game_Play;
struct AcHaniwa;

typedef void (*HaniwaActionFunc)(struct AcHaniwa*, struct Game_Play*);

typedef struct AcHaniwa {
    /* 0x000 */ Actor actor;
    /* 0x174 */ UNK_TYPE1 unk_174[0x7C];
    /* 0x1F0 */ ClObjPipe collider;
    /* 0x20C */ UNK_TYPE1 unk_20C[0x7C];
} AcHaniwa; // size = 0x288

#endif
