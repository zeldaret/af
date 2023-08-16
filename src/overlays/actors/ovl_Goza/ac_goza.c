#include "ac_goza.h"
#include "overlays/gamestates/ovl_play/m_play.h"

void aGOZ_actor_ct(Actor* thisx, PlayState* play);
void func_80A76208_jp(Actor* thisx, PlayState* play);
void aGOZ_actor_init(Actor* thisx, PlayState* play);
void aGOZ_actor_draw(Actor* thisx, PlayState* play);

#if 0
ActorProfile Goza_Profile = {
    /* */ 124,
    /* */ ACTOR_PART_0,
    /* */ 0,
    /* */ 22570,
    /* */ 3,
    /* */ sizeof(Goza),
    /* */ aGOZ_actor_ct,
    /* */ func_80A76208_jp,
    /* */ aGOZ_actor_init,
    /* */ aGOZ_actor_draw,
    /* */ NULL,
};
#endif

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Goza/ac_goza/aGOZ_actor_ct.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Goza/ac_goza/func_80A76208_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Goza/ac_goza/func_80A76294_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Goza/ac_goza/func_80A76494_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Goza/ac_goza/func_80A764A4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Goza/ac_goza/func_80A764C0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Goza/ac_goza/aGOZ_actor_init.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Goza/ac_goza/aGOZ_actor_draw.s")
