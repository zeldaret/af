#ifndef AC_T_UTIWA_H
#define AC_T_UTIWA_H

#include "ultra64.h"
#include "m_actor.h"
#include "unk.h"

struct Game_Play;
struct T_Utiwa;

typedef void (*T_UtiwaActionFunc)(struct T_Utiwa*, struct Game_Play*);

typedef struct T_Utiwa {
    /* 0x000 */ Actor actor;
    /* 0x174 */ UNK_TYPE1 unk_174[0x5C];
} T_Utiwa; // size = 0x1D0

#endif
