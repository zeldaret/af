#include "ac_countdown.h"
#include "m_actor_dlftbls.h"
#include "m_object.h"
#include "overlays/gamestates/ovl_play/m_play.h"

void func_805ac0ac(Actor* thisx, Game_Play* gamePlay);
void func_805ac120(Actor* thisx, Game_Play* gamePlay);
void func_805ac5ec(Actor* thisx, Game_Play* gamePlay);
void func_805ac7b0(Actor* thisx, Game_Play* gamePlay);

#if 0
ActorProfile Count_Profile = {
    /* */ ACTOR_COUNT,
    /* */ ACTOR_PART_0,
    /* */ 0,
    /* */ 0x5831,
    /* */ GAMEPLAY_KEEP,
    /* */ sizeof(Count),
    /* */ func_805ac0ac,
    /* */ func_805ac120,
    /* */ func_805ac5ec,
    /* */ func_805ac7b0,
    /* */ NULL,
};
#endif

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Count/ac_countdown/func_805ac0ac.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Count/ac_countdown/func_805ac120.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Count/ac_countdown/func_80A84D2C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Count/ac_countdown/func_80A84D44_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Count/ac_countdown/func_80A84D7C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Count/ac_countdown/func_80A84D9C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Count/ac_countdown/func_80A84F9C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Count/ac_countdown/func_80A8502C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Count/ac_countdown/func_80A85060_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Count/ac_countdown/func_80A85088_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Count/ac_countdown/func_80A8512C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Count/ac_countdown/func_805ac5ec.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Count/ac_countdown/func_80A852C4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Count/ac_countdown/func_805ac7b0.s")
