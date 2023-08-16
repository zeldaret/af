#include "ac_tunahiki_npc0.h"
#include "m_lib.h"
#include "overlays/gamestates/ovl_play/m_play.h"

void aTNN0_actor_ct(Actor* thisx, PlayState* play);
void aTNN0_actor_dt(Actor* thisx, PlayState* play);
void aTNN0_actor_init(Actor* thisx, PlayState* play);
void aTNN0_actor_save(Actor* thisx, PlayState* play);

#if 0
ActorProfile Tunahiki_Npc0_Profile = {
    /* */ 161,
    /* */ ACTOR_PART_NPC,
    /* */ 0,
    /* */ 53343,
    /* */ 3,
    /* */ sizeof(Tunahiki_Npc0),
    /* */ aTNN0_actor_ct,
    /* */ aTNN0_actor_dt,
    /* */ aTNN0_actor_init,
    /* */ (ActorFunc)none_proc1,
    /* */ aTNN0_actor_save,
};
#endif

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Tunahiki_Npc0/ac_tunahiki_npc0/aTNN0_actor_ct.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Tunahiki_Npc0/ac_tunahiki_npc0/aTNN0_actor_save.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Tunahiki_Npc0/ac_tunahiki_npc0/aTNN0_actor_dt.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Tunahiki_Npc0/ac_tunahiki_npc0/aTNN0_actor_init.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Tunahiki_Npc0/ac_tunahiki_npc0/func_80A91C6C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Tunahiki_Npc0/ac_tunahiki_npc0/func_80A91D08_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Tunahiki_Npc0/ac_tunahiki_npc0/func_80A91D6C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Tunahiki_Npc0/ac_tunahiki_npc0/func_80A91DB4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Tunahiki_Npc0/ac_tunahiki_npc0/func_80A91E4C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Tunahiki_Npc0/ac_tunahiki_npc0/func_80A91E98_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Tunahiki_Npc0/ac_tunahiki_npc0/func_80A91ED8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Tunahiki_Npc0/ac_tunahiki_npc0/func_80A91F54_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Tunahiki_Npc0/ac_tunahiki_npc0/func_80A92088_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Tunahiki_Npc0/ac_tunahiki_npc0/func_80A920C4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Tunahiki_Npc0/ac_tunahiki_npc0/func_80A920FC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Tunahiki_Npc0/ac_tunahiki_npc0/func_80A9215C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Tunahiki_Npc0/ac_tunahiki_npc0/func_80A921FC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Tunahiki_Npc0/ac_tunahiki_npc0/func_80A92244_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Tunahiki_Npc0/ac_tunahiki_npc0/func_80A92284_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Tunahiki_Npc0/ac_tunahiki_npc0/func_80A922F0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Tunahiki_Npc0/ac_tunahiki_npc0/func_80A92338_jp.s")
