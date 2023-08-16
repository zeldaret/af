#include "ac_shop_design.h"
#include "overlays/gamestates/ovl_play/m_play.h"

void Shop_Design_Actor_ct(Actor* thisx, PlayState* play);
void Shop_Design_Actor_dt(Actor* thisx, PlayState* play);
void Shop_Design_Actor_move(Actor* thisx, PlayState* play);
void Shop_Design_Actor_draw(Actor* thisx, PlayState* play);

#if 0
ActorProfile Shop_Design_Profile = {
    /* */ 37,
    /* */ ACTOR_PART_7,
    /* */ 48,
    /* */ 0,
    /* */ 3,
    /* */ sizeof(Shop_Design),
    /* */ Shop_Design_Actor_ct,
    /* */ Shop_Design_Actor_dt,
    /* */ Shop_Design_Actor_move,
    /* */ Shop_Design_Actor_draw,
    /* */ NULL,
};
#endif

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Shop_Design/ac_shop_design/func_80953E20_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Shop_Design/ac_shop_design/func_80953FF4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Shop_Design/ac_shop_design/func_809540C8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Shop_Design/ac_shop_design/func_809541CC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Shop_Design/ac_shop_design/func_809542D0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Shop_Design/ac_shop_design/func_80954314_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Shop_Design/ac_shop_design/func_80954384_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Shop_Design/ac_shop_design/func_809543B4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Shop_Design/ac_shop_design/func_80954400_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Shop_Design/ac_shop_design/func_80954440_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Shop_Design/ac_shop_design/func_80954514_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Shop_Design/ac_shop_design/Shop_Design_Actor_ct.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Shop_Design/ac_shop_design/Shop_Design_Actor_dt.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Shop_Design/ac_shop_design/Shop_Design_Actor_draw.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Shop_Design/ac_shop_design/Shop_Design_Actor_move.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Shop_Design/ac_shop_design/func_809547E4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Shop_Design/ac_shop_design/func_80954970_jp.s")