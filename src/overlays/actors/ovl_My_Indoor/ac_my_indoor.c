#include "ac_my_indoor.h"
#include "overlays/gamestates/ovl_play/m_play.h"

void My_Indoor_Actor_ct(Actor* thisx, PlayState* play);
void My_Indoor_Actor_dt(Actor* thisx, PlayState* play);
void My_Indoor_Actor_move(Actor* thisx, PlayState* play);
void My_Indoor_Actor_draw(Actor* thisx, PlayState* play);

#if 0
ActorProfile My_Indoor_Profile = {
    /* */ ACTOR_MY_INDOOR,
    /* */ ACTOR_PART_5,
    /* */ ACTOR_FLAG_10 | ACTOR_FLAG_20,
    /* */ 0x0000,
    /* */ GAMEPLAY_KEEP,
    /* */ sizeof(My_Indoor),
    /* */ My_Indoor_Actor_ct,
    /* */ My_Indoor_Actor_dt,
    /* */ My_Indoor_Actor_move,
    /* */ My_Indoor_Actor_draw,
    /* */ NULL,
};
#endif

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_My_Indoor/ac_my_indoor/func_80951A70_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_My_Indoor/ac_my_indoor/func_80951A9C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_My_Indoor/ac_my_indoor/func_80951BC4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_My_Indoor/ac_my_indoor/func_80951CDC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_My_Indoor/ac_my_indoor/func_80951DF4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_My_Indoor/ac_my_indoor/func_80951E64_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_My_Indoor/ac_my_indoor/func_80951EBC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_My_Indoor/ac_my_indoor/func_80951F14_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_My_Indoor/ac_my_indoor/My_Indoor_Actor_ct.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_My_Indoor/ac_my_indoor/My_Indoor_Actor_dt.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_My_Indoor/ac_my_indoor/func_8095205C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_My_Indoor/ac_my_indoor/func_80952254_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_My_Indoor/ac_my_indoor/My_Indoor_Actor_draw.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_My_Indoor/ac_my_indoor/func_80952444_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_My_Indoor/ac_my_indoor/func_8095253C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_My_Indoor/ac_my_indoor/My_Indoor_Actor_move.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_My_Indoor/ac_my_indoor/func_8095267C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_My_Indoor/ac_my_indoor/func_809526D4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_My_Indoor/ac_my_indoor/func_8095272C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_My_Indoor/ac_my_indoor/func_80952754_jp.s")
