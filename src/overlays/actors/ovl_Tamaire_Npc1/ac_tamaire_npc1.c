#include "ac_tamaire_npc1.h"
#include "m_lib.h"
#include "m_actor_dlftbls.h"
#include "m_object.h"
#include "overlays/gamestates/ovl_play/m_play.h"

void aTMN1_actor_ct(Actor* thisx, Game_Play* gamePlay);
void aTMN1_actor_dt(Actor* thisx, Game_Play* gamePlay);
void aTMN1_actor_init(Actor* thisx, Game_Play* gamePlay);
void aTMN1_actor_save(Actor* thisx, Game_Play* gamePlay);

#if 0
ActorProfile Tamaire_Npc1_Profile = {
    /* */ ACTOR_TAMAIRE_NPC1,
    /* */ ACTOR_PART_NPC,
    /* */ 0,
    /* */ 0xD054,
    /* */ GAMEPLAY_KEEP,
    /* */ sizeof(Tamaire_Npc1),
    /* */ aTMN1_actor_ct,
    /* */ aTMN1_actor_dt,
    /* */ aTMN1_actor_init,
    /* */ (ActorFunc)none_proc1,
    /* */ aTMN1_actor_save,
};
#endif

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Tamaire_Npc1/ac_tamaire_npc1/aTMN1_actor_ct.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Tamaire_Npc1/ac_tamaire_npc1/aTMN1_actor_save.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Tamaire_Npc1/ac_tamaire_npc1/aTMN1_actor_dt.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Tamaire_Npc1/ac_tamaire_npc1/aTMN1_actor_init.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Tamaire_Npc1/ac_tamaire_npc1/func_80A8740C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Tamaire_Npc1/ac_tamaire_npc1/func_80A874A8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Tamaire_Npc1/ac_tamaire_npc1/func_80A87598_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Tamaire_Npc1/ac_tamaire_npc1/func_80A875E0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Tamaire_Npc1/ac_tamaire_npc1/func_80A8767C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Tamaire_Npc1/ac_tamaire_npc1/func_80A876C8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Tamaire_Npc1/ac_tamaire_npc1/func_80A87708_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Tamaire_Npc1/ac_tamaire_npc1/func_80A87784_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Tamaire_Npc1/ac_tamaire_npc1/func_80A877C0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Tamaire_Npc1/ac_tamaire_npc1/func_80A8780C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Tamaire_Npc1/ac_tamaire_npc1/func_80A87858_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Tamaire_Npc1/ac_tamaire_npc1/func_80A8789C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Tamaire_Npc1/ac_tamaire_npc1/func_80A879A8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Tamaire_Npc1/ac_tamaire_npc1/func_80A879E8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Tamaire_Npc1/ac_tamaire_npc1/func_80A87A78_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Tamaire_Npc1/ac_tamaire_npc1/func_80A87B40_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Tamaire_Npc1/ac_tamaire_npc1/func_80A87B7C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Tamaire_Npc1/ac_tamaire_npc1/func_80A87C08_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Tamaire_Npc1/ac_tamaire_npc1/func_80A87C38_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Tamaire_Npc1/ac_tamaire_npc1/func_80A87C8C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Tamaire_Npc1/ac_tamaire_npc1/func_80A87DCC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Tamaire_Npc1/ac_tamaire_npc1/func_80A87E68_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Tamaire_Npc1/ac_tamaire_npc1/func_80A87F10_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Tamaire_Npc1/ac_tamaire_npc1/func_80A87F4C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Tamaire_Npc1/ac_tamaire_npc1/func_80A87F84_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Tamaire_Npc1/ac_tamaire_npc1/func_80A88010_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Tamaire_Npc1/ac_tamaire_npc1/func_80A88058_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Tamaire_Npc1/ac_tamaire_npc1/func_80A88084_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Tamaire_Npc1/ac_tamaire_npc1/func_80A880D4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Tamaire_Npc1/ac_tamaire_npc1/func_80A88128_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Tamaire_Npc1/ac_tamaire_npc1/func_80A88160_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Tamaire_Npc1/ac_tamaire_npc1/func_80A881B8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Tamaire_Npc1/ac_tamaire_npc1/func_80A881E8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Tamaire_Npc1/ac_tamaire_npc1/func_80A88238_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Tamaire_Npc1/ac_tamaire_npc1/func_80A88284_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Tamaire_Npc1/ac_tamaire_npc1/func_80A8832C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Tamaire_Npc1/ac_tamaire_npc1/func_80A88374_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Tamaire_Npc1/ac_tamaire_npc1/func_80A883B4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Tamaire_Npc1/ac_tamaire_npc1/func_80A88420_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Tamaire_Npc1/ac_tamaire_npc1/func_80A88468_jp.s")
