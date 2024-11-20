#include "ac_hanami_npc1.h"
#include "m_lib.h"
#include "m_actor_dlftbls.h"
#include "m_object.h"
#include "overlays/gamestates/ovl_play/m_play.h"

void aHM1_actor_ct(Actor* thisx, Game_Play* game_play);
void aHM1_actor_dt(Actor* thisx, Game_Play* game_play);
void aHM1_actor_init(Actor* thisx, Game_Play* game_play);
void aHM1_actor_save(Actor* thisx, Game_Play* game_play);

#if 0
ActorProfile Hanami_Npc1_Profile = {
    /* */ ACTOR_HANAMI_NPC1,
    /* */ ACTOR_PART_NPC,
    /* */ 0,
    /* */ 0x0000,
    /* */ GAMEPLAY_KEEP,
    /* */ sizeof(Hanami_Npc1),
    /* */ aHM1_actor_ct,
    /* */ aHM1_actor_dt,
    /* */ aHM1_actor_init,
    /* */ (void*)none_proc1,
    /* */ aHM1_actor_save,
};
#endif

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Hanami_Npc1/ac_hanami_npc1/aHM1_actor_ct.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Hanami_Npc1/ac_hanami_npc1/aHM1_actor_save.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Hanami_Npc1/ac_hanami_npc1/aHM1_actor_dt.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Hanami_Npc1/ac_hanami_npc1/aHM1_actor_init.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Hanami_Npc1/ac_hanami_npc1/aHM1_set_animation.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Hanami_Npc1/ac_hanami_npc1/aHM1_actor_move.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Hanami_Npc1/ac_hanami_npc1/aHM1_set_request_act.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Hanami_Npc1/ac_hanami_npc1/aHM1_check_moveRange.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Hanami_Npc1/ac_hanami_npc1/aHM1_check_inBlock.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Hanami_Npc1/ac_hanami_npc1/aHM1_revise_moveRange.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Hanami_Npc1/ac_hanami_npc1/aHM1_turn.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Hanami_Npc1/ac_hanami_npc1/aHM1_walk.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Hanami_Npc1/ac_hanami_npc1/aHM1_set_spd_info.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Hanami_Npc1/ac_hanami_npc1/aHM1_setupAction.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Hanami_Npc1/ac_hanami_npc1/aHM1_act_chg_data_proc.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Hanami_Npc1/ac_hanami_npc1/aHM1_act_init_proc.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Hanami_Npc1/ac_hanami_npc1/aHM1_act_main_proc.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Hanami_Npc1/ac_hanami_npc1/aHM1_act_proc.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Hanami_Npc1/ac_hanami_npc1/aHM1_think_main_proc.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Hanami_Npc1/ac_hanami_npc1/aHM1_think_init_proc.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Hanami_Npc1/ac_hanami_npc1/aHM1_think_proc.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Hanami_Npc1/ac_hanami_npc1/aHM1_schedule_init_proc.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Hanami_Npc1/ac_hanami_npc1/aHM1_schedule_main_proc.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Hanami_Npc1/ac_hanami_npc1/aHM1_schedule_proc.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Hanami_Npc1/ac_hanami_npc1/aHM1_set_talk_info.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Hanami_Npc1/ac_hanami_npc1/aHM1_talk_request.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Hanami_Npc1/ac_hanami_npc1/aHM1_talk_init.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Hanami_Npc1/ac_hanami_npc1/aHM1_talk_end_chk.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Hanami_Npc1/ac_hanami_npc1/aHM1_actor_draw.s")
