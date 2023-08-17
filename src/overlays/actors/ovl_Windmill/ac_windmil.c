#include "ac_windmil.h"
#include "overlays/gamestates/ovl_play/m_play.h"

void func_80A9C3C0_jp(Actor* thisx, PlayState* play);
void aWIN_actor_dt(Actor* thisx, PlayState* play);
void aWIN_actor_init(Actor* thisx, PlayState* play);
void aWIN_actor_draw(Actor* thisx, PlayState* play);

#if 0
ActorProfile Windmill_Profile = {
    /* */ ACTOR_WINDMILL,
    /* */ ACTOR_PART_0,
    /* */ 0,
    /* */ 0x583B,
    /* */ GAMEPLAY_KEEP,
    /* */ sizeof(Windmill),
    /* */ func_80A9C3C0_jp,
    /* */ aWIN_actor_dt,
    /* */ aWIN_actor_init,
    /* */ aWIN_actor_draw,
    /* */ NULL,
};
#endif

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Windmill/ac_windmil/func_80A9C3C0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Windmill/ac_windmil/aWIN_actor_dt.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Windmill/ac_windmil/func_80A9C554_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Windmill/ac_windmil/func_80A9C754_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Windmill/ac_windmil/func_80A9C77C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Windmill/ac_windmil/func_80A9C81C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Windmill/ac_windmil/aWIN_actor_init.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Windmill/ac_windmil/func_80A9C8FC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Windmill/ac_windmil/aWIN_actor_draw.s")
