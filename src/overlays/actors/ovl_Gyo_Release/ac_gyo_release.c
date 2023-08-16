#include "ac_gyo_release.h"
#include "overlays/gamestates/ovl_play/m_play.h"

void aGYR_actor_ct(Actor* thisx, PlayState* play);
void aGYR_actor_dt(Actor* thisx, PlayState* play);
void aGYR_actor_move(Actor* thisx, PlayState* play);
void aGYR_actor_draw(Actor* thisx, PlayState* play);

#if 0
ActorProfile Gyo_Release_Profile = {
    /* */ ACTOR_GTO_RELEASE,
    /* */ ACTOR_PART_4,
    /* */ ACTOR_FLAG_10 | ACTOR_FLAG_20,
    /* */ 0x0000,
    /* */ GAMEPLAY_KEEP,
    /* */ sizeof(Gyo_Release),
    /* */ aGYR_actor_ct,
    /* */ aGYR_actor_dt,
    /* */ aGYR_actor_move,
    /* */ aGYR_actor_draw,
    /* */ NULL,
};
#endif

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Gyo_Release/ac_gyo_release/func_80A7A680_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Gyo_Release/ac_gyo_release/func_80A7A708_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Gyo_Release/ac_gyo_release/func_80A7A748_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Gyo_Release/ac_gyo_release/func_80A7A7F0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Gyo_Release/ac_gyo_release/func_80A7A82C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Gyo_Release/ac_gyo_release/aGYR_actor_ct.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Gyo_Release/ac_gyo_release/aGYR_actor_dt.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Gyo_Release/ac_gyo_release/func_80A7AB0C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Gyo_Release/ac_gyo_release/func_80A7AB50_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Gyo_Release/ac_gyo_release/func_80A7AB90_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Gyo_Release/ac_gyo_release/func_80A7ACAC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Gyo_Release/ac_gyo_release/func_80A7AD14_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Gyo_Release/ac_gyo_release/aGYR_actor_move.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Gyo_Release/ac_gyo_release/aGYR_actor_draw.s")
