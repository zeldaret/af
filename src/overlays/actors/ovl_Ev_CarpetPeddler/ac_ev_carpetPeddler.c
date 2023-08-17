#include "ac_ev_carpetPeddler.h"
#include "m_lib.h"
#include "overlays/gamestates/ovl_play/m_play.h"

void aECPD_actor_ct(Actor* thisx, Game_Play* play);
void aECPD_actor_dt(Actor* thisx, Game_Play* play);
void aECPD_actor_init(Actor* thisx, Game_Play* play);
void aECPD_actor_save(Actor* thisx, Game_Play* play);

#if 0
ActorProfile Ev_CarpetPeddler_Profile = {
    /* */ ACTOR_EV_CARPET_PEDDLER,
    /* */ ACTOR_PART_NPC,
    /* */ 0,
    /* */ 0xD006,
    /* */ GAMEPLAY_KEEP,
    /* */ sizeof(Ev_CarpetPeddler),
    /* */ aECPD_actor_ct,
    /* */ aECPD_actor_dt,
    /* */ aECPD_actor_init,
    /* */ (ActorFunc)none_proc1,
    /* */ aECPD_actor_save,
};
#endif

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_CarpetPeddler/ac_ev_carpetPeddler/aECPD_actor_ct.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_CarpetPeddler/ac_ev_carpetPeddler/aECPD_actor_save.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_CarpetPeddler/ac_ev_carpetPeddler/aECPD_actor_dt.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_CarpetPeddler/ac_ev_carpetPeddler/aECPD_actor_init.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_CarpetPeddler/ac_ev_carpetPeddler/func_809D9DA8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_CarpetPeddler/ac_ev_carpetPeddler/func_809D9F10_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_CarpetPeddler/ac_ev_carpetPeddler/func_809D9FD8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_CarpetPeddler/ac_ev_carpetPeddler/func_809DA0C0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_CarpetPeddler/ac_ev_carpetPeddler/func_809DA108_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_CarpetPeddler/ac_ev_carpetPeddler/func_809DA158_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_CarpetPeddler/ac_ev_carpetPeddler/func_809DA1BC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_CarpetPeddler/ac_ev_carpetPeddler/func_809DA24C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_CarpetPeddler/ac_ev_carpetPeddler/func_809DA340_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_CarpetPeddler/ac_ev_carpetPeddler/func_809DA3B4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_CarpetPeddler/ac_ev_carpetPeddler/func_809DA404_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_CarpetPeddler/ac_ev_carpetPeddler/func_809DA4A4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_CarpetPeddler/ac_ev_carpetPeddler/func_809DA59C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_CarpetPeddler/ac_ev_carpetPeddler/func_809DA5DC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_CarpetPeddler/ac_ev_carpetPeddler/func_809DA65C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_CarpetPeddler/ac_ev_carpetPeddler/func_809DA698_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_CarpetPeddler/ac_ev_carpetPeddler/func_809DA704_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_CarpetPeddler/ac_ev_carpetPeddler/func_809DA79C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_CarpetPeddler/ac_ev_carpetPeddler/func_809DA800_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_CarpetPeddler/ac_ev_carpetPeddler/func_809DA830_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_CarpetPeddler/ac_ev_carpetPeddler/func_809DA928_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_CarpetPeddler/ac_ev_carpetPeddler/func_809DA958_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_CarpetPeddler/ac_ev_carpetPeddler/func_809DA988_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_CarpetPeddler/ac_ev_carpetPeddler/func_809DA9D0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_CarpetPeddler/ac_ev_carpetPeddler/func_809DAA70_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_CarpetPeddler/ac_ev_carpetPeddler/func_809DAAA0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_CarpetPeddler/ac_ev_carpetPeddler/func_809DAAD0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_CarpetPeddler/ac_ev_carpetPeddler/func_809DAB00_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_CarpetPeddler/ac_ev_carpetPeddler/func_809DAB30_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_CarpetPeddler/ac_ev_carpetPeddler/func_809DAB54_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_CarpetPeddler/ac_ev_carpetPeddler/func_809DAB88_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_CarpetPeddler/ac_ev_carpetPeddler/func_809DABBC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_CarpetPeddler/ac_ev_carpetPeddler/func_809DAC18_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_CarpetPeddler/ac_ev_carpetPeddler/func_809DAC44_jp.s")
