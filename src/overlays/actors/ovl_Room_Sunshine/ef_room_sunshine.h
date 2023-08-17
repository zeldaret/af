#ifndef EF_ROOM_SUNSHINE_H
#define EF_ROOM_SUNSHINE_H

#include "ultra64.h"
#include "m_actor.h"
#include "unk.h"

struct PlayState;
struct Room_Sunshine;

typedef void (*Room_SunshineActionFunc)(struct Room_Sunshine*, struct PlayState*);

typedef struct Room_Sunshine {
    /* 0x000 */ Actor actor;
    /* 0x174 */ UNK_TYPE1 unk_174[0x4];
} Room_Sunshine; // size = 0x178

#endif
