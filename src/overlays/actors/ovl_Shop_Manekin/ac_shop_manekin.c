#include "ac_shop_manekin.h"
#include "m_actor_dlftbls.h"
#include "m_object.h"
#include "overlays/gamestates/ovl_play/m_play.h"

void Shop_Manekin_Actor_ct(Actor* thisx, Game_Play* gamePlay);
void Shop_Manekin_Actor_dt(Actor* thisx, Game_Play* gamePlay);
void Shop_Manekin_Actor_move(Actor* thisx, Game_Play* gamePlay);
void Shop_Manekin_Actor_draw(Actor* thisx, Game_Play* gamePlay);

#if 0
ActorProfile Shop_Manekin_Profile = {
    /* */ ACTOR_SHOP_MANEKIN,
    /* */ ACTOR_PART_7,
    /* */ ACTOR_FLAG_10 | ACTOR_FLAG_20,
    /* */ 0x0000,
    /* */ GAMEPLAY_KEEP,
    /* */ sizeof(Shop_Manekin),
    /* */ Shop_Manekin_Actor_ct,
    /* */ Shop_Manekin_Actor_dt,
    /* */ Shop_Manekin_Actor_move,
    /* */ Shop_Manekin_Actor_draw,
    /* */ NULL,
};
#endif

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Shop_Manekin/ac_shop_manekin/func_809592B0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Shop_Manekin/ac_shop_manekin/func_809593D4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Shop_Manekin/ac_shop_manekin/func_80959434_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Shop_Manekin/ac_shop_manekin/func_80959674_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Shop_Manekin/ac_shop_manekin/func_809597B4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Shop_Manekin/ac_shop_manekin/func_809599B0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Shop_Manekin/ac_shop_manekin/func_80959A04_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Shop_Manekin/ac_shop_manekin/func_80959A80_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Shop_Manekin/ac_shop_manekin/func_80959B64_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Shop_Manekin/ac_shop_manekin/Shop_Manekin_Actor_ct.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Shop_Manekin/ac_shop_manekin/Shop_Manekin_Actor_dt.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Shop_Manekin/ac_shop_manekin/Shop_Manekin_Actor_draw.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Shop_Manekin/ac_shop_manekin/Shop_Manekin_Actor_move.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Shop_Manekin/ac_shop_manekin/func_80959F34_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Shop_Manekin/ac_shop_manekin/func_8095A024_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Shop_Manekin/ac_shop_manekin/func_8095A158_jp.s")
