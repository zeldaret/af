#ifndef AC_MY_ROOM_H
#define AC_MY_ROOM_H

#include "ultra64.h"
#include "m_actor.h"
#include "unk.h"
#include "c_keyframe.h"

struct Game_Play;
struct My_Room;


typedef void (*My_RoomActionFunc)(struct My_Room*, struct Game_Play*);

typedef struct My_Room {
    /* 0x000 */ Actor actor;
    /* 0x174 */ UNK_TYPE1 unk_174[0x36C];
} My_Room; // size = 0x4E0

typedef struct FurnitureActor {
    /* 0x000 */ UNK_TYPE1 unk_000[0x134];
    /* 0x134 */ SkeletonInfoR skeletonInfo;
    /* 0x1A4 */ s_xyz jointTable[9];
    /* 0x1DA */ s_xyz morphTable[9];
    /* 0x210 */ Mtx matrix[2][12];
} FurnitureActor; // size >= 0x210

#endif
