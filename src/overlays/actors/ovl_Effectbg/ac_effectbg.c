#include "ac_effectbg.h"
#include "overlays/gamestates/ovl_play/m_play.h"

void Effectbg_actor_ct(Actor* thisx, Game_Play* game_play);
void Effectbg_actor_dt(Actor* thisx, Game_Play* game_play);
void Effectbg_actor_move(Actor* thisx, Game_Play* game_play);
void Effectbg_actor_draw(Actor* thisx, Game_Play* game_play);

#if 0
ActorProfile Effectbg_Profile = {
    /* */ ACTOR_EFFECTBG,
    /* */ ACTOR_PART_6,
    /* */ ACTOR_FLAG_10 | ACTOR_FLAG_20,
    /* */ 0x0000,
    /* */ GAMEPLAY_KEEP,
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
