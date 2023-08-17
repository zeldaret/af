#ifndef AC_T_PISTOL_H
#define AC_T_PISTOL_H

#include "ultra64.h"
#include "m_actor.h"
#include "unk.h"

struct Game_Play;
struct T_Pistol;

typedef void (*T_PistolActionFunc)(struct T_Pistol*, struct Game_Play*);

typedef struct T_Pistol {
    /* 0x000 */ Actor actor;
    /* 0x174 */ UNK_TYPE1 unk_174[0x5C];
} T_Pistol; // size = 0x1D0

#endif
