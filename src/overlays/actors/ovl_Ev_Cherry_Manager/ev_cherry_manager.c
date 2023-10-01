#include "ev_cherry_manager.h"
#include "m_actor_dlftbls.h"
#include "m_object.h"
#include "overlays/gamestates/ovl_play/m_play.h"
#include "m_event.h"

void eChryMgr_ct(Actor* thisx, Game_Play* game_play);
void eChryMgr_dt(Actor* thisx, Game_Play* game_play);
void eChryMgr_move(Actor* thisx, Game_Play* game_play);
void eChryMgr_draw(Actor* thisx, Game_Play* game_play);

ActorProfile Ev_Cherry_Manager_Profile = {
    /* */ ACTOR_EV_CHERRY_MANAGER,
    /* */ ACTOR_PART_7,
    /* */ ACTOR_FLAG_20000000,
    /* */ 0x0000,
    /* */ GAMEPLAY_KEEP,
    /* */ sizeof(Ev_Cherry_Manager),
    /* */ eChryMgr_ct,
    /* */ eChryMgr_dt,
    /* */ eChryMgr_move,
    /* */ eChryMgr_draw,
    /* */ NULL,
};

void eChryMgr_move(Actor* thisx UNUSED, Game_Play* game_play UNUSED) {
}

void eChryMgr_draw(Actor* thisx UNUSED, Game_Play* game_play UNUSED) {
}

void eChryMgr_ct(Actor* thisx UNUSED, Game_Play* game_play UNUSED) {
}

void eChryMgr_dt(Actor* thisx UNUSED, Game_Play* game_play UNUSED) {
    mEv_clear_status(0xC, 1);
}
