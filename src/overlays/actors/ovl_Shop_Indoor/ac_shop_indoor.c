#include "ac_shop_indoor.h"
#include "overlays/gamestates/ovl_play/m_play.h"

void Shop_Indoor_Actor_ct(Actor* thisx, PlayState* play);
void Shop_Indoor_Actor_dt(Actor* thisx, PlayState* play);
void Shop_Indoor_Actor_move(Actor* thisx, PlayState* play);
void Shop_Indoor_Actor_draw(Actor* thisx, PlayState* play);

#if 0
ActorProfile Shop_Indoor_Profile = {
    /* */ 51,
    /* */ ACTOR_PART_5,
    /* */ 48,
    /* */ 0,
    /* */ 3,
    /* */ sizeof(Shop_Indoor),
    /* */ Shop_Indoor_Actor_ct,
    /* */ Shop_Indoor_Actor_dt,
    /* */ Shop_Indoor_Actor_move,
    /* */ Shop_Indoor_Actor_draw,
    /* */ NULL,
};
#endif

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Shop_Indoor/ac_shop_indoor/func_8095A3B0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Shop_Indoor/ac_shop_indoor/func_8095A3F8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Shop_Indoor/ac_shop_indoor/func_8095A514_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Shop_Indoor/ac_shop_indoor/func_8095A62C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Shop_Indoor/ac_shop_indoor/func_8095A744_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Shop_Indoor/ac_shop_indoor/func_8095A808_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Shop_Indoor/ac_shop_indoor/func_8095A86C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Shop_Indoor/ac_shop_indoor/Shop_Indoor_Actor_ct.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Shop_Indoor/ac_shop_indoor/Shop_Indoor_Actor_dt.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Shop_Indoor/ac_shop_indoor/func_8095A9D0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Shop_Indoor/ac_shop_indoor/func_8095AD48_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Shop_Indoor/ac_shop_indoor/func_8095AF7C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Shop_Indoor/ac_shop_indoor/func_8095B2B0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Shop_Indoor/ac_shop_indoor/Shop_Indoor_Actor_draw.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Shop_Indoor/ac_shop_indoor/Shop_Indoor_Actor_move.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Shop_Indoor/ac_shop_indoor/func_8095B33C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Shop_Indoor/ac_shop_indoor/func_8095B3C0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Shop_Indoor/ac_shop_indoor/func_8095B444_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Shop_Indoor/ac_shop_indoor/func_8095B4B0_jp.s")
