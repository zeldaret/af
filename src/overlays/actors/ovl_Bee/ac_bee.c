#include "ac_bee.h"
#include "m_actor_dlftbls.h"
#include "m_object.h"
#include "overlays/gamestates/ovl_play/m_play.h"

void aBEE_actor_ct(Actor* thisx, Game_Play* gamePlay);
void func_80A93DD0_jp(Actor* thisx, Game_Play* gamePlay);
void aBEE_actor_move(Actor* thisx, Game_Play* gamePlay);
void aBEE_actor_draw(Actor* thisx, Game_Play* gamePlay);

#if 0
ActorProfile Bee_Profile = {
    /* */ ACTOR_BEE,
    /* */ ACTOR_PART_4,
    /* */ ACTOR_FLAG_10,
    /* */ 0x0000,
    /* */ OBJECT_392,
    /* */ sizeof(Bee),
    /* */ aBEE_actor_ct,
    /* */ func_80A93DD0_jp,
    /* */ aBEE_actor_move,
    /* */ aBEE_actor_draw,
    /* */ NULL,
};
#endif

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Bee/ac_bee/aBEE_actor_ct.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Bee/ac_bee/func_80A93DD0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Bee/ac_bee/func_80A93DE0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Bee/ac_bee/func_80A93E38_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Bee/ac_bee/func_80A93E48_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Bee/ac_bee/func_80A93E6C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Bee/ac_bee/func_80A93EFC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Bee/ac_bee/func_80A94408_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Bee/ac_bee/func_80A94450_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Bee/ac_bee/func_80A9449C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Bee/ac_bee/aBEE_actor_move.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Bee/ac_bee/aBEE_actor_draw.s")
