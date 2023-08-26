#include "ac_npc_p_sel.h"
#include "m_lib.h"
#include "m_actor_dlftbls.h"
#include "m_object.h"
#include "overlays/gamestates/ovl_play/m_play.h"

void aNPS_actor_ct(Actor* thisx, Game_Play* gamePlay);
void aNPS_actor_dt(Actor* thisx, Game_Play* gamePlay);
void aNPS_actor_init(Actor* thisx, Game_Play* gamePlay);
void aNPS_actor_save(Actor* thisx, Game_Play* gamePlay);

#if 0
ActorProfile Npc_P_Sel_Profile = {
    /* */ ACTOR_NPC_P_SEL,
    /* */ ACTOR_PART_NPC,
    /* */ 0,
    /* */ 0xD018,
    /* */ GAMEPLAY_KEEP,
    /* */ sizeof(Npc_P_Sel),
    /* */ aNPS_actor_ct,
    /* */ aNPS_actor_dt,
    /* */ aNPS_actor_init,
    /* */ (ActorFunc)none_proc1,
    /* */ aNPS_actor_save,
};
#endif

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_P_Sel/ac_npc_p_sel/aNPS_actor_ct.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_P_Sel/ac_npc_p_sel/aNPS_actor_save.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_P_Sel/ac_npc_p_sel/aNPS_actor_dt.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_P_Sel/ac_npc_p_sel/aNPS_actor_init.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_P_Sel/ac_npc_p_sel/func_809BDB74_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_P_Sel/ac_npc_p_sel/func_809BDC54_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_P_Sel/ac_npc_p_sel/func_809BDCC4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_P_Sel/ac_npc_p_sel/func_809BDE58_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_P_Sel/ac_npc_p_sel/func_809BDE78_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_P_Sel/ac_npc_p_sel/func_809BDEA8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_P_Sel/ac_npc_p_sel/func_809BDF08_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_P_Sel/ac_npc_p_sel/func_809BDF74_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_P_Sel/ac_npc_p_sel/func_809BDFA4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_P_Sel/ac_npc_p_sel/func_809BE04C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_P_Sel/ac_npc_p_sel/func_809BE104_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_P_Sel/ac_npc_p_sel/func_809BE194_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_P_Sel/ac_npc_p_sel/func_809BE1D0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_P_Sel/ac_npc_p_sel/func_809BE20C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_P_Sel/ac_npc_p_sel/func_809BE27C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_P_Sel/ac_npc_p_sel/func_809BE2EC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_P_Sel/ac_npc_p_sel/func_809BE30C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_P_Sel/ac_npc_p_sel/func_809BE350_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_P_Sel/ac_npc_p_sel/func_809BE384_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_P_Sel/ac_npc_p_sel/func_809BE3D8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_P_Sel/ac_npc_p_sel/func_809BE548_jp.s")
