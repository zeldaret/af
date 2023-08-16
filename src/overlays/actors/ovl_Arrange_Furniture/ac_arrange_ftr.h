#ifndef AC_ARRANGE_FTR_H
#define AC_ARRANGE_FTR_H

#include "ultra64.h"
#include "m_actor.h"
#include "unk.h"

struct Arrange_Furniture;

typedef struct Arrange_Furniture {
    /* 0x000 */ Actor actor;
    /* 0x174 */ UNK_TYPE1 unk_174[0x104];
} Arrange_Furniture; // size = 0x278

#endif
