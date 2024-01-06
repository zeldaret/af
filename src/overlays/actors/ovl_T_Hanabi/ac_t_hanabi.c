#include "ac_t_hanabi.h"
#include "m_actor_dlftbls.h"
#include "m_object.h"
#include "overlays/gamestates/ovl_play/m_play.h"
#include "m_rcp.h"
#include "objects/tol_utiwa_1/tol_utiwa_1.h"

#define THIS ((T_Hanabi*)thisx)

void aTHB_actor_ct(Actor* thisx, Game_Play* game_play);
void aTHB_actor_dt(Actor* thisx, Game_Play* game_play);
void aTHB_actor_move(Actor* thisx, Game_Play* game_play);
void aTHB_actor_draw(Actor* thisx, Game_Play* game_play);
void aTHB_setupAction(T_Hanabi* this, s32 processIndex);

ActorProfile T_Hanabi_Profile = {
    /* */ ACTOR_T_HANABI,
    /* */ ACTOR_PART_4,
    /* */ ACTOR_FLAG_10 | ACTOR_FLAG_20,
    /* */ 0x0000,
    /* */ OBJECT_TOL_UTIWA_1,
    /* */ sizeof(T_Hanabi),
    /* */ aTHB_actor_ct,
    /* */ aTHB_actor_dt,
    /* */ aTHB_actor_move,
    /* */ aTHB_actor_draw,
    /* */ NULL,
};

void aTHB_actor_ct(Actor* thisx, Game_Play* game_play UNUSED) {
    T_Hanabi* this = THIS;

    aTHB_setupAction(this, 0);
}

void aTHB_actor_dt(Actor* thisx UNUSED, Game_Play* game_play UNUSED) {
}

void aTHB_calc_scale(T_Hanabi* this, s32 aimIndex) {
    static f32 aim[] = { 1.0f, 0.0f };
    xyz_t* actorScale = &this->toolActor.actor.scale;
    f32 newScale = actorScale->x;

    chase_f(&newScale, aim[aimIndex], 0.1f);
    actorScale->x = newScale;
    actorScale->y = newScale;
    actorScale->z = newScale;
}

void aTHB_takeout(T_Hanabi* this) {
    aTHB_calc_scale(this, 0);
}

void aTHB_putaway(T_Hanabi* this) {
    aTHB_calc_scale(this, 1);
}

void aTHB_destruct(T_Hanabi* this) {
    Actor_delete(&this->toolActor.actor);
}

void aTHB_setupAction(T_Hanabi* this, s32 processIndex) {
    static T_HanabiActionFunc process[] = { aTHB_takeout, aTHB_putaway, aTHB_destruct,
                                            (T_HanabiActionFunc)(void*)none_proc1, NULL };
    static f32 start_scale[] = { 0.0f, 1.0f, 1.0f, 1.0f, 0.0f };
    f32 scale;

    this->process = process[processIndex];
    this->processIndex = processIndex;
    scale = start_scale[processIndex];
    this->toolActor.actor.scale.x = scale;
    this->toolActor.actor.scale.y = scale;
    this->toolActor.actor.scale.z = scale;
}

void aTHB_actor_move(Actor* thisx, Game_Play* game_play UNUSED) {
    T_Hanabi* this = THIS;

    if (this->toolActor.unk1BC != this->processIndex) {
        aTHB_setupAction(this, this->toolActor.unk1BC);
    }

    this->process(this);
}

#define OPEN_POLY_OPA_DISPS()                 \
    {                                         \
        Gfx* __polyOpa = __gfxCtx->polyOpa.p; \
        int __opa_opened = 0;                 \
        while (0)

#define CLOSE_POLY_OPA_DISPS()       \
    __gfxCtx->polyOpa.p = __polyOpa; \
    (void)__opa_opened;              \
    }                                \
    while (0)

void aTHB_actor_draw(Actor* thisx, Game_Play* game_play) {
    static xyz_t D_80A200A4_jp = { 0.0f, 0.0f, 0.0f };
    T_Hanabi* this = THIS;
    GraphicsContext* gfxCtx = game_play->state.gfxCtx;

    if (this->toolActor.unk1B8 == 1) {
        Matrix_put(&this->toolActor.unk178);
        Matrix_Position(&D_80A200A4_jp, &this->toolActor.actor.world.pos);
        this->toolActor.unk1B8 = 0;

    } else {
        Matrix_translate(thisx->world.pos.x, thisx->world.pos.y, thisx->world.pos.z, MTXMODE_NEW);
        Matrix_scale(0.01f, 0.01f, 0.01f, MTXMODE_APPLY);
    }

    Matrix_scale(thisx->scale.x, thisx->scale.y, thisx->scale.z, MTXMODE_APPLY);
    func_800BD5E8_jp(gfxCtx);
    OPEN_DISPS(gfxCtx);
    OPEN_POLY_OPA_DISPS();
    gSPMatrix(__polyOpa++, _Matrix_to_Mtx_new(gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(__polyOpa++, &main_utiwa1_model);
    CLOSE_POLY_OPA_DISPS();
    CLOSE_DISPS(gfxCtx);
}
