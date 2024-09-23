#include "ef_room_sunshine.h"
#include "m_lib.h"
#include "m_actor_dlftbls.h"
#include "m_object.h"
#include "overlays/gamestates/ovl_play/m_play.h"
#include "m_time.h"

void Ef_Room_Sunshine_actor_ct(Actor* actor, Game_Play* game_play);
void Ef_Room_SunshineR_actor_move(Actor* actor, Game_Play* game_play);
void Ef_Room_SunshineR_actor_draw(Actor* actor, Game_Play* play);
void Ef_Room_SunshineL_actor_move(Actor* actor, Game_Play* game_play);
void Ef_Room_SunshineL_actor_draw(Actor* actor, Game_Play* play);

extern Gfx light_floor01_mode[];
extern Vtx light_floorL01_vtx[];
extern Vtx light_floorR01_vtx[];
extern Gfx light_shine01_mode[];
extern Vtx light_shineL01_vtx[];
extern Vtx light_shineR01_vtx[];

ActorProfile Room_Sunshine_Profile = {
    /* */ ACTOR_ROOM_SUNSHINE,
    /* */ ACTOR_PART_6,
    /* */ ACTOR_FLAG_10 | ACTOR_FLAG_20,
    /* */ 0x0000,
    /* */ OBJECT_5,
    /* */ sizeof(Room_Sunshine),
    /* */ Ef_Room_Sunshine_actor_ct,
    /* */ (void*)none_proc1,
    /* */ Ef_Room_SunshineR_actor_move,
    /* */ Ef_Room_SunshineR_actor_draw,
    /* */ NULL,
};

void Ef_Room_Sunshine_actor_ct(Actor* actor, Game_Play* play) {
    Room_Sunshine* sunshine = (Room_Sunshine*)actor;

    sunshine->unk_174 = 0;

    if (actor->params == 0) {
        actor->update = Ef_Room_SunshineL_actor_move;
        actor->draw = Ef_Room_SunshineL_actor_draw;
    } else {
        actor->world.pos.x -= 1.0f;
    }

    actor->world.pos.y = mCoBG_GetBgY_OnlyCenter_FromWpos(actor->world.pos, 0.0f);

    actor->scale.x = 1.0f;
    actor->scale.y = 1.0f;
    actor->scale.z = 1.0f;

    switch (actor->params) {
        case 2:
            actor->update = Ef_Room_SunshineL_actor_move;
            actor->draw = Ef_Room_SunshineL_actor_draw;
            actor->world.pos.x += 5.0f;
            actor->world.pos.y = 1.0f + mCoBG_GetBgY_OnlyCenter_FromWpos(actor->world.pos, 0.0f);
            actor->world.pos.x -= 6.0f;
            break;
        case 3:
            actor->world.pos.x -= 5.0f;
            actor->world.pos.y = 1.0f + mCoBG_GetBgY_OnlyCenter_FromWpos(actor->world.pos, 0.0f);
            actor->world.pos.x += 6.0f;
            break;
    }
}

f32 calc_scale_Ef_Room_Sunshine(s32 flag, s32 sec) {

    if (flag == 0) {
        return 1.5f * sin_s((sec << 14) / (f32)mTM_TIME_TO_SEC(8, 0, 0));
    } else {
        return 1.5f * sin_s((sec << 14) / (f32)mTM_TIME_TO_SEC(4, 0, 0));
    }
}

u8 calc_alpha_Ef_Room_Sunshine() {
    f32 ret;
    s32 sec;

    if (common_data.time.nowSec < mTM_TIME_TO_SEC(4, 0, 0)) {
        ret = 120.0f * ((mTM_TIME_TO_SEC(4, 0, 0) - common_data.time.nowSec) / (f32)mTM_TIME_TO_SEC(4, 0, 0));

    } else if (common_data.time.nowSec < mTM_TIME_TO_SEC(20, 0, 0)) {
        sec = (common_data.time.nowSec - mTM_TIME_TO_SEC(12, 0, 0)) >= 0
                  ? (common_data.time.nowSec - mTM_TIME_TO_SEC(12, 0, 0))
                  : -(common_data.time.nowSec - mTM_TIME_TO_SEC(12, 0, 0));

        ret = 255.0f * ((mTM_TIME_TO_SEC(8, 0, 0) - sec) / (f32)mTM_TIME_TO_SEC(8, 0, 0));
    } else {
        ret = 120.0f * ((mTM_TIME_TO_SEC(4, 0, 0) - (mTM_TIME_TO_SEC(24, 0, 0) - common_data.time.nowSec)) /
                        (f32)mTM_TIME_TO_SEC(4, 0, 0));
    }

    if ((common_data.weather == SUMMER) || (common_data.weather == FALL)) {
        ret *= 0.6f;
    }

    return (s32)ret;
}

