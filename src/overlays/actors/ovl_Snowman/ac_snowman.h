#ifndef AC_SNOWMAN_H
#define AC_SNOWMAN_H

#include "ultra64.h"
#include "m_actor.h"
#include "m_collision_obj.h"
#include "unk.h"

struct Game_Play;
struct Snowman;

typedef void (*SnowmanActionFunc)(struct Snowman*, struct Game_Play*);

typedef struct Snowman {
    /* 0x000 */ Actor actor;
    /* 0x174 */ ClObjPipe collider;
    /* 0x190 */ UNK_TYPE1 unk_190[0x6C];
} Snowman; // size = 0x1FC

#endif
