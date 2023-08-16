#include "ac_gyo_kage.h"
#include "overlays/gamestates/ovl_play/m_play.h"

void aGYO_KAGE_actor_ct(Actor* thisx, PlayState* play);
void aGYO_KAGE_actor_dt(Actor* thisx, PlayState* play);
void aGYO_KAGE_actor_move(Actor* thisx, PlayState* play);
void aGYO_KAGE_actor_draw(Actor* thisx, PlayState* play);

#if 0
ActorProfile Gyo_Kage_Profile = {
    /* */ 133,
    /* */ ACTOR_PART_4,
    /* */ 48,
    /* */ 0,
    /* */ 3,
    /* */ sizeof(Gyo_Kage),
    /* */ aGYO_KAGE_actor_ct,
    /* */ aGYO_KAGE_actor_dt,
    /* */ aGYO_KAGE_actor_move,
    /* */ aGYO_KAGE_actor_draw,
    /* */ NULL,
};
#endif

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Gyo_Kage/ac_gyo_kage/func_80A81950_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Gyo_Kage/ac_gyo_kage/func_80A819E0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Gyo_Kage/ac_gyo_kage/func_80A81A6C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Gyo_Kage/ac_gyo_kage/func_80A81AD0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Gyo_Kage/ac_gyo_kage/func_80A81B0C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Gyo_Kage/ac_gyo_kage/func_80A81BF4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Gyo_Kage/ac_gyo_kage/aGYO_KAGE_actor_ct.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Gyo_Kage/ac_gyo_kage/aGYO_KAGE_actor_dt.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Gyo_Kage/ac_gyo_kage/func_80A81F90_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Gyo_Kage/ac_gyo_kage/func_80A81FCC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Gyo_Kage/ac_gyo_kage/func_80A8200C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Gyo_Kage/ac_gyo_kage/aGYO_KAGE_actor_move.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Gyo_Kage/ac_gyo_kage/aGYO_KAGE_actor_draw.s")
