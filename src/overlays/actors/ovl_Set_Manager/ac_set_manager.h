#ifndef AC_SET_MANAGER_H
#define AC_SET_MANAGER_H

#include "ultra64.h"
#include "m_actor.h"
#include "unk.h"

struct Set_Manager;

typedef struct Set_Manager {
    /* 0x0000 */ Actor actor;
    /* 0x0174 */ UNK_TYPE1 unk_0174[0x4174];
} Set_Manager; // size = 0x42E8

#endif
