#include "ac_shop.h"
#include "overlays/gamestates/ovl_play/m_play.h"

void aSHOP_actor_ct(Actor* thisx, PlayState* play);
void aSHOP_actor_dt(Actor* thisx, PlayState* play);
void aSHOP_actor_init(Actor* thisx, PlayState* play);
void aSHOP_actor_draw(Actor* thisx, PlayState* play);

#if 0
ActorProfile Shop_Profile = {
    /* */ 42,
    /* */ ACTOR_PART_0,
    /* */ 0,
    /* */ 22532,
    /* */ 3,
    /* */ sizeof(Shop),
    /* */ aSHOP_actor_ct,
    /* */ aSHOP_actor_dt,
    /* */ aSHOP_actor_init,
    /* */ aSHOP_actor_draw,
    /* */ NULL,
};
#endif

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Shop/ac_shop/aSHOP_actor_ct.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Shop/ac_shop/aSHOP_actor_dt.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Shop/ac_shop/func_80A0DD54_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Shop/ac_shop/func_80A0DED4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Shop/ac_shop/func_80A0DFD0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Shop/ac_shop/func_80A0E02C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Shop/ac_shop/func_80A0E0DC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Shop/ac_shop/func_80A0E1F0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Shop/ac_shop/func_80A0E2B4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Shop/ac_shop/func_80A0E334_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Shop/ac_shop/func_80A0E440_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Shop/ac_shop/func_80A0E474_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Shop/ac_shop/func_80A0E4A8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Shop/ac_shop/func_80A0E564_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Shop/ac_shop/aSHOP_actor_init.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Shop/ac_shop/func_80A0E654_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Shop/ac_shop/func_80A0E6E8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Shop/ac_shop/aSHOP_actor_draw.s")
