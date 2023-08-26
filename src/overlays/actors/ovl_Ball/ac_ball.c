#include "ac_ball.h"
#include "m_actor_dlftbls.h"
#include "m_object.h"
#include "overlays/gamestates/ovl_play/m_play.h"

void aBALL_actor_ct(Actor* thisx, Game_Play* gamePlay);
void aBALL_actor_dt(Actor* thisx, Game_Play* gamePlay);
void aBALL_actor_move(Actor* thisx, Game_Play* gamePlay);
void aBALL_actor_draw(Actor* thisx, Game_Play* gamePlay);

#if 0
ActorProfile Ball_Profile = {
    /* */ ACTOR_BALL,
    /* */ ACTOR_PART_4,
    /* */ ACTOR_FLAG_10,
    /* */ 0x8001,
    /* */ GAMEPLAY_KEEP,
    /* */ sizeof(Ball),
    /* */ aBALL_actor_ct,
    /* */ aBALL_actor_dt,
    /* */ aBALL_actor_move,
    /* */ aBALL_actor_draw,
    /* */ NULL,
};
#endif

extern ClObjPipe_Init aBALL_CoInfoData;
extern CollisionCheck_Status_Init aBALL_StatusData;

#if 0
ClObjPipe_Init aBALL_CoInfoData = { { OC1_1 | OC1_TYPE_8 | OC1_TYPE_10 | OC1_TYPE_20, OC2_TYPE_20, COLSHAPE_PIPE }, { ELEM_FLAG_1 }, { { 0xD, 0x1E, -0xA, { 0, 0, 0 } } }, };
CollisionCheck_Status_Init aBALL_StatusData = { 0, 0xD, 0x1E, -0xA, 100, };
#endif

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ball/ac_ball/func_80968A10_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ball/ac_ball/func_80968AF4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ball/ac_ball/func_80968B9C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ball/ac_ball/aBALL_actor_ct.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ball/ac_ball/aBALL_actor_dt.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ball/ac_ball/func_80969040_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ball/ac_ball/func_80969114_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ball/ac_ball/func_809693EC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ball/ac_ball/func_80969800_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ball/ac_ball/func_8096983C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ball/ac_ball/func_809698E8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ball/ac_ball/func_80969998_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ball/ac_ball/func_809699D8_jp.s")

// TODO: this function includes an unreferenced float. It was forced to be in this function to
// be able to build and match the file. It needs to be figured out where to put this float and
// how to handle this when this file gets decompiled.
#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ball/ac_ball/func_80969DE8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ball/ac_ball/func_80969FBC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ball/ac_ball/func_80969FD8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ball/ac_ball/func_8096A0CC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ball/ac_ball/func_8096A0EC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ball/ac_ball/func_8096A23C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ball/ac_ball/func_8096A334_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ball/ac_ball/func_8096A3D8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ball/ac_ball/aBALL_actor_move.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ball/ac_ball/aBALL_actor_draw.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ball/ac_ball/func_8096A86C_jp.s")
