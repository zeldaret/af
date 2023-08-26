#include "ac_set_npc_manager.h"
#include "m_lib.h"
#include "m_actor_dlftbls.h"
#include "m_object.h"
#include "overlays/gamestates/ovl_play/m_play.h"

void aSNMgr_actor_ct(Actor* thisx, Game_Play* gamePlay);
void aSNMgr_actor_dt(Actor* thisx, Game_Play* gamePlay);
void aSNMgr_actor_move(Actor* thisx, Game_Play* gamePlay);

#if 0
ActorProfile Set_Npc_Manager_Profile = {
    /* */ ACTOR_SET_NPC_MANAGER,
    /* */ ACTOR_PART_7,
    /* */ ACTOR_FLAG_10 | ACTOR_FLAG_20 | ACTOR_FLAG_20000000,
    /* */ 0x0000,
    /* */ GAMEPLAY_KEEP,
    /* */ sizeof(Set_Npc_Manager),
    /* */ aSNMgr_actor_ct,
    /* */ aSNMgr_actor_dt,
    /* */ aSNMgr_actor_move,
    /* */ (ActorFunc)none_proc1,
    /* */ NULL,
};
#endif

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Set_Npc_Manager/ac_set_npc_manager/func_80A22EB0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Set_Npc_Manager/ac_set_npc_manager/func_80A22ED0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Set_Npc_Manager/ac_set_npc_manager/func_80A22F64_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Set_Npc_Manager/ac_set_npc_manager/func_80A22FB8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Set_Npc_Manager/ac_set_npc_manager/func_80A23010_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Set_Npc_Manager/ac_set_npc_manager/func_80A23044_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Set_Npc_Manager/ac_set_npc_manager/func_80A230D0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Set_Npc_Manager/ac_set_npc_manager/func_80A23130_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Set_Npc_Manager/ac_set_npc_manager/func_80A2316C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Set_Npc_Manager/ac_set_npc_manager/func_80A231D0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Set_Npc_Manager/ac_set_npc_manager/func_80A23248_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Set_Npc_Manager/ac_set_npc_manager/func_80A23330_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Set_Npc_Manager/ac_set_npc_manager/func_80A23364_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Set_Npc_Manager/ac_set_npc_manager/func_80A233F0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Set_Npc_Manager/ac_set_npc_manager/func_80A23488_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Set_Npc_Manager/ac_set_npc_manager/func_80A2356C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Set_Npc_Manager/ac_set_npc_manager/func_80A23608_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Set_Npc_Manager/ac_set_npc_manager/func_80A23688_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Set_Npc_Manager/ac_set_npc_manager/func_80A2375C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Set_Npc_Manager/ac_set_npc_manager/func_80A238BC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Set_Npc_Manager/ac_set_npc_manager/func_80A23A84_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Set_Npc_Manager/ac_set_npc_manager/func_80A23BDC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Set_Npc_Manager/ac_set_npc_manager/func_80A23CD8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Set_Npc_Manager/ac_set_npc_manager/func_80A23D10_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Set_Npc_Manager/ac_set_npc_manager/func_80A23D88_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Set_Npc_Manager/ac_set_npc_manager/func_80A23F30_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Set_Npc_Manager/ac_set_npc_manager/func_80A23FC0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Set_Npc_Manager/ac_set_npc_manager/func_80A2408C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Set_Npc_Manager/ac_set_npc_manager/func_80A240C4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Set_Npc_Manager/ac_set_npc_manager/func_80A24114_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Set_Npc_Manager/ac_set_npc_manager/func_80A241C4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Set_Npc_Manager/ac_set_npc_manager/func_80A242E0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Set_Npc_Manager/ac_set_npc_manager/func_80A24418_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Set_Npc_Manager/ac_set_npc_manager/func_80A24588_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Set_Npc_Manager/ac_set_npc_manager/func_80A2460C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Set_Npc_Manager/ac_set_npc_manager/func_80A246B4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Set_Npc_Manager/ac_set_npc_manager/func_80A24734_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Set_Npc_Manager/ac_set_npc_manager/func_80A247B4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Set_Npc_Manager/ac_set_npc_manager/func_80A2487C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Set_Npc_Manager/ac_set_npc_manager/func_80A24A8C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Set_Npc_Manager/ac_set_npc_manager/func_80A24D08_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Set_Npc_Manager/ac_set_npc_manager/func_80A24F24_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Set_Npc_Manager/ac_set_npc_manager/func_80A2513C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Set_Npc_Manager/ac_set_npc_manager/aSNMgr_actor_move.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Set_Npc_Manager/ac_set_npc_manager/aSNMgr_actor_ct.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Set_Npc_Manager/ac_set_npc_manager/aSNMgr_actor_dt.s")
