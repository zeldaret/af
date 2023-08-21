#ifndef M_PLAYER_H
#define M_PLAYER_H

#include "ultra64.h"
#include "m_actor.h"
#include "unk.h"

struct Game_Play;
struct Player;

typedef struct Player {
    /* 0x0000 */ Actor actor;
    /* 0x0174 */ UNK_TYPE1 unk_0174[0x1164];
} Player; // size = 0x12D8

void Player_actor_ct(Actor* thisx, struct Game_Play* game_play);
void Player_actor_dt(Actor* thisx, struct Game_Play* game_play);
void Player_actor_move(Actor* thisx, struct Game_Play* game_play);
void Player_actor_draw(Actor* thisx, struct Game_Play* game_play);

#endif
