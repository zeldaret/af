#include "ac_police_box.h"
#include "overlays/gamestates/ovl_play/m_play.h"

void aPBOX_actor_ct(Actor* thisx, PlayState* play);
void func_80A078A4_jp(Actor* thisx, PlayState* play);
void aPBOX_actor_init(Actor* thisx, PlayState* play);
void aPBOX_actor_draw(Actor* thisx, PlayState* play);

#if 0
ActorProfile Police_Box_Profile = {
    /* */ 77,
    /* */ ACTOR_PART_0,
    /* */ 0,
    /* */ 22540,
    /* */ 3,
    /* */ sizeof(Police_Box),
    /* */ aPBOX_actor_ct,
    /* */ func_80A078A4_jp,
    /* */ aPBOX_actor_init,
    /* */ aPBOX_actor_draw,
    /* */ NULL,
};
#endif

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Police_Box/ac_police_box/aPBOX_actor_ct.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Police_Box/ac_police_box/func_80A078A4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Police_Box/ac_police_box/func_80A07930_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Police_Box/ac_police_box/func_80A07B30_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Police_Box/ac_police_box/func_80A07C2C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Police_Box/ac_police_box/func_80A07CE0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Police_Box/ac_police_box/aPBOX_actor_init.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Police_Box/ac_police_box/aPBOX_actor_draw.s")
