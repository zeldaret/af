#include "ac_goza.h"
#include "overlays/gamestates/ovl_play/m_play.h"

void aGOZ_actor_ct(Actor* thisx, Game_Play* game_play);
void func_80A76208_jp(Actor* thisx, Game_Play* game_play);
void aGOZ_actor_init(Actor* thisx, Game_Play* game_play);
void aGOZ_actor_draw(Actor* thisx, Game_Play* game_play);

#if 0
ActorProfile Goza_Profile = {
    /* */ ACTOR_GOZA,
    /* */ ACTOR_PART_0,
    /* */ 0,
    /* */ 0x582A,
    /* */ GAMEPLAY_KEEP,
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
