#ifndef AC_POST_OFFICE_H
#define AC_POST_OFFICE_H

#include "ultra64.h"
#include "m_actor.h"
#include "unk.h"

struct PlayState;
struct Post_Office;

typedef void (*Post_OfficeActionFunc)(struct Post_Office*, struct PlayState*);

typedef struct Post_Office {
    /* 0x000 */ Actor actor;
    /* 0x174 */ UNK_TYPE1 unk_174[0x164];
} Post_Office; // size = 0x2D8

#endif
