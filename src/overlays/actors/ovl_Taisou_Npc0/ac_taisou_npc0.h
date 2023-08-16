#ifndef AC_TAISOU_NPC0_H
#define AC_TAISOU_NPC0_H

#include "ultra64.h"
#include "m_actor.h"
#include "unk.h"

struct PlayState;
struct Taisou_Npc0;

typedef void (*Taisou_Npc0ActionFunc)(struct Taisou_Npc0*, struct PlayState*);

typedef struct Taisou_Npc0 {
    /* 0x000 */ Actor actor;
    /* 0x174 */ UNK_TYPE1 unk_174[0x7DC];
} Taisou_Npc0; // size = 0x950

#endif
