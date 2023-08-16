#include "ac_s_car.h"
#include "overlays/gamestates/ovl_play/m_play.h"

void aSCR_actor_ct(Actor* thisx, PlayState* play);
void aSCR_actor_dt(Actor* thisx, PlayState* play);
void aSCR_actor_init(Actor* thisx, PlayState* play);
void aSCR_actor_draw(Actor* thisx, PlayState* play);

#if 0
ActorProfile S_Car_Profile = {
    /* */ 99,
    /* */ ACTOR_PART_0,
    /* */ 0,
    /* */ 22568,
    /* */ 3,
    /* */ sizeof(S_Car),
    /* */ aSCR_actor_ct,
    /* */ aSCR_actor_dt,
    /* */ aSCR_actor_init,
    /* */ aSCR_actor_draw,
    /* */ NULL,
};
#endif

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_S_Car/ac_s_car/aSCR_actor_ct.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_S_Car/ac_s_car/aSCR_actor_dt.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_S_Car/ac_s_car/func_80A09928_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_S_Car/ac_s_car/func_80A09A88_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_S_Car/ac_s_car/aSCR_actor_init.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_S_Car/ac_s_car/func_80A09C9C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_S_Car/ac_s_car/aSCR_actor_draw.s")
