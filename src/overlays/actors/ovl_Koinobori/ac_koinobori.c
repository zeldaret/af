#include "ac_koinobori.h"
#include "overlays/gamestates/ovl_play/m_play.h"

void aKOI_actor_ct(Actor* thisx, PlayState* play);
void aKOI_actor_dt(Actor* thisx, PlayState* play);
void aKOI_actor_init(Actor* thisx, PlayState* play);
void aKOI_actor_draw(Actor* thisx, PlayState* play);

#if 0
ActorProfile Koinobori_Profile = {
    /* */ 163,
    /* */ ACTOR_PART_0,
    /* */ 0,
    /* */ 22585,
    /* */ 3,
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
