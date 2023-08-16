#include "ac_boxTrick01.h"
#include "m_lib.h"
#include "overlays/gamestates/ovl_play/m_play.h"

void BoxTrick01_Actor_ct(Actor* thisx, PlayState* play);
void BoxTrick01_Actor_dt(Actor* thisx, PlayState* play);
void BoxTrick01_Actor_move(Actor* thisx, PlayState* play);

#if 0
ActorProfile BoxTrick01_Profile = {
    /* */ ACTOR_BOX_TRICK_01,
    /* */ ACTOR_PART_4,
    /* */ ACTOR_FLAG_10 | ACTOR_FLAG_20,
    /* */ 0x8004,
    /* */ GAMEPLAY_KEEP,
    /* */ sizeof(BoxTrick01),
    /* */ BoxTrick01_Actor_ct,
    /* */ BoxTrick01_Actor_dt,
    /* */ BoxTrick01_Actor_move,
    /* */ (ActorFunc)none_proc1,
    /* */ NULL,
};
#endif

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_BoxTrick01/ac_boxTrick01/func_80973160_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_BoxTrick01/ac_boxTrick01/func_80973280_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_BoxTrick01/ac_boxTrick01/BoxTrick01_Actor_ct.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_BoxTrick01/ac_boxTrick01/BoxTrick01_Actor_dt.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_BoxTrick01/ac_boxTrick01/BoxTrick01_Actor_move.s")
