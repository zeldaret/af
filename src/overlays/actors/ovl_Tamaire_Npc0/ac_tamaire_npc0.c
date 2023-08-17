#include "ac_tamaire_npc0.h"
#include "m_lib.h"
#include "overlays/gamestates/ovl_play/m_play.h"

void aTMN0_actor_ct(Actor* thisx, Game_Play* play);
void aTMN0_actor_dt(Actor* thisx, Game_Play* play);
void aTMN0_actor_init(Actor* thisx, Game_Play* play);
void aTMN0_actor_save(Actor* thisx, Game_Play* play);

#if 0
ActorProfile Tamaire_Npc0_Profile = {
    /* */ ACTOR_TAMAIRE_NPC0,
    /* */ ACTOR_PART_NPC,
    /* */ 0,
    /* */ 0xD053,
    /* */ GAMEPLAY_KEEP,
    /* */ sizeof(Tamaire_Npc0),
    /* */ aTMN0_actor_ct,
    /* */ aTMN0_actor_dt,
    /* */ aTMN0_actor_init,
    /* */ (ActorFunc)none_proc1,
    /* */ aTMN0_actor_save,
};
#endif

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Tamaire_Npc0/ac_tamaire_npc0/aTMN0_actor_ct.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Tamaire_Npc0/ac_tamaire_npc0/aTMN0_actor_save.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Tamaire_Npc0/ac_tamaire_npc0/aTMN0_actor_dt.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Tamaire_Npc0/ac_tamaire_npc0/aTMN0_actor_init.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Tamaire_Npc0/ac_tamaire_npc0/func_80A867B4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Tamaire_Npc0/ac_tamaire_npc0/func_80A86850_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Tamaire_Npc0/ac_tamaire_npc0/func_80A8687C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Tamaire_Npc0/ac_tamaire_npc0/func_80A8689C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Tamaire_Npc0/ac_tamaire_npc0/func_80A868F4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Tamaire_Npc0/ac_tamaire_npc0/func_80A86934_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Tamaire_Npc0/ac_tamaire_npc0/func_80A86980_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Tamaire_Npc0/ac_tamaire_npc0/func_80A869C0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Tamaire_Npc0/ac_tamaire_npc0/func_80A86A3C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Tamaire_Npc0/ac_tamaire_npc0/func_80A86AD0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Tamaire_Npc0/ac_tamaire_npc0/func_80A86B24_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Tamaire_Npc0/ac_tamaire_npc0/func_80A86B70_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Tamaire_Npc0/ac_tamaire_npc0/func_80A86C20_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Tamaire_Npc0/ac_tamaire_npc0/func_80A86C84_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Tamaire_Npc0/ac_tamaire_npc0/func_80A86CEC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Tamaire_Npc0/ac_tamaire_npc0/func_80A86D28_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Tamaire_Npc0/ac_tamaire_npc0/func_80A86D60_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Tamaire_Npc0/ac_tamaire_npc0/func_80A86DAC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Tamaire_Npc0/ac_tamaire_npc0/func_80A86DF4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Tamaire_Npc0/ac_tamaire_npc0/func_80A86E80_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Tamaire_Npc0/ac_tamaire_npc0/func_80A86F2C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Tamaire_Npc0/ac_tamaire_npc0/func_80A86F74_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Tamaire_Npc0/ac_tamaire_npc0/func_80A86FB4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Tamaire_Npc0/ac_tamaire_npc0/func_80A87020_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Tamaire_Npc0/ac_tamaire_npc0/func_80A87068_jp.s")
