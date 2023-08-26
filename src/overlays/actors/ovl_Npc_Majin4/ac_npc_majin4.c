#include "ac_npc_majin4.h"
#include "m_lib.h"
#include "m_actor_dlftbls.h"
#include "m_object.h"
#include "overlays/gamestates/ovl_play/m_play.h"

void aMJN4_actor_ct(Actor* thisx, Game_Play* gamePlay);
void aMJN4_actor_dt(Actor* thisx, Game_Play* gamePlay);
void aMJN4_actor_init(Actor* thisx, Game_Play* gamePlay);
void aMJN4_actor_save(Actor* thisx, Game_Play* gamePlay);

#if 0
ActorProfile Npc_Majin4_Profile = {
    /* */ ACTOR_NPC_MAJIN4,
    /* */ ACTOR_PART_NPC,
    /* */ ACTOR_FLAG_10 | ACTOR_FLAG_20,
    /* */ 0xD069,
    /* */ GAMEPLAY_KEEP,
    /* */ sizeof(Npc_Majin4),
    /* */ aMJN4_actor_ct,
    /* */ aMJN4_actor_dt,
    /* */ aMJN4_actor_init,
    /* */ (ActorFunc)none_proc1,
    /* */ aMJN4_actor_save,
};
#endif

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Majin4/ac_npc_majin4/aMJN4_actor_ct.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Majin4/ac_npc_majin4/aMJN4_actor_save.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Majin4/ac_npc_majin4/aMJN4_actor_dt.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Majin4/ac_npc_majin4/aMJN4_actor_init.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Majin4/ac_npc_majin4/func_809B5AD0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Majin4/ac_npc_majin4/func_809B5B08_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Majin4/ac_npc_majin4/func_809B5B48_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Majin4/ac_npc_majin4/func_809B5BC0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Majin4/ac_npc_majin4/func_809B5BF4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Majin4/ac_npc_majin4/func_809B5C24_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Majin4/ac_npc_majin4/func_809B5C80_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Majin4/ac_npc_majin4/func_809B5D00_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Majin4/ac_npc_majin4/func_809B5D20_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Majin4/ac_npc_majin4/func_809B5D30_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Majin4/ac_npc_majin4/func_809B5D60_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Majin4/ac_npc_majin4/func_809B5E00_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Majin4/ac_npc_majin4/func_809B5EB8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Majin4/ac_npc_majin4/func_809B5F60_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Majin4/ac_npc_majin4/func_809B5FA4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Majin4/ac_npc_majin4/func_809B5FD8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Majin4/ac_npc_majin4/func_809B602C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Majin4/ac_npc_majin4/func_809B6140_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Majin4/ac_npc_majin4/func_809B615C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Majin4/ac_npc_majin4/func_809B61CC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Majin4/ac_npc_majin4/func_809B6210_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Majin4/ac_npc_majin4/func_809B6288_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Majin4/ac_npc_majin4/func_809B62B8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Majin4/ac_npc_majin4/func_809B62F8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Majin4/ac_npc_majin4/func_809B6364_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Majin4/ac_npc_majin4/func_809B6394_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Majin4/ac_npc_majin4/func_809B6690_jp.s")
