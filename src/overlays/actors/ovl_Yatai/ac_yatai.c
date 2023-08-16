#include "ac_yatai.h"
#include "overlays/gamestates/ovl_play/m_play.h"

void aYAT_actor_ct(Actor* thisx, PlayState* play);
void func_80A76EC4_jp(Actor* thisx, PlayState* play);
void aYAT_actor_init(Actor* thisx, PlayState* play);
void aYAT_actor_draw(Actor* thisx, PlayState* play);

#if 0
ActorProfile Yatai_Profile = {
    /* */ 126,
    /* */ ACTOR_PART_0,
    /* */ 0,
    /* */ 22572,
    /* */ 3,
    /* */ sizeof(Yatai),
    /* */ aYAT_actor_ct,
    /* */ func_80A76EC4_jp,
    /* */ aYAT_actor_init,
    /* */ aYAT_actor_draw,
    /* */ NULL,
};
#endif

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Yatai/ac_yatai/aYAT_actor_ct.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Yatai/ac_yatai/func_80A76EC4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Yatai/ac_yatai/func_80A76F50_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Yatai/ac_yatai/func_80A77160_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Yatai/ac_yatai/func_80A77170_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Yatai/ac_yatai/func_80A77190_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Yatai/ac_yatai/aYAT_actor_init.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Yatai/ac_yatai/aYAT_actor_draw.s")
