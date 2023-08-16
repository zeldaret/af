#include "ac_npc_shop_mastersp.h"
#include "m_lib.h"
#include "overlays/gamestates/ovl_play/m_play.h"

void aSHM_actor_ct(Actor* thisx, PlayState* play);
void aSHM_actor_dt(Actor* thisx, PlayState* play);
void aSHM_actor_init(Actor* thisx, PlayState* play);
void aSHM_actor_save(Actor* thisx, PlayState* play);

#if 0
ActorProfile Npc_Shop_Mastersp_Profile = {
    /* */ 116,
    /* */ ACTOR_PART_NPC,
    /* */ 0,
    /* */ 53278,
    /* */ 3,
    /* */ sizeof(Npc_Shop_Mastersp),
    /* */ aSHM_actor_ct,
    /* */ aSHM_actor_dt,
    /* */ aSHM_actor_init,
    /* */ (ActorFunc)none_proc1,
    /* */ aSHM_actor_save,
};
#endif

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Shop_Mastersp/ac_npc_shop_mastersp/aSHM_actor_ct.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Shop_Mastersp/ac_npc_shop_mastersp/aSHM_actor_save.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Shop_Mastersp/ac_npc_shop_mastersp/aSHM_actor_dt.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Shop_Mastersp/ac_npc_shop_mastersp/aSHM_actor_init.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Shop_Mastersp/ac_npc_shop_mastersp/func_80A6C6B8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Shop_Mastersp/ac_npc_shop_mastersp/func_80A6C6EC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Shop_Mastersp/ac_npc_shop_mastersp/func_80A6C724_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Shop_Mastersp/ac_npc_shop_mastersp/func_80A6C93C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Shop_Mastersp/ac_npc_shop_mastersp/func_80A6C968_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Shop_Mastersp/ac_npc_shop_mastersp/func_80A6C998_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Shop_Mastersp/ac_npc_shop_mastersp/func_80A6C9F4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Shop_Mastersp/ac_npc_shop_mastersp/func_80A6CA90_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Shop_Mastersp/ac_npc_shop_mastersp/func_80A6CABC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Shop_Mastersp/ac_npc_shop_mastersp/func_80A6CB0C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Shop_Mastersp/ac_npc_shop_mastersp/func_80A6CBDC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Shop_Mastersp/ac_npc_shop_mastersp/func_80A6CC24_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Shop_Mastersp/ac_npc_shop_mastersp/func_80A6CC98_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Shop_Mastersp/ac_npc_shop_mastersp/func_80A6CD00_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Shop_Mastersp/ac_npc_shop_mastersp/func_80A6CD68_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Shop_Mastersp/ac_npc_shop_mastersp/func_80A6CE1C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Shop_Mastersp/ac_npc_shop_mastersp/func_80A6CF7C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Shop_Mastersp/ac_npc_shop_mastersp/func_80A6D008_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Shop_Mastersp/ac_npc_shop_mastersp/func_80A6D0DC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Shop_Mastersp/ac_npc_shop_mastersp/func_80A6D1A8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Shop_Mastersp/ac_npc_shop_mastersp/func_80A6D280_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Shop_Mastersp/ac_npc_shop_mastersp/func_80A6D320_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Shop_Mastersp/ac_npc_shop_mastersp/func_80A6D3D4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Shop_Mastersp/ac_npc_shop_mastersp/func_80A6D450_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Shop_Mastersp/ac_npc_shop_mastersp/func_80A6D534_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Shop_Mastersp/ac_npc_shop_mastersp/func_80A6D590_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Shop_Mastersp/ac_npc_shop_mastersp/func_80A6D5E4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Shop_Mastersp/ac_npc_shop_mastersp/func_80A6D658_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Shop_Mastersp/ac_npc_shop_mastersp/func_80A6D6C4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Shop_Mastersp/ac_npc_shop_mastersp/func_80A6D758_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Shop_Mastersp/ac_npc_shop_mastersp/func_80A6D78C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Shop_Mastersp/ac_npc_shop_mastersp/func_80A6D7F4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Shop_Mastersp/ac_npc_shop_mastersp/func_80A6D828_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Shop_Mastersp/ac_npc_shop_mastersp/func_80A6D868_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Shop_Mastersp/ac_npc_shop_mastersp/func_80A6D8F4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Shop_Mastersp/ac_npc_shop_mastersp/func_80A6D9B4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Shop_Mastersp/ac_npc_shop_mastersp/func_80A6DA18_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Shop_Mastersp/ac_npc_shop_mastersp/func_80A6DA80_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Shop_Mastersp/ac_npc_shop_mastersp/func_80A6DADC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Shop_Mastersp/ac_npc_shop_mastersp/func_80A6DB44_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Shop_Mastersp/ac_npc_shop_mastersp/func_80A6DB74_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Shop_Mastersp/ac_npc_shop_mastersp/func_80A6DBD4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Shop_Mastersp/ac_npc_shop_mastersp/func_80A6DC04_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Shop_Mastersp/ac_npc_shop_mastersp/func_80A6DC8C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Shop_Mastersp/ac_npc_shop_mastersp/func_80A6DCD0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Shop_Mastersp/ac_npc_shop_mastersp/func_80A6DD64_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Shop_Mastersp/ac_npc_shop_mastersp/func_80A6DDC0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Shop_Mastersp/ac_npc_shop_mastersp/func_80A6DE00_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Shop_Mastersp/ac_npc_shop_mastersp/func_80A6DEAC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Shop_Mastersp/ac_npc_shop_mastersp/func_80A6DF00_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Shop_Mastersp/ac_npc_shop_mastersp/func_80A6DFA0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Shop_Mastersp/ac_npc_shop_mastersp/func_80A6DFF8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Shop_Mastersp/ac_npc_shop_mastersp/func_80A6E034_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Shop_Mastersp/ac_npc_shop_mastersp/func_80A6E094_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Shop_Mastersp/ac_npc_shop_mastersp/func_80A6E0E0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Shop_Mastersp/ac_npc_shop_mastersp/func_80A6E12C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Shop_Mastersp/ac_npc_shop_mastersp/func_80A6E13C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Shop_Mastersp/ac_npc_shop_mastersp/func_80A6E198_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Shop_Mastersp/ac_npc_shop_mastersp/func_80A6E1C4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Shop_Mastersp/ac_npc_shop_mastersp/func_80A6E210_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Shop_Mastersp/ac_npc_shop_mastersp/func_80A6E268_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Shop_Mastersp/ac_npc_shop_mastersp/func_80A6E298_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Shop_Mastersp/ac_npc_shop_mastersp/func_80A6E2D8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Shop_Mastersp/ac_npc_shop_mastersp/func_80A6E344_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Shop_Mastersp/ac_npc_shop_mastersp/func_80A6E374_jp.s")
