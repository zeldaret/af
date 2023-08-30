#include "ac_kamakura_npc0.h"
#include "m_lib.h"
#include "m_actor_dlftbls.h"
#include "m_object.h"
#include "overlays/gamestates/ovl_play/m_play.h"

void aKM0_actor_ct(Actor* thisx, Game_Play* game_play);
void aKM0_actor_dt(Actor* thisx, Game_Play* game_play);
void aKM0_actor_init(Actor* thisx, Game_Play* game_play);
void aKM0_actor_save(Actor* thisx, Game_Play* game_play);
void func_809DF884_jp(UNK_TYPE arg1, UNK_TYPE arg2);
void func_809DF8B4_jp(UNK_TYPE arg1, UNK_TYPE arg2);
s32 func_809DF8E4_jp(UNK_TYPE arg1, UNK_TYPE arg2);
void func_809DF92C_jp(void);
void func_809DF958_jp(void);

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

struct_809AEFA4 D_809DF9B4_jp = {
    func_809DF92C_jp, func_809DF958_jp, 3, func_809DF884_jp, func_809DF8B4_jp, func_809DF8E4_jp,
};

void aKM0_actor_ct(Actor* thisx, Game_Play* game_play) {
    if (common_data.unk_1004C->unk_BC(thisx, game_play) == 1) {
        common_data.unk_1004C->unk_C0(thisx, game_play, &D_809DF9B4_jp);
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

void func_809DF884_jp(UNK_TYPE arg1, UNK_TYPE arg2) {
    common_data.unk_10078->unk_00(arg1);
}

void func_809DF8B4_jp(UNK_TYPE arg1, UNK_TYPE arg2) {
    common_data.unk_10078->unk_04(arg1);
}

s32 func_809DF8E4_jp(UNK_TYPE arg1, UNK_TYPE arg2) {
    s32 var_v1;
    s32 sp1C;

    sp1C = 0;
    var_v1 = sp1C;
    if (common_data.unk_10078->unk_08(arg1) == 1) {
        var_v1 = 1;
    }
    return var_v1;
}

void func_809DF92C_jp(void) {
    common_data.unk_1004C->unk_D0();
}

void func_809DF958_jp(void) {
    common_data.unk_1004C->unk_E4();
}
