#include "ac_effectbg.h"
#include "overlays/gamestates/ovl_play/m_play.h"

void Effectbg_actor_ct(Actor* thisx, PlayState* play);
void Effectbg_actor_dt(Actor* thisx, PlayState* play);
void Effectbg_actor_move(Actor* thisx, PlayState* play);
void Effectbg_actor_draw(Actor* thisx, PlayState* play);

#if 0
ActorProfile Effectbg_Profile = {
    /* */ 119,
    /* */ ACTOR_PART_6,
    /* */ 48,
    /* */ 0,
    /* */ 3,
    /* */ sizeof(Effectbg),
    /* */ Effectbg_actor_ct,
    /* */ Effectbg_actor_dt,
    /* */ Effectbg_actor_move,
    /* */ Effectbg_actor_draw,
    /* */ NULL,
};
#endif

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Effectbg/ac_effectbg/func_80A1CBD0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Effectbg/ac_effectbg/Effectbg_actor_ct.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Effectbg/ac_effectbg/Effectbg_actor_dt.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Effectbg/ac_effectbg/func_80A1CDE4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Effectbg/ac_effectbg/func_80A1D1A0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Effectbg/ac_effectbg/func_80A1D47C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Effectbg/ac_effectbg/func_80A1D760_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Effectbg/ac_effectbg/func_80A1D770_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Effectbg/ac_effectbg/Effectbg_actor_move.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Effectbg/ac_effectbg/func_80A1DC64_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Effectbg/ac_effectbg/func_80A1DE88_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Effectbg/ac_effectbg/func_80A1E2A4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Effectbg/ac_effectbg/func_80A1E324_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Effectbg/ac_effectbg/Effectbg_actor_draw.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Effectbg/ac_effectbg/func_80A1E71C_jp.s")
