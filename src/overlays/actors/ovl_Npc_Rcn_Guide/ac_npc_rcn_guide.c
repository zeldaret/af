#include "ac_npc_rcn_guide.h"
#include "m_lib.h"
#include "overlays/gamestates/ovl_play/m_play.h"

void aNRG_actor_ct(Actor* thisx, Game_Play* play);
void aNRG_actor_dt(Actor* thisx, Game_Play* play);
void aNRG_actor_init(Actor* thisx, Game_Play* play);
void aNRG_actor_save(Actor* thisx, Game_Play* play);

#if 0
ActorProfile Npc_Rcn_Guide_Profile = {
    /* */ ACTOR_NPC_RCN_GUIDE,
    /* */ ACTOR_PART_NPC,
    /* */ ACTOR_FLAG_10 | ACTOR_FLAG_20000000,
    /* */ 0xD014,
    /* */ GAMEPLAY_KEEP,
    /* */ sizeof(Npc_Rcn_Guide),
    /* */ aNRG_actor_ct,
    /* */ aNRG_actor_dt,
    /* */ aNRG_actor_init,
    /* */ (ActorFunc)none_proc1,
    /* */ aNRG_actor_save,
};
#endif

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Rcn_Guide/ac_npc_rcn_guide/aNRG_actor_ct.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Rcn_Guide/ac_npc_rcn_guide/aNRG_actor_save.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Rcn_Guide/ac_npc_rcn_guide/aNRG_actor_dt.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Rcn_Guide/ac_npc_rcn_guide/aNRG_actor_init.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Rcn_Guide/ac_npc_rcn_guide/func_809C6D10_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Rcn_Guide/ac_npc_rcn_guide/func_809C6DAC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Rcn_Guide/ac_npc_rcn_guide/func_809C6E18_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Rcn_Guide/ac_npc_rcn_guide/func_809C6EA4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Rcn_Guide/ac_npc_rcn_guide/func_809C6ED0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Rcn_Guide/ac_npc_rcn_guide/func_809C6F2C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Rcn_Guide/ac_npc_rcn_guide/func_809C6FAC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Rcn_Guide/ac_npc_rcn_guide/func_809C7030_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Rcn_Guide/ac_npc_rcn_guide/func_809C7084_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Rcn_Guide/ac_npc_rcn_guide/func_809C70F4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Rcn_Guide/ac_npc_rcn_guide/func_809C7110_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Rcn_Guide/ac_npc_rcn_guide/func_809C71B4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Rcn_Guide/ac_npc_rcn_guide/func_809C71E8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Rcn_Guide/ac_npc_rcn_guide/func_809C7274_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Rcn_Guide/ac_npc_rcn_guide/func_809C72A8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Rcn_Guide/ac_npc_rcn_guide/func_809C72D8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Rcn_Guide/ac_npc_rcn_guide/func_809C7354_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Rcn_Guide/ac_npc_rcn_guide/func_809C7394_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Rcn_Guide/ac_npc_rcn_guide/func_809C73D4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Rcn_Guide/ac_npc_rcn_guide/func_809C746C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Rcn_Guide/ac_npc_rcn_guide/func_809C7520_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Rcn_Guide/ac_npc_rcn_guide/func_809C7570_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Rcn_Guide/ac_npc_rcn_guide/func_809C76BC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Rcn_Guide/ac_npc_rcn_guide/func_809C7710_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Rcn_Guide/ac_npc_rcn_guide/func_809C7734_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Rcn_Guide/ac_npc_rcn_guide/func_809C777C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Rcn_Guide/ac_npc_rcn_guide/func_809C77C8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Rcn_Guide/ac_npc_rcn_guide/func_809C7874_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Rcn_Guide/ac_npc_rcn_guide/func_809C78AC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Rcn_Guide/ac_npc_rcn_guide/func_809C7904_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Rcn_Guide/ac_npc_rcn_guide/func_809C7970_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Rcn_Guide/ac_npc_rcn_guide/func_809C79A4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Rcn_Guide/ac_npc_rcn_guide/func_809C7A54_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Rcn_Guide/ac_npc_rcn_guide/func_809C7AAC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Rcn_Guide/ac_npc_rcn_guide/func_809C7ADC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Rcn_Guide/ac_npc_rcn_guide/func_809C7B1C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Rcn_Guide/ac_npc_rcn_guide/func_809C7B88_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Rcn_Guide/ac_npc_rcn_guide/func_809C7BB8_jp.s")
