#include "ac_reserve.h"
#include "overlays/gamestates/ovl_play/m_play.h"

void aRSV_actor_ct(Actor* thisx, PlayState* play);
void func_80A09370_jp(Actor* thisx, PlayState* play);
void aRSV_actor_init(Actor* thisx, PlayState* play);
void aRSV_actor_draw(Actor* thisx, PlayState* play);

#if 0
ActorProfile Reserve_Profile = {
    /* */ 63,
    /* */ ACTOR_PART_0,
    /* */ 0,
    /* */ 22544,
    /* */ 3,
    /* */ sizeof(Reserve),
    /* */ aRSV_actor_ct,
    /* */ func_80A09370_jp,
    /* */ aRSV_actor_init,
    /* */ aRSV_actor_draw,
    /* */ NULL,
};
#endif

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Reserve/ac_reserve/aRSV_actor_ct.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Reserve/ac_reserve/func_80A09370_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Reserve/ac_reserve/func_80A093FC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Reserve/ac_reserve/func_80A0940C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Reserve/ac_reserve/func_80A094EC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Reserve/ac_reserve/func_80A09580_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Reserve/ac_reserve/func_80A095A0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Reserve/ac_reserve/aRSV_actor_init.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Reserve/ac_reserve/aRSV_actor_draw.s")
