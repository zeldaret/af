#include "bg_winter_item.h"
#include "m_actor_dlftbls.h"
#include "m_object.h"
#include "overlays/gamestates/ovl_play/m_play.h"

void bWI_actor_ct(Actor* thisx, Game_Play* game_play);
void bWI_actor_dt(Actor* thisx, Game_Play* game_play);
void bWI_actor_move(Actor* thisx, Game_Play* game_play);
void bWI_actor_draw(Actor* thisx, Game_Play* game_play);

#if 0
ActorProfile BgWinterItem_Profile = {
    /* */ ACTOR_BG_WINTER_ITEM,
    /* */ ACTOR_PART_0,
    /* */ ACTOR_FLAG_10 | ACTOR_FLAG_20,
    /* */ 0x0000,
    /* */ OBJECT_37,
    /* */ sizeof(BgWinterItem),
    /* */ bWI_actor_ct,
    /* */ bWI_actor_dt,
    /* */ bWI_actor_move,
    /* */ bWI_actor_draw,
    /* */ NULL,
};
#endif

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_BgWinterItem/bg_winter_item/func_808F7130_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_BgWinterItem/bg_winter_item/func_808F725C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_BgWinterItem/bg_winter_item/func_808F7440_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_BgWinterItem/bg_winter_item/func_808F75C4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_BgWinterItem/bg_winter_item/func_808F75F4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_BgWinterItem/bg_winter_item/func_808F7778_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_BgWinterItem/bg_winter_item/func_808F78B4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_BgWinterItem/bg_winter_item/func_808F7908_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_BgWinterItem/bg_winter_item/func_808F79BC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_BgWinterItem/bg_winter_item/func_808F7D48_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_BgWinterItem/bg_winter_item/func_808F7DB8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_BgWinterItem/bg_winter_item/func_808F7E00_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_BgWinterItem/bg_winter_item/func_808F7F38_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_BgWinterItem/bg_winter_item/func_808F7F80_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_BgWinterItem/bg_winter_item/func_808F7FE8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_BgWinterItem/bg_winter_item/func_808F822C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_BgWinterItem/bg_winter_item/func_808F82B4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_BgWinterItem/bg_winter_item/func_808F84B0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_BgWinterItem/bg_winter_item/func_808F84F4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_BgWinterItem/bg_winter_item/func_808F85C0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_BgWinterItem/bg_winter_item/func_808F8664_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_BgWinterItem/bg_winter_item/func_808F87FC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_BgWinterItem/bg_winter_item/func_808F8854_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_BgWinterItem/bg_winter_item/func_808F8A0C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_BgWinterItem/bg_winter_item/func_808F8A74_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_BgWinterItem/bg_winter_item/func_808F8AD4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_BgWinterItem/bg_winter_item/func_808F8C98_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_BgWinterItem/bg_winter_item/func_808F8E8C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_BgWinterItem/bg_winter_item/func_808F8F6C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_BgWinterItem/bg_winter_item/func_808F8FF0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_BgWinterItem/bg_winter_item/func_808F9230_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_BgWinterItem/bg_winter_item/func_808F978C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_BgWinterItem/bg_winter_item/func_808F97C8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_BgWinterItem/bg_winter_item/func_808F9984_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_BgWinterItem/bg_winter_item/func_808F9A70_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_BgWinterItem/bg_winter_item/func_808F9BBC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_BgWinterItem/bg_winter_item/func_808F9C64_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_BgWinterItem/bg_winter_item/func_808F9CB4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_BgWinterItem/bg_winter_item/func_808F9F38_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_BgWinterItem/bg_winter_item/func_808FA054_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_BgWinterItem/bg_winter_item/func_808FA260_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_BgWinterItem/bg_winter_item/func_808FA344_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_BgWinterItem/bg_winter_item/func_808FA4F0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_BgWinterItem/bg_winter_item/func_808FA624_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_BgWinterItem/bg_winter_item/func_808FA7FC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_BgWinterItem/bg_winter_item/func_808FA934_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_BgWinterItem/bg_winter_item/func_808FA9F0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_BgWinterItem/bg_winter_item/func_808FAA58_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_BgWinterItem/bg_winter_item/func_808FABB4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_BgWinterItem/bg_winter_item/func_808FABD4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_BgWinterItem/bg_winter_item/func_808FAC20_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_BgWinterItem/bg_winter_item/func_808FAC94_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_BgWinterItem/bg_winter_item/func_808FACF8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_BgWinterItem/bg_winter_item/func_808FAD5C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_BgWinterItem/bg_winter_item/func_808FB178_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_BgWinterItem/bg_winter_item/func_808FB1F0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_BgWinterItem/bg_winter_item/func_808FB290_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_BgWinterItem/bg_winter_item/func_808FB368_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_BgWinterItem/bg_winter_item/func_808FB4F0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_BgWinterItem/bg_winter_item/func_808FB6E4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_BgWinterItem/bg_winter_item/func_808FB8D8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_BgWinterItem/bg_winter_item/func_808FBA8C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_BgWinterItem/bg_winter_item/func_808FBB58_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_BgWinterItem/bg_winter_item/func_808FBC40_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_BgWinterItem/bg_winter_item/func_808FBCC8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_BgWinterItem/bg_winter_item/func_808FBFAC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_BgWinterItem/bg_winter_item/func_808FC080_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_BgWinterItem/bg_winter_item/func_808FC0C8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_BgWinterItem/bg_winter_item/func_808FC174_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_BgWinterItem/bg_winter_item/func_808FC450_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_BgWinterItem/bg_winter_item/func_808FC598_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_BgWinterItem/bg_winter_item/func_808FC8C4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_BgWinterItem/bg_winter_item/func_808FC940_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_BgWinterItem/bg_winter_item/func_808FCB0C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_BgWinterItem/bg_winter_item/func_808FCB9C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_BgWinterItem/bg_winter_item/func_808FCC10_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_BgWinterItem/bg_winter_item/func_808FCF44_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_BgWinterItem/bg_winter_item/func_808FD024_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_BgWinterItem/bg_winter_item/func_808FD214_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_BgWinterItem/bg_winter_item/func_808FD6A8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_BgWinterItem/bg_winter_item/func_808FD728_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_BgWinterItem/bg_winter_item/func_808FD79C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_BgWinterItem/bg_winter_item/func_808FD7E8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_BgWinterItem/bg_winter_item/func_808FD844_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_BgWinterItem/bg_winter_item/func_808FD924_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_BgWinterItem/bg_winter_item/func_808FDA04_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_BgWinterItem/bg_winter_item/func_808FDA5C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_BgWinterItem/bg_winter_item/func_808FDB40_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_BgWinterItem/bg_winter_item/func_808FDC88_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_BgWinterItem/bg_winter_item/func_808FDD18_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_BgWinterItem/bg_winter_item/func_808FDDF0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_BgWinterItem/bg_winter_item/func_808FDEB8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_BgWinterItem/bg_winter_item/func_808FDF50_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_BgWinterItem/bg_winter_item/func_808FE088_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_BgWinterItem/bg_winter_item/func_808FE1C4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_BgWinterItem/bg_winter_item/func_808FE25C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_BgWinterItem/bg_winter_item/func_808FE3EC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_BgWinterItem/bg_winter_item/func_808FE58C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_BgWinterItem/bg_winter_item/func_808FE618_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_BgWinterItem/bg_winter_item/func_808FE6A4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_BgWinterItem/bg_winter_item/bWI_actor_ct.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_BgWinterItem/bg_winter_item/bWI_actor_dt.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_BgWinterItem/bg_winter_item/func_808FEBCC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_BgWinterItem/bg_winter_item/bWI_actor_move.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_BgWinterItem/bg_winter_item/bWI_actor_draw.s")
