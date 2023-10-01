#include "ac_kamakura_npc0.h"
#include "m_lib.h"
#include "m_actor_dlftbls.h"
#include "m_object.h"
#include "overlays/gamestates/ovl_play/m_play.h"

void aKM0_actor_ct(Actor* thisx, Game_Play* game_play);
void aKM0_actor_dt(Actor* thisx, Game_Play* game_play);
void aKM0_actor_init(Actor* thisx, Game_Play* game_play);
void aKM0_actor_save(Actor* thisx, Game_Play* game_play);
void aKM0_talk_request(UNK_TYPE arg0, UNK_TYPE arg1);
void aKM0_talk_init(UNK_TYPE arg0, UNK_TYPE arg1);
s32 aKM0_talk_end_chk(UNK_TYPE arg0, UNK_TYPE arg1);
void aKM0_actor_move(void);
void aKM0_actor_draw(void);

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
    /* */ (void*)none_proc1,
    /* */ aKM0_actor_save,
};

struct_809AEFA4 aKM0_ct_data = {
    aKM0_actor_move, aKM0_actor_draw, 3, aKM0_talk_request, aKM0_talk_init, aKM0_talk_end_chk,
};

void aKM0_actor_ct(Actor* thisx, Game_Play* game_play) {
    if (common_data.unk_1004C->unk_BC(thisx, game_play) == 1) {
        common_data.unk_1004C->unk_C0(thisx, game_play, &aKM0_ct_data);
        common_data.unk_1004C->unk_118(thisx);
    }
}

void aKM0_actor_save(Actor* thisx, Game_Play* game_play) {
    common_data.unk_1004C->unk_C8(thisx, game_play);
}

void aKM0_actor_dt(Actor* thisx, Game_Play* game_play) {
    common_data.unk_1004C->unk_C4(thisx, game_play);
}

void aKM0_actor_init(Actor* thisx, Game_Play* game_play) {
    common_data.unk_1004C->unk_CC(thisx, game_play);
}

void aKM0_talk_request(UNK_TYPE arg0, UNK_TYPE arg1 UNUSED) {
    common_data.unk_10078->unk_00(arg0);
}

void aKM0_talk_init(UNK_TYPE arg0, UNK_TYPE arg1 UNUSED) {
    common_data.unk_10078->unk_04(arg0);
}

s32 aKM0_talk_end_chk(UNK_TYPE arg0, UNK_TYPE arg1 UNUSED) {
    s32 var_v1;

    var_v1 = false;
    if (common_data.unk_10078->unk_08(arg0) == 1) {
        var_v1 = true;
    }
    return var_v1;
}

void aKM0_actor_move(void) {
    common_data.unk_1004C->unk_D0();
}

void aKM0_actor_draw(void) {
    common_data.unk_1004C->unk_E4();
}
