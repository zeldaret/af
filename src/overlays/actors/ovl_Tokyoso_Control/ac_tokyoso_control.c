#include "ac_tokyoso_control.h"
#include "m_lib.h"
#include "m_actor_dlftbls.h"
#include "m_object.h"
#include "overlays/gamestates/ovl_play/m_play.h"

void aTKC_actor_ct(Actor* thisx, Game_Play* game_play);
void aTKC_actor_dt(Actor* thisx, Game_Play* game_play);
void aTKC_actor_move(Actor* thisx, Game_Play* game_play);

#if 0
ActorProfile Tokyoso_Control_Profile = {
    /* */ ACTOR_TOKYOSO_CONTROL,
    /* */ ACTOR_PART_7,
    /* */ ACTOR_FLAG_10,
    /* */ 0x0000,
    /* */ GAMEPLAY_KEEP,
    /* */ sizeof(Tokyoso_Control),
    /* */ aTKC_actor_ct,
    /* */ aTKC_actor_dt,
    /* */ aTKC_actor_move,
    /* */ (void*)none_proc1,
    /* */ NULL,
};
#endif

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Tokyoso_Control/ac_tokyoso_control/aTKC_actor_ct.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Tokyoso_Control/ac_tokyoso_control/aTKC_actor_dt.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Tokyoso_Control/ac_tokyoso_control/aTKC_actor_move.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Tokyoso_Control/ac_tokyoso_control/func_80A777C0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Tokyoso_Control/ac_tokyoso_control/func_80A77814_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Tokyoso_Control/ac_tokyoso_control/func_80A77878_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Tokyoso_Control/ac_tokyoso_control/func_80A7790C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Tokyoso_Control/ac_tokyoso_control/func_80A77A40_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Tokyoso_Control/ac_tokyoso_control/func_80A77AB8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Tokyoso_Control/ac_tokyoso_control/func_80A77B34_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Tokyoso_Control/ac_tokyoso_control/func_80A77BB8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Tokyoso_Control/ac_tokyoso_control/func_80A77C10_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Tokyoso_Control/ac_tokyoso_control/func_80A77C70_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Tokyoso_Control/ac_tokyoso_control/func_80A77C90_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Tokyoso_Control/ac_tokyoso_control/func_80A77D2C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Tokyoso_Control/ac_tokyoso_control/func_80A77D64_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Tokyoso_Control/ac_tokyoso_control/func_80A77D84_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Tokyoso_Control/ac_tokyoso_control/func_80A77DE0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Tokyoso_Control/ac_tokyoso_control/func_80A77E40_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Tokyoso_Control/ac_tokyoso_control/func_80A77EA0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Tokyoso_Control/ac_tokyoso_control/func_80A77F00_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Tokyoso_Control/ac_tokyoso_control/func_80A77F54_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Tokyoso_Control/ac_tokyoso_control/func_80A77F94_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Tokyoso_Control/ac_tokyoso_control/func_80A78020_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Tokyoso_Control/ac_tokyoso_control/func_80A78078_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Tokyoso_Control/ac_tokyoso_control/func_80A780E4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Tokyoso_Control/ac_tokyoso_control/func_80A78144_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Tokyoso_Control/ac_tokyoso_control/func_80A78178_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Tokyoso_Control/ac_tokyoso_control/func_80A781C4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Tokyoso_Control/ac_tokyoso_control/func_80A78210_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Tokyoso_Control/ac_tokyoso_control/func_80A7823C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Tokyoso_Control/ac_tokyoso_control/func_80A78290_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Tokyoso_Control/ac_tokyoso_control/func_80A782C4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Tokyoso_Control/ac_tokyoso_control/func_80A78304_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Tokyoso_Control/ac_tokyoso_control/func_80A78374_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Tokyoso_Control/ac_tokyoso_control/func_80A783AC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Tokyoso_Control/ac_tokyoso_control/func_80A78630_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Tokyoso_Control/ac_tokyoso_control/func_80A78698_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Tokyoso_Control/ac_tokyoso_control/func_80A78730_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Tokyoso_Control/ac_tokyoso_control/func_80A78804_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Tokyoso_Control/ac_tokyoso_control/func_80A788B4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Tokyoso_Control/ac_tokyoso_control/func_80A7892C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Tokyoso_Control/ac_tokyoso_control/func_80A78990_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Tokyoso_Control/ac_tokyoso_control/func_80A78A68_jp.s")
