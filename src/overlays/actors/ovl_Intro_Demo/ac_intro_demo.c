#include "ac_intro_demo.h"
#include "m_lib.h"
#include "overlays/gamestates/ovl_play/m_play.h"

void aID_actor_ct(Actor* thisx, PlayState* play);
void aID_actor_dt(Actor* thisx, PlayState* play);
void aID_actor_move(Actor* thisx, PlayState* play);

#if 0
ActorProfile Intro_Demo_Profile = {
    /* */ 91,
    /* */ ACTOR_PART_7,
    /* */ 536870928,
    /* */ 0,
    /* */ 3,
    /* */ sizeof(Intro_Demo),
    /* */ aID_actor_ct,
    /* */ aID_actor_dt,
    /* */ aID_actor_move,
    /* */ (ActorFunc)none_proc1,
    /* */ NULL,
};
#endif

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Intro_Demo/ac_intro_demo/aID_actor_ct.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Intro_Demo/ac_intro_demo/aID_actor_dt.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Intro_Demo/ac_intro_demo/func_80952ACC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Intro_Demo/ac_intro_demo/func_80952B0C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Intro_Demo/ac_intro_demo/func_80952B48_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Intro_Demo/ac_intro_demo/func_80952B8C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Intro_Demo/ac_intro_demo/func_80952BD0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Intro_Demo/ac_intro_demo/func_80952C34_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Intro_Demo/ac_intro_demo/func_80952C8C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Intro_Demo/ac_intro_demo/func_80952D04_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Intro_Demo/ac_intro_demo/func_80952D70_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Intro_Demo/ac_intro_demo/func_80952DE0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Intro_Demo/ac_intro_demo/func_80952F84_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Intro_Demo/ac_intro_demo/func_80952FB8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Intro_Demo/ac_intro_demo/func_8095305C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Intro_Demo/ac_intro_demo/func_8095308C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Intro_Demo/ac_intro_demo/func_809531C8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Intro_Demo/ac_intro_demo/func_80953238_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Intro_Demo/ac_intro_demo/func_80953288_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Intro_Demo/ac_intro_demo/func_809532F0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Intro_Demo/ac_intro_demo/func_8095337C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Intro_Demo/ac_intro_demo/func_809533B8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Intro_Demo/ac_intro_demo/func_809533F0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Intro_Demo/ac_intro_demo/func_80953444_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Intro_Demo/ac_intro_demo/func_80953474_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Intro_Demo/ac_intro_demo/func_809534C4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Intro_Demo/ac_intro_demo/func_80953550_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Intro_Demo/ac_intro_demo/func_80953580_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Intro_Demo/ac_intro_demo/aID_actor_move.s")
