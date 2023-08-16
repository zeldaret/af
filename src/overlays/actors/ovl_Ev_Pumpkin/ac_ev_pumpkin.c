#include "ac_ev_pumpkin.h"
#include "m_lib.h"
#include "overlays/gamestates/ovl_play/m_play.h"

void aEPK_actor_ct(Actor* thisx, PlayState* play);
void aEPK_actor_dt(Actor* thisx, PlayState* play);
void aEPK_actor_init(Actor* thisx, PlayState* play);
void aEPK_actor_save(Actor* thisx, PlayState* play);

#if 0
ActorProfile Ev_Pumpkin_Profile = {
    /* */ ACTOR_EV_PUMPKIN,
    /* */ ACTOR_PART_NPC,
    /* */ 0,
    /* */ 0x0000,
    /* */ GAMEPLAY_KEEP,
    /* */ sizeof(Ev_Pumpkin),
    /* */ aEPK_actor_ct,
    /* */ aEPK_actor_dt,
    /* */ aEPK_actor_init,
    /* */ (ActorFunc)none_proc1,
    /* */ aEPK_actor_save,
};
#endif

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Pumpkin/ac_ev_pumpkin/aEPK_actor_ct.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Pumpkin/ac_ev_pumpkin/aEPK_actor_save.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Pumpkin/ac_ev_pumpkin/aEPK_actor_dt.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Pumpkin/ac_ev_pumpkin/aEPK_actor_init.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Pumpkin/ac_ev_pumpkin/func_809E6504_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Pumpkin/ac_ev_pumpkin/func_809E6530_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Pumpkin/ac_ev_pumpkin/func_809E66CC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Pumpkin/ac_ev_pumpkin/func_809E6718_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Pumpkin/ac_ev_pumpkin/func_809E67AC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Pumpkin/ac_ev_pumpkin/func_809E67EC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Pumpkin/ac_ev_pumpkin/func_809E6880_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Pumpkin/ac_ev_pumpkin/func_809E68E8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Pumpkin/ac_ev_pumpkin/func_809E69E0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Pumpkin/ac_ev_pumpkin/func_809E6A70_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Pumpkin/ac_ev_pumpkin/func_809E6AF4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Pumpkin/ac_ev_pumpkin/func_809E6B54_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Pumpkin/ac_ev_pumpkin/func_809E6BE0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Pumpkin/ac_ev_pumpkin/func_809E6C38_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Pumpkin/ac_ev_pumpkin/func_809E6C98_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Pumpkin/ac_ev_pumpkin/func_809E6CFC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Pumpkin/ac_ev_pumpkin/func_809E6D4C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Pumpkin/ac_ev_pumpkin/func_809E6DF8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Pumpkin/ac_ev_pumpkin/func_809E6E58_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Pumpkin/ac_ev_pumpkin/func_809E6E74_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Pumpkin/ac_ev_pumpkin/func_809E6EFC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Pumpkin/ac_ev_pumpkin/func_809E6F30_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Pumpkin/ac_ev_pumpkin/func_809E6F5C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Pumpkin/ac_ev_pumpkin/func_809E6FE8_jp.s")
