#include "ac_npc_police.h"
#include "m_lib.h"
#include "m_actor_dlftbls.h"
#include "m_object.h"
#include "overlays/gamestates/ovl_play/m_play.h"

void aPOL_actor_ct(Actor* thisx, Game_Play* game_play);
void aPOL_actor_dt(Actor* thisx, Game_Play* game_play);
void aPOL_actor_init(Actor* thisx, Game_Play* game_play);
void aPOL_actor_save(Actor* thisx, Game_Play* game_play);

#if 0
ActorProfile Npc_Police_Profile = {
    /* */ ACTOR_NPC_POLICE,
    /* */ ACTOR_PART_NPC,
    /* */ 0,
    /* */ 0xD00D,
    /* */ GAMEPLAY_KEEP,
    /* */ sizeof(Npc_Police),
    /* */ aPOL_actor_ct,
    /* */ aPOL_actor_dt,
    /* */ aPOL_actor_init,
    /* */ (void*)none_proc1,
    /* */ aPOL_actor_save,
};
#endif

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Police/ac_npc_police/aPOL_actor_ct.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Police/ac_npc_police/aPOL_actor_save.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Police/ac_npc_police/aPOL_actor_dt.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Police/ac_npc_police/aPOL_actor_init.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Police/ac_npc_police/func_809C1358_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Police/ac_npc_police/func_809C14D0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Police/ac_npc_police/func_809C1550_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Police/ac_npc_police/func_809C1580_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Police/ac_npc_police/func_809C15B0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Police/ac_npc_police/func_809C15F0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Police/ac_npc_police/func_809C165C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Police/ac_npc_police/func_809C168C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Police/ac_npc_police/func_809C16D8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Police/ac_npc_police/func_809C1704_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Police/ac_npc_police/func_809C1798_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Police/ac_npc_police/func_809C181C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Police/ac_npc_police/func_809C18B4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Police/ac_npc_police/func_809C190C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Police/ac_npc_police/func_809C19AC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Police/ac_npc_police/func_809C1A48_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Police/ac_npc_police/func_809C1B4C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Police/ac_npc_police/func_809C1C00_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Police/ac_npc_police/func_809C1C6C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Police/ac_npc_police/func_809C1D28_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Police/ac_npc_police/D_809C1D44_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Police/ac_npc_police/D_809C1D5C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Police/ac_npc_police/func_809C1D74_jp.s")
