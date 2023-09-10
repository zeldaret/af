#include "ac_fieldm_draw.h"
#include "m_actor_dlftbls.h"
#include "m_object.h"
#include "overlays/gamestates/ovl_play/m_play.h"

void Fieldm_Actor_ct(Actor* thisx, Game_Play* game_play);
void Fieldm_Actor_dt(Actor* thisx, Game_Play* game_play);
void Fieldm_Actor_move(Actor* thisx, Game_Play* game_play);
void Fieldm_Actor_draw(Actor* thisx, Game_Play* game_play);

ActorProfile Fieldm_Draw_Profile = {
    /* */ ACTOR_FIELDM_DRAW,
    /* */ ACTOR_PART_4,
    /* */ 0,
    /* */ 0x0000,
    /* */ GAMEPLAY_KEEP,
    /* */ sizeof(Fieldm_Draw),
    /* */ Fieldm_Actor_ct,
    /* */ Fieldm_Actor_dt,
    /* */ Fieldm_Actor_move,
    /* */ Fieldm_Actor_draw,
    /* */ NULL,
};

void Fieldm_Actor_ct(Actor* thisx UNUSED, Game_Play* game_play UNUSED) {
}

void Fieldm_Actor_dt(Actor* thisx UNUSED, Game_Play* game_play UNUSED) {
}

void Fieldm_Actor_move(Actor* thisx UNUSED, Game_Play* game_play UNUSED) {
}

void Fieldm_Actor_draw(Actor* thisx UNUSED, Game_Play* game_play UNUSED) {
}
