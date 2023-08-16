#ifndef EF_ROOM_SUNSHINE_POSTHOUSE_H
#define EF_ROOM_SUNSHINE_POSTHOUSE_H

#include "ultra64.h"
#include "m_actor.h"
#include "unk.h"

struct PlayState;
struct Room_Sunshine_Posthouse;

typedef void (*Room_Sunshine_PosthouseActionFunc)(struct Room_Sunshine_Posthouse*, struct PlayState*);

typedef struct Room_Sunshine_Posthouse {
    /* 0x000 */ Actor actor;
    /* 0x174 */ UNK_TYPE1 unk_174[0x4];
} Room_Sunshine_Posthouse; // size = 0x178

#endif
