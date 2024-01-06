#include "ac_haniwa.h"
#include "m_lib.h"
#include "m_actor_dlftbls.h"
#include "m_object.h"
#include "overlays/gamestates/ovl_play/m_play.h"

void aHNW_actor_ct(Actor* thisx, Game_Play* game_play);
void aHNW_actor_dt(Actor* thisx, Game_Play* game_play);
void aHNW_actor_init(Actor* thisx, Game_Play* game_play);

#if 0
ActorProfile Haniwa_Profile = {
    /* */ ACTOR_HANIWA,
    /* */ ACTOR_PART_4,
    /* */ 0,
    /* */ 0xA004,
    /* */ OBJECT_12,
    /* */ sizeof(Haniwa),
    /* */ aHNW_actor_ct,
    /* */ aHNW_actor_dt,
    /* */ aHNW_actor_init,
    /* */ (void*)none_proc1,
    /* */ NULL,
};
#endif

extern ClObjPipe_Init AcHaniwaCoInfoData;
extern CollisionCheck_Status_Init AcHaniwaStatusData;

#if 0
ClObjPipe_Init AcHaniwaCoInfoData = { { OC1_1 | OC1_TYPE_8 | OC1_TYPE_10 | OC1_TYPE_20, OC2_TYPE_20, COLSHAPE_PIPE }, { ELEM_FLAG_1 }, { { 0x14, 0x1E, 0, { 0, 0, 0 } } }, };
CollisionCheck_Status_Init AcHaniwaStatusData = { 0, 0x14, 0x1E, 0, MASS_HEAVY, };
#endif

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Haniwa/ac_haniwa/aHNW_actor_ct.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Haniwa/ac_haniwa/aHNW_actor_dt.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Haniwa/ac_haniwa/func_8096ACB8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Haniwa/ac_haniwa/func_8096AD94_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Haniwa/ac_haniwa/func_8096ADC0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Haniwa/ac_haniwa/func_8096AE18_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Haniwa/ac_haniwa/func_8096AE88_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Haniwa/ac_haniwa/func_8096AEDC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Haniwa/ac_haniwa/func_8096AFE8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Haniwa/ac_haniwa/func_8096B0DC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Haniwa/ac_haniwa/func_8096B168_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Haniwa/ac_haniwa/func_8096B1A4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Haniwa/ac_haniwa/func_8096B2D8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Haniwa/ac_haniwa/func_8096B398_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Haniwa/ac_haniwa/func_8096B474_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Haniwa/ac_haniwa/func_8096B558_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Haniwa/ac_haniwa/func_8096B664_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Haniwa/ac_haniwa/func_8096B6A4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Haniwa/ac_haniwa/func_8096B754_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Haniwa/ac_haniwa/func_8096B7AC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Haniwa/ac_haniwa/func_8096B88C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Haniwa/ac_haniwa/func_8096B900_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Haniwa/ac_haniwa/func_8096B958_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Haniwa/ac_haniwa/func_8096B9DC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Haniwa/ac_haniwa/func_8096BB98_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Haniwa/ac_haniwa/func_8096BC3C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Haniwa/ac_haniwa/func_8096BD00_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Haniwa/ac_haniwa/func_8096BD30_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Haniwa/ac_haniwa/func_8096BD60_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Haniwa/ac_haniwa/func_8096BDD0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Haniwa/ac_haniwa/func_8096BDE8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Haniwa/ac_haniwa/func_8096BE18_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Haniwa/ac_haniwa/func_8096C01C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Haniwa/ac_haniwa/func_8096C174_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Haniwa/ac_haniwa/aHNW_actor_init.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Haniwa/ac_haniwa/func_8096C29C_jp.s")
