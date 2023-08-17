#include "ac_kamakura_npc0.h"
#include "m_lib.h"
#include "overlays/gamestates/ovl_play/m_play.h"

void aKM0_actor_ct(Actor* thisx, Game_Play* game_play);
void aKM0_actor_dt(Actor* thisx, Game_Play* game_play);
void aKM0_actor_init(Actor* thisx, Game_Play* game_play);
void aKM0_actor_save(Actor* thisx, Game_Play* game_play);

#if 0
ActorProfile Kamakura_Npc0_Profile = {
    /* */ ACTOR_KAMAKURA_NPC0,
    /* */ ACTOR_PART_NPC,
    /* */ 0,
    /* */ 0x0000,
    /* */ GAMEPLAY_KEEP,
    /* */ sizeof(Kamakura_Npc0),
    /* */ aKM0_actor_ct,
    /* */ aKM0_actor_dt,
    /* */ aKM0_actor_init,
    /* */ (ActorFunc)none_proc1,
    /* */ aKM0_actor_save,
};
#endif

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Kamakura_Npc0/ac_kamakura_npc0/aKM0_actor_ct.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Kamakura_Npc0/ac_kamakura_npc0/aKM0_actor_save.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Kamakura_Npc0/ac_kamakura_npc0/aKM0_actor_dt.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Kamakura_Npc0/ac_kamakura_npc0/aKM0_actor_init.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Kamakura_Npc0/ac_kamakura_npc0/func_809DF884_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Kamakura_Npc0/ac_kamakura_npc0/func_809DF8B4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Kamakura_Npc0/ac_kamakura_npc0/func_809DF8E4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Kamakura_Npc0/ac_kamakura_npc0/func_809DF92C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Kamakura_Npc0/ac_kamakura_npc0/func_809DF958_jp.s")
