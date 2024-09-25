#ifndef M_PLAYER_H
#define M_PLAYER_H

#include "ultra64.h"
#include "m_actor.h"
#include "m_collision_obj.h"
#include "m_controller.h"
#include "unk.h"

struct Game;
struct Game_Play;
struct Player;

typedef enum Player_ItemKind {
    Player_ITEM_KIND_START,
    Player_ITEM_KIND_AXE = Player_ITEM_KIND_START,
    Player_ITEM_KIND_NET,
    Player_ITEM_KIND_UMBRELLA00,
    Player_ITEM_KIND_UMBRELLA01,
    Player_ITEM_KIND_UMBRELLA02,
    Player_ITEM_KIND_UMBRELLA03,
    Player_ITEM_KIND_UMBRELLA04,
    Player_ITEM_KIND_UMBRELLA05,
    Player_ITEM_KIND_UMBRELLA06,
    Player_ITEM_KIND_UMBRELLA07,
    Player_ITEM_KIND_UMBRELLA08,
    Player_ITEM_KIND_UMBRELLA09,
    Player_ITEM_KIND_UMBRELLA10,
    Player_ITEM_KIND_UMBRELLA11,
    Player_ITEM_KIND_UMBRELLA12,
    Player_ITEM_KIND_UMBRELLA13,
    Player_ITEM_KIND_UMBRELLA14,
    Player_ITEM_KIND_UMBRELLA15,
    Player_ITEM_KIND_UMBRELLA16,
    Player_ITEM_KIND_UMBRELLA17,
    Player_ITEM_KIND_UMBRELLA18,
    Player_ITEM_KIND_UMBRELLA19,
    Player_ITEM_KIND_UMBRELLA20,
    Player_ITEM_KIND_UMBRELLA21,
    Player_ITEM_KIND_UMBRELLA22,
    Player_ITEM_KIND_UMBRELLA23,
    Player_ITEM_KIND_UMBRELLA24,
    Player_ITEM_KIND_UMBRELLA25,
    Player_ITEM_KIND_UMBRELLA26,
    Player_ITEM_KIND_UMBRELLA27,
    Player_ITEM_KIND_UMBRELLA28,
    Player_ITEM_KIND_UMBRELLA29,
    Player_ITEM_KIND_UMBRELLA30,
    Player_ITEM_KIND_UMBRELLA31,
    Player_ITEM_KIND_ROD,
    Player_ITEM_KIND_SCOOP
} Player_ItemKind;

#define Player_ITEM_KIND_CHECK(kind, min, max) (kind >= min && kind < max + 1)
#define Player_ITEM_IS_AXE(kind) (kind == Player_ITEM_KIND_AXE)
#define Player_ITEM_IS_NET(kind) (kind == Player_ITEM_KIND_NET)
#define Player_ITEM_IS_ROD(kind) (kind == Player_ITEM_KIND_ROD)
#define Player_ITEM_IS_SCOOP(kind) (kind == Player_ITEM_KIND_SCOOP)
#define Player_ITEM_IS_UMBRELLA(kind) \
    (Player_ITEM_KIND_CHECK(kind, Player_ITEM_KIND_UMBRELLA00, Player_ITEM_KIND_UMBRELLA31))
#define Player_ITEM_IS_VALID(kind) (Player_ITEM_KIND_CHECK(kind, Player_ITEM_KIND_START, Player_ITEM_KIND_SCOOP))

typedef struct PlayerControllerData {
    /* 0x00 */ Controller controller;
    /* 0x38 */ s8 triggerButtonA;
    /* 0x39 */ s8 buttonA;
    /* 0x3A */ s8 triggerButtonB;
    /* 0x3B */ s8 buttonB;
    /* 0x3C */ u16 equippedItem;
} PlayerControllerData; // size = 0x40;

typedef void (*PlayerUnk1230Func)(struct Player*, struct Game_Play*, Actor*, s32, xyz_t*, f32);
typedef f32 (*PlayerUnk1234Func)(struct Player*, struct Game_Play*);
typedef void (*PlayerUnk1238Func)(struct Player*, struct Game_Play*, Actor*, s32);
typedef s32 (*SetMgrGetEndPosProc)(struct Game*, xyz_t*);

typedef struct Player {
    /* 0x0000 */ Actor actor;
    /* 0x0174 */ UNK_TYPE1 unk_0174[0xB7C];
    /* 0x0CF0*/ s32 unk_0CF0;
    /* 0x0CF4*/ s32 unk_0CF4;
    /* 0x0CF8 */ UNK_TYPE1 unk_0CF8[0x8];
    /* 0x0D00 */ s32 unk_0D00;
    /* 0x0D04 */ s32 unk_0D04;
    /* 0x0D08 */ s32 unk_0D08;
    /* 0x0D0C */ UNK_TYPE1 unk_0D0C[0xA0];
    /* 0x0DAC */ UNK_TYPE unk_0DAC;
    /* 0x0DB0 */ UNK_TYPE unk_0DB0;
    /* 0x0DB4 */ UNK_TYPE1 unk_0DB4[0x8];
    /* 0x0DBC */ u8* unk_0DBC[2];
    /* 0x0DC4 */ UNK_TYPE1 unk_0DC4[0x18];
    /* 0x0DDC */ UNK_TYPE unk_0DDC[2];
    /* 0x0DE4 */ UNK_TYPE unk_0DE4[2];
    /* 0x0DEC */ UNK_TYPE1 unk_0DEC[0x160];
    /* 0x0F4C */ ClObjTris colliderTris1;
    /* 0x0F60 */ UNK_TYPE1 unk_0F60[0x44];
    /* 0x0FA4 */ ClObjTris colliderTris2;
    /* 0x0FB8 */ UNK_TYPE1 unk_0FB8[0x50];
    /* 0x1008 */ ClObjPipe colliderPipe;
    /* 0x1024 */ UNK_TYPE1 unk_1024[0x20C];
    /* 0x1230 */ PlayerUnk1230Func unk_1230;
    /* 0x1234 */ PlayerUnk1234Func unk_1234;
    /* 0x1238 */ PlayerUnk1238Func unk_1238;
    /* 0x123C */ UNK_TYPE1 unk_123C[0x8];
    /* 0x1244 */ SetMgrGetEndPosProc getEndPos;
    /* 0x1248 */ UNK_TYPE1 unk_1248[0x70];
    /* 0x12B8 */ UNK_TYPE unk_12B8;
    /* 0x12BC */ s32 unk_12BC;
    /* 0x12C0 */ u16 unk_12C0;
    /* 0x12C2 */ UNK_TYPE1 unk_12C2[0x2];
    /* 0x12C4 */ UNK_TYPE1 unk_12C4[0x14];
} Player; // size = 0x12D8

void Player_actor_ct(Actor* thisx, struct Game_Play* game_play);
void Player_actor_dt(Actor* thisx, struct Game_Play* game_play);
void Player_actor_move(Actor* thisx, struct Game_Play* game_play);
void Player_actor_draw(Actor* thisx, struct Game_Play* game_play);

#endif
