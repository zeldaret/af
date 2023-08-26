#include "ac_npc_super_master.h"
#include "m_lib.h"
#include "m_actor_dlftbls.h"
#include "m_object.h"
#include "overlays/gamestates/ovl_play/m_play.h"

void aNSPM_actor_ct(Actor* thisx, Game_Play* gamePlay);
void aNSPM_actor_dt(Actor* thisx, Game_Play* gamePlay);
void aNSPM_actor_init(Actor* thisx, Game_Play* gamePlay);
void aNSPM_actor_save(Actor* thisx, Game_Play* gamePlay);

#if 0
ActorProfile Npc_Super_Master_Profile = {
    /* */ ACTOR_NPC_SUPER_MASTER,
    /* */ ACTOR_PART_NPC,
    /* */ 0,
    /* */ 0xD00A,
    /* */ GAMEPLAY_KEEP,
    /* */ sizeof(Npc_Super_Master),
    /* */ aNSPM_actor_ct,
    /* */ aNSPM_actor_dt,
    /* */ aNSPM_actor_init,
    /* */ (ActorFunc)none_proc1,
    /* */ aNSPM_actor_save,
};
#endif

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Super_Master/ac_npc_super_master/aNSPM_actor_ct.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Super_Master/ac_npc_super_master/aNSPM_actor_save.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Super_Master/ac_npc_super_master/aNSPM_actor_dt.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Super_Master/ac_npc_super_master/aNSPM_actor_init.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Super_Master/ac_npc_super_master/func_809CF604_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Super_Master/ac_npc_super_master/func_809CF638_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Super_Master/ac_npc_super_master/func_809CF808_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Super_Master/ac_npc_super_master/func_809CF840_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Super_Master/ac_npc_super_master/func_809CF8D8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Super_Master/ac_npc_super_master/func_809CF99C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Super_Master/ac_npc_super_master/func_809CF9E4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Super_Master/ac_npc_super_master/func_809CFA28_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Super_Master/ac_npc_super_master/func_809CFA64_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Super_Master/ac_npc_super_master/func_809CFA90_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Super_Master/ac_npc_super_master/func_809CFB14_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Super_Master/ac_npc_super_master/func_809CFB3C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Super_Master/ac_npc_super_master/func_809CFBBC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Super_Master/ac_npc_super_master/func_809CFC64_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Super_Master/ac_npc_super_master/func_809CFCC0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Super_Master/ac_npc_super_master/func_809CFCE0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Super_Master/ac_npc_super_master/func_809CFD0C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Super_Master/ac_npc_super_master/func_809CFD38_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Super_Master/ac_npc_super_master/func_809CFD60_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Super_Master/ac_npc_super_master/func_809CFDEC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Super_Master/ac_npc_super_master/func_809CFE28_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Super_Master/ac_npc_super_master/func_809CFE88_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Super_Master/ac_npc_super_master/func_809CFEDC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Super_Master/ac_npc_super_master/func_809CFF24_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Super_Master/ac_npc_super_master/func_809CFF74_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Super_Master/ac_npc_super_master/func_809D0048_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Super_Master/ac_npc_super_master/func_809D0188_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Super_Master/ac_npc_super_master/func_809D0204_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Super_Master/ac_npc_super_master/func_809D0214_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Super_Master/ac_npc_super_master/func_809D02E4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Super_Master/ac_npc_super_master/func_809D03DC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Super_Master/ac_npc_super_master/func_809D0430_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Super_Master/ac_npc_super_master/func_809D04D8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Super_Master/ac_npc_super_master/func_809D05D4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Super_Master/ac_npc_super_master/func_809D0670_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Super_Master/ac_npc_super_master/func_809D06C0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Super_Master/ac_npc_super_master/func_809D0714_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Super_Master/ac_npc_super_master/func_809D0744_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Super_Master/ac_npc_super_master/func_809D0774_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Super_Master/ac_npc_super_master/func_809D07A4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Super_Master/ac_npc_super_master/func_809D08B4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Super_Master/ac_npc_super_master/func_809D08F4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Super_Master/ac_npc_super_master/func_809D0934_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Super_Master/ac_npc_super_master/func_809D09AC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Super_Master/ac_npc_super_master/func_809D09D8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Super_Master/ac_npc_super_master/func_809D0A04_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Super_Master/ac_npc_super_master/func_809D0D24_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Super_Master/ac_npc_super_master/func_809D0F78_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Super_Master/ac_npc_super_master/func_809D0FF0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Super_Master/ac_npc_super_master/func_809D105C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Super_Master/ac_npc_super_master/func_809D11FC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Super_Master/ac_npc_super_master/func_809D123C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Super_Master/ac_npc_super_master/func_809D1294_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Super_Master/ac_npc_super_master/func_809D13D8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Super_Master/ac_npc_super_master/func_809D14D8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Super_Master/ac_npc_super_master/func_809D150C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Super_Master/ac_npc_super_master/func_809D1584_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Super_Master/ac_npc_super_master/func_809D16C0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Super_Master/ac_npc_super_master/func_809D1718_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Super_Master/ac_npc_super_master/func_809D1784_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Super_Master/ac_npc_super_master/func_809D17D0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Super_Master/ac_npc_super_master/func_809D1800_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Super_Master/ac_npc_super_master/func_809D18C8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Super_Master/ac_npc_super_master/func_809D1964_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Super_Master/ac_npc_super_master/func_809D1B8C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Super_Master/ac_npc_super_master/func_809D1C00_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Super_Master/ac_npc_super_master/func_809D1CE8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Super_Master/ac_npc_super_master/func_809D1D7C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Super_Master/ac_npc_super_master/func_809D1E58_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Super_Master/ac_npc_super_master/func_809D1F68_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Super_Master/ac_npc_super_master/func_809D1FB8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Super_Master/ac_npc_super_master/func_809D207C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Super_Master/ac_npc_super_master/func_809D222C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Super_Master/ac_npc_super_master/func_809D22E0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Super_Master/ac_npc_super_master/func_809D24B0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Super_Master/ac_npc_super_master/func_809D2518_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Super_Master/ac_npc_super_master/func_809D2570_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Super_Master/ac_npc_super_master/func_809D25DC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Super_Master/ac_npc_super_master/func_809D2648_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Super_Master/ac_npc_super_master/func_809D26E4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Super_Master/ac_npc_super_master/func_809D2718_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Super_Master/ac_npc_super_master/func_809D27B0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Super_Master/ac_npc_super_master/func_809D2808_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Super_Master/ac_npc_super_master/func_809D287C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Super_Master/ac_npc_super_master/func_809D28A0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Super_Master/ac_npc_super_master/func_809D28C8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Super_Master/ac_npc_super_master/func_809D2900_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Super_Master/ac_npc_super_master/func_809D2930_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Super_Master/ac_npc_super_master/func_809D2968_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Super_Master/ac_npc_super_master/func_809D2998_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Super_Master/ac_npc_super_master/func_809D29C8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Super_Master/ac_npc_super_master/func_809D2A08_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Super_Master/ac_npc_super_master/func_809D2A38_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Super_Master/ac_npc_super_master/func_809D2A68_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Super_Master/ac_npc_super_master/func_809D2B4C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Super_Master/ac_npc_super_master/func_809D2B7C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Super_Master/ac_npc_super_master/func_809D2BBC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Super_Master/ac_npc_super_master/func_809D2BF4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Super_Master/ac_npc_super_master/func_809D2C2C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Super_Master/ac_npc_super_master/func_809D2D14_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Super_Master/ac_npc_super_master/func_809D2D3C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Super_Master/ac_npc_super_master/func_809D2D94_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Super_Master/ac_npc_super_master/func_809D2DD0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Super_Master/ac_npc_super_master/func_809D2DE0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Super_Master/ac_npc_super_master/func_809D2E04_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Super_Master/ac_npc_super_master/func_809D2E34_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Super_Master/ac_npc_super_master/func_809D2E58_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Super_Master/ac_npc_super_master/func_809D2E7C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Super_Master/ac_npc_super_master/func_809D2EA0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Super_Master/ac_npc_super_master/func_809D2EC4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Super_Master/ac_npc_super_master/func_809D2EF4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Super_Master/ac_npc_super_master/func_809D2F24_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Super_Master/ac_npc_super_master/func_809D2F78_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Super_Master/ac_npc_super_master/func_809D302C_jp.s")
