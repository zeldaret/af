#include "ev_cherry_manager.h"
#include "overlays/gamestates/ovl_play/m_play.h"

void eChryMgr_ct(Actor* thisx, PlayState* play);
void eChryMgr_dt(Actor* thisx, PlayState* play);
void eChryMgr_move(Actor* thisx, PlayState* play);
void eChryMgr_draw(Actor* thisx, PlayState* play);

#if 0
ActorProfile Ev_Cherry_Manager_Profile = {
    /* */ 120,
    /* */ ACTOR_PART_7,
    /* */ 536870912,
    /* */ 0,
    /* */ 3,
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