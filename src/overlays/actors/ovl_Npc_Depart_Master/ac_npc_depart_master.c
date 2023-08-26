#include "ac_npc_depart_master.h"
#include "m_lib.h"
#include "m_actor_dlftbls.h"
#include "m_object.h"
#include "overlays/gamestates/ovl_play/m_play.h"

void aNDM_actor_ct(Actor* thisx, Game_Play* gamePlay);
void aNDM_actor_dt(Actor* thisx, Game_Play* gamePlay);
void aNDM_actor_init(Actor* thisx, Game_Play* gamePlay);
void aNDM_actor_save(Actor* thisx, Game_Play* gamePlay);

#if 0
ActorProfile Npc_Depart_Master_Profile = {
    /* */ ACTOR_NPC_DEPART_MASTER,
    /* */ ACTOR_PART_NPC,
    /* */ 0,
    /* */ 0xD00B,
    /* */ GAMEPLAY_KEEP,
    /* */ sizeof(Npc_Depart_Master),
    /* */ aNDM_actor_ct,
    /* */ aNDM_actor_dt,
    /* */ aNDM_actor_init,
    /* */ (ActorFunc)none_proc1,
    /* */ aNDM_actor_save,
};
#endif

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Depart_Master/ac_npc_depart_master/aNDM_actor_ct.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Depart_Master/ac_npc_depart_master/aNDM_actor_save.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Depart_Master/ac_npc_depart_master/aNDM_actor_dt.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Depart_Master/ac_npc_depart_master/aNDM_actor_init.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Depart_Master/ac_npc_depart_master/func_809AA65C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Depart_Master/ac_npc_depart_master/func_809AA690_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Depart_Master/ac_npc_depart_master/func_809AA734_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Depart_Master/ac_npc_depart_master/func_809AA764_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Depart_Master/ac_npc_depart_master/func_809AA7FC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Depart_Master/ac_npc_depart_master/func_809AA8C0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Depart_Master/ac_npc_depart_master/func_809AA928_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Depart_Master/ac_npc_depart_master/func_809AA96C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Depart_Master/ac_npc_depart_master/func_809AA9A8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Depart_Master/ac_npc_depart_master/func_809AA9D4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Depart_Master/ac_npc_depart_master/func_809AAA58_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Depart_Master/ac_npc_depart_master/func_809AAA80_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Depart_Master/ac_npc_depart_master/func_809AAB00_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Depart_Master/ac_npc_depart_master/func_809AABA8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Depart_Master/ac_npc_depart_master/func_809AAC04_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Depart_Master/ac_npc_depart_master/func_809AAC24_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Depart_Master/ac_npc_depart_master/func_809AAC50_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Depart_Master/ac_npc_depart_master/func_809AAC7C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Depart_Master/ac_npc_depart_master/func_809AACA4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Depart_Master/ac_npc_depart_master/func_809AAD30_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Depart_Master/ac_npc_depart_master/func_809AAD6C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Depart_Master/ac_npc_depart_master/func_809AADCC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Depart_Master/ac_npc_depart_master/func_809AAE20_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Depart_Master/ac_npc_depart_master/func_809AAE68_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Depart_Master/ac_npc_depart_master/func_809AAEB8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Depart_Master/ac_npc_depart_master/func_809AAF8C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Depart_Master/ac_npc_depart_master/func_809AB0CC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Depart_Master/ac_npc_depart_master/func_809AB148_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Depart_Master/ac_npc_depart_master/func_809AB158_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Depart_Master/ac_npc_depart_master/func_809AB228_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Depart_Master/ac_npc_depart_master/func_809AB320_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Depart_Master/ac_npc_depart_master/func_809AB374_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Depart_Master/ac_npc_depart_master/func_809AB41C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Depart_Master/ac_npc_depart_master/func_809AB518_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Depart_Master/ac_npc_depart_master/func_809AB5B4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Depart_Master/ac_npc_depart_master/func_809AB604_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Depart_Master/ac_npc_depart_master/func_809AB658_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Depart_Master/ac_npc_depart_master/func_809AB688_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Depart_Master/ac_npc_depart_master/func_809AB6B8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Depart_Master/ac_npc_depart_master/func_809AB6E8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Depart_Master/ac_npc_depart_master/func_809AB7F8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Depart_Master/ac_npc_depart_master/func_809AB838_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Depart_Master/ac_npc_depart_master/func_809AB878_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Depart_Master/ac_npc_depart_master/func_809AB8F0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Depart_Master/ac_npc_depart_master/func_809AB91C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Depart_Master/ac_npc_depart_master/func_809AB948_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Depart_Master/ac_npc_depart_master/func_809ABC68_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Depart_Master/ac_npc_depart_master/func_809ABEBC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Depart_Master/ac_npc_depart_master/func_809ABF34_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Depart_Master/ac_npc_depart_master/func_809ABFA0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Depart_Master/ac_npc_depart_master/func_809AC140_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Depart_Master/ac_npc_depart_master/func_809AC180_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Depart_Master/ac_npc_depart_master/func_809AC1D8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Depart_Master/ac_npc_depart_master/func_809AC31C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Depart_Master/ac_npc_depart_master/func_809AC41C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Depart_Master/ac_npc_depart_master/func_809AC450_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Depart_Master/ac_npc_depart_master/func_809AC4C8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Depart_Master/ac_npc_depart_master/func_809AC604_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Depart_Master/ac_npc_depart_master/func_809AC65C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Depart_Master/ac_npc_depart_master/func_809AC6C8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Depart_Master/ac_npc_depart_master/func_809AC714_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Depart_Master/ac_npc_depart_master/func_809AC744_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Depart_Master/ac_npc_depart_master/func_809AC80C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Depart_Master/ac_npc_depart_master/func_809AC8A8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Depart_Master/ac_npc_depart_master/func_809ACAD0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Depart_Master/ac_npc_depart_master/func_809ACB44_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Depart_Master/ac_npc_depart_master/func_809ACC2C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Depart_Master/ac_npc_depart_master/func_809ACCC0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Depart_Master/ac_npc_depart_master/func_809ACD9C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Depart_Master/ac_npc_depart_master/func_809ACEAC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Depart_Master/ac_npc_depart_master/func_809ACEFC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Depart_Master/ac_npc_depart_master/func_809ACFC0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Depart_Master/ac_npc_depart_master/func_809AD170_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Depart_Master/ac_npc_depart_master/func_809AD224_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Depart_Master/ac_npc_depart_master/func_809AD3F4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Depart_Master/ac_npc_depart_master/func_809AD45C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Depart_Master/ac_npc_depart_master/func_809AD4B4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Depart_Master/ac_npc_depart_master/func_809AD520_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Depart_Master/ac_npc_depart_master/func_809AD58C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Depart_Master/ac_npc_depart_master/func_809AD628_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Depart_Master/ac_npc_depart_master/func_809AD65C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Depart_Master/ac_npc_depart_master/func_809AD6F4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Depart_Master/ac_npc_depart_master/func_809AD74C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Depart_Master/ac_npc_depart_master/func_809AD7C0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Depart_Master/ac_npc_depart_master/func_809AD7E4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Depart_Master/ac_npc_depart_master/func_809AD80C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Depart_Master/ac_npc_depart_master/func_809AD844_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Depart_Master/ac_npc_depart_master/func_809AD874_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Depart_Master/ac_npc_depart_master/func_809AD8AC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Depart_Master/ac_npc_depart_master/func_809AD8DC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Depart_Master/ac_npc_depart_master/func_809AD90C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Depart_Master/ac_npc_depart_master/func_809AD94C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Depart_Master/ac_npc_depart_master/func_809AD97C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Depart_Master/ac_npc_depart_master/func_809AD9AC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Depart_Master/ac_npc_depart_master/func_809ADA90_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Depart_Master/ac_npc_depart_master/func_809ADAC0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Depart_Master/ac_npc_depart_master/func_809ADB00_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Depart_Master/ac_npc_depart_master/func_809ADB38_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Depart_Master/ac_npc_depart_master/func_809ADB70_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Depart_Master/ac_npc_depart_master/func_809ADC58_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Depart_Master/ac_npc_depart_master/func_809ADC80_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Depart_Master/ac_npc_depart_master/func_809ADCD8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Depart_Master/ac_npc_depart_master/func_809ADD14_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Depart_Master/ac_npc_depart_master/func_809ADD24_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Depart_Master/ac_npc_depart_master/func_809ADD48_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Depart_Master/ac_npc_depart_master/func_809ADD78_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Depart_Master/ac_npc_depart_master/func_809ADD9C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Depart_Master/ac_npc_depart_master/func_809ADDC0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Depart_Master/ac_npc_depart_master/func_809ADDE4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Depart_Master/ac_npc_depart_master/func_809ADE08_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Depart_Master/ac_npc_depart_master/func_809ADE38_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Depart_Master/ac_npc_depart_master/func_809ADE68_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Depart_Master/ac_npc_depart_master/func_809ADEBC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Depart_Master/ac_npc_depart_master/func_809ADF90_jp.s")
