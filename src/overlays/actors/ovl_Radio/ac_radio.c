#include "ac_radio.h"
#include "overlays/gamestates/ovl_play/m_play.h"

void aRAD_actor_ct(Actor* thisx, PlayState* play);
void func_80A76958_jp(Actor* thisx, PlayState* play);
void aRAD_actor_init(Actor* thisx, PlayState* play);
void aRAD_actor_draw(Actor* thisx, PlayState* play);

#if 0
ActorProfile Radio_Profile = {
    /* */ 125,
    /* */ ACTOR_PART_0,
    /* */ 0,
    /* */ 22571,
    /* */ 3,
    /* */ sizeof(Radio),
    /* */ aRAD_actor_ct,
    /* */ func_80A76958_jp,
    /* */ aRAD_actor_init,
    /* */ aRAD_actor_draw,
    /* */ NULL,
};
#endif

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Radio/ac_radio/aRAD_actor_ct.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Radio/ac_radio/func_80A76958_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Radio/ac_radio/func_80A769E4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Radio/ac_radio/func_80A76A30_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Radio/ac_radio/func_80A76B2C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Radio/ac_radio/func_80A76B4C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Radio/ac_radio/aRAD_actor_init.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Radio/ac_radio/aRAD_actor_draw.s")
