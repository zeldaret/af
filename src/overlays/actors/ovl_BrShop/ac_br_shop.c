#include "ac_br_shop.h"
#include "overlays/gamestates/ovl_play/m_play.h"

void aBRS_actor_ct(Actor* thisx, PlayState* play);
void aBRS_actor_dt(Actor* thisx, PlayState* play);
void aBRS_actor_init(Actor* thisx, PlayState* play);
void aBRS_actor_draw(Actor* thisx, PlayState* play);

#if 0
ActorProfile BrShop_Profile = {
    /* */ 54,
    /* */ ACTOR_PART_0,
    /* */ 0,
    /* */ 22566,
    /* */ 3,
    /* */ sizeof(BrShop),
    /* */ aBRS_actor_ct,
    /* */ aBRS_actor_dt,
    /* */ aBRS_actor_init,
    /* */ aBRS_actor_draw,
    /* */ NULL,
};
#endif

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_BrShop/ac_br_shop/aBRS_actor_ct.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_BrShop/ac_br_shop/aBRS_actor_dt.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_BrShop/ac_br_shop/func_809FEAEC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_BrShop/ac_br_shop/func_809FECD4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_BrShop/ac_br_shop/func_809FEED4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_BrShop/ac_br_shop/func_809FEF90_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_BrShop/ac_br_shop/func_809FF034_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_BrShop/ac_br_shop/func_809FF0B4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_BrShop/ac_br_shop/func_809FF120_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_BrShop/ac_br_shop/func_809FF1C8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_BrShop/ac_br_shop/func_809FF2C8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_BrShop/ac_br_shop/func_809FF2FC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_BrShop/ac_br_shop/func_809FF330_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_BrShop/ac_br_shop/func_809FF3EC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_BrShop/ac_br_shop/aBRS_actor_init.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_BrShop/ac_br_shop/func_809FF59C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_BrShop/ac_br_shop/func_809FF650_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_BrShop/ac_br_shop/aBRS_actor_draw.s")
