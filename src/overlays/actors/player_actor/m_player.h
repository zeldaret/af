#ifndef M_PLAYER_H
#define M_PLAYER_H

#include "ultra64.h"
#include "m_actor.h"
#include "m_collision_obj.h"
#include "unk.h"

struct Game_Play;
struct Player;

typedef struct Player {
    /* 0x0000 */ Actor actor;
    /* 0x0174 */ UNK_TYPE1 unk_0174[0xDD8];
    /* 0x0F4C */ ClObjTris colliderTris1;
    /* 0x0F60 */ UNK_TYPE1 unk_0F60[0x44];
    /* 0x0FA4 */ ClObjTris colliderTris2;
    /* 0x0FB8 */ UNK_TYPE1 unk_0FB8[0x50];
    /* 0x1008 */ ClObjPipe colliderPipe;
    /* 0x1024 */ UNK_TYPE1 unk_1024[0x2B4];
} Player; // size = 0x12D8

void Player_actor_ct(Actor* thisx, struct Game_Play* game_play);
void Player_actor_dt(Actor* thisx, struct Game_Play* game_play);
void Player_actor_move(Actor* thisx, struct Game_Play* game_play);
void Player_actor_draw(Actor* thisx, struct Game_Play* game_play);

#endif
