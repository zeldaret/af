#ifndef AC_T_TAM_H
#define AC_T_TAM_H

#include "ultra64.h"
#include "m_actor.h"
#include "unk.h"

struct PlayState;
struct T_Tama;

typedef void (*T_TamaActionFunc)(struct T_Tama*, struct PlayState*);

typedef struct T_Tama {
    /* 0x000 */ Actor actor;
    /* 0x174 */ UNK_TYPE1 unk_174[0x54];
} T_Tama; // size = 0x1C8

#endif
