#include "ac_ev_gypsy.h"
#include "m_lib.h"
#include "overlays/gamestates/ovl_play/m_play.h"

void aEGPS_actor_ct(Actor* thisx, PlayState* play);
void aEGPS_actor_dt(Actor* thisx, PlayState* play);
void aEGPS_actor_init(Actor* thisx, PlayState* play);
void aEGPS_actor_save(Actor* thisx, PlayState* play);

#if 0
ActorProfile Ev_Gypsy_Profile = {
    /* */ ACTOR_EV_GYPSY,
    /* */ ACTOR_PART_NPC,
    /* */ 0,
    /* */ 0xD00C,
    /* */ GAMEPLAY_KEEP,
    /* */ sizeof(Ev_Gypsy),
    /* */ aEGPS_actor_ct,
    /* */ aEGPS_actor_dt,
    /* */ aEGPS_actor_init,
    /* */ (ActorFunc)none_proc1,
    /* */ aEGPS_actor_save,
};
#endif

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Gypsy/ac_ev_gypsy/aEGPS_actor_ct.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Gypsy/ac_ev_gypsy/aEGPS_actor_save.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Gypsy/ac_ev_gypsy/aEGPS_actor_dt.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Gypsy/ac_ev_gypsy/aEGPS_actor_init.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Gypsy/ac_ev_gypsy/func_809DC590_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Gypsy/ac_ev_gypsy/func_809DC608_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Gypsy/ac_ev_gypsy/func_809DC6E4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Gypsy/ac_ev_gypsy/func_809DC7F4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Gypsy/ac_ev_gypsy/func_809DC850_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Gypsy/ac_ev_gypsy/func_809DC880_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Gypsy/ac_ev_gypsy/func_809DC8B4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Gypsy/ac_ev_gypsy/func_809DC90C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Gypsy/ac_ev_gypsy/func_809DC940_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Gypsy/ac_ev_gypsy/func_809DC990_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Gypsy/ac_ev_gypsy/func_809DC9E0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Gypsy/ac_ev_gypsy/func_809DCA44_jp.s")
