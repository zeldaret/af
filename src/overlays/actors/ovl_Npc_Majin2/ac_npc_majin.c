#include "ac_npc_majin.h"
#include "m_lib.h"
#include "m_actor_dlftbls.h"
#include "m_object.h"
#include "overlays/gamestates/ovl_play/m_play.h"

void aMJN2_actor_ct(Actor* thisx, Game_Play* gamePlay);
void aMJN2_actor_dt(Actor* thisx, Game_Play* gamePlay);
void aMJN2_actor_init(Actor* thisx, Game_Play* gamePlay);
void aMJN2_actor_save(Actor* thisx, Game_Play* gamePlay);

#if 0
ActorProfile Npc_Majin2_Profile = {
    /* */ ACTOR_NPC_MAJIN2,
    /* */ ACTOR_PART_NPC,
    /* */ ACTOR_FLAG_10 | ACTOR_FLAG_20,
    /* */ 0xD065,
    /* */ GAMEPLAY_KEEP,
    /* */ sizeof(Npc_Majin2),
    /* */ aMJN2_actor_ct,
    /* */ aMJN2_actor_dt,
    /* */ aMJN2_actor_init,
    /* */ (ActorFunc)none_proc1,
    /* */ aMJN2_actor_save,
};
#endif

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Majin2/ac_npc_majin/aMJN2_actor_ct.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Majin2/ac_npc_majin/aMJN2_actor_save.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Majin2/ac_npc_majin/aMJN2_actor_dt.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Majin2/ac_npc_majin/aMJN2_actor_init.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Majin2/ac_npc_majin/func_809B3D70_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Majin2/ac_npc_majin/func_809B3DA8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Majin2/ac_npc_majin/func_809B3DE8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Majin2/ac_npc_majin/func_809B3E5C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Majin2/ac_npc_majin/func_809B3E78_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Majin2/ac_npc_majin/func_809B3F10_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Majin2/ac_npc_majin/func_809B3F44_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Majin2/ac_npc_majin/func_809B3FB4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Majin2/ac_npc_majin/func_809B3FE8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Majin2/ac_npc_majin/func_809B4018_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Majin2/ac_npc_majin/func_809B40B8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Majin2/ac_npc_majin/func_809B40D8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Majin2/ac_npc_majin/func_809B40E8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Majin2/ac_npc_majin/func_809B4118_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Majin2/ac_npc_majin/func_809B4200_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Majin2/ac_npc_majin/func_809B423C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Majin2/ac_npc_majin/func_809B4294_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Majin2/ac_npc_majin/func_809B4360_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Majin2/ac_npc_majin/func_809B4394_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Majin2/ac_npc_majin/func_809B43E8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Majin2/ac_npc_majin/func_809B44FC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Majin2/ac_npc_majin/func_809B4594_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Majin2/ac_npc_majin/func_809B4624_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Majin2/ac_npc_majin/func_809B4654_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Majin2/ac_npc_majin/func_809B4694_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Majin2/ac_npc_majin/func_809B4700_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Majin2/ac_npc_majin/func_809B4730_jp.s")
