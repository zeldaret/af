#include "ac_npc_station_master.h"
#include "m_lib.h"
#include "overlays/gamestates/ovl_play/m_play.h"

void aSTM_actor_ct(Actor* thisx, PlayState* play);
void aSTM_actor_dt(Actor* thisx, PlayState* play);
void aSTM_actor_init(Actor* thisx, PlayState* play);
void aSTM_actor_save(Actor* thisx, PlayState* play);

#if 0
ActorProfile Npc_Station_Master_Profile = {
    /* */ ACTOR_NPC_STATION_MASTER,
    /* */ ACTOR_PART_NPC,
    /* */ 0,
    /* */ 0xD00E,
    /* */ GAMEPLAY_KEEP,
    /* */ sizeof(Npc_Station_Master),
    /* */ aSTM_actor_ct,
    /* */ aSTM_actor_dt,
    /* */ aSTM_actor_init,
    /* */ (ActorFunc)none_proc1,
    /* */ aSTM_actor_save,
};
#endif

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Station_Master/ac_npc_station_master/aSTM_actor_ct.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Station_Master/ac_npc_station_master/aSTM_actor_save.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Station_Master/ac_npc_station_master/aSTM_actor_dt.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Station_Master/ac_npc_station_master/aSTM_actor_init.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Station_Master/ac_npc_station_master/func_809D4320_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Station_Master/ac_npc_station_master/func_809D43BC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Station_Master/ac_npc_station_master/func_809D43E8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Station_Master/ac_npc_station_master/func_809D4400_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Station_Master/ac_npc_station_master/func_809D44BC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Station_Master/ac_npc_station_master/func_809D44F0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Station_Master/ac_npc_station_master/func_809D4570_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Station_Master/ac_npc_station_master/func_809D45A4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Station_Master/ac_npc_station_master/func_809D4618_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Station_Master/ac_npc_station_master/func_809D46CC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Station_Master/ac_npc_station_master/func_809D4738_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Station_Master/ac_npc_station_master/func_809D47C4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Station_Master/ac_npc_station_master/func_809D4878_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Station_Master/ac_npc_station_master/func_809D48A8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Station_Master/ac_npc_station_master/func_809D49D8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Station_Master/ac_npc_station_master/func_809D49F8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Station_Master/ac_npc_station_master/func_809D4A20_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Station_Master/ac_npc_station_master/func_809D4A94_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Station_Master/ac_npc_station_master/func_809D4B44_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Station_Master/ac_npc_station_master/func_809D4BC4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Station_Master/ac_npc_station_master/func_809D4C24_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Station_Master/ac_npc_station_master/func_809D4C44_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Station_Master/ac_npc_station_master/func_809D4CD4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Station_Master/ac_npc_station_master/func_809D4D84_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Station_Master/ac_npc_station_master/func_809D4DD4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Station_Master/ac_npc_station_master/func_809D4E40_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Station_Master/ac_npc_station_master/func_809D4E94_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Station_Master/ac_npc_station_master/func_809D4F7C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Station_Master/ac_npc_station_master/func_809D4FC4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Station_Master/ac_npc_station_master/func_809D5010_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Station_Master/ac_npc_station_master/func_809D507C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Station_Master/ac_npc_station_master/func_809D50F8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Station_Master/ac_npc_station_master/func_809D5110_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Station_Master/ac_npc_station_master/func_809D5130_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Station_Master/ac_npc_station_master/func_809D51C4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Station_Master/ac_npc_station_master/func_809D522C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Station_Master/ac_npc_station_master/func_809D526C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Station_Master/ac_npc_station_master/func_809D52B0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Station_Master/ac_npc_station_master/func_809D533C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Station_Master/ac_npc_station_master/func_809D536C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Station_Master/ac_npc_station_master/func_809D53AC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Station_Master/ac_npc_station_master/func_809D5418_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Station_Master/ac_npc_station_master/func_809D5448_jp.s")
