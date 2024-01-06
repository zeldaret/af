#include "ac_countdown_npc0.h"
#include "m_lib.h"
#include "m_actor_dlftbls.h"
#include "m_object.h"
#include "overlays/gamestates/ovl_play/m_play.h"

void aCD0_actor_ct(Actor* thisx, Game_Play* game_play);
void aCD0_actor_dt(Actor* thisx, Game_Play* game_play);
void aCD0_actor_init(Actor* thisx, Game_Play* game_play);
void aCD0_actor_save(Actor* thisx, Game_Play* game_play);

#if 0
ActorProfile Countdown_Npc0_Profile = {
    /* */ ACTOR_COUNTDOWN_NPC0,
    /* */ ACTOR_PART_NPC,
    /* */ 0,
    /* */ 0x0000,
    /* */ GAMEPLAY_KEEP,
    /* */ sizeof(Countdown_Npc0),
    /* */ aCD0_actor_ct,
    /* */ aCD0_actor_dt,
    /* */ aCD0_actor_init,
    /* */ (void*)none_proc1,
    /* */ aCD0_actor_save,
};
#endif

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Countdown_Npc0/ac_countdown_npc0/aCD0_actor_ct.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Countdown_Npc0/ac_countdown_npc0/aCD0_actor_save.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Countdown_Npc0/ac_countdown_npc0/aCD0_actor_dt.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Countdown_Npc0/ac_countdown_npc0/aCD0_actor_init.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Countdown_Npc0/ac_countdown_npc0/func_809E0C04_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Countdown_Npc0/ac_countdown_npc0/func_809E0C44_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Countdown_Npc0/ac_countdown_npc0/func_809E0C70_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Countdown_Npc0/ac_countdown_npc0/func_809E0C8C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Countdown_Npc0/ac_countdown_npc0/func_809E0CBC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Countdown_Npc0/ac_countdown_npc0/func_809E0CF0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Countdown_Npc0/ac_countdown_npc0/func_809E0D28_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Countdown_Npc0/ac_countdown_npc0/func_809E0D3C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Countdown_Npc0/ac_countdown_npc0/func_809E0D98_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Countdown_Npc0/ac_countdown_npc0/func_809E0DC0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Countdown_Npc0/ac_countdown_npc0/func_809E0DF0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Countdown_Npc0/ac_countdown_npc0/func_809E0EA4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Countdown_Npc0/ac_countdown_npc0/func_809E100C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Countdown_Npc0/ac_countdown_npc0/func_809E104C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Countdown_Npc0/ac_countdown_npc0/func_809E107C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Countdown_Npc0/ac_countdown_npc0/func_809E10AC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Countdown_Npc0/ac_countdown_npc0/func_809E11C0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Countdown_Npc0/ac_countdown_npc0/func_809E122C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Countdown_Npc0/ac_countdown_npc0/func_809E125C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Countdown_Npc0/ac_countdown_npc0/func_809E12AC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Countdown_Npc0/ac_countdown_npc0/func_809E1310_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Countdown_Npc0/ac_countdown_npc0/func_809E138C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Countdown_Npc0/ac_countdown_npc0/func_809E13C0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Countdown_Npc0/ac_countdown_npc0/func_809E1450_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Countdown_Npc0/ac_countdown_npc0/func_809E1484_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Countdown_Npc0/ac_countdown_npc0/func_809E14F4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Countdown_Npc0/ac_countdown_npc0/func_809E1570_jp.s")
