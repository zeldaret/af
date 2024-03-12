#include "ac_normal_npc.h"
#include "m_lib.h"
#include "m_actor_dlftbls.h"
#include "m_object.h"
#include "overlays/gamestates/ovl_play/m_play.h"

void aNOR_actor_ct(Actor* thisx, Game_Play* game_play);
void aNOR_actor_dt(Actor* thisx, Game_Play* game_play);
void aNOR_actor_init(Actor* thisx, Game_Play* game_play);
void aNOR_actor_save(Actor* thisx, Game_Play* game_play);
void aNOR_actor_move(void);
void aNOR_actor_draw(void);

ActorProfile Normal_Npc_Profile = {
    /* */ ACTOR_NORMAL_NPC,
    /* */ ACTOR_PART_NPC,
    /* */ 0,
    /* */ 0x0000,
    /* */ GAMEPLAY_KEEP,
    /* */ sizeof(Normal_Npc),
    /* */ aNOR_actor_ct,
    /* */ aNOR_actor_dt,
    /* */ aNOR_actor_init,
    /* */ (void*)none_proc1,
    /* */ aNOR_actor_save,
};

struct_809AEFA4 aNOR_ct_data = {
    aNOR_actor_move, aNOR_actor_draw, 1, NULL, NULL, NULL,
};

void aNOR_actor_ct(Actor* thisx, Game_Play* game_play) {
    if (common_data.clip.unk_040->unk_BC(thisx, game_play) == 1) {
        common_data.clip.unk_040->unk_C0(thisx, game_play, &aNOR_ct_data);
    }
}

void aNOR_actor_dt(Actor* thisx, Game_Play* game_play) {
    common_data.clip.unk_040->unk_C4(thisx, game_play);
}

void aNOR_actor_save(Actor* thisx, Game_Play* game_play) {
    common_data.clip.unk_040->unk_C8(thisx, game_play);
}

void aNOR_actor_init(Actor* thisx, Game_Play* game_play) {
    common_data.clip.unk_040->unk_CC(thisx, game_play);
}

void aNOR_actor_move(void) {
    common_data.clip.unk_040->unk_D0();
}

void aNOR_actor_draw(void) {
    common_data.clip.unk_040->unk_E4();
}
