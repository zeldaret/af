#include "ac_house.h"
#include "overlays/gamestates/ovl_play/m_play.h"

void aHUS_actor_ct(Actor* thisx, Game_Play* game_play);
void aHUS_actor_dt(Actor* thisx, Game_Play* game_play);
void aHUS_actor_init(Actor* thisx, Game_Play* game_play);
void aHUS_actor_draw(Actor* thisx, Game_Play* game_play);

#if 0
ActorProfile House_Profile = {
    /* */ ACTOR_HOUSE,
    /* */ ACTOR_PART_0,
    /* */ 0,
    /* */ 0x5000,
    /* */ GAMEPLAY_KEEP,
    /* */ sizeof(House),
    /* */ aHUS_actor_ct,
    /* */ aHUS_actor_dt,
    /* */ aHUS_actor_init,
    /* */ aHUS_actor_draw,
    /* */ NULL,
};
#endif

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_House/ac_house/aHUS_actor_ct.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_House/ac_house/aHUS_actor_dt.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_House/ac_house/func_80A039C0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_House/ac_house/func_80A039F0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_House/ac_house/func_80A03BD8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_House/ac_house/func_80A03C64_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_House/ac_house/func_80A03E08_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_House/ac_house/func_80A03EE4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_House/ac_house/func_80A0401C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_House/ac_house/func_80A040B4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_House/ac_house/func_80A041A4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_House/ac_house/func_80A041D8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_House/ac_house/func_80A042A4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_House/ac_house/func_80A044A4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_House/ac_house/func_80A04590_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_House/ac_house/func_80A04654_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_House/ac_house/func_80A046C8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_House/ac_house/func_80A0477C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_House/ac_house/func_80A04798_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_House/ac_house/aHUS_actor_init.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_House/ac_house/func_80A04880_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_House/ac_house/func_80A04908_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_House/ac_house/aHUS_actor_draw.s")
