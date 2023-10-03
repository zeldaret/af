#include "ac_npc_sleep_obaba.h"
#include "m_lib.h"
#include "m_actor_dlftbls.h"
#include "m_object.h"
#include "overlays/gamestates/ovl_play/m_play.h"

void aNSO_actor_ct(Actor* thisx, Game_Play* game_play);
void aNSO_actor_dt(Actor* thisx, Game_Play* game_play);
void aNSO_actor_init(Actor* thisx, Game_Play* game_play);
void aNSO_actor_save(Actor* thisx, Game_Play* game_play);

#if 0
ActorProfile Npc_Sleep_Obaba_Profile = {
    /* */ ACTORNPC_SLEEP_OBABA,
    /* */ ACTOR_PART_NPC,
    /* */ 0,
    /* */ 0xD038,
    /* */ GAMEPLAY_KEEP,
    /* */ sizeof(Npc_Sleep_Obaba),
    /* */ aNSO_actor_ct,
    /* */ aNSO_actor_dt,
    /* */ aNSO_actor_init,
    /* */ (void*)none_proc1,
    /* */ aNSO_actor_save,
};
#endif

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Sleep_Obaba/ac_npc_sleep_obaba/aNSO_actor_ct.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Sleep_Obaba/ac_npc_sleep_obaba/aNSO_actor_save.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Sleep_Obaba/ac_npc_sleep_obaba/aNSO_actor_dt.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Sleep_Obaba/ac_npc_sleep_obaba/aNSO_actor_init.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Sleep_Obaba/ac_npc_sleep_obaba/func_809CEFE4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Sleep_Obaba/ac_npc_sleep_obaba/func_809CF024_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Sleep_Obaba/ac_npc_sleep_obaba/func_809CF058_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Sleep_Obaba/ac_npc_sleep_obaba/func_809CF078_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Sleep_Obaba/ac_npc_sleep_obaba/func_809CF0AC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Sleep_Obaba/ac_npc_sleep_obaba/func_809CF0CC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Sleep_Obaba/ac_npc_sleep_obaba/func_809CF138_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Sleep_Obaba/ac_npc_sleep_obaba/func_809CF14C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Sleep_Obaba/ac_npc_sleep_obaba/func_809CF170_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Sleep_Obaba/ac_npc_sleep_obaba/func_809CF198_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Sleep_Obaba/ac_npc_sleep_obaba/func_809CF1C8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Sleep_Obaba/ac_npc_sleep_obaba/func_809CF240_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Sleep_Obaba/ac_npc_sleep_obaba/func_809CF270_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Sleep_Obaba/ac_npc_sleep_obaba/func_809CF2A0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Sleep_Obaba/ac_npc_sleep_obaba/func_809CF2E4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Sleep_Obaba/ac_npc_sleep_obaba/func_809CF350_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Sleep_Obaba/ac_npc_sleep_obaba/func_809CF380_jp.s")
