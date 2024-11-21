#include "ac_hanami_npc1.h"
#include "m_lib.h"
#include "m_actor_dlftbls.h"
#include "m_object.h"
#include "overlays/gamestates/ovl_play/m_play.h"

#define THIS ((Hanami_Npc1*)thisx)

void aHM1_actor_ct(Actor* thisx, Game_Play* game_play);
void aHM1_actor_dt(Actor* thisx, Game_Play* game_play);
void aHM1_actor_init(Actor* thisx, Game_Play* game_play);
void aHM1_actor_save(Actor* thisx, Game_Play* game_play);
// TODO: below are copy-pasted from ac_hanami_npc0--verify signatures!!
void aHM1_actor_move(void);
void aHM1_schedule_proc(Actor* thisx, Game_Play* game_play, s32 index);
void aHM1_talk_request(Actor* thisx, UNK_TYPE arg1 UNUSED);
s32 aHM1_talk_init(UNK_TYPE arg0 UNUSED, UNK_TYPE arg1 UNUSED);
s32 aHM1_talk_end_chk(Actor* thisx, UNK_TYPE arg1 UNUSED);
void aHM1_actor_draw(Actor* thisx, Game_Play* game_play);

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

extern struct_809AEFA4 aHM1_ct_data;
// TODO: import data
// struct_809AEFA4 aHM1_ct_data = {
//     /* */ aHM1_actor_move,
//     /* */ aHM1_actor_draw,
//     /* */ 4,
//     /* */ aHM1_talk_request,
//     /* */ aHM1_talk_init,
//     /* */ aHM1_talk_end_chk,
//     /* */ NULL,
// };

void aHM1_actor_ct(Actor* thisx, Game_Play* game_play) {
    Hanami_Npc1* this = THIS;

    if (common_data.clip.unk_040->unk_BC(&this->actor, game_play) == 1) {
        this->unk_7C0 = aHM1_schedule_proc;
        common_data.clip.unk_040->unk_C0(&this->actor, game_play, &aHM1_ct_data);
    }
}

void aHM1_actor_save(Actor* thisx, Game_Play* game_play) {
    common_data.clip.unk_040->unk_C8(thisx, game_play);
}

void aHM1_actor_dt(Actor* thisx, Game_Play* game_play) {
    common_data.clip.unk_040->unk_C4(thisx, game_play);
}

void aHM1_actor_init(Actor* thisx, Game_Play* game_play) {
    common_data.clip.unk_040->unk_CC(thisx, game_play);
}

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

// void arguments for both this function and unk_E4 also match,
// but an ActorFunc signature for both seems more plausible.
void aHM1_actor_draw(Actor* thisx, Game_Play* game_play) {
    common_data.clip.unk_040->unk_E4(thisx, game_play);
}
