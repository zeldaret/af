#include "ac_ev_kabuPeddler.h"
#include "m_lib.h"
#include "overlays/gamestates/ovl_play/m_play.h"

void aEKPD_actor_ct(Actor* thisx, Game_Play* play);
void aEKPD_actor_dt(Actor* thisx, Game_Play* play);
void aEKPD_actor_init(Actor* thisx, Game_Play* play);
void aEKPD_actor_save(Actor* thisx, Game_Play* play);

#if 0
ActorProfile Ev_KabuPeddler_Profile = {
    /* */ ACTOR_EV_KABU_PEDDLER,
    /* */ ACTOR_PART_NPC,
    /* */ 0,
    /* */ 0xD007,
    /* */ GAMEPLAY_KEEP,
    /* */ sizeof(Ev_KabuPeddler),
    /* */ aEKPD_actor_ct,
    /* */ aEKPD_actor_dt,
    /* */ aEKPD_actor_init,
    /* */ (ActorFunc)none_proc1,
    /* */ aEKPD_actor_save,
};
#endif

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_KabuPeddler/ac_ev_kabuPeddler/aEKPD_actor_ct.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_KabuPeddler/ac_ev_kabuPeddler/aEKPD_actor_save.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_KabuPeddler/ac_ev_kabuPeddler/aEKPD_actor_dt.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_KabuPeddler/ac_ev_kabuPeddler/aEKPD_actor_init.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_KabuPeddler/ac_ev_kabuPeddler/func_809E4B30_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_KabuPeddler/ac_ev_kabuPeddler/func_809E4BB0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_KabuPeddler/ac_ev_kabuPeddler/func_809E4C04_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_KabuPeddler/ac_ev_kabuPeddler/func_809E4C74_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_KabuPeddler/ac_ev_kabuPeddler/func_809E4C9C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_KabuPeddler/ac_ev_kabuPeddler/func_809E4D6C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_KabuPeddler/ac_ev_kabuPeddler/func_809E4E54_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_KabuPeddler/ac_ev_kabuPeddler/func_809E4E9C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_KabuPeddler/ac_ev_kabuPeddler/func_809E4EE4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_KabuPeddler/ac_ev_kabuPeddler/func_809E4FD8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_KabuPeddler/ac_ev_kabuPeddler/func_809E5128_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_KabuPeddler/ac_ev_kabuPeddler/func_809E518C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_KabuPeddler/ac_ev_kabuPeddler/func_809E51E8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_KabuPeddler/ac_ev_kabuPeddler/func_809E5234_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_KabuPeddler/ac_ev_kabuPeddler/func_809E526C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_KabuPeddler/ac_ev_kabuPeddler/func_809E52C4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_KabuPeddler/ac_ev_kabuPeddler/func_809E530C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_KabuPeddler/ac_ev_kabuPeddler/func_809E533C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_KabuPeddler/ac_ev_kabuPeddler/func_809E5370_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_KabuPeddler/ac_ev_kabuPeddler/func_809E53B0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_KabuPeddler/ac_ev_kabuPeddler/func_809E53E4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_KabuPeddler/ac_ev_kabuPeddler/func_809E5460_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_KabuPeddler/ac_ev_kabuPeddler/func_809E54BC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_KabuPeddler/ac_ev_kabuPeddler/func_809E54E8_jp.s")
