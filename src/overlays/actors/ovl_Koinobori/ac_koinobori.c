#include "ac_koinobori.h"
#include "overlays/gamestates/ovl_play/m_play.h"

void aKOI_actor_ct(Actor* thisx, Game_Play* game_play);
void aKOI_actor_dt(Actor* thisx, Game_Play* game_play);
void aKOI_actor_init(Actor* thisx, Game_Play* game_play);
void aKOI_actor_draw(Actor* thisx, Game_Play* game_play);

#if 0
ActorProfile Koinobori_Profile = {
    /* */ ACTOR_KOINOBORI,
    /* */ ACTOR_PART_0,
    /* */ 0,
    /* */ 0x5839,
    /* */ GAMEPLAY_KEEP,
    /* */ sizeof(Koinobori),
    /* */ aKOI_actor_ct,
    /* */ aKOI_actor_dt,
    /* */ aKOI_actor_init,
    /* */ aKOI_actor_draw,
    /* */ NULL,
};
#endif

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Koinobori/ac_koinobori/aKOI_actor_ct.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Koinobori/ac_koinobori/aKOI_actor_dt.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Koinobori/ac_koinobori/func_80A9369C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Koinobori/ac_koinobori/func_80A936AC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Koinobori/ac_koinobori/func_80A936BC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Koinobori/ac_koinobori/func_80A9373C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Koinobori/ac_koinobori/aKOI_actor_init.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Koinobori/ac_koinobori/aKOI_actor_draw.s")
