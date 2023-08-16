#include "ac_station.h"
#include "overlays/gamestates/ovl_play/m_play.h"

void aSTA_actor_ct(Actor* thisx, PlayState* play);
void aSTA_actor_dt(Actor* thisx, PlayState* play);
void aSTA_actor_init(Actor* thisx, PlayState* play);
void aSTA_actor_draw(Actor* thisx, PlayState* play);

#if 0
ActorProfile Station_Profile = {
    /* */ 60,
    /* */ ACTOR_PART_0,
    /* */ 0,
    /* */ 22537,
    /* */ 3,
    /* */ sizeof(Station),
    /* */ aSTA_actor_ct,
    /* */ aSTA_actor_dt,
    /* */ aSTA_actor_init,
    /* */ aSTA_actor_draw,
    /* */ NULL,
};
#endif

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Station/ac_station/aSTA_actor_ct.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Station/ac_station/aSTA_actor_dt.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Station/ac_station/func_80A0EE1C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Station/ac_station/func_80A0EE2C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Station/ac_station/func_80A0EECC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Station/ac_station/aSTA_actor_init.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Station/ac_station/func_80A0EF58_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Station/ac_station/aSTA_actor_draw.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Station/ac_station/func_80A0F108_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Station/ac_station/func_80A0F12C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Station/ac_station/func_80A0F13C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Station/ac_station/func_80A0F184_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Station/ac_station/func_80A0F20C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Station/ac_station/func_80A0F294_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Station/ac_station/func_80A0F424_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Station/ac_station/func_80A0F484_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Station/ac_station/func_80A0F504_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Station/ac_station/func_80A0F548_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Station/ac_station/func_80A0F5B8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Station/ac_station/func_80A0F634_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Station/ac_station/func_80A0F694_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Station/ac_station/func_80A0F76C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Station/ac_station/func_80A0F90C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Station/ac_station/func_80A0F98C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Station/ac_station/func_80A0FA20_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Station/ac_station/func_80A0FAF0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Station/ac_station/func_80A0FB3C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Station/ac_station/func_80A0FBDC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Station/ac_station/func_80A0FC84_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Station/ac_station/func_80A0FD98_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Station/ac_station/func_80A0FE04_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Station/ac_station/func_80A0FE60_jp.s")
