#include "ac_tunahiki_npc1.h"
#include "m_lib.h"
#include "m_actor_dlftbls.h"
#include "m_object.h"
#include "overlays/gamestates/ovl_play/m_play.h"

void aTNN1_actor_ct(Actor* thisx, Game_Play* game_play);
void aTNN1_actor_dt(Actor* thisx, Game_Play* game_play);
void aTNN1_actor_init(Actor* thisx, Game_Play* game_play);
void aTNN1_actor_save(Actor* thisx, Game_Play* game_play);

#if 0
ActorProfile Tunahiki_Npc1_Profile = {
    /* */ ACTOR_TUNAHIKI_NPC1,
    /* */ ACTOR_PART_NPC,
    /* */ 0,
    /* */ 0xD060,
    /* */ GAMEPLAY_KEEP,
    /* */ sizeof(Tunahiki_Npc1),
    /* */ aTNN1_actor_ct,
    /* */ aTNN1_actor_dt,
    /* */ aTNN1_actor_init,
    /* */ (ActorFunc)none_proc1,
    /* */ aTNN1_actor_save,
};
#endif

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Tunahiki_Npc1/ac_tunahiki_npc1/aTNN1_actor_ct.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Tunahiki_Npc1/ac_tunahiki_npc1/aTNN1_actor_save.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Tunahiki_Npc1/ac_tunahiki_npc1/aTNN1_actor_dt.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Tunahiki_Npc1/ac_tunahiki_npc1/aTNN1_actor_init.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Tunahiki_Npc1/ac_tunahiki_npc1/func_80A92670_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Tunahiki_Npc1/ac_tunahiki_npc1/func_80A9270C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Tunahiki_Npc1/ac_tunahiki_npc1/func_80A927A0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Tunahiki_Npc1/ac_tunahiki_npc1/func_80A92838_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Tunahiki_Npc1/ac_tunahiki_npc1/func_80A92884_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Tunahiki_Npc1/ac_tunahiki_npc1/func_80A92924_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Tunahiki_Npc1/ac_tunahiki_npc1/func_80A929FC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Tunahiki_Npc1/ac_tunahiki_npc1/func_80A92AC4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Tunahiki_Npc1/ac_tunahiki_npc1/func_80A92E20_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Tunahiki_Npc1/ac_tunahiki_npc1/func_80A92E98_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Tunahiki_Npc1/ac_tunahiki_npc1/func_80A92F00_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Tunahiki_Npc1/ac_tunahiki_npc1/func_80A9306C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Tunahiki_Npc1/ac_tunahiki_npc1/func_80A930A4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Tunahiki_Npc1/ac_tunahiki_npc1/func_80A93144_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Tunahiki_Npc1/ac_tunahiki_npc1/func_80A93164_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Tunahiki_Npc1/ac_tunahiki_npc1/func_80A93184_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Tunahiki_Npc1/ac_tunahiki_npc1/func_80A931A4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Tunahiki_Npc1/ac_tunahiki_npc1/func_80A93244_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Tunahiki_Npc1/ac_tunahiki_npc1/func_80A9328C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Tunahiki_Npc1/ac_tunahiki_npc1/func_80A932CC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Tunahiki_Npc1/ac_tunahiki_npc1/func_80A93338_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Tunahiki_Npc1/ac_tunahiki_npc1/func_80A93380_jp.s")
