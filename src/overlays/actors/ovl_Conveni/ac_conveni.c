#include "ac_conveni.h"
#include "overlays/gamestates/ovl_play/m_play.h"

void aCNV_actor_ct(Actor* thisx, PlayState* play);
void aCNV_actor_dt(Actor* thisx, PlayState* play);
void aCNV_actor_init(Actor* thisx, PlayState* play);
void aCNV_actor_draw(Actor* thisx, PlayState* play);

#if 0
ActorProfile Conveni_Profile = {
    /* */ 95,
    /* */ ACTOR_PART_0,
    /* */ 0,
    /* */ 22533,
    /* */ 3,
    /* */ sizeof(Conveni),
    /* */ aCNV_actor_ct,
    /* */ aCNV_actor_dt,
    /* */ aCNV_actor_init,
    /* */ aCNV_actor_draw,
    /* */ NULL,
};
#endif

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Conveni/ac_conveni/aCNV_actor_ct.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Conveni/ac_conveni/aCNV_actor_dt.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Conveni/ac_conveni/func_80A010E0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Conveni/ac_conveni/func_80A01110_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Conveni/ac_conveni/func_80A01214_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Conveni/ac_conveni/func_80A01270_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Conveni/ac_conveni/func_80A0134C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Conveni/ac_conveni/func_80A01460_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Conveni/ac_conveni/func_80A014A0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Conveni/ac_conveni/func_80A015AC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Conveni/ac_conveni/func_80A01648_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Conveni/ac_conveni/func_80A0178C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Conveni/ac_conveni/func_80A017C0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Conveni/ac_conveni/func_80A017F4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Conveni/ac_conveni/func_80A018FC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Conveni/ac_conveni/aCNV_actor_init.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Conveni/ac_conveni/func_80A019EC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Conveni/ac_conveni/func_80A01A80_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Conveni/ac_conveni/aCNV_actor_draw.s")
