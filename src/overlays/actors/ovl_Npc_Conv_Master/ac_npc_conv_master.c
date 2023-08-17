#include "ac_npc_conv_master.h"
#include "m_lib.h"
#include "overlays/gamestates/ovl_play/m_play.h"

void aNCM_actor_ct(Actor* thisx, Game_Play* play);
void aNCM_actor_dt(Actor* thisx, Game_Play* play);
void aNCM_actor_init(Actor* thisx, Game_Play* play);
void aNCM_actor_save(Actor* thisx, Game_Play* play);

#if 0
ActorProfile Npc_Conv_Master_Profile = {
    /* */ ACTOR_NPC_CONV_MASTER,
    /* */ ACTOR_PART_NPC,
    /* */ 0,
    /* */ 0xD009,
    /* */ GAMEPLAY_KEEP,
    /* */ sizeof(Npc_Conv_Master),
    /* */ aNCM_actor_ct,
    /* */ aNCM_actor_dt,
    /* */ aNCM_actor_init,
    /* */ (ActorFunc)none_proc1,
    /* */ aNCM_actor_save,
};
#endif

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Conv_Master/ac_npc_conv_master/aNCM_actor_ct.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Conv_Master/ac_npc_conv_master/aNCM_actor_save.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Conv_Master/ac_npc_conv_master/aNCM_actor_dt.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Conv_Master/ac_npc_conv_master/aNCM_actor_init.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Conv_Master/ac_npc_conv_master/func_809A5D44_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Conv_Master/ac_npc_conv_master/func_809A5D98_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Conv_Master/ac_npc_conv_master/func_809A5E38_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Conv_Master/ac_npc_conv_master/func_809A5E6C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Conv_Master/ac_npc_conv_master/func_809A5F04_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Conv_Master/ac_npc_conv_master/func_809A5FC8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Conv_Master/ac_npc_conv_master/func_809A6008_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Conv_Master/ac_npc_conv_master/func_809A604C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Conv_Master/ac_npc_conv_master/func_809A6088_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Conv_Master/ac_npc_conv_master/func_809A60B4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Conv_Master/ac_npc_conv_master/func_809A6138_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Conv_Master/ac_npc_conv_master/func_809A6160_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Conv_Master/ac_npc_conv_master/func_809A61E0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Conv_Master/ac_npc_conv_master/func_809A6288_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Conv_Master/ac_npc_conv_master/func_809A62E4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Conv_Master/ac_npc_conv_master/func_809A6304_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Conv_Master/ac_npc_conv_master/func_809A6330_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Conv_Master/ac_npc_conv_master/func_809A635C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Conv_Master/ac_npc_conv_master/func_809A6384_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Conv_Master/ac_npc_conv_master/func_809A6410_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Conv_Master/ac_npc_conv_master/func_809A644C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Conv_Master/ac_npc_conv_master/func_809A64AC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Conv_Master/ac_npc_conv_master/func_809A6500_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Conv_Master/ac_npc_conv_master/func_809A6548_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Conv_Master/ac_npc_conv_master/func_809A6598_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Conv_Master/ac_npc_conv_master/func_809A666C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Conv_Master/ac_npc_conv_master/func_809A67AC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Conv_Master/ac_npc_conv_master/func_809A6828_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Conv_Master/ac_npc_conv_master/func_809A6838_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Conv_Master/ac_npc_conv_master/func_809A6908_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Conv_Master/ac_npc_conv_master/func_809A6A00_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Conv_Master/ac_npc_conv_master/func_809A6A54_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Conv_Master/ac_npc_conv_master/func_809A6AFC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Conv_Master/ac_npc_conv_master/func_809A6BF8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Conv_Master/ac_npc_conv_master/func_809A6C94_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Conv_Master/ac_npc_conv_master/func_809A6CE4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Conv_Master/ac_npc_conv_master/func_809A6D38_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Conv_Master/ac_npc_conv_master/func_809A6D68_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Conv_Master/ac_npc_conv_master/func_809A6D98_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Conv_Master/ac_npc_conv_master/func_809A6DC8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Conv_Master/ac_npc_conv_master/func_809A6ED8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Conv_Master/ac_npc_conv_master/func_809A6F18_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Conv_Master/ac_npc_conv_master/func_809A6F58_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Conv_Master/ac_npc_conv_master/func_809A6FD0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Conv_Master/ac_npc_conv_master/func_809A6FFC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Conv_Master/ac_npc_conv_master/func_809A7028_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Conv_Master/ac_npc_conv_master/func_809A7348_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Conv_Master/ac_npc_conv_master/func_809A759C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Conv_Master/ac_npc_conv_master/func_809A7614_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Conv_Master/ac_npc_conv_master/func_809A7680_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Conv_Master/ac_npc_conv_master/func_809A7820_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Conv_Master/ac_npc_conv_master/func_809A7860_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Conv_Master/ac_npc_conv_master/func_809A78B8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Conv_Master/ac_npc_conv_master/func_809A79FC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Conv_Master/ac_npc_conv_master/func_809A7AFC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Conv_Master/ac_npc_conv_master/func_809A7B30_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Conv_Master/ac_npc_conv_master/func_809A7BA8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Conv_Master/ac_npc_conv_master/func_809A7CE4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Conv_Master/ac_npc_conv_master/func_809A7D3C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Conv_Master/ac_npc_conv_master/func_809A7DA8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Conv_Master/ac_npc_conv_master/func_809A7DF4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Conv_Master/ac_npc_conv_master/func_809A7E24_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Conv_Master/ac_npc_conv_master/func_809A7EEC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Conv_Master/ac_npc_conv_master/func_809A7F88_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Conv_Master/ac_npc_conv_master/func_809A81B0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Conv_Master/ac_npc_conv_master/func_809A8224_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Conv_Master/ac_npc_conv_master/func_809A830C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Conv_Master/ac_npc_conv_master/func_809A83A0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Conv_Master/ac_npc_conv_master/func_809A847C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Conv_Master/ac_npc_conv_master/func_809A858C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Conv_Master/ac_npc_conv_master/func_809A85DC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Conv_Master/ac_npc_conv_master/func_809A86A0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Conv_Master/ac_npc_conv_master/func_809A8850_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Conv_Master/ac_npc_conv_master/func_809A8904_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Conv_Master/ac_npc_conv_master/func_809A8AD4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Conv_Master/ac_npc_conv_master/func_809A8B3C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Conv_Master/ac_npc_conv_master/func_809A8B94_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Conv_Master/ac_npc_conv_master/func_809A8C00_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Conv_Master/ac_npc_conv_master/func_809A8C6C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Conv_Master/ac_npc_conv_master/func_809A8D08_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Conv_Master/ac_npc_conv_master/func_809A8D3C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Conv_Master/ac_npc_conv_master/func_809A8DD4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Conv_Master/ac_npc_conv_master/func_809A8E2C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Conv_Master/ac_npc_conv_master/func_809A8EA0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Conv_Master/ac_npc_conv_master/func_809A8EC4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Conv_Master/ac_npc_conv_master/func_809A8EEC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Conv_Master/ac_npc_conv_master/func_809A8F24_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Conv_Master/ac_npc_conv_master/func_809A8F54_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Conv_Master/ac_npc_conv_master/func_809A8F8C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Conv_Master/ac_npc_conv_master/func_809A8FBC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Conv_Master/ac_npc_conv_master/func_809A8FEC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Conv_Master/ac_npc_conv_master/func_809A902C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Conv_Master/ac_npc_conv_master/func_809A905C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Conv_Master/ac_npc_conv_master/func_809A908C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Conv_Master/ac_npc_conv_master/func_809A9170_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Conv_Master/ac_npc_conv_master/func_809A91A0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Conv_Master/ac_npc_conv_master/func_809A91E0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Conv_Master/ac_npc_conv_master/func_809A9218_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Conv_Master/ac_npc_conv_master/func_809A9250_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Conv_Master/ac_npc_conv_master/func_809A9338_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Conv_Master/ac_npc_conv_master/func_809A9360_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Conv_Master/ac_npc_conv_master/func_809A93B8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Conv_Master/ac_npc_conv_master/func_809A93F4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Conv_Master/ac_npc_conv_master/func_809A9404_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Conv_Master/ac_npc_conv_master/func_809A9428_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Conv_Master/ac_npc_conv_master/func_809A9458_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Conv_Master/ac_npc_conv_master/func_809A947C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Conv_Master/ac_npc_conv_master/func_809A94A0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Conv_Master/ac_npc_conv_master/func_809A94C4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Conv_Master/ac_npc_conv_master/func_809A94E8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Conv_Master/ac_npc_conv_master/func_809A9518_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Conv_Master/ac_npc_conv_master/func_809A9548_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Conv_Master/ac_npc_conv_master/func_809A959C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Conv_Master/ac_npc_conv_master/func_809A9650_jp.s")
