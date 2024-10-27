#include "ac_boxTrick01.h"
#include "m_lib.h"
#include "m_actor_dlftbls.h"
#include "m_object.h"
#include "overlays/gamestates/ovl_play/m_play.h"
#include "m_common_data.h"
#include "m_field_info.h"

void BoxTrick01_Actor_ct(Actor* actor, Game_Play* game_play);
void BoxTrick01_Actor_dt(Actor* actor, Game_Play* game_play);
void BoxTrick01_Actor_move(Actor* thisx, Game_Play* game_play);

ActorProfile BoxTrick01_Profile = {
    /* */ ACTOR_BOX_TRICK_01,
    /* */ ACTOR_PART_4,
    /* */ ACTOR_FLAG_10 | ACTOR_FLAG_20,
    /* */ 0x8004,
    /* */ GAMEPLAY_KEEP,
    /* */ sizeof(BoxTrick01),
    /* */ BoxTrick01_Actor_ct,
    /* */ BoxTrick01_Actor_dt,
    /* */ BoxTrick01_Actor_move,
    /* */ (void*)none_proc1,
    /* */ NULL,
};

void func_80973160_jp(void* data, Actor* actor) {
    Clip_BoxTrickData* clip;
    s32 i;
    s32 blockX;
    s32 blockZ;

    mFI_Wpos2BlockNum(&blockX, &blockZ, actor->world.pos);

    clip = common_data.clip.boxTrickData;

    for (i = 0; i < 4; i++) {
        if (clip[i].data == NULL) {
            clip[i].data = data;
            clip[i].blockX = blockX;
            clip[i].blockZ = blockZ;
            return;
        }
    }
}

void func_80973280_jp(Actor* actor) {
    s32 i;
    Clip_BoxTrickData* clip;
    s32 blockX;
    s32 blockZ;

    mFI_Wpos2BlockNum(&blockX, &blockZ, actor->world.pos);

    clip = common_data.clip.boxTrickData;

    for (i = 0; i < 4; i++) {
        if (clip[i].data != NULL && blockX == clip[i].blockX && blockZ == clip[i].blockZ) {
            clip[i].data = NULL;
            clip[i].blockX = -1;
            clip[i].blockZ = -1;
            return;
        }
    }
}

u8 D_80973424_jp[] = {
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -1, -1, -1, -1, -2, -2, -2, -2, -2, -2, -2,
    -2, -2, -2, -2, -2, -2, -2, -1, -1, -1, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -1,
    -1, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -1, -1, -1, -2, -2, -2, -2, -2, -2, -2,
    -2, -2, -2, -2, -2, -2, -2, -1, -1, -1, -1, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -1, -1,
    -1, -1, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -1, -1, -1, -1, -2, -2, -2, -2, -2, -2, -2,
    -2, -2, -2, -2, -2, -2, -2, -1, -1, -1, -1, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -1, -1,
    -1, -1, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -2,
    -2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,

};

void BoxTrick01_Actor_ct(Actor* actor, UNUSED Game_Play* play) {
    BoxTrick01* boxTrick = (BoxTrick01*)actor;
    s32 blockX;
    s32 blockZ;

    mFI_Wpos2BlockNum(&blockX, &blockZ, actor->world.pos);
    boxTrick->blockX = blockX;
    boxTrick->blockZ = blockZ;
    func_80973160_jp(D_80973424_jp, actor);
}

void BoxTrick01_Actor_dt(Actor* actor, UNUSED Game_Play* play) {
    func_80973280_jp(actor);
}

void BoxTrick01_Actor_move(UNUSED Actor* actor, UNUSED Game_Play* play) {
}
