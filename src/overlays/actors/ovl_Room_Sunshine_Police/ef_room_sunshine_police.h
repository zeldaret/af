#ifndef EF_ROOM_SUNSHINE_POLICE_H
#define EF_ROOM_SUNSHINE_POLICE_H

#include "ultra64.h"
#include "m_actor.h"
#include "unk.h"

struct PlayState;
struct Room_Sunshine_Police;

typedef void (*Room_Sunshine_PoliceActionFunc)(struct Room_Sunshine_Police*, struct PlayState*);

typedef struct Room_Sunshine_Police {
    /* 0x000 */ Actor actor;
    /* 0x174 */ UNK_TYPE1 unk_174[0x4];
} Room_Sunshine_Police; // size = 0x178

#endif
