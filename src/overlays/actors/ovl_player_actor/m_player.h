#ifndef M_PLAYER_H
#define M_PLAYER_H

#include "ultra64.h"
#include "m_actor.h"
#include "unk.h"

struct Player;

typedef struct Player {
    /* 0x0000 */ Actor actor;
    /* 0x0174 */ UNK_TYPE1 unk_0174[0x1164];
} Player; // size = 0x12D8

#endif
