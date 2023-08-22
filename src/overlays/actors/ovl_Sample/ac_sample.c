#include "ac_sample.h"
#include "overlays/gamestates/ovl_play/m_play.h"

void Ac_Sample_Actor_ct(Actor* thisx, Game_Play* game_play);
void Ac_Sample_Actor_dt(Actor* thisx, Game_Play* game_play);
void Ac_Sample_Actor_main(Actor* thisx, Game_Play* game_play);
void Ac_Sample_Actor_draw(Actor* thisx, Game_Play* game_play);

#if 0
ActorProfile Sample_Profile = {
    /* */ ACTOR_SAMPLE,
    /* */ ACTOR_PART_4,
    /* */ 0,
    /* */ 0x9000,
    /* */ OBJECT_12,
    /* */ sizeof(Sample),
    /* */ Ac_Sample_Actor_ct,
    /* */ Ac_Sample_Actor_dt,
    /* */ Ac_Sample_Actor_main,
    /* */ Ac_Sample_Actor_draw,
    /* */ NULL,
};
#endif

extern ClObjPipe_Init Ac_Sample_OcInfoData_forStand;
#if 0
ClObjPipe_Init Ac_Sample_OcInfoData_forStand = { { OC1_1 | OC1_TYPE_8 | OC1_TYPE_10 | OC1_TYPE_20, OC2_TYPE_20, COLSHAPE_PIPE }, { ELEM_FLAG_1 }, { { 0x1E, 0x3C, 0, { 0, 0, 0 } } } };
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
