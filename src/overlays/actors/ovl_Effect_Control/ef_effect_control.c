#include "ef_effect_control.h"
#include "overlays/gamestates/ovl_play/m_play.h"

void eEC_actor_ct(Actor* thisx, PlayState* play);
void eEC_actor_dt(Actor* thisx, PlayState* play);
void eEC_actor_move(Actor* thisx, PlayState* play);
void eEC_actor_draw(Actor* thisx, PlayState* play);

#if 0
ActorProfile Effect_Control_Profile = {
    /* */ 33,
    /* */ ACTOR_PART_7,
    /* */ 536870960,
    /* */ 0,
    /* */ 3,
    /* */ sizeof(Effect_Control),
    /* */ eEC_actor_ct,
    /* */ eEC_actor_dt,
    /* */ eEC_actor_move,
    /* */ eEC_actor_draw,
    /* */ NULL,
};
#endif

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Effect_Control/ef_effect_control/func_80A17190_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Effect_Control/ef_effect_control/func_80A171E4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Effect_Control/ef_effect_control/func_80A17278_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Effect_Control/ef_effect_control/func_80A173C4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Effect_Control/ef_effect_control/func_80A17430_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Effect_Control/ef_effect_control/func_80A174BC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Effect_Control/ef_effect_control/func_80A175C4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Effect_Control/ef_effect_control/func_80A17710_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Effect_Control/ef_effect_control/func_80A177C8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Effect_Control/ef_effect_control/func_80A1786C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Effect_Control/ef_effect_control/func_80A178AC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Effect_Control/ef_effect_control/func_80A178FC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Effect_Control/ef_effect_control/func_80A17C14_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Effect_Control/ef_effect_control/func_80A17C84_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Effect_Control/ef_effect_control/func_80A17DF0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Effect_Control/ef_effect_control/func_80A17EAC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Effect_Control/ef_effect_control/func_80A1802C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Effect_Control/ef_effect_control/func_80A18170_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Effect_Control/ef_effect_control/func_80A181B8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Effect_Control/ef_effect_control/func_80A18344_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Effect_Control/ef_effect_control/func_80A18490_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Effect_Control/ef_effect_control/func_80A18594_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Effect_Control/ef_effect_control/func_80A186AC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Effect_Control/ef_effect_control/func_80A18794_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Effect_Control/ef_effect_control/func_80A187F8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Effect_Control/ef_effect_control/func_80A188E4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Effect_Control/ef_effect_control/func_80A18940_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Effect_Control/ef_effect_control/eEC_actor_ct.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Effect_Control/ef_effect_control/func_80A189F0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Effect_Control/ef_effect_control/eEC_actor_dt.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Effect_Control/ef_effect_control/func_80A18A8C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Effect_Control/ef_effect_control/eEC_actor_draw.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Effect_Control/ef_effect_control/func_80A18D50_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Effect_Control/ef_effect_control/func_80A18E68_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Effect_Control/ef_effect_control/eEC_actor_move.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Effect_Control/ef_effect_control/func_80A1902C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Effect_Control/ef_effect_control/func_80A1906C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Effect_Control/ef_effect_control/func_80A19170_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Effect_Control/ef_effect_control/RO_80A1A880_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Effect_Control/ef_effect_control/func_80A191F0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Effect_Control/ef_effect_control/func_80A19254_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Effect_Control/ef_effect_control/func_80A19304_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Effect_Control/ef_effect_control/func_80A1950C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Effect_Control/ef_effect_control/func_80A19770_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Effect_Control/ef_effect_control/func_80A198D4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Effect_Control/ef_effect_control/func_80A19940_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Effect_Control/ef_effect_control/func_80A19ADC_jp.s")
