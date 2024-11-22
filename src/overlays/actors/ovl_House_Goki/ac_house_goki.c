#include "ac_house_goki.h"
#include "m_actor_dlftbls.h"
#include "m_object.h"
#include "overlays/gamestates/ovl_play/m_play.h"

void aHG_actor_ct(Actor* thisx, Game_Play* game_play);
void func_80A83770_jp(Actor* thisx, Game_Play* game_play);
void aHG_actor_move(Actor* thisx, Game_Play* game_play);
void aHG_actor_draw(Actor* thisx, Game_Play* game_play);

void func_80A83930_jp(House_Goki* this, Game_Play* game_play);
void func_80A83994_jp(House_Goki* this, Game_Play* game_play);
void func_80A83A00_jp(House_Goki* this, Game_Play* game_play);

void func_80A83A24_jp(House_Goki* this, Game_Play* game_play);
void func_80A83D4C_jp(House_Goki* this, Game_Play* game_play);
void func_80A8401C_jp(House_Goki* this, Game_Play* game_play);

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

static House_GokiActionFunc init_process[] = { func_80A83930_jp, func_80A83994_jp, func_80A83A00_jp };
static House_GokiActionFunc process[] = { func_80A83A24_jp, func_80A83D4C_jp, func_80A8401C_jp };
static s32 D_80A845DC_jp[] = { 0x060000C0, 0x06000188 };

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
