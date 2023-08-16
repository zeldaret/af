#include "ac_hanami_npc0.h"
#include "m_lib.h"
#include "overlays/gamestates/ovl_play/m_play.h"

void aHM0_actor_ct(Actor* thisx, PlayState* play);
void aHM0_actor_dt(Actor* thisx, PlayState* play);
void aHM0_actor_init(Actor* thisx, PlayState* play);
void aHM0_actor_save(Actor* thisx, PlayState* play);

#if 0
ActorProfile Hanami_Npc0_Profile = {
    /* */ 98,
    /* */ ACTOR_PART_NPC,
    /* */ 0,
    /* */ 0,
    /* */ 3,
    /* */ sizeof(Hanami_Npc0),
    /* */ aHM0_actor_ct,
    /* */ aHM0_actor_dt,
    /* */ aHM0_actor_init,
    /* */ (ActorFunc)none_proc1,
    /* */ aHM0_actor_save,
};
#endif

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Hanami_Npc0/ac_hanami_npc0/aHM0_actor_ct.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Hanami_Npc0/ac_hanami_npc0/aHM0_actor_save.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Hanami_Npc0/ac_hanami_npc0/aHM0_actor_dt.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Hanami_Npc0/ac_hanami_npc0/aHM0_actor_init.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Hanami_Npc0/ac_hanami_npc0/func_809DE434_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Hanami_Npc0/ac_hanami_npc0/func_809DE474_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Hanami_Npc0/ac_hanami_npc0/func_809DE4A0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Hanami_Npc0/ac_hanami_npc0/func_809DE4C0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Hanami_Npc0/ac_hanami_npc0/func_809DE538_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Hanami_Npc0/ac_hanami_npc0/func_809DE56C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Hanami_Npc0/ac_hanami_npc0/func_809DE5BC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Hanami_Npc0/ac_hanami_npc0/func_809DE5DC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Hanami_Npc0/ac_hanami_npc0/func_809DE6B4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Hanami_Npc0/ac_hanami_npc0/func_809DE6C8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Hanami_Npc0/ac_hanami_npc0/func_809DE6EC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Hanami_Npc0/ac_hanami_npc0/func_809DE714_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Hanami_Npc0/ac_hanami_npc0/func_809DE744_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Hanami_Npc0/ac_hanami_npc0/func_809DE7D0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Hanami_Npc0/ac_hanami_npc0/func_809DE800_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Hanami_Npc0/ac_hanami_npc0/func_809DE830_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Hanami_Npc0/ac_hanami_npc0/func_809DE8D0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Hanami_Npc0/ac_hanami_npc0/func_809DE948_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Hanami_Npc0/ac_hanami_npc0/func_809DE978_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Hanami_Npc0/ac_hanami_npc0/func_809DE9EC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Hanami_Npc0/ac_hanami_npc0/func_809DEA20_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Hanami_Npc0/ac_hanami_npc0/func_809DEA4C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Hanami_Npc0/ac_hanami_npc0/func_809DEA8C_jp.s")
