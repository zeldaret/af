#include "ac_kamakura.h"
#include "overlays/gamestates/ovl_play/m_play.h"

void aKKR_actor_ct(Actor* thisx, PlayState* play);
void aKKR_actor_dt(Actor* thisx, PlayState* play);
void aKKR_actor_init(Actor* thisx, PlayState* play);
void aKKR_actor_draw(Actor* thisx, PlayState* play);

#if 0
ActorProfile Kamakura_Profile = {
    /* */ 106,
    /* */ ACTOR_PART_0,
    /* */ 0,
    /* */ 22569,
    /* */ 3,
    /* */ sizeof(Kamakura),
    /* */ aKKR_actor_ct,
    /* */ aKKR_actor_dt,
    /* */ aKKR_actor_init,
    /* */ aKKR_actor_draw,
    /* */ NULL,
};
#endif

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Kamakura/ac_kamakura/aKKR_actor_ct.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Kamakura/ac_kamakura/aKKR_actor_dt.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Kamakura/ac_kamakura/func_80A0510C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Kamakura/ac_kamakura/func_80A052F4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Kamakura/ac_kamakura/func_80A054F4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Kamakura/ac_kamakura/func_80A055EC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Kamakura/ac_kamakura/func_80A05690_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Kamakura/ac_kamakura/func_80A05760_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Kamakura/ac_kamakura/func_80A05780_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Kamakura/ac_kamakura/aKKR_actor_init.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Kamakura/ac_kamakura/aKKR_actor_draw.s")
