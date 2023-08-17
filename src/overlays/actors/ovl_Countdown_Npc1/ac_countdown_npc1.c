#include "ac_countdown_npc1.h"
#include "m_lib.h"
#include "overlays/gamestates/ovl_play/m_play.h"

void aCD1_actor_ct(Actor* thisx, Game_Play* play);
void aCD1_actor_dt(Actor* thisx, Game_Play* play);
void aCD1_actor_init(Actor* thisx, Game_Play* play);
void aCD1_actor_save(Actor* thisx, Game_Play* play);

#if 0
ActorProfile Countdown_Npc1_Profile = {
    /* */ ACTOR_COUNTDOWN_NPC1,
    /* */ ACTOR_PART_NPC,
    /* */ 0,
    /* */ 0x0000,
    /* */ GAMEPLAY_KEEP,
    /* */ sizeof(Countdown_Npc1),
    /* */ aCD1_actor_ct,
    /* */ aCD1_actor_dt,
    /* */ aCD1_actor_init,
    /* */ (ActorFunc)none_proc1,
    /* */ aCD1_actor_save,
};
#endif

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Countdown_Npc1/ac_countdown_npc1/aCD1_actor_ct.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Countdown_Npc1/ac_countdown_npc1/aCD1_actor_save.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Countdown_Npc1/ac_countdown_npc1/aCD1_actor_dt.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Countdown_Npc1/ac_countdown_npc1/aCD1_actor_init.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Countdown_Npc1/ac_countdown_npc1/func_809E1874_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Countdown_Npc1/ac_countdown_npc1/func_809E18B4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Countdown_Npc1/ac_countdown_npc1/func_809E18E0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Countdown_Npc1/ac_countdown_npc1/func_809E18FC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Countdown_Npc1/ac_countdown_npc1/func_809E1960_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Countdown_Npc1/ac_countdown_npc1/func_809E19B0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Countdown_Npc1/ac_countdown_npc1/func_809E1A3C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Countdown_Npc1/ac_countdown_npc1/func_809E1B78_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Countdown_Npc1/ac_countdown_npc1/func_809E1BAC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Countdown_Npc1/ac_countdown_npc1/func_809E1C24_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Countdown_Npc1/ac_countdown_npc1/func_809E1C78_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Countdown_Npc1/ac_countdown_npc1/func_809E1CCC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Countdown_Npc1/ac_countdown_npc1/func_809E1D30_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Countdown_Npc1/ac_countdown_npc1/func_809E1D6C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Countdown_Npc1/ac_countdown_npc1/func_809E1E4C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Countdown_Npc1/ac_countdown_npc1/func_809E1E9C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Countdown_Npc1/ac_countdown_npc1/func_809E1F10_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Countdown_Npc1/ac_countdown_npc1/func_809E1F5C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Countdown_Npc1/ac_countdown_npc1/func_809E1F70_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Countdown_Npc1/ac_countdown_npc1/func_809E1F98_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Countdown_Npc1/ac_countdown_npc1/func_809E1FC8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Countdown_Npc1/ac_countdown_npc1/func_809E2068_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Countdown_Npc1/ac_countdown_npc1/func_809E22A4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Countdown_Npc1/ac_countdown_npc1/func_809E2328_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Countdown_Npc1/ac_countdown_npc1/func_809E24C4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Countdown_Npc1/ac_countdown_npc1/func_809E2504_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Countdown_Npc1/ac_countdown_npc1/func_809E2534_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Countdown_Npc1/ac_countdown_npc1/func_809E2644_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Countdown_Npc1/ac_countdown_npc1/func_809E26BC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Countdown_Npc1/ac_countdown_npc1/func_809E26EC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Countdown_Npc1/ac_countdown_npc1/func_809E273C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Countdown_Npc1/ac_countdown_npc1/func_809E279C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Countdown_Npc1/ac_countdown_npc1/func_809E2824_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Countdown_Npc1/ac_countdown_npc1/func_809E2858_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Countdown_Npc1/ac_countdown_npc1/func_809E2898_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Countdown_Npc1/ac_countdown_npc1/func_809E28D8_jp.s")
