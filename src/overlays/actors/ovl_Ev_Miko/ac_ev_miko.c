#include "ac_ev_miko.h"
#include "m_lib.h"
#include "overlays/gamestates/ovl_play/m_play.h"

void aEMK_actor_ct(Actor* thisx, Game_Play* game_play);
void aEMK_actor_dt(Actor* thisx, Game_Play* game_play);
void aEMK_actor_init(Actor* thisx, Game_Play* game_play);
void aEMK_actor_save(Actor* thisx, Game_Play* game_play);

#if 0
ActorProfile Ev_Miko_Profile = {
    /* */ ACTOR_EV_MIKO,
    /* */ ACTOR_PART_NPC,
    /* */ 0,
    /* */ 0xD03D,
    /* */ GAMEPLAY_KEEP,
    /* */ sizeof(Ev_Miko),
    /* */ aEMK_actor_ct,
    /* */ aEMK_actor_dt,
    /* */ aEMK_actor_init,
    /* */ (ActorFunc)none_proc1,
    /* */ aEMK_actor_save,
};
#endif

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Miko/ac_ev_miko/aEMK_actor_ct.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Miko/ac_ev_miko/aEMK_actor_save.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Miko/ac_ev_miko/aEMK_actor_dt.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Miko/ac_ev_miko/aEMK_actor_init.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Miko/ac_ev_miko/func_809E58E0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Miko/ac_ev_miko/func_809E597C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Miko/ac_ev_miko/func_809E59C4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Miko/ac_ev_miko/func_809E5A94_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Miko/ac_ev_miko/func_809E5B7C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Miko/ac_ev_miko/func_809E5BC4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Miko/ac_ev_miko/func_809E5CF8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Miko/ac_ev_miko/func_809E5DF0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Miko/ac_ev_miko/func_809E5EA0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Miko/ac_ev_miko/func_809E5FA0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Miko/ac_ev_miko/func_809E5FE4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Miko/ac_ev_miko/func_809E6014_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Miko/ac_ev_miko/func_809E6048_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Miko/ac_ev_miko/func_809E6084_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Miko/ac_ev_miko/func_809E60C4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Miko/ac_ev_miko/func_809E60F0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Miko/ac_ev_miko/func_809E61C8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Miko/ac_ev_miko/func_809E6234_jp.s")
