#include "ac_npc_engineer.h"
#include "m_lib.h"
#include "m_actor_dlftbls.h"
#include "m_object.h"
#include "overlays/gamestates/ovl_play/m_play.h"
#include "include/unknown_structs.h"

void aNEG_actor_ct(Actor* thisx, Game_Play* game_play);
void aNEG_actor_dt(Actor* thisx, Game_Play* game_play);
void aNEG_actor_init(Actor* thisx, Game_Play* game_play);
void aNEG_actor_save(Actor* thisx, Game_Play* game_play);
void aNEG_actor_move(void);
void aNEG_actor_draw(void);

ActorProfile Npc_Engineer_Profile = {
    /* */ ACTOR_NPC_ENGINEER,
    /* */ ACTOR_PART_NPC,
    /* */ ACTOR_FLAG_10 | ACTOR_FLAG_20000000,
    /* */ 0x0000,
    /* */ GAMEPLAY_KEEP,
    /* */ sizeof(Npc_Engineer),
    /* */ aNEG_actor_ct,
    /* */ aNEG_actor_dt,
    /* */ aNEG_actor_init,
    /* */ (void*)none_proc1,
    /* */ aNEG_actor_save,
};

struct_809AEFA4 aNEG_ct_data = {
    aNEG_actor_move, aNEG_actor_draw, 4, NULL, NULL, NULL,
};

void aNEG_actor_ct(Actor* thisx, Game_Play* game_play) {
    Npc_Engineer* this = (Npc_Engineer*)thisx;

    if (common_data.unk_1004C->unk_BC(thisx, game_play) == 1) {
        this->unk7C0 = none_proc1;
        common_data.unk_1004C->unk_C0(thisx, game_play, &aNEG_ct_data);
        this->unk80C = -1;
        this->unk7FD = 0;
        this->unk8AC = -1;
        this->actor.colStatus.mass = MASS_HEAVY;
        this->actor.shape.rot.y = 0x4000;
        this->actor.world.rot.y = 0x4000;
        this->unk8DC = 0x4000;
        this->unk7D4 = 4;
        this->unk7D5 = 0;
        this->unk7D6 = 0;
    }
}

void aNEG_actor_save(Actor* thisx, Game_Play* game_play) {
    common_data.unk_1004C->unk_C8(thisx, game_play);
}

void aNEG_actor_dt(Actor* thisx, Game_Play* game_play) {
    common_data.unk_1004C->unk_C4(thisx, game_play);
}

void aNEG_actor_init(Actor* thisx, Game_Play* game_play) {
    common_data.unk_1004C->unk_CC(thisx, game_play);
}

void aNEG_actor_move(void) {
    common_data.unk_1004C->unk_D0();
}

void aNEG_actor_draw(void) {
    common_data.unk_1004C->unk_E4();
}
