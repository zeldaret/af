#include "ac_npc_majin3.h"
#include "m_lib.h"
#include "overlays/gamestates/ovl_play/m_play.h"

void aMJN3_actor_ct(Actor* thisx, PlayState* play);
void aMJN3_actor_dt(Actor* thisx, PlayState* play);
void aMJN3_actor_init(Actor* thisx, PlayState* play);
void aMJN3_actor_save(Actor* thisx, PlayState* play);

#if 0
ActorProfile Npc_Majin3_Profile = {
    /* */ ACTOR_NPC_MAJIN3,
    /* */ ACTOR_PART_NPC,
    /* */ ACTOR_FLAG_10 | ACTOR_FLAG_20,
    /* */ 0xD068,
    /* */ GAMEPLAY_KEEP,
    /* */ sizeof(Npc_Majin3),
    /* */ aMJN3_actor_ct,
    /* */ aMJN3_actor_dt,
    /* */ aMJN3_actor_init,
    /* */ (ActorFunc)none_proc1,
    /* */ aMJN3_actor_save,
};
#endif

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Majin3/ac_npc_majin3/aMJN3_actor_ct.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Majin3/ac_npc_majin3/aMJN3_actor_save.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Majin3/ac_npc_majin3/aMJN3_actor_dt.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Majin3/ac_npc_majin3/aMJN3_actor_init.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Majin3/ac_npc_majin3/func_809B4B40_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Majin3/ac_npc_majin3/func_809B4B78_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Majin3/ac_npc_majin3/func_809B4BB8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Majin3/ac_npc_majin3/func_809B4C18_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Majin3/ac_npc_majin3/func_809B4D08_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Majin3/ac_npc_majin3/func_809B4D68_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Majin3/ac_npc_majin3/func_809B4DB8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Majin3/ac_npc_majin3/func_809B4E34_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Majin3/ac_npc_majin3/func_809B4E84_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Majin3/ac_npc_majin3/func_809B4F0C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Majin3/ac_npc_majin3/func_809B4F28_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Majin3/ac_npc_majin3/func_809B4F90_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Majin3/ac_npc_majin3/func_809B4FC4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Majin3/ac_npc_majin3/func_809B5084_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Majin3/ac_npc_majin3/func_809B50F0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Majin3/ac_npc_majin3/func_809B5110_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Majin3/ac_npc_majin3/func_809B5120_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Majin3/ac_npc_majin3/func_809B5150_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Majin3/ac_npc_majin3/func_809B51BC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Majin3/ac_npc_majin3/func_809B5214_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Majin3/ac_npc_majin3/func_809B5300_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Majin3/ac_npc_majin3/func_809B5334_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Majin3/ac_npc_majin3/func_809B5388_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Majin3/ac_npc_majin3/func_809B549C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Majin3/ac_npc_majin3/func_809B5530_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Majin3/ac_npc_majin3/func_809B55A8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Majin3/ac_npc_majin3/func_809B55D8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Majin3/ac_npc_majin3/func_809B5618_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Majin3/ac_npc_majin3/func_809B5684_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Majin3/ac_npc_majin3/func_809B56B4_jp.s")
