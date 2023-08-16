#include "ac_airplane.h"
#include "overlays/gamestates/ovl_play/m_play.h"

void Airplane_Actor_ct(Actor* thisx, PlayState* play);
void Airplane_Actor_dt(Actor* thisx, PlayState* play);
void Airplane_Actor_move(Actor* thisx, PlayState* play);
void Airplane_Actor_draw(Actor* thisx, PlayState* play);

#if 0
ActorProfile Airplane_Profile = {
    /* */ 5,
    /* */ ACTOR_PART_4,
    /* */ 48,
    /* */ 32768,
    /* */ 7,
    /* */ sizeof(Airplane),
    /* */ Airplane_Actor_ct,
    /* */ Airplane_Actor_dt,
    /* */ Airplane_Actor_move,
    /* */ Airplane_Actor_draw,
    /* */ NULL,
};
#endif

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Airplane/ac_airplane/Airplane_Actor_ct.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Airplane/ac_airplane/Airplane_Actor_dt.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Airplane/ac_airplane/Airplane_Actor_draw.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Airplane/ac_airplane/func_80967B50_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Airplane/ac_airplane/func_80967B78_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Airplane/ac_airplane/func_80967B9C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Airplane/ac_airplane/func_80967C8C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Airplane/ac_airplane/func_80967D04_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Airplane/ac_airplane/func_80967E1C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Airplane/ac_airplane/func_80967E98_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Airplane/ac_airplane/func_80968058_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Airplane/ac_airplane/func_80968068_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Airplane/ac_airplane/func_809680C8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Airplane/ac_airplane/func_809681A4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Airplane/ac_airplane/func_80968280_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Airplane/ac_airplane/func_80968304_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Airplane/ac_airplane/func_80968464_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Airplane/ac_airplane/func_809685B8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Airplane/ac_airplane/func_80968638_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Airplane/ac_airplane/Airplane_Actor_move.s")
