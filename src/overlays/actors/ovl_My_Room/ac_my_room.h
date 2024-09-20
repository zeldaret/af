#ifndef AC_MY_ROOM_H
#define AC_MY_ROOM_H

#include "ultra64.h"
#include "m_actor.h"
#include "unk.h"
#include "c_keyframe.h"
#include "libc/stdint.h"

struct Game_Play;
struct Game;
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

typedef struct FurnitureActorProfile {
    /* 0x00 */ uintptr_t objectRomStart;
    /* 0x04 */ uintptr_t objectRomEnd;
    /* 0x08 */ void* objectSegmentStart;
    /* 0x0C */ void* objectSegmentEnd;
    /* 0x10 */ UNK_PTR unk10; // opaque0
    /* 0x14 */ UNK_PTR unk14; // opaque1
    /* 0x18 */ UNK_PTR unk18; // translucent0
    /* 0x1C */ UNK_PTR unk1C; // translucent1
    /* 0x20 */ UNK_PTR unk20; // texture
    /* 0x24 */ UNK_PTR unk24; // palette
    /* 0x28 */ UNK_PTR unk28; // rig
    /* 0x2C */ UNK_PTR unk2C; // tex_anim
    /* 0x30 */ f32 height;
    /* 0x34 */ f32 scale;
    /* 0x38 */ UNK_TYPE1 unk38; // shape
    /* 0x39 */ UNK_TYPE1 unk39; // move_bg_type
    /* 0x3A */ UNK_TYPE1 unk3A; // check_rotation
    /* 0x3B */ UNK_TYPE1 unk3B; // kankyo_map
    /* 0x3C */ UNK_TYPE1 unk3C; // contact_action
    /* 0x3E */ UNK_TYPE2 unk3E; // interaction_type
    /* 0x40 */ FurnitureActorFunctions* furnitureActorFunctions;
} FurnitureActorProfile; // size = 0x44

#endif
