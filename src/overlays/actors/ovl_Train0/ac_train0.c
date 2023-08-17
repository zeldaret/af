#include "ac_train0.h"
#include "overlays/gamestates/ovl_play/m_play.h"

void func_805bfc28(Actor* thisx, Game_Play* play);
void func_805bfcdc(Actor* thisx, Game_Play* play);
void func_805c03ec(Actor* thisx, Game_Play* play);
void func_805c04e0(Actor* thisx, Game_Play* play);

#if 0
ActorProfile Train0_Profile = {
    /* */ ACTOR_TRAIN0,
    /* */ ACTOR_PART_0,
    /* */ ACTOR_FLAG_10 | ACTOR_FLAG_20000000,
    /* */ 0x580A,
    /* */ GAMEPLAY_KEEP,
    /* */ sizeof(Train0),
    /* */ func_805bfc28,
    /* */ func_805bfcdc,
    /* */ func_805c03ec,
    /* */ func_805c04e0,
    /* */ NULL,
};
#endif

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Train0/ac_train0/func_805bfc28.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Train0/ac_train0/func_805bfcdc.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Train0/ac_train0/func_80A0C7A4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Train0/ac_train0/func_80A0C874_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Train0/ac_train0/func_80A0C990_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Train0/ac_train0/func_80A0CAA0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Train0/ac_train0/func_80A0CB14_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Train0/ac_train0/func_80A0CB84_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Train0/ac_train0/func_80A0CBC0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Train0/ac_train0/func_80A0CC90_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Train0/ac_train0/func_80A0CD20_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Train0/ac_train0/func_80A0CD8C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Train0/ac_train0/func_805c03ec.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Train0/ac_train0/func_805c04e0.s")
