#include "ac_gyoei.h"
#include "overlays/gamestates/ovl_play/m_play.h"

void aGYO_actor_ct(Actor* thisx, Game_Play* game_play);
void aGYO_actor_dt(Actor* thisx, Game_Play* game_play);
void aGYO_actor_move(Actor* thisx, Game_Play* game_play);
void aGYO_actor_draw(Actor* thisx, Game_Play* game_play);

#if 0
ActorProfile Gyoei_Profile = {
    /* */ ACTOR_GYOEI,
    /* */ ACTOR_PART_7,
    /* */ ACTOR_FLAG_10 | ACTOR_FLAG_20,
    /* */ 0x0000,
    /* */ GAMEPLAY_KEEP,
    /* */ sizeof(Gyoei),
    /* */ aGYO_actor_ct,
    /* */ aGYO_actor_dt,
    /* */ aGYO_actor_move,
    /* */ aGYO_actor_draw,
    /* */ NULL,
};
#endif

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Gyoei/ac_gyoei/aGYO_actor_ct.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Gyoei/ac_gyoei/aGYO_actor_dt.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Gyoei/ac_gyoei/func_80A5B04C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Gyoei/ac_gyoei/func_80A5B0DC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Gyoei/ac_gyoei/func_80A5B15C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Gyoei/ac_gyoei/func_80A5B180_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Gyoei/ac_gyoei/func_80A5B238_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Gyoei/ac_gyoei/func_80A5B364_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Gyoei/ac_gyoei/func_80A5B3A8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Gyoei/ac_gyoei/func_80A5B440_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Gyoei/ac_gyoei/func_80A5B474_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Gyoei/ac_gyoei/func_80A5B4B4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Gyoei/ac_gyoei/func_80A5B7C8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Gyoei/ac_gyoei/func_80A5B808_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Gyoei/ac_gyoei/func_80A5B844_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Gyoei/ac_gyoei/func_80A5B920_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Gyoei/ac_gyoei/func_80A5BA40_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Gyoei/ac_gyoei/func_80A5BADC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Gyoei/ac_gyoei/func_80A5BB08_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Gyoei/ac_gyoei/func_80A5BB70_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Gyoei/ac_gyoei/func_80A5BBAC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Gyoei/ac_gyoei/func_80A5BC80_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Gyoei/ac_gyoei/aGYO_actor_move.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Gyoei/ac_gyoei/func_80A5BE14_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Gyoei/ac_gyoei/func_80A5BED4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Gyoei/ac_gyoei/func_80A5C234_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Gyoei/ac_gyoei/aGYO_actor_draw.s")
