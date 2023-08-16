#include "ac_npc_mamedanuki.h"
#include "m_lib.h"
#include "overlays/gamestates/ovl_play/m_play.h"

void aNMD_actor_ct(Actor* thisx, PlayState* play);
void aNMD_actor_dt(Actor* thisx, PlayState* play);
void aNMD_actor_init(Actor* thisx, PlayState* play);
void aNMD_actor_save(Actor* thisx, PlayState* play);

#if 0
ActorProfile Npc_Mamedanuki_Profile = {
    /* */ ACTOR_NPC_MAMEDANUKI,
    /* */ ACTOR_PART_NPC,
    /* */ 0,
    /* */ 0xD026,
    /* */ GAMEPLAY_KEEP,
    /* */ sizeof(Npc_Mamedanuki),
    /* */ aNMD_actor_ct,
    /* */ aNMD_actor_dt,
    /* */ aNMD_actor_init,
    /* */ (ActorFunc)none_proc1,
    /* */ aNMD_actor_save,
};
#endif

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Mamedanuki/ac_npc_mamedanuki/aNMD_actor_ct.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Mamedanuki/ac_npc_mamedanuki/aNMD_actor_save.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Mamedanuki/ac_npc_mamedanuki/aNMD_actor_dt.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Mamedanuki/ac_npc_mamedanuki/aNMD_actor_init.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Mamedanuki/ac_npc_mamedanuki/func_809B6B58_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Mamedanuki/ac_npc_mamedanuki/func_809B6C34_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Mamedanuki/ac_npc_mamedanuki/func_809B6C80_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Mamedanuki/ac_npc_mamedanuki/func_809B6D18_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Mamedanuki/ac_npc_mamedanuki/func_809B6E08_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Mamedanuki/ac_npc_mamedanuki/func_809B6E58_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Mamedanuki/ac_npc_mamedanuki/func_809B6E9C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Mamedanuki/ac_npc_mamedanuki/func_809B6ED8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Mamedanuki/ac_npc_mamedanuki/func_809B6F04_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Mamedanuki/ac_npc_mamedanuki/func_809B6F88_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Mamedanuki/ac_npc_mamedanuki/func_809B6FB0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Mamedanuki/ac_npc_mamedanuki/func_809B7030_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Mamedanuki/ac_npc_mamedanuki/func_809B70D8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Mamedanuki/ac_npc_mamedanuki/func_809B7134_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Mamedanuki/ac_npc_mamedanuki/func_809B7154_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Mamedanuki/ac_npc_mamedanuki/func_809B7180_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Mamedanuki/ac_npc_mamedanuki/func_809B71AC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Mamedanuki/ac_npc_mamedanuki/func_809B7238_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Mamedanuki/ac_npc_mamedanuki/func_809B7274_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Mamedanuki/ac_npc_mamedanuki/func_809B72D4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Mamedanuki/ac_npc_mamedanuki/func_809B7328_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Mamedanuki/ac_npc_mamedanuki/func_809B7370_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Mamedanuki/ac_npc_mamedanuki/func_809B73C0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Mamedanuki/ac_npc_mamedanuki/func_809B7494_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Mamedanuki/ac_npc_mamedanuki/func_809B765C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Mamedanuki/ac_npc_mamedanuki/func_809B76D8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Mamedanuki/ac_npc_mamedanuki/func_809B76E8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Mamedanuki/ac_npc_mamedanuki/func_809B77B8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Mamedanuki/ac_npc_mamedanuki/func_809B78B0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Mamedanuki/ac_npc_mamedanuki/func_809B7904_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Mamedanuki/ac_npc_mamedanuki/func_809B79AC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Mamedanuki/ac_npc_mamedanuki/func_809B7AA8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Mamedanuki/ac_npc_mamedanuki/func_809B7B44_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Mamedanuki/ac_npc_mamedanuki/func_809B7B94_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Mamedanuki/ac_npc_mamedanuki/func_809B7BE8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Mamedanuki/ac_npc_mamedanuki/func_809B7C08_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Mamedanuki/ac_npc_mamedanuki/func_809B7C38_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Mamedanuki/ac_npc_mamedanuki/func_809B7C68_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Mamedanuki/ac_npc_mamedanuki/func_809B7D78_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Mamedanuki/ac_npc_mamedanuki/func_809B7DB8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Mamedanuki/ac_npc_mamedanuki/func_809B7DF8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Mamedanuki/ac_npc_mamedanuki/func_809B7E70_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Mamedanuki/ac_npc_mamedanuki/func_809B7E9C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Mamedanuki/ac_npc_mamedanuki/func_809B7EC8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Mamedanuki/ac_npc_mamedanuki/func_809B7F2C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Mamedanuki/ac_npc_mamedanuki/func_809B7F4C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Mamedanuki/ac_npc_mamedanuki/func_809B7F6C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Mamedanuki/ac_npc_mamedanuki/func_809B7F8C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Mamedanuki/ac_npc_mamedanuki/func_809B80C4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Mamedanuki/ac_npc_mamedanuki/func_809B8168_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Mamedanuki/ac_npc_mamedanuki/func_809B837C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Mamedanuki/ac_npc_mamedanuki/func_809B844C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Mamedanuki/ac_npc_mamedanuki/func_809B84A8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Mamedanuki/ac_npc_mamedanuki/func_809B8520_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Mamedanuki/ac_npc_mamedanuki/func_809B8564_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Mamedanuki/ac_npc_mamedanuki/func_809B85BC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Mamedanuki/ac_npc_mamedanuki/func_809B85F0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Mamedanuki/ac_npc_mamedanuki/func_809B8668_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Mamedanuki/ac_npc_mamedanuki/func_809B87A4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Mamedanuki/ac_npc_mamedanuki/func_809B87FC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Mamedanuki/ac_npc_mamedanuki/func_809B8868_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Mamedanuki/ac_npc_mamedanuki/func_809B88B4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Mamedanuki/ac_npc_mamedanuki/func_809B88E4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Mamedanuki/ac_npc_mamedanuki/func_809B89AC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Mamedanuki/ac_npc_mamedanuki/func_809B8A48_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Mamedanuki/ac_npc_mamedanuki/func_809B8C70_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Mamedanuki/ac_npc_mamedanuki/func_809B8CE4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Mamedanuki/ac_npc_mamedanuki/func_809B8DCC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Mamedanuki/ac_npc_mamedanuki/func_809B8E60_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Mamedanuki/ac_npc_mamedanuki/func_809B8F3C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Mamedanuki/ac_npc_mamedanuki/func_809B904C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Mamedanuki/ac_npc_mamedanuki/func_809B909C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Mamedanuki/ac_npc_mamedanuki/func_809B9160_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Mamedanuki/ac_npc_mamedanuki/func_809B9310_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Mamedanuki/ac_npc_mamedanuki/func_809B93C4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Mamedanuki/ac_npc_mamedanuki/func_809B9594_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Mamedanuki/ac_npc_mamedanuki/func_809B95FC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Mamedanuki/ac_npc_mamedanuki/func_809B9654_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Mamedanuki/ac_npc_mamedanuki/func_809B96C0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Mamedanuki/ac_npc_mamedanuki/func_809B972C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Mamedanuki/ac_npc_mamedanuki/func_809B97C8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Mamedanuki/ac_npc_mamedanuki/func_809B97FC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Mamedanuki/ac_npc_mamedanuki/func_809B989C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Mamedanuki/ac_npc_mamedanuki/func_809B98CC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Mamedanuki/ac_npc_mamedanuki/func_809B9924_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Mamedanuki/ac_npc_mamedanuki/func_809B9990_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Mamedanuki/ac_npc_mamedanuki/func_809B99B4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Mamedanuki/ac_npc_mamedanuki/func_809B99DC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Mamedanuki/ac_npc_mamedanuki/func_809B9A14_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Mamedanuki/ac_npc_mamedanuki/func_809B9A44_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Mamedanuki/ac_npc_mamedanuki/func_809B9A74_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Mamedanuki/ac_npc_mamedanuki/func_809B9AB4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Mamedanuki/ac_npc_mamedanuki/func_809B9AE4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Mamedanuki/ac_npc_mamedanuki/func_809B9B14_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Mamedanuki/ac_npc_mamedanuki/func_809B9BF8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Mamedanuki/ac_npc_mamedanuki/func_809B9C28_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Mamedanuki/ac_npc_mamedanuki/func_809B9C68_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Mamedanuki/ac_npc_mamedanuki/func_809B9CA0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Mamedanuki/ac_npc_mamedanuki/func_809B9CD8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Mamedanuki/ac_npc_mamedanuki/func_809B9DC0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Mamedanuki/ac_npc_mamedanuki/func_809B9DE8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Mamedanuki/ac_npc_mamedanuki/func_809B9E40_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Mamedanuki/ac_npc_mamedanuki/func_809B9E7C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Mamedanuki/ac_npc_mamedanuki/func_809B9E8C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Mamedanuki/ac_npc_mamedanuki/func_809B9EB0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Mamedanuki/ac_npc_mamedanuki/func_809B9EE0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Mamedanuki/ac_npc_mamedanuki/func_809B9F04_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Mamedanuki/ac_npc_mamedanuki/func_809B9F28_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Mamedanuki/ac_npc_mamedanuki/func_809B9F4C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Mamedanuki/ac_npc_mamedanuki/func_809B9F70_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Mamedanuki/ac_npc_mamedanuki/func_809B9FA0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Mamedanuki/ac_npc_mamedanuki/func_809B9FD0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Mamedanuki/ac_npc_mamedanuki/func_809BA024_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Mamedanuki/ac_npc_mamedanuki/func_809BA100_jp.s")
