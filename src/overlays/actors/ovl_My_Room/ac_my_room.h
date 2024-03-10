#ifndef AC_MY_ROOM_H
#define AC_MY_ROOM_H

#include "ultra64.h"
#include "m_actor.h"
#include "unk.h"
#include "c_keyframe.h"

struct Game_Play;
struct My_Room;
struct Actor;


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
    /* 0x210 */ Mtx matrix[2][10]; // not sure if the array dimensions are correct
} FurnitureActor; // size >= 0xA10

typedef void (*FurnitureCreate)(FurnitureActor* this, u8* data);
typedef void (*FurnitureMove)(FurnitureActor* this, struct Actor* myRoomActor, struct Game_Play* game_play, u8* data);
typedef void (*FurnitureDraw)(FurnitureActor* this, struct Actor* myRoomActor, struct Game_Play* game_play, u8* data);
typedef void (*FurnitureDestroy)(FurnitureActor* this, u8* data);
typedef void (*FurnitureDma)(u16* name, u8* data);

typedef struct FurnitureActorFunctions {
    /* 0x00 */ FurnitureCreate furnitureCreate;
    /* 0x04 */ FurnitureMove furnitureMove;
    /* 0x08 */ FurnitureDraw furnitureDraw;
    /* 0x0C */ FurnitureDestroy furnitureDestroy;
    /* 0x10 */ FurnitureDma furnitureDma;
} FurnitureActorFunctions; // size = 0x14

typedef struct FurnitureActorUnkStruct {
    /* 0x00 */ UNK_TYPE4 unk00;
    /* 0x04 */ UNK_TYPE4 unk04;
    /* 0x08 */ UNK_TYPE4 unk08;
    /* 0x0C */ UNK_TYPE4 unk0C;
    /* 0x10 */ UNK_TYPE4 unk10;
    /* 0x14 */ UNK_TYPE4 unk14;
    /* 0x18 */ UNK_TYPE4 unk18;
    /* 0x1C */ UNK_TYPE4 unk1C;
    /* 0x20 */ UNK_TYPE4 unk20;
    /* 0x24 */ UNK_TYPE4 unk24;
    /* 0x28 */ UNK_TYPE4 unk28;
    /* 0x2C */ UNK_TYPE4 unk2C;
    /* 0x30 */ UNK_TYPE4 unk30;
    /* 0x34 */ UNK_TYPE4 unk34;
    /* 0x38 */ UNK_TYPE4 unk38;
    /* 0x3C */ UNK_TYPE4 unk3C;
    /* 0x40 */ UNK_TYPE4 unk40;
    /* 0x44 */ FurnitureActorFunctions* furnitureActorFunctions;
} FurnitureActorUnkStruct; // size = 0x48

#endif
