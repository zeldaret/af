#ifndef EF_ROOM_SUNSHINE_H
#define EF_ROOM_SUNSHINE_H

#include "ultra64.h"
#include "m_actor.h"
#include "unk.h"

struct Game_Play;
struct Room_Sunshine;

typedef void (*Room_SunshineActionFunc)(struct Room_Sunshine*, struct Game_Play*);

typedef struct Room_Sunshine {
    /* 0x000 */ Actor actor;
    /* 0x174 */ u8 unk_174;
} Room_Sunshine; // size = 0x178

#endif
