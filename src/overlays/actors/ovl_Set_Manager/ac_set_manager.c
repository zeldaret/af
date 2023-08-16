#include "ac_set_manager.h"
#include "m_lib.h"
#include "overlays/gamestates/ovl_play/m_play.h"

void aSetMgr_ct(Actor* thisx, PlayState* play);
void aSetMgr_dt(Actor* thisx, PlayState* play);
void aSetMgr_move(Actor* thisx, PlayState* play);

#if 0
ActorProfile Set_Manager_Profile = {
    /* */ ACTOR_SET_MANAGER,
    /* */ ACTOR_PART_7,
    /* */ 536870960,
    /* */ 0x0000,
    /* */ GAMEPLAY_KEEP,
    /* */ sizeof(Set_Manager),
    /* */ aSetMgr_ct,
    /* */ aSetMgr_dt,
    /* */ aSetMgr_move,
    /* */ (ActorFunc)none_proc1,
    /* */ NULL,
};
#endif

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Set_Manager/ac_set_manager/func_80957DF0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Set_Manager/ac_set_manager/func_80957E74_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Set_Manager/ac_set_manager/func_80957F0C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Set_Manager/ac_set_manager/func_80957F68_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Set_Manager/ac_set_manager/func_80957F88_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Set_Manager/ac_set_manager/func_80957FA8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Set_Manager/ac_set_manager/func_80957FD4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Set_Manager/ac_set_manager/func_8095804C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Set_Manager/ac_set_manager/func_8095806C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Set_Manager/ac_set_manager/func_809580D4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Set_Manager/ac_set_manager/func_80958130_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Set_Manager/ac_set_manager/aSetMgr_move.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Set_Manager/ac_set_manager/aSetMgr_ct.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Set_Manager/ac_set_manager/aSetMgr_dt.s")
