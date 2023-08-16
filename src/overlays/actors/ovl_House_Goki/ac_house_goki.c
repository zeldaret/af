#include "ac_house_goki.h"
#include "overlays/gamestates/ovl_play/m_play.h"

void aHG_actor_ct(Actor* thisx, PlayState* play);
void func_80A83770_jp(Actor* thisx, PlayState* play);
void aHG_actor_move(Actor* thisx, PlayState* play);
void aHG_actor_draw(Actor* thisx, PlayState* play);

#if 0
ActorProfile House_Goki_Profile = {
    /* */ ACTOR_HOUSE_GOKI,
    /* */ ACTOR_PART_4,
    /* */ ACTOR_FLAG_10,
    /* */ 0x0000,
    /* */ OBJECT_369,
    /* */ sizeof(House_Goki),
    /* */ aHG_actor_ct,
    /* */ func_80A83770_jp,
    /* */ aHG_actor_move,
    /* */ aHG_actor_draw,
    /* */ NULL,
};
#endif

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_House_Goki/ac_house_goki/aHG_actor_ct.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_House_Goki/ac_house_goki/func_80A83770_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_House_Goki/ac_house_goki/func_80A83780_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_House_Goki/ac_house_goki/func_80A837C4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_House_Goki/ac_house_goki/func_80A83930_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_House_Goki/ac_house_goki/func_80A83994_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_House_Goki/ac_house_goki/func_80A83A00_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_House_Goki/ac_house_goki/func_80A83A24_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_House_Goki/ac_house_goki/func_80A83D4C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_House_Goki/ac_house_goki/func_80A8401C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_House_Goki/ac_house_goki/func_80A8409C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_House_Goki/ac_house_goki/aHG_actor_move.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_House_Goki/ac_house_goki/aHG_actor_draw.s")
