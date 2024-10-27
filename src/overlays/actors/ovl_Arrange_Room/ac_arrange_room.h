#ifndef AC_ARRANGE_ROOM_H
#define AC_ARRANGE_ROOM_H

#include "ultra64.h"
#include "m_actor.h"
#include "unk.h"
#include "m_clip.h"

struct Game_Play;
struct Arrange_Room;

typedef struct Arrange_Room {
    /* 0x000 */ Actor actor;
    /* 0x174 */ u8* vram;
    /* 0x178 */ u8* wallDataPtr;
    /* 0x17C */ s32 wallIdx;
    /* 0x180 */ u8* floorDataPtr; 
    /* 0x184 */ s32 floorIdx;
    /* 0x188 */ Arrange_RoomClip clip;
} Arrange_Room; // size = 0x190

#endif
