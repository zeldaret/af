#include "ac_hanami_npc1.h"
#include "m_lib.h"
#include "overlays/gamestates/ovl_play/m_play.h"

void aHM1_actor_ct(Actor* thisx, PlayState* play);
void aHM1_actor_dt(Actor* thisx, PlayState* play);
void aHM1_actor_init(Actor* thisx, PlayState* play);
void aHM1_actor_save(Actor* thisx, PlayState* play);

#if 0
ActorProfile Hanami_Npc1_Profile = {
    /* */ 100,
    /* */ ACTOR_PART_NPC,
    /* */ 0,
    /* */ 0,
    /* */ 3,
    /* */ sizeof(Hanami_Npc1),
    /* */ aHM1_actor_ct,
    /* */ aHM1_actor_dt,
    /* */ aHM1_actor_init,
    /* */ (ActorFunc)none_proc1,
    /* */ aHM1_actor_save,
};
#endif

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Hanami_Npc1/ac_hanami_npc1/aHM1_actor_ct.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Hanami_Npc1/ac_hanami_npc1/aHM1_actor_save.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Hanami_Npc1/ac_hanami_npc1/aHM1_actor_dt.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Hanami_Npc1/ac_hanami_npc1/aHM1_actor_init.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Hanami_Npc1/ac_hanami_npc1/func_809DED84_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Hanami_Npc1/ac_hanami_npc1/func_809DEDC4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Hanami_Npc1/ac_hanami_npc1/func_809DEDF0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Hanami_Npc1/ac_hanami_npc1/func_809DEE10_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Hanami_Npc1/ac_hanami_npc1/func_809DEE60_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Hanami_Npc1/ac_hanami_npc1/func_809DEEEC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Hanami_Npc1/ac_hanami_npc1/func_809DF028_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Hanami_Npc1/ac_hanami_npc1/func_809DF074_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Hanami_Npc1/ac_hanami_npc1/func_809DF0EC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Hanami_Npc1/ac_hanami_npc1/func_809DF134_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Hanami_Npc1/ac_hanami_npc1/func_809DF180_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Hanami_Npc1/ac_hanami_npc1/func_809DF194_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Hanami_Npc1/ac_hanami_npc1/func_809DF1B8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Hanami_Npc1/ac_hanami_npc1/func_809DF1E0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Hanami_Npc1/ac_hanami_npc1/func_809DF210_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Hanami_Npc1/ac_hanami_npc1/func_809DF30C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Hanami_Npc1/ac_hanami_npc1/func_809DF33C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Hanami_Npc1/ac_hanami_npc1/func_809DF36C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Hanami_Npc1/ac_hanami_npc1/func_809DF3FC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Hanami_Npc1/ac_hanami_npc1/func_809DF468_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Hanami_Npc1/ac_hanami_npc1/func_809DF498_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Hanami_Npc1/ac_hanami_npc1/func_809DF4F0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Hanami_Npc1/ac_hanami_npc1/func_809DF524_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Hanami_Npc1/ac_hanami_npc1/func_809DF550_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Hanami_Npc1/ac_hanami_npc1/func_809DF590_jp.s")
