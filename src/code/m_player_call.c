#include "m_player_call.h"
#include "m_actor.h"
#include "overlays/gamestates/ovl_play/m_play.h"

extern ActorFunc Player_actor_ct_func;
extern ActorFunc Player_actor_draw_func;
extern ActorFunc Player_actor_dt_func;
extern ActorFunc Player_actor_move_func;

void Player_actor_ct_call(Actor* thisx, Game_Play* game_play);
void Player_actor_dt_call(Actor* thisx, Game_Play* game_play);
void Player_actor_move_call(Actor* thisx, Game_Play* game_play);
void Player_actor_draw_call(Actor* thisx, Game_Play* game_play);

void initfunc(Game_Play* game_play);
#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_player_call/initfunc.s")

void Player_actor_ct_call(Actor* thisx, Game_Play* game_play) {
    load_player(&game_play->unk_1CBC);
    initfunc(game_play);
    Player_actor_ct_func(thisx, game_play);
}

void Player_actor_dt_call(Actor* thisx, Game_Play* game_play) {
    load_player(&game_play->unk_1CBC);
    Player_actor_dt_func(thisx, game_play);
}

void Player_actor_move_call(Actor* thisx, Game_Play* game_play) {
    load_player(&game_play->unk_1CBC);
    Player_actor_move_func(thisx, game_play);
}

void Player_actor_draw_call(Actor* thisx, Game_Play* game_play) {
    load_player(&game_play->unk_1CBC);
    Player_actor_draw_func(thisx, game_play);
}
