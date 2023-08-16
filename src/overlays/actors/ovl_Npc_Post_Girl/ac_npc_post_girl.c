#include "ac_npc_post_girl.h"
#include "m_lib.h"
#include "overlays/gamestates/ovl_play/m_play.h"

void aPG_actor_ct(Actor* thisx, PlayState* play);
void aPG_actor_dt(Actor* thisx, PlayState* play);
void aPG_actor_init(Actor* thisx, PlayState* play);
void aPG_actor_save(Actor* thisx, PlayState* play);

#if 0
ActorProfile Npc_Post_Girl_Profile = {
    /* */ 28,
    /* */ ACTOR_PART_NPC,
    /* */ 0,
    /* */ 53251,
    /* */ 3,
    /* */ sizeof(Npc_Post_Girl),
    /* */ aPG_actor_ct,
    /* */ aPG_actor_dt,
    /* */ aPG_actor_init,
    /* */ (ActorFunc)none_proc1,
    /* */ aPG_actor_save,
};
#endif

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Post_Girl/ac_npc_post_girl/aPG_actor_ct.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Post_Girl/ac_npc_post_girl/aPG_actor_save.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Post_Girl/ac_npc_post_girl/aPG_actor_dt.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Post_Girl/ac_npc_post_girl/aPG_actor_init.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Post_Girl/ac_npc_post_girl/func_809C3580_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Post_Girl/ac_npc_post_girl/func_809C35C0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Post_Girl/ac_npc_post_girl/func_809C360C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Post_Girl/ac_npc_post_girl/func_809C3644_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Post_Girl/ac_npc_post_girl/func_809C3708_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Post_Girl/ac_npc_post_girl/func_809C3770_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Post_Girl/ac_npc_post_girl/func_809C37F8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Post_Girl/ac_npc_post_girl/func_809C3868_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Post_Girl/ac_npc_post_girl/func_809C3938_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Post_Girl/ac_npc_post_girl/func_809C39AC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Post_Girl/ac_npc_post_girl/func_809C3A54_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Post_Girl/ac_npc_post_girl/func_809C3B60_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Post_Girl/ac_npc_post_girl/func_809C3BA0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Post_Girl/ac_npc_post_girl/func_809C3BE8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Post_Girl/ac_npc_post_girl/func_809C3CF8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Post_Girl/ac_npc_post_girl/func_809C3D58_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Post_Girl/ac_npc_post_girl/func_809C3DBC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Post_Girl/ac_npc_post_girl/func_809C3E00_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Post_Girl/ac_npc_post_girl/func_809C3E44_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Post_Girl/ac_npc_post_girl/func_809C3E84_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Post_Girl/ac_npc_post_girl/func_809C3EC0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Post_Girl/ac_npc_post_girl/func_809C3F0C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Post_Girl/ac_npc_post_girl/func_809C3F94_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Post_Girl/ac_npc_post_girl/func_809C3FEC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Post_Girl/ac_npc_post_girl/func_809C403C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Post_Girl/ac_npc_post_girl/func_809C40B4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Post_Girl/ac_npc_post_girl/func_809C419C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Post_Girl/ac_npc_post_girl/func_809C41EC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Post_Girl/ac_npc_post_girl/func_809C4284_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Post_Girl/ac_npc_post_girl/func_809C42D4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Post_Girl/ac_npc_post_girl/func_809C4338_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Post_Girl/ac_npc_post_girl/func_809C43CC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Post_Girl/ac_npc_post_girl/func_809C44A0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Post_Girl/ac_npc_post_girl/func_809C4500_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Post_Girl/ac_npc_post_girl/func_809C45C8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Post_Girl/ac_npc_post_girl/func_809C4610_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Post_Girl/ac_npc_post_girl/func_809C46C8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Post_Girl/ac_npc_post_girl/func_809C471C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Post_Girl/ac_npc_post_girl/func_809C4884_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Post_Girl/ac_npc_post_girl/func_809C4914_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Post_Girl/ac_npc_post_girl/func_809C49D8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Post_Girl/ac_npc_post_girl/func_809C4A08_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Post_Girl/ac_npc_post_girl/func_809C4A3C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Post_Girl/ac_npc_post_girl/func_809C4A74_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Post_Girl/ac_npc_post_girl/func_809C4AD4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Post_Girl/ac_npc_post_girl/func_809C4B04_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Post_Girl/ac_npc_post_girl/func_809C4B34_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Post_Girl/ac_npc_post_girl/func_809C4B64_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Post_Girl/ac_npc_post_girl/func_809C4BD4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Post_Girl/ac_npc_post_girl/func_809C4BF8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Post_Girl/ac_npc_post_girl/func_809C4C2C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Post_Girl/ac_npc_post_girl/func_809C4C5C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Post_Girl/ac_npc_post_girl/func_809C4C8C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Post_Girl/ac_npc_post_girl/func_809C4CD4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Post_Girl/ac_npc_post_girl/func_809C4D2C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Post_Girl/ac_npc_post_girl/func_809C4D5C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Post_Girl/ac_npc_post_girl/func_809C4D8C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Post_Girl/ac_npc_post_girl/func_809C4DBC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Post_Girl/ac_npc_post_girl/func_809C4E04_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Post_Girl/ac_npc_post_girl/func_809C4E44_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Post_Girl/ac_npc_post_girl/func_809C4E74_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Post_Girl/ac_npc_post_girl/func_809C4EA8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Post_Girl/ac_npc_post_girl/func_809C4EF4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Post_Girl/ac_npc_post_girl/func_809C4F28_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Post_Girl/ac_npc_post_girl/func_809C4F5C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Post_Girl/ac_npc_post_girl/func_809C4FA8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Post_Girl/ac_npc_post_girl/func_809C4FD4_jp.s")
