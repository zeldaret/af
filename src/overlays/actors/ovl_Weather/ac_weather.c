#include "ac_weather.h"
#include "overlays/gamestates/ovl_play/m_play.h"

void Weather_Actor_ct(Actor* thisx, PlayState* play);
void Weather_Actor_dt(Actor* thisx, PlayState* play);
void Weather_Actor_move(Actor* thisx, PlayState* play);
void Weather_Actor_draw(Actor* thisx, PlayState* play);

#if 0
ActorProfile Weather_Profile = {
    /* */ ACTOR_WEATHER,
    /* */ ACTOR_PART_7,
    /* */ ACTOR_FLAG_10 | ACTOR_FLAG_20 | ACTOR_FLAG_20000000,
    /* */ 0x0000,
    /* */ GAMEPLAY_KEEP,
    /* */ sizeof(Weather),
    /* */ Weather_Actor_ct,
    /* */ Weather_Actor_dt,
    /* */ Weather_Actor_move,
    /* */ Weather_Actor_draw,
    /* */ NULL,
};
#endif

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Weather/ac_weather/func_80A21670_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Weather/ac_weather/func_80A216C4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Weather/ac_weather/func_80A216E4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Weather/ac_weather/func_80A21724_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Weather/ac_weather/func_80A21760_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Weather/ac_weather/func_80A217A8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Weather/ac_weather/func_80A21828_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Weather/ac_weather/func_80A21858_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Weather/ac_weather/func_80A21914_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Weather/ac_weather/func_80A219A0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Weather/ac_weather/func_80A21A64_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Weather/ac_weather/func_80A21B04_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Weather/ac_weather/func_80A21CD8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Weather/ac_weather/func_80A21D90_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Weather/ac_weather/func_80A21DFC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Weather/ac_weather/func_80A21E78_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Weather/ac_weather/func_80A21F14_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Weather/ac_weather/func_80A21F3C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Weather/ac_weather/func_80A21FA0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Weather/ac_weather/func_80A22028_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Weather/ac_weather/func_80A220CC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Weather/ac_weather/Weather_Actor_ct.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Weather/ac_weather/Weather_Actor_dt.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Weather/ac_weather/func_80A2236C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Weather/ac_weather/Weather_Actor_draw.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Weather/ac_weather/func_80A22484_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Weather/ac_weather/func_80A224C8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Weather/ac_weather/func_80A225D0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Weather/ac_weather/func_80A22644_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Weather/ac_weather/func_80A22740_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Weather/ac_weather/func_80A2276C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Weather/ac_weather/func_80A227E4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Weather/ac_weather/func_80A22950_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Weather/ac_weather/Weather_Actor_move.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Weather/ac_weather/func_80A22BF0_jp.s")
