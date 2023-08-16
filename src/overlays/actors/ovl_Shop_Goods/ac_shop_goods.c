#include "ac_shop_goods.h"
#include "overlays/gamestates/ovl_play/m_play.h"

void Shop_Goods_Actor_ct(Actor* thisx, PlayState* play);
void Shop_Goods_Actor_dt(Actor* thisx, PlayState* play);
void Shop_Goods_Actor_move(Actor* thisx, PlayState* play);
void Shop_Goods_Actor_draw(Actor* thisx, PlayState* play);

#if 0
ActorProfile Shop_Goods_Profile = {
    /* */ ACTOR_SHOP_GOODS,
    /* */ ACTOR_PART_7,
    /* */ 48,
    /* */ 0x0000,
    /* */ OBJECT_30,
    /* */ sizeof(Shop_Goods),
    /* */ Shop_Goods_Actor_ct,
    /* */ Shop_Goods_Actor_dt,
    /* */ Shop_Goods_Actor_move,
    /* */ Shop_Goods_Actor_draw,
    /* */ NULL,
};
#endif

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Shop_Goods/ac_shop_goods/func_80962A20_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Shop_Goods/ac_shop_goods/func_80962C10_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Shop_Goods/ac_shop_goods/func_80962D58_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Shop_Goods/ac_shop_goods/func_80962E08_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Shop_Goods/ac_shop_goods/func_809630C8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Shop_Goods/ac_shop_goods/func_80963320_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Shop_Goods/ac_shop_goods/func_80963358_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Shop_Goods/ac_shop_goods/func_809633E4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Shop_Goods/ac_shop_goods/Shop_Goods_Actor_ct.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Shop_Goods/ac_shop_goods/Shop_Goods_Actor_dt.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Shop_Goods/ac_shop_goods/Shop_Goods_Actor_move.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Shop_Goods/ac_shop_goods/func_809635A8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Shop_Goods/ac_shop_goods/func_80963760_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Shop_Goods/ac_shop_goods/Shop_Goods_Actor_draw.s")
