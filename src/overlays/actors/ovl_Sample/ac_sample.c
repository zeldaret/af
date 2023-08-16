#include "ac_sample.h"
#include "overlays/gamestates/ovl_play/m_play.h"

void Ac_Sample_Actor_ct(Actor* thisx, PlayState* play);
void Ac_Sample_Actor_dt(Actor* thisx, PlayState* play);
void Ac_Sample_Actor_main(Actor* thisx, PlayState* play);
void Ac_Sample_Actor_draw(Actor* thisx, PlayState* play);

#if 0
ActorProfile Sample_Profile = {
    /* */ 2,
    /* */ ACTOR_PART_4,
    /* */ 0,
    /* */ 36864,
    /* */ 12,
    /* */ sizeof(Sample),
    /* */ Ac_Sample_Actor_ct,
    /* */ Ac_Sample_Actor_dt,
    /* */ Ac_Sample_Actor_main,
    /* */ Ac_Sample_Actor_draw,
    /* */ NULL,
};
#endif

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Sample/ac_sample/func_80933F40_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Sample/ac_sample/func_80933F8C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Sample/ac_sample/Ac_Sample_Actor_dt.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Sample/ac_sample/func_8093401C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Sample/ac_sample/func_80934040_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Sample/ac_sample/func_80934104_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Sample/ac_sample/func_80934190_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Sample/ac_sample/func_8093420C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Sample/ac_sample/Ac_Sample_Actor_main.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Sample/ac_sample/Ac_Sample_Actor_ct.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Sample/ac_sample/func_809343BC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Sample/ac_sample/Ac_Sample_Actor_draw.s")