void Ef_Room_SunshineL_actor_move(Actor* actor, Game_Play* play) {
    Room_Sunshine* sunshine = (Room_Sunshine*)actor;

    if (common_data.time.nowSec < mTM_TIME_TO_SEC(4, 0, 0)) {
        actor->scale.x = calc_scale_Ef_Room_Sunshine(1, common_data.time.nowSec);
    } else if (common_data.time.nowSec >= mTM_TIME_TO_SEC(12, 0, 0) &&
               common_data.time.nowSec < mTM_TIME_TO_SEC(20, 0, 0)) {
        actor->scale.x = calc_scale_Ef_Room_Sunshine(0, common_data.time.nowSec - mTM_TIME_TO_SEC(12, 0, 0));
    } else {
        actor->scale.x = 0.0f;
    }
}

void Ef_Room_SunshineR_actor_move(Actor* actor, Game_Play* play) {
    Room_Sunshine* sunshine = (Room_Sunshine*)actor;

    if (common_data.time.nowSec >= mTM_TIME_TO_SEC(4, 0, 0) && common_data.time.nowSec < mTM_TIME_TO_SEC(12, 0, 0)) {
        actor->scale.x = calc_scale_Ef_Room_Sunshine(0, mTM_TIME_TO_SEC(12, 0, 0) - common_data.time.nowSec);
    } else if (common_data.time.nowSec >= mTM_TIME_TO_SEC(20, 0, 0)) {
        actor->scale.x = calc_scale_Ef_Room_Sunshine(1, mTM_TIME_TO_SEC(24, 0, 0) - common_data.time.nowSec);
    } else {
        actor->scale.x = 0.0f;
    }
}

void setup_mode_Ef_Room_Sunshine(Actor* actor, Game_Play* play) {
    OPEN_DISPS(play->state.gfxCtx);
    Matrix_translate(actor->world.pos.x, actor->world.pos.y, actor->world.pos.z, 0);
    Matrix_scale(actor->scale.x, actor->scale.y, actor->scale.z, 1);

    gDPPipeSync(POLY_XLU_DISP++);

    gSPMatrix(POLY_XLU_DISP++, _Matrix_to_Mtx_new(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    {
        u8* color;
        s32 alpha;

        if (common_data.time.nowSec >= mTM_TIME_TO_SEC(4, 0, 0) &&
            common_data.time.nowSec < mTM_TIME_TO_SEC(20, 0, 0)) {
            color = play->kankyo.baseLight.sunColorWindow;
        } else {
            color = play->kankyo.baseLight.moonColorWindow;
        }

        alpha = calc_alpha_Ef_Room_Sunshine() * mKK_windowlight_alpha_get();

        gDPSetPrimColor(POLY_XLU_DISP++, 0, 0, color[0], color[1], color[2], (u8)alpha);
    }
    CLOSE_DISPS(play->state.gfxCtx);
}

void Ef_Room_SunshineL_actor_draw(Actor* actor, Game_Play* play) {
    GraphicsContext* graph;

    if ((mKK_windowlight_alpha_get() < 0.0001f) || (actor->scale.x == 0.0f)) {
        return;
    }
    graph = play->state.gfxCtx;
    setup_mode_Ef_Room_Sunshine(actor, play);

    OPEN_DISPS(graph);

    gSPDisplayList(POLY_XLU_DISP++, light_floor01_mode);
    gSPDisplayList(POLY_XLU_DISP++, light_floorL01_vtx);
    gSPDisplayList(POLY_XLU_DISP++, light_shine01_mode);
    gSPDisplayList(POLY_XLU_DISP++, light_shineL01_vtx);

    CLOSE_DISPS(graph);
}

void Ef_Room_SunshineR_actor_draw(Actor* actor, Game_Play* play) {
    GraphicsContext* graph;

    if ((mKK_windowlight_alpha_get() < 0.0001f) || (actor->scale.x == 0.0f)) {
        return;
    }
    graph = play->state.gfxCtx;
    setup_mode_Ef_Room_Sunshine(actor, play);

    OPEN_DISPS(graph);

    gSPDisplayList(POLY_XLU_DISP++, light_floor01_mode);
    gSPDisplayList(POLY_XLU_DISP++, light_floorR01_vtx);
    gSPDisplayList(POLY_XLU_DISP++, light_shine01_mode);
    gSPDisplayList(POLY_XLU_DISP++, light_shineR01_vtx);

    CLOSE_DISPS(graph);
}
