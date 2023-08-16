#include "ac_nameplate.h"
#include "overlays/gamestates/ovl_play/m_play.h"

void func_80A963C0_jp(Actor* thisx, PlayState* play);
void func_80A963D0_jp(Actor* thisx, PlayState* play);
void aNP_actor_init(Actor* thisx, PlayState* play);

#if 0
ActorProfile Nameplate_Profile = {
    /* */ 165,
    /* */ ACTOR_PART_0,
    /* */ 0,
    /* */ 40978,
    /* */ 3,
    /* */ sizeof(Nameplate),
    /* */ func_80A963C0_jp,
    /* */ func_80A963D0_jp,
    /* */ aNP_actor_init,
    /* */ NULL,
    /* */ NULL,
};
#endif

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Nameplate/ac_nameplate/func_80A963C0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Nameplate/ac_nameplate/func_80A963D0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Nameplate/ac_nameplate/func_80A963E0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Nameplate/ac_nameplate/func_80A9648C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Nameplate/ac_nameplate/aNP_actor_init.s")
