#ifndef M_PLAYER_H
#define M_PLAYER_H

#include "ultra64.h"
#include "m_actor.h"
#include "m_collision_obj.h"
#include "unk.h"

struct Game;
struct Game_Play;
struct Player;

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
    /* 0x0DBC */ UNK_TYPE unk_0DBC[2];
    /* 0x0DC4 */ UNK_TYPE1 unk_0DC4[0x18];
    /* 0x0DDC */ UNK_TYPE unk_0DDC[2];
    /* 0x0DE4 */ UNK_TYPE unk_0DE4[2];
    /* 0x0DEC */ UNK_TYPE1 unk_0DEC[0x160];
    /* 0x0F4C */ ClObjTris colliderTris1;
    /* 0x0F60 */ UNK_TYPE1 unk_0F60[0x44];
    /* 0x0FA4 */ ClObjTris colliderTris2;
    /* 0x0FB8 */ UNK_TYPE1 unk_0FB8[0x50];
    /* 0x1008 */ ClObjPipe colliderPipe;
    /* 0x1024 */ UNK_TYPE1 unk_1024[0x220];
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
