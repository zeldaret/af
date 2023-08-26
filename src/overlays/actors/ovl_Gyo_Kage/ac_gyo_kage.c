#include "ac_gyo_kage.h"
#include "m_actor_dlftbls.h"
#include "m_object.h"
#include "overlays/gamestates/ovl_play/m_play.h"

void aGYO_KAGE_actor_ct(Actor* thisx, Game_Play* gamePlay);
void aGYO_KAGE_actor_dt(Actor* thisx, Game_Play* gamePlay);
void aGYO_KAGE_actor_move(Actor* thisx, Game_Play* gamePlay);
void aGYO_KAGE_actor_draw(Actor* thisx, Game_Play* gamePlay);

#if 0
ActorProfile Gyo_Kage_Profile = {
    /* */ ACTOR_GYO_KAGE,
    /* */ ACTOR_PART_4,
    /* */ ACTOR_FLAG_10 | ACTOR_FLAG_20,
    /* */ 0x0000,
    /* */ GAMEPLAY_KEEP,
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
