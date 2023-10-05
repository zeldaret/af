#include "ac_npc_rcn_guide2.h"
#include "m_lib.h"
#include "m_actor_dlftbls.h"
#include "m_object.h"
#include "overlays/gamestates/ovl_play/m_play.h"

void aNRG2_actor_ct(Actor* thisx, Game_Play* game_play);
void aNRG2_actor_dt(Actor* thisx, Game_Play* game_play);
void aNRG2_actor_init(Actor* thisx, Game_Play* game_play);
void aNRG2_actor_save(Actor* thisx, Game_Play* game_play);

#if 0
ActorProfile Npc_Rcn_Guide2_Profile = {
    /* */ ACTOR_NPC_RCN_GUIDE2,
    /* */ ACTOR_PART_NPC,
    /* */ 0,
    /* */ 0xD019,
    /* */ GAMEPLAY_KEEP,
    /* */ sizeof(Npc_Rcn_Guide2),
    /* */ aNRG2_actor_ct,
    /* */ aNRG2_actor_dt,
    /* */ aNRG2_actor_init,
    /* */ (void*)none_proc1,
    /* */ aNRG2_actor_save,
};
#endif

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Rcn_Guide2/ac_npc_rcn_guide2/aNRG2_actor_ct.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Rcn_Guide2/ac_npc_rcn_guide2/aNRG2_actor_save.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Rcn_Guide2/ac_npc_rcn_guide2/aNRG2_actor_dt.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Rcn_Guide2/ac_npc_rcn_guide2/aNRG2_actor_init.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Rcn_Guide2/ac_npc_rcn_guide2/func_809C8130_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Rcn_Guide2/ac_npc_rcn_guide2/func_809C8190_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Rcn_Guide2/ac_npc_rcn_guide2/func_809C81F0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Rcn_Guide2/ac_npc_rcn_guide2/func_809C8248_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Rcn_Guide2/ac_npc_rcn_guide2/func_809C834C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Rcn_Guide2/ac_npc_rcn_guide2/func_809C83B0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Rcn_Guide2/ac_npc_rcn_guide2/func_809C83F4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Rcn_Guide2/ac_npc_rcn_guide2/func_809C8564_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Rcn_Guide2/ac_npc_rcn_guide2/func_809C8600_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Rcn_Guide2/ac_npc_rcn_guide2/func_809C862C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Rcn_Guide2/ac_npc_rcn_guide2/func_809C8654_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Rcn_Guide2/ac_npc_rcn_guide2/func_809C86E4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Rcn_Guide2/ac_npc_rcn_guide2/func_809C8760_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Rcn_Guide2/ac_npc_rcn_guide2/func_809C87EC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Rcn_Guide2/ac_npc_rcn_guide2/func_809C8864_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Rcn_Guide2/ac_npc_rcn_guide2/func_809C888C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Rcn_Guide2/ac_npc_rcn_guide2/func_809C88B4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Rcn_Guide2/ac_npc_rcn_guide2/func_809C88DC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Rcn_Guide2/ac_npc_rcn_guide2/func_809C8940_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Rcn_Guide2/ac_npc_rcn_guide2/func_809C899C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Rcn_Guide2/ac_npc_rcn_guide2/func_809C8AA8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Rcn_Guide2/ac_npc_rcn_guide2/func_809C8AE4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Rcn_Guide2/ac_npc_rcn_guide2/func_809C8B24_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Rcn_Guide2/ac_npc_rcn_guide2/func_809C8B78_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Rcn_Guide2/ac_npc_rcn_guide2/func_809C8C18_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Rcn_Guide2/ac_npc_rcn_guide2/func_809C8C78_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Rcn_Guide2/ac_npc_rcn_guide2/func_809C8CF4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Rcn_Guide2/ac_npc_rcn_guide2/func_809C8D78_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Rcn_Guide2/ac_npc_rcn_guide2/func_809C8E0C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Rcn_Guide2/ac_npc_rcn_guide2/func_809C8EE0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Rcn_Guide2/ac_npc_rcn_guide2/func_809C8F30_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Rcn_Guide2/ac_npc_rcn_guide2/func_809C8F78_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Rcn_Guide2/ac_npc_rcn_guide2/func_809C8FEC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Rcn_Guide2/ac_npc_rcn_guide2/func_809C9090_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Rcn_Guide2/ac_npc_rcn_guide2/func_809C9114_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Rcn_Guide2/ac_npc_rcn_guide2/func_809C91FC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Rcn_Guide2/ac_npc_rcn_guide2/func_809C9224_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Rcn_Guide2/ac_npc_rcn_guide2/func_809C9240_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Rcn_Guide2/ac_npc_rcn_guide2/func_809C9298_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Rcn_Guide2/ac_npc_rcn_guide2/func_809C9374_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Rcn_Guide2/ac_npc_rcn_guide2/func_809C93D8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Rcn_Guide2/ac_npc_rcn_guide2/func_809C9430_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Rcn_Guide2/ac_npc_rcn_guide2/func_809C94EC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Rcn_Guide2/ac_npc_rcn_guide2/func_809C9524_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Rcn_Guide2/ac_npc_rcn_guide2/func_809C95B8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Rcn_Guide2/ac_npc_rcn_guide2/func_809C9654_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Rcn_Guide2/ac_npc_rcn_guide2/func_809C9684_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Rcn_Guide2/ac_npc_rcn_guide2/func_809C96FC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Rcn_Guide2/ac_npc_rcn_guide2/func_809C9768_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Rcn_Guide2/ac_npc_rcn_guide2/func_809C978C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Rcn_Guide2/ac_npc_rcn_guide2/func_809C97EC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Rcn_Guide2/ac_npc_rcn_guide2/func_809C9870_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Rcn_Guide2/ac_npc_rcn_guide2/func_809C98B8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Rcn_Guide2/ac_npc_rcn_guide2/func_809C9918_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Rcn_Guide2/ac_npc_rcn_guide2/func_809C993C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Rcn_Guide2/ac_npc_rcn_guide2/func_809C994C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Rcn_Guide2/ac_npc_rcn_guide2/func_809C995C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Rcn_Guide2/ac_npc_rcn_guide2/func_809C99AC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Rcn_Guide2/ac_npc_rcn_guide2/func_809C9A20_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Rcn_Guide2/ac_npc_rcn_guide2/func_809C9A9C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Rcn_Guide2/ac_npc_rcn_guide2/func_809C9ADC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Rcn_Guide2/ac_npc_rcn_guide2/func_809C9B10_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Rcn_Guide2/ac_npc_rcn_guide2/func_809C9C38_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Rcn_Guide2/ac_npc_rcn_guide2/func_809C9C74_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Rcn_Guide2/ac_npc_rcn_guide2/func_809C9C94_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Rcn_Guide2/ac_npc_rcn_guide2/func_809C9CB4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Rcn_Guide2/ac_npc_rcn_guide2/func_809C9D00_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Rcn_Guide2/ac_npc_rcn_guide2/func_809C9DA8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Rcn_Guide2/ac_npc_rcn_guide2/func_809C9DD8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Rcn_Guide2/ac_npc_rcn_guide2/func_809C9E18_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Rcn_Guide2/ac_npc_rcn_guide2/func_809C9E84_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Rcn_Guide2/ac_npc_rcn_guide2/func_809C9EB4_jp.s")
