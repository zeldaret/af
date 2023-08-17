#include "ac_shop_level.h"
#include "overlays/gamestates/ovl_play/m_play.h"

void Shop_Level_Actor_ct(Actor* thisx, PlayState* play);
void Shop_Level_Actor_dt(Actor* thisx, PlayState* play);
void Shop_Level_Actor_move(Actor* thisx, PlayState* play);
void Shop_Level_Actor_draw(Actor* thisx, PlayState* play);

#if 0
ActorProfile Shop_Level_Profile = {
    /* */ ACTOR_SHOP_LEVEL,
    /* */ ACTOR_PART_7,
    /* */ ACTOR_FLAG_10 | ACTOR_FLAG_20 | ACTOR_FLAG_20000000,
    /* */ 0x0000,
    /* */ GAMEPLAY_KEEP,
    /* */ sizeof(Shop_Level),
    /* */ Shop_Level_Actor_ct,
    /* */ Shop_Level_Actor_dt,
    /* */ Shop_Level_Actor_move,
    /* */ Shop_Level_Actor_draw,
    /* */ NULL,
};
#endif

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Shop_Level/ac_shop_level/func_809583B0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Shop_Level/ac_shop_level/func_809585F4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Shop_Level/ac_shop_level/func_809586FC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Shop_Level/ac_shop_level/func_80958824_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Shop_Level/ac_shop_level/func_809588D4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Shop_Level/ac_shop_level/Shop_Level_Actor_ct.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Shop_Level/ac_shop_level/Shop_Level_Actor_dt.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Shop_Level/ac_shop_level/Shop_Level_Actor_draw.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Shop_Level/ac_shop_level/func_80958B38_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Shop_Level/ac_shop_level/func_80958EA4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Shop_Level/ac_shop_level/func_80958F70_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Shop_Level/ac_shop_level/Shop_Level_Actor_move.s")
