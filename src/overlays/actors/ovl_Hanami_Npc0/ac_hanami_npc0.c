#include "ac_hanami_npc0.h"
#include "m_lib.h"
#include "m_actor_dlftbls.h"
#include "m_object.h"
#include "overlays/gamestates/ovl_play/m_play.h"
#include "m_demo.h"
#include "macros.h"

#define THIS ((Hanami_Npc0*)thisx)

void aHM0_actor_ct(Actor* thisx, Game_Play* game_play);
void aHM0_actor_dt(Actor* thisx, Game_Play* game_play);
void aHM0_actor_init(Actor* thisx, Game_Play* game_play);
void aHM0_actor_save(Actor* thisx, Game_Play* game_play);
void func_809DE978_jp(Actor* thisx);
void func_809DE948_jp(UNK_TYPE arg0);

#if 0
ActorProfile Hanami_Npc0_Profile = {
    /* */ ACTOR_HANAMI_NPC0,
    /* */ ACTOR_PART_NPC,
    /* */ 0,
    /* */ 0x0000,
    /* */ GAMEPLAY_KEEP,
    /* */ sizeof(Hanami_Npc0),
    /* */ aHM0_actor_ct,
    /* */ aHM0_actor_dt,
    /* */ aHM0_actor_init,
    /* */ (void*)none_proc1,
    /* */ aHM0_actor_save,
};
#endif

extern struct_809AEFA4 aHM0_ct_data;

void aHM0_actor_ct(Actor* thisx, Game_Play* game_play) {
    // TODO: import data
    // static struct_809AEFA4 aHM0_ct_data = {
    //     &aHM0_actor_move,
    //     &aHM0_actor_draw,
    //     4,
    //     &aHM0_talk_request,
    //     &func_809DEA20_jp,
    //     aHM0_talk_end_chk,
    // };
    
    Hanami_Npc0* this = THIS;
    
    if (common_data.clip.unk_040->unk_BC(thisx, game_play) == 1) {
        this->unk7C0 = &func_809DE948_jp;
        common_data.clip.unk_040->unk_C0(thisx, game_play, &aHM0_ct_data);
    }
}

void aHM0_actor_save(Actor *thisx, Game_Play *game_play) {
    common_data.clip.unk_040->unk_C8(thisx, game_play);
}

void aHM0_actor_dt(Actor *thisx, Game_Play *game_play) {
    common_data.clip.unk_040->unk_C4(thisx, game_play);
}

void aHM0_actor_init(Actor* thisx, Game_Play* game_play) {
    common_data.clip.unk_040->unk_CC(thisx, game_play);
}

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Hanami_Npc0/ac_hanami_npc0/func_809DE434_jp.s")

void aHM0_actor_move(void) {
    common_data.clip.unk_040->unk_D0();
}

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Hanami_Npc0/ac_hanami_npc0/func_809DE4A0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Hanami_Npc0/ac_hanami_npc0/func_809DE4C0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Hanami_Npc0/ac_hanami_npc0/func_809DE538_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Hanami_Npc0/ac_hanami_npc0/func_809DE56C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Hanami_Npc0/ac_hanami_npc0/func_809DE5BC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Hanami_Npc0/ac_hanami_npc0/func_809DE5DC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Hanami_Npc0/ac_hanami_npc0/func_809DE6B4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Hanami_Npc0/ac_hanami_npc0/func_809DE6C8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Hanami_Npc0/ac_hanami_npc0/func_809DE6EC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Hanami_Npc0/ac_hanami_npc0/func_809DE714_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Hanami_Npc0/ac_hanami_npc0/func_809DE744_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Hanami_Npc0/ac_hanami_npc0/func_809DE7D0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Hanami_Npc0/ac_hanami_npc0/func_809DE800_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Hanami_Npc0/ac_hanami_npc0/func_809DE830_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Hanami_Npc0/ac_hanami_npc0/func_809DE8D0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Hanami_Npc0/ac_hanami_npc0/func_809DE948_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Hanami_Npc0/ac_hanami_npc0/func_809DE978_jp.s")

void aHM0_talk_request(Actor* thisx, UNK_TYPE arg1 UNUSED) {
    mDemo_Request(7, thisx, func_809DE978_jp);
}

// TODO: Possibly aHM0_talk_init, which exists in map, but type is different from function of same name
// as found in ac_kamakura_npc0.c and ac_npc_engineer.c (both are void)
s32 func_809DEA20_jp(UNK_TYPE arg0 UNUSED, UNK_TYPE arg1 UNUSED) {
    mDemo_Set_ListenAble();
    
    return 1;
}

s32 aHM0_talk_end_chk(Actor* thisx, UNK_TYPE arg1 UNUSED) {
    s32 result = FALSE;
    
    if (!mDemo_Check(7, thisx)) {
        result = TRUE;
    }
    
    return result;
}

void aHM0_actor_draw(void) {
    common_data.clip.unk_040->unk_E4();
}
