#ifndef AC_T_NPC_SAO_H
#define AC_T_NPC_SAO_H

#include "ultra64.h"
#include "m_actor.h"
#include "unk.h"

struct Game_Play;
struct T_NpcSao;

typedef void (*T_NpcSaoActionFunc)(struct T_NpcSao*, struct Game_Play*);

typedef struct T_NpcSao {
    /* 0x000 */ Actor actor;
    /* 0x174 */ UNK_TYPE1 unk_174[0x68];
} T_NpcSao; // size = 0x1DC

#endif
