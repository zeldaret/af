#include "ac_npc_guide2.h"
#include "m_lib.h"
#include "m_actor_dlftbls.h"
#include "m_object.h"
#include "overlays/gamestates/ovl_play/m_play.h"

void aNG2_actor_ct(Actor* thisx, Game_Play* game_play);
void aNG2_actor_dt(Actor* thisx, Game_Play* game_play);
void aNG2_actor_init(Actor* thisx, Game_Play* game_play);
void aNG2_actor_save(Actor* thisx, Game_Play* game_play);

#if 0
ActorProfile Npc_Guide2_Profile = {
    /* */ ACTOR_NPC_GUIDE2,
    /* */ ACTOR_PART_NPC,
    /* */ ACTOR_FLAG_10 | ACTOR_FLAG_20,
    /* */ 0xD005,
    /* */ GAMEPLAY_KEEP,
    /* */ sizeof(Npc_Guide2),
    /* */ aNG2_actor_ct,
    /* */ aNG2_actor_dt,
    /* */ aNG2_actor_init,
    /* */ (void*)none_proc1,
    /* */ aNG2_actor_save,
};
#endif

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Guide2/ac_npc_guide2/aNG2_actor_ct.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Guide2/ac_npc_guide2/aNG2_actor_save.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Guide2/ac_npc_guide2/aNG2_actor_dt.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Guide2/ac_npc_guide2/aNG2_actor_init.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Guide2/ac_npc_guide2/func_809B13D8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Guide2/ac_npc_guide2/func_809B141C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Guide2/ac_npc_guide2/D_809B15CC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Guide2/ac_npc_guide2/func_809B17C4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Guide2/ac_npc_guide2/func_809B1808_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Guide2/ac_npc_guide2/func_809B1834_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Guide2/ac_npc_guide2/func_809B1860_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Guide2/ac_npc_guide2/func_809B1880_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Guide2/ac_npc_guide2/func_809B190C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Guide2/ac_npc_guide2/func_809B1964_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Guide2/ac_npc_guide2/func_809B19AC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Guide2/ac_npc_guide2/func_809B1A88_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Guide2/ac_npc_guide2/func_809B1B3C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Guide2/ac_npc_guide2/func_809B1BD8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Guide2/ac_npc_guide2/func_809B1C58_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Guide2/ac_npc_guide2/func_809B1CBC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Guide2/ac_npc_guide2/func_809B1CEC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Guide2/ac_npc_guide2/func_809B1D54_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Guide2/ac_npc_guide2/func_809B1D94_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Guide2/ac_npc_guide2/func_809B1DEC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Guide2/ac_npc_guide2/func_809B1E84_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Guide2/ac_npc_guide2/func_809B1ECC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Guide2/ac_npc_guide2/func_809B1F3C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Guide2/ac_npc_guide2/func_809B1FA4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Guide2/ac_npc_guide2/func_809B1FEC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Guide2/ac_npc_guide2/func_809B2018_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Guide2/ac_npc_guide2/func_809B20BC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Guide2/ac_npc_guide2/func_809B2154_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Guide2/ac_npc_guide2/func_809B2294_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Guide2/ac_npc_guide2/func_809B230C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Guide2/ac_npc_guide2/func_809B2358_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Guide2/ac_npc_guide2/func_809B2388_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Guide2/ac_npc_guide2/func_809B23C0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Guide2/ac_npc_guide2/func_809B2418_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Guide2/ac_npc_guide2/func_809B24A4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Guide2/ac_npc_guide2/func_809B24F4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Guide2/ac_npc_guide2/func_809B2520_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Guide2/ac_npc_guide2/func_809B25D0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Guide2/ac_npc_guide2/func_809B2650_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Guide2/ac_npc_guide2/func_809B26DC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Guide2/ac_npc_guide2/func_809B2728_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Guide2/ac_npc_guide2/func_809B275C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Guide2/ac_npc_guide2/func_809B27F4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Guide2/ac_npc_guide2/func_809B2844_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Guide2/ac_npc_guide2/func_809B287C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Guide2/ac_npc_guide2/func_809B28BC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Guide2/ac_npc_guide2/func_809B28EC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Guide2/ac_npc_guide2/func_809B2928_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Guide2/ac_npc_guide2/func_809B2960_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Guide2/ac_npc_guide2/func_809B2990_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Guide2/ac_npc_guide2/func_809B29A4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Guide2/ac_npc_guide2/func_809B29B8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Guide2/ac_npc_guide2/func_809B29D0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Guide2/ac_npc_guide2/func_809B29F4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Guide2/ac_npc_guide2/func_809B2A3C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Guide2/ac_npc_guide2/func_809B2A70_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Guide2/ac_npc_guide2/func_809B2A84_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Guide2/ac_npc_guide2/func_809B2ABC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Guide2/ac_npc_guide2/func_809B2AEC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Guide2/ac_npc_guide2/func_809B2B08_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Guide2/ac_npc_guide2/func_809B2B38_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Guide2/ac_npc_guide2/func_809B2BB8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Guide2/ac_npc_guide2/func_809B2BE8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Guide2/ac_npc_guide2/func_809B2C3C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Guide2/ac_npc_guide2/func_809B2CD4_jp.s")
