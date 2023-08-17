#include "ev_cherry_manager.h"
#include "overlays/gamestates/ovl_play/m_play.h"

void eChryMgr_ct(Actor* thisx, Game_Play* play);
void eChryMgr_dt(Actor* thisx, Game_Play* play);
void eChryMgr_move(Actor* thisx, Game_Play* play);
void eChryMgr_draw(Actor* thisx, Game_Play* play);

#if 0
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
#endif

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Cherry_Manager/ev_cherry_manager/eChryMgr_move.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Cherry_Manager/ev_cherry_manager/eChryMgr_draw.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Cherry_Manager/ev_cherry_manager/eChryMgr_ct.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Cherry_Manager/ev_cherry_manager/eChryMgr_dt.s")
