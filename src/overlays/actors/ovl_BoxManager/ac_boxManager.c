#include "ac_boxManager.h"
#include "m_actor_dlftbls.h"
#include "m_object.h"
#include "overlays/gamestates/ovl_play/m_play.h"

void BoxManager_Actor_ct(Actor* thisx, Game_Play* game_play);
void BoxManager_Actor_dt(Actor* thisx, Game_Play* game_play);
void BoxManager_Actor_move(Actor* thisx, Game_Play* game_play);
void BoxManager_Actor_draw(Actor* thisx, Game_Play* game_play);

ActorProfile BoxManager_Profile = {
    /* */ ACTOR_BOX_MANAGER,
    /* */ ACTOR_PART_4,
    /* */ ACTOR_FLAG_10 | ACTOR_FLAG_20,
    /* */ 0x8005,
    /* */ OBJECT_20,
    /* */ sizeof(BoxManager),
    /* */ BoxManager_Actor_ct,
    /* */ BoxManager_Actor_dt,
    /* */ BoxManager_Actor_move,
    /* */ BoxManager_Actor_draw,
    /* */ NULL,
};

void BoxManager_Actor_ct(Actor* thisx UNUSED, Game_Play* game_play UNUSED) {
}

void BoxManager_Actor_dt(Actor* thisx UNUSED, Game_Play* game_play UNUSED) {
}

void BoxManager_Actor_move(Actor* thisx UNUSED, Game_Play* game_play UNUSED) {
}

void BoxManager_Actor_draw(Actor* thisx UNUSED, Game_Play* game_play UNUSED) {
}
