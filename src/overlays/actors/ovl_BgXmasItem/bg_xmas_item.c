#include "bg_xmas_item.h"
#include "m_actor_dlftbls.h"
#include "m_object.h"
#include "overlays/gamestates/ovl_play/m_play.h"

void bXI_actor_ct(Actor* thisx, Game_Play* gamePlay);
void bXI_actor_dt(Actor* thisx, Game_Play* gamePlay);
void bXI_actor_move(Actor* thisx, Game_Play* gamePlay);
void bXI_actor_draw(Actor* thisx, Game_Play* gamePlay);

#if 0
ActorProfile BgXmasItem_Profile = {
    /* */ ACTOR_BG_XMAS_ITEM,
    /* */ ACTOR_PART_0,
    /* */ ACTOR_FLAG_10 | ACTOR_FLAG_20,
    /* */ 0x0000,
    /* */ OBJECT_38,
    /* */ sizeof(BgXmasItem),
    /* */ bXI_actor_ct,
    /* */ bXI_actor_dt,
    /* */ bXI_actor_move,
    /* */ bXI_actor_draw,
    /* */ NULL,
};
#endif

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_BgXmasItem/bg_xmas_item/func_80902120_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_BgXmasItem/bg_xmas_item/func_8090224C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_BgXmasItem/bg_xmas_item/func_80902430_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_BgXmasItem/bg_xmas_item/func_809025B4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_BgXmasItem/bg_xmas_item/func_809025E4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_BgXmasItem/bg_xmas_item/func_80902768_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_BgXmasItem/bg_xmas_item/func_809028A4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_BgXmasItem/bg_xmas_item/func_809028F8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_BgXmasItem/bg_xmas_item/func_809029AC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_BgXmasItem/bg_xmas_item/func_80902D38_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_BgXmasItem/bg_xmas_item/func_80902DA8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_BgXmasItem/bg_xmas_item/func_80902DF0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_BgXmasItem/bg_xmas_item/func_80902F28_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_BgXmasItem/bg_xmas_item/func_80902F70_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_BgXmasItem/bg_xmas_item/func_80902FD8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_BgXmasItem/bg_xmas_item/func_8090321C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_BgXmasItem/bg_xmas_item/func_809032A4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_BgXmasItem/bg_xmas_item/func_809034A0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_BgXmasItem/bg_xmas_item/func_809034E4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_BgXmasItem/bg_xmas_item/func_809035B0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_BgXmasItem/bg_xmas_item/func_80903654_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_BgXmasItem/bg_xmas_item/func_809037EC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_BgXmasItem/bg_xmas_item/func_80903844_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_BgXmasItem/bg_xmas_item/func_809039FC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_BgXmasItem/bg_xmas_item/func_80903A64_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_BgXmasItem/bg_xmas_item/func_80903AC4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_BgXmasItem/bg_xmas_item/func_80903C88_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_BgXmasItem/bg_xmas_item/func_80903E7C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_BgXmasItem/bg_xmas_item/func_80903F5C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_BgXmasItem/bg_xmas_item/func_80903FE0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_BgXmasItem/bg_xmas_item/func_80904220_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_BgXmasItem/bg_xmas_item/func_8090477C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_BgXmasItem/bg_xmas_item/func_809047B8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_BgXmasItem/bg_xmas_item/func_80904974_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_BgXmasItem/bg_xmas_item/func_80904A60_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_BgXmasItem/bg_xmas_item/func_80904BAC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_BgXmasItem/bg_xmas_item/func_80904C54_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_BgXmasItem/bg_xmas_item/func_80904CA4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_BgXmasItem/bg_xmas_item/func_80904F28_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_BgXmasItem/bg_xmas_item/func_80905044_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_BgXmasItem/bg_xmas_item/func_80905250_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_BgXmasItem/bg_xmas_item/func_80905334_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_BgXmasItem/bg_xmas_item/func_809054E0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_BgXmasItem/bg_xmas_item/func_80905614_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_BgXmasItem/bg_xmas_item/func_809057EC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_BgXmasItem/bg_xmas_item/func_80905924_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_BgXmasItem/bg_xmas_item/func_809059E0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_BgXmasItem/bg_xmas_item/func_80905A48_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_BgXmasItem/bg_xmas_item/func_80905BA4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_BgXmasItem/bg_xmas_item/func_80905BC4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_BgXmasItem/bg_xmas_item/func_80905C10_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_BgXmasItem/bg_xmas_item/func_80905C84_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_BgXmasItem/bg_xmas_item/func_80905CE8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_BgXmasItem/bg_xmas_item/func_80905D4C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_BgXmasItem/bg_xmas_item/func_80906168_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_BgXmasItem/bg_xmas_item/func_809061E0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_BgXmasItem/bg_xmas_item/func_80906280_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_BgXmasItem/bg_xmas_item/func_80906358_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_BgXmasItem/bg_xmas_item/func_809064E0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_BgXmasItem/bg_xmas_item/func_809066D4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_BgXmasItem/bg_xmas_item/func_809068C8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_BgXmasItem/bg_xmas_item/func_80906A7C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_BgXmasItem/bg_xmas_item/func_80906B48_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_BgXmasItem/bg_xmas_item/func_80906C30_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_BgXmasItem/bg_xmas_item/func_80906CB8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_BgXmasItem/bg_xmas_item/func_80906F9C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_BgXmasItem/bg_xmas_item/func_80907070_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_BgXmasItem/bg_xmas_item/func_809070B8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_BgXmasItem/bg_xmas_item/func_80907164_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_BgXmasItem/bg_xmas_item/func_80907440_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_BgXmasItem/bg_xmas_item/func_80907588_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_BgXmasItem/bg_xmas_item/func_809078B4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_BgXmasItem/bg_xmas_item/func_80907930_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_BgXmasItem/bg_xmas_item/func_80907AFC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_BgXmasItem/bg_xmas_item/func_80907B8C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_BgXmasItem/bg_xmas_item/func_80907C00_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_BgXmasItem/bg_xmas_item/func_80907F34_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_BgXmasItem/bg_xmas_item/func_80907FF4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_BgXmasItem/bg_xmas_item/func_809081E4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_BgXmasItem/bg_xmas_item/func_80908678_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_BgXmasItem/bg_xmas_item/func_809086F8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_BgXmasItem/bg_xmas_item/func_8090876C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_BgXmasItem/bg_xmas_item/func_809087B8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_BgXmasItem/bg_xmas_item/func_80908814_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_BgXmasItem/bg_xmas_item/func_809088F4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_BgXmasItem/bg_xmas_item/func_809089D4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_BgXmasItem/bg_xmas_item/func_80908A2C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_BgXmasItem/bg_xmas_item/func_80908B10_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_BgXmasItem/bg_xmas_item/func_80908C58_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_BgXmasItem/bg_xmas_item/func_80908CE8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_BgXmasItem/bg_xmas_item/func_80908DC0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_BgXmasItem/bg_xmas_item/func_80908E88_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_BgXmasItem/bg_xmas_item/func_80908F20_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_BgXmasItem/bg_xmas_item/func_80909058_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_BgXmasItem/bg_xmas_item/func_80909194_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_BgXmasItem/bg_xmas_item/func_8090922C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_BgXmasItem/bg_xmas_item/func_809093BC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_BgXmasItem/bg_xmas_item/func_8090955C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_BgXmasItem/bg_xmas_item/func_809095E8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_BgXmasItem/bg_xmas_item/func_80909674_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_BgXmasItem/bg_xmas_item/bXI_actor_ct.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_BgXmasItem/bg_xmas_item/bXI_actor_dt.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_BgXmasItem/bg_xmas_item/func_80909C48_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_BgXmasItem/bg_xmas_item/bXI_actor_move.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_BgXmasItem/bg_xmas_item/bXI_actor_draw.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_BgXmasItem/bg_xmas_item/func_80909E78_jp.s")
