#include "ac_npc_totakeke.h"
#include "m_lib.h"
#include "overlays/gamestates/ovl_play/m_play.h"

void aNTT_actor_ct(Actor* thisx, PlayState* play);
void aNTT_actor_dt(Actor* thisx, PlayState* play);
void aNTT_actor_init(Actor* thisx, PlayState* play);
void aNTT_actor_save(Actor* thisx, PlayState* play);

#if 0
ActorProfile Npc_Totakeke_Profile = {
    /* */ 153,
    /* */ ACTOR_PART_NPC,
    /* */ 0,
    /* */ 53341,
    /* */ 3,
    /* */ sizeof(Npc_Totakeke),
    /* */ aNTT_actor_ct,
    /* */ aNTT_actor_dt,
    /* */ aNTT_actor_init,
    /* */ (ActorFunc)none_proc1,
    /* */ aNTT_actor_save,
};
#endif

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Totakeke/ac_npc_totakeke/aNTT_actor_ct.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Totakeke/ac_npc_totakeke/aNTT_actor_save.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Totakeke/ac_npc_totakeke/aNTT_actor_dt.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Totakeke/ac_npc_totakeke/aNTT_actor_init.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Totakeke/ac_npc_totakeke/func_80A89C54_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Totakeke/ac_npc_totakeke/func_80A89CA0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Totakeke/ac_npc_totakeke/func_80A89D14_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Totakeke/ac_npc_totakeke/func_80A89D70_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Totakeke/ac_npc_totakeke/func_80A89D8C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Totakeke/ac_npc_totakeke/func_80A89E3C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Totakeke/ac_npc_totakeke/func_80A89F60_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Totakeke/ac_npc_totakeke/func_80A8A0D4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Totakeke/ac_npc_totakeke/func_80A8A1A4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Totakeke/ac_npc_totakeke/func_80A8A228_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Totakeke/ac_npc_totakeke/func_80A8A370_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Totakeke/ac_npc_totakeke/func_80A8A3EC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Totakeke/ac_npc_totakeke/func_80A8A444_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Totakeke/ac_npc_totakeke/func_80A8A4CC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Totakeke/ac_npc_totakeke/func_80A8A518_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Totakeke/ac_npc_totakeke/func_80A8A58C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Totakeke/ac_npc_totakeke/func_80A8A5D8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Totakeke/ac_npc_totakeke/func_80A8A644_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Totakeke/ac_npc_totakeke/func_80A8A6DC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Totakeke/ac_npc_totakeke/func_80A8A7B0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Totakeke/ac_npc_totakeke/func_80A8A834_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Totakeke/ac_npc_totakeke/func_80A8A900_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Totakeke/ac_npc_totakeke/func_80A8AB48_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Totakeke/ac_npc_totakeke/func_80A8ACA4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Totakeke/ac_npc_totakeke/func_80A8AD34_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Totakeke/ac_npc_totakeke/func_80A8AD68_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Totakeke/ac_npc_totakeke/func_80A8AD94_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Totakeke/ac_npc_totakeke/func_80A8AE2C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Totakeke/ac_npc_totakeke/func_80A8AE74_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Totakeke/ac_npc_totakeke/func_80A8AEB4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Totakeke/ac_npc_totakeke/func_80A8AF20_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Totakeke/ac_npc_totakeke/func_80A8AF68_jp.s")
