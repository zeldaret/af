#include "ac_count02.h"
#include "m_actor_dlftbls.h"
#include "m_object.h"
#include "overlays/gamestates/ovl_play/m_play.h"

void func_805ab8b8(Actor* thisx, Game_Play* gamePlay);
void func_805ab988(Actor* thisx, Game_Play* gamePlay);
void func_805abdac(Actor* thisx, Game_Play* gamePlay);
void func_805abe88(Actor* thisx, Game_Play* gamePlay);

#if 0
ActorProfile Count02_Profile = {
    /* */ ACTOR_COUNT02,
    /* */ ACTOR_PART_0,
    /* */ ACTOR_FLAG_10 | ACTOR_FLAG_20,
    /* */ 0x5832,
    /* */ GAMEPLAY_KEEP,
    /* */ sizeof(Count02),
    /* */ func_805ab8b8,
    /* */ func_805ab988,
    /* */ func_805abdac,
    /* */ func_805abe88,
    /* */ NULL,
};
#endif

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Count02/ac_count02/func_805ab8b8.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Count02/ac_count02/func_805ab988.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Count02/ac_count02/func_80A8B3C8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Count02/ac_count02/func_80A8B430_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Count02/ac_count02/func_80A8B5DC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Count02/ac_count02/func_80A8B61C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Count02/ac_count02/func_80A8B754_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Count02/ac_count02/func_80A8B7E8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Count02/ac_count02/func_805abdac.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Count02/ac_count02/func_80A8B938_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Count02/ac_count02/func_805abe88.s")
