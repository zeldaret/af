#include "ac_shop_umbrella.h"
#include "overlays/gamestates/ovl_play/m_play.h"

void Shop_Umbrella_Actor_ct(Actor* thisx, PlayState* play);
void Shop_Umbrella_Actor_dt(Actor* thisx, PlayState* play);
void Shop_Umbrella_Actor_move(Actor* thisx, PlayState* play);
void Shop_Umbrella_Actor_draw(Actor* thisx, PlayState* play);

#if 0
ActorProfile Shop_Umbrella_Profile = {
    /* */ ACTOR_SHOP_UMBRELLA,
    /* */ ACTOR_PART_4,
    /* */ 48,
    /* */ 0x0000,
    /* */ GAMEPLAY_KEEP,
    /* */ sizeof(Shop_Umbrella),
    /* */ Shop_Umbrella_Actor_ct,
    /* */ Shop_Umbrella_Actor_dt,
    /* */ Shop_Umbrella_Actor_move,
    /* */ Shop_Umbrella_Actor_draw,
    /* */ NULL,
};
#endif

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Shop_Umbrella/ac_shop_umbrella/func_80A79350_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Shop_Umbrella/ac_shop_umbrella/func_80A79450_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Shop_Umbrella/ac_shop_umbrella/func_80A79594_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Shop_Umbrella/ac_shop_umbrella/func_80A79780_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Shop_Umbrella/ac_shop_umbrella/func_80A797BC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Shop_Umbrella/ac_shop_umbrella/func_80A797E8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Shop_Umbrella/ac_shop_umbrella/func_80A79824_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Shop_Umbrella/ac_shop_umbrella/func_80A79A34_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Shop_Umbrella/ac_shop_umbrella/func_80A79A88_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Shop_Umbrella/ac_shop_umbrella/func_80A79B04_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Shop_Umbrella/ac_shop_umbrella/func_80A79BD0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Shop_Umbrella/ac_shop_umbrella/Shop_Umbrella_Actor_ct.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Shop_Umbrella/ac_shop_umbrella/Shop_Umbrella_Actor_dt.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Shop_Umbrella/ac_shop_umbrella/Shop_Umbrella_Actor_draw.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Shop_Umbrella/ac_shop_umbrella/func_80A79F5C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Shop_Umbrella/ac_shop_umbrella/func_80A79F70_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Shop_Umbrella/ac_shop_umbrella/func_80A79FC8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Shop_Umbrella/ac_shop_umbrella/Shop_Umbrella_Actor_move.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Shop_Umbrella/ac_shop_umbrella/func_80A7A068_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Shop_Umbrella/ac_shop_umbrella/func_80A7A148_jp.s")
