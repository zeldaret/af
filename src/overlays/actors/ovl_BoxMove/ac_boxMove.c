#include "ac_boxMove.h"
#include "m_actor_dlftbls.h"
#include "m_object.h"
#include "overlays/gamestates/ovl_play/m_play.h"

void BoxMove_Actor_ct(Actor* thisx, Game_Play* game_play);
void BoxMove_Actor_dt(Actor* thisx, Game_Play* game_play);
void BoxMove_Actor_move(Actor* thisx, Game_Play* game_play);
void BoxMove_Actor_draw(Actor* thisx, Game_Play* game_play);

ActorProfile BoxMove_Profile = {
    /* */ ACTOR_BOX_MOVE,
    /* */ ACTOR_PART_4,
    /* */ 0,
    /* */ 0x0000,
    /* */ OBJECT_17,
    /* */ sizeof(BoxMove),
    /* */ BoxMove_Actor_ct,
    /* */ BoxMove_Actor_dt,
    /* */ BoxMove_Actor_move,
    /* */ BoxMove_Actor_draw,
    /* */ NULL,
};

void BoxMove_Actor_ct(Actor* thisx UNUSED, Game_Play* game_play UNUSED) {
}

void BoxMove_Actor_dt(Actor* thisx UNUSED, Game_Play* game_play UNUSED) {
}

void BoxMove_Actor_move(Actor* thisx UNUSED, Game_Play* game_play UNUSED) {
}

void BoxMove_Actor_draw(Actor* thisx UNUSED, Game_Play* game_play UNUSED) {
}
