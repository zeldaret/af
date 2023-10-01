#include "ac_npc_post_man.h"
#include "m_lib.h"
#include "m_actor_dlftbls.h"
#include "m_object.h"
#include "overlays/gamestates/ovl_play/m_play.h"

void aPMAN_actor_ct(Actor* thisx, Game_Play* game_play);
void aPMAN_actor_dt(Actor* thisx, Game_Play* game_play);
void aPMAN_actor_init(Actor* thisx, Game_Play* game_play);
void aPMAN_actor_save(Actor* thisx, Game_Play* game_play);

#if 0
ActorProfile Npc_Post_Man_Profile = {
    /* */ ACTOR_NPC_POST_MAN,
    /* */ ACTOR_PART_NPC,
    /* */ ACTOR_FLAG_10,
    /* */ 0xD011,
    /* */ GAMEPLAY_KEEP,
    /* */ sizeof(Npc_Post_Man),
    /* */ aPMAN_actor_ct,
    /* */ aPMAN_actor_dt,
    /* */ aPMAN_actor_init,
    /* */ (ActorFunc)none_proc1,
    /* */ aPMAN_actor_save,
};
#endif

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Post_Man/ac_npc_post_man/aPMAN_actor_ct.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Post_Man/ac_npc_post_man/aPMAN_actor_save.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Post_Man/ac_npc_post_man/aPMAN_actor_dt.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Post_Man/ac_npc_post_man/aPMAN_actor_init.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Post_Man/ac_npc_post_man/func_809C56AC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Post_Man/ac_npc_post_man/func_809C56F4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Post_Man/ac_npc_post_man/func_809C5768_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Post_Man/ac_npc_post_man/func_809C5854_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Post_Man/ac_npc_post_man/func_809C58AC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Post_Man/ac_npc_post_man/func_809C5930_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Post_Man/ac_npc_post_man/func_809C5A08_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Post_Man/ac_npc_post_man/func_809C5AC8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Post_Man/ac_npc_post_man/func_809C5AF0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Post_Man/ac_npc_post_man/func_809C5B5C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Post_Man/ac_npc_post_man/func_809C5BA8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Post_Man/ac_npc_post_man/func_809C5C90_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Post_Man/ac_npc_post_man/func_809C5D54_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Post_Man/ac_npc_post_man/func_809C5D98_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Post_Man/ac_npc_post_man/func_809C5DDC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Post_Man/ac_npc_post_man/func_809C5E68_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Post_Man/ac_npc_post_man/func_809C5E98_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Post_Man/ac_npc_post_man/func_809C5EDC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Post_Man/ac_npc_post_man/func_809C5FA8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Post_Man/ac_npc_post_man/func_809C602C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Post_Man/ac_npc_post_man/func_809C6090_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Post_Man/ac_npc_post_man/func_809C60EC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Post_Man/ac_npc_post_man/func_809C6144_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Post_Man/ac_npc_post_man/func_809C6210_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Post_Man/ac_npc_post_man/func_809C633C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Post_Man/ac_npc_post_man/func_809C635C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Post_Man/ac_npc_post_man/func_809C6394_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Post_Man/ac_npc_post_man/func_809C63F4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Post_Man/ac_npc_post_man/func_809C6438_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Post_Man/ac_npc_post_man/func_809C645C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Post_Man/ac_npc_post_man/func_809C6480_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Post_Man/ac_npc_post_man/func_809C64A8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Post_Man/ac_npc_post_man/func_809C6518_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Post_Man/ac_npc_post_man/func_809C6548_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Post_Man/ac_npc_post_man/func_809C6584_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Post_Man/ac_npc_post_man/func_809C65C8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Post_Man/ac_npc_post_man/func_809C6600_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Post_Man/ac_npc_post_man/func_809C6620_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Post_Man/ac_npc_post_man/func_809C6688_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Post_Man/ac_npc_post_man/func_809C6720_jp.s")
