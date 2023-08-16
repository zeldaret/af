#include "ac_house_clock.h"
#include "overlays/gamestates/ovl_play/m_play.h"

void House_Clock_Actor_ct(Actor* thisx, PlayState* play);
void House_Clock_Actor_dt(Actor* thisx, PlayState* play);
void House_Clock_Actor_move(Actor* thisx, PlayState* play);
void House_Clock_Actor_draw(Actor* thisx, PlayState* play);

#if 0
ActorProfile House_Clock_Profile = {
    /* */ 159,
    /* */ ACTOR_PART_5,
    /* */ 48,
    /* */ 0,
    /* */ 3,
    /* */ sizeof(House_Clock),
    /* */ House_Clock_Actor_ct,
    /* */ House_Clock_Actor_dt,
    /* */ House_Clock_Actor_move,
    /* */ House_Clock_Actor_draw,
    /* */ NULL,
};
#endif

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_House_Clock/ac_house_clock/func_80A90B70_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_House_Clock/ac_house_clock/func_80A90B80_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_House_Clock/ac_house_clock/func_80A90B90_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_House_Clock/ac_house_clock/func_80A90CAC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_House_Clock/ac_house_clock/func_80A90CE0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_House_Clock/ac_house_clock/func_80A90D14_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_House_Clock/ac_house_clock/func_80A90D4C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_House_Clock/ac_house_clock/func_80A90DCC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_House_Clock/ac_house_clock/House_Clock_Actor_ct.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_House_Clock/ac_house_clock/House_Clock_Actor_dt.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_House_Clock/ac_house_clock/func_80A90F80_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_House_Clock/ac_house_clock/func_80A9101C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_House_Clock/ac_house_clock/func_80A9106C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_House_Clock/ac_house_clock/func_80A912A8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_House_Clock/ac_house_clock/House_Clock_Actor_draw.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_House_Clock/ac_house_clock/func_80A9140C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_House_Clock/ac_house_clock/House_Clock_Actor_move.s")
