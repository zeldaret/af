#include "ac_npc_police2.h"
#include "m_lib.h"
#include "m_actor_dlftbls.h"
#include "m_object.h"
#include "overlays/gamestates/ovl_play/m_play.h"

void aPOL2_actor_ct(Actor* thisx, Game_Play* game_play);
void aPOL2_actor_dt(Actor* thisx, Game_Play* game_play);
void aPOL2_actor_init(Actor* thisx, Game_Play* game_play);
void aPOL2_actor_save(Actor* thisx, Game_Play* game_play);

#if 0
ActorProfile Npc_Police2_Profile = {
    /* */ ACTOR_NPC_POLICE2,
    /* */ ACTOR_PART_NPC,
    /* */ 0,
    /* */ 0xD010,
    /* */ GAMEPLAY_KEEP,
    /* */ sizeof(Npc_Police2),
    /* */ aPOL2_actor_ct,
    /* */ aPOL2_actor_dt,
    /* */ aPOL2_actor_init,
    /* */ (ActorFunc)none_proc1,
    /* */ aPOL2_actor_save,
};
#endif

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Police2/ac_npc_police2/aPOL2_actor_ct.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Police2/ac_npc_police2/aPOL2_actor_save.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Police2/ac_npc_police2/aPOL2_actor_dt.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Police2/ac_npc_police2/aPOL2_actor_init.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Police2/ac_npc_police2/func_809C2080_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Police2/ac_npc_police2/func_809C20BC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Police2/ac_npc_police2/func_809C20FC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Police2/ac_npc_police2/func_809C211C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Police2/ac_npc_police2/func_809C2148_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Police2/ac_npc_police2/func_809C2174_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Police2/ac_npc_police2/func_809C2230_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Police2/ac_npc_police2/func_809C22D8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Police2/ac_npc_police2/func_809C23E4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Police2/ac_npc_police2/func_809C24FC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Police2/ac_npc_police2/func_809C2568_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Police2/ac_npc_police2/func_809C2690_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Police2/ac_npc_police2/func_809C2720_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Police2/ac_npc_police2/func_809C2810_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Police2/ac_npc_police2/func_809C288C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Police2/ac_npc_police2/func_809C289C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Police2/ac_npc_police2/func_809C28F8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Police2/ac_npc_police2/func_809C2940_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Police2/ac_npc_police2/func_809C2994_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Police2/ac_npc_police2/func_809C2A74_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Police2/ac_npc_police2/func_809C2AD8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Police2/ac_npc_police2/func_809C2C30_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Police2/ac_npc_police2/func_809C2C94_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Police2/ac_npc_police2/func_809C2CF8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Police2/ac_npc_police2/func_809C2D5C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Police2/ac_npc_police2/func_809C2DC0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Police2/ac_npc_police2/func_809C2E54_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Police2/ac_npc_police2/func_809C2FD4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Police2/ac_npc_police2/func_809C3020_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Police2/ac_npc_police2/func_809C3050_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Police2/ac_npc_police2/func_809C3098_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Police2/ac_npc_police2/func_809C3144_jp.s")
