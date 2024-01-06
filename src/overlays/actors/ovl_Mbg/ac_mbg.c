#include "ac_mbg.h"
#include "m_actor_dlftbls.h"
#include "m_object.h"
#include "overlays/gamestates/ovl_play/m_play.h"
#include "m_collision_bg.h"
#include "sys_math.h"
#include "m_rcp.h"

void Mbg_Actor_ct(Actor* thisx, Game_Play* game_play);
void Mbg_Actor_dt(Actor* thisx, Game_Play* game_play);
void Mbg_Actor_move(Actor* thisx, Game_Play* game_play);
void Mbg_Actor_draw(Actor* thisx, Game_Play* game_play);

#if 0
ActorProfile Mbg_Profile = {  //TODO: import data (some is DisplayList)
    /* */ ACTOR_MBG,
    /* */ ACTOR_PART_0,
    /* */ 0,
    /* */ 0x8003,
    /* */ GAMEPLAY_KEEP,
    /* */ sizeof(Mbg),
    /* */ Mbg_Actor_ct,
    /* */ Mbg_Actor_dt,
    /* */ Mbg_Actor_move,
    /* */ Mbg_Actor_draw,
    /* */ NULL,
};
#endif

extern Gfx D_80972F40_jp[];

void Mbg_Actor_ct(Actor* thisx, Game_Play* game_play UNUSED) {
    PosRot* temp_a1;
    Mbg* this = (Mbg*)thisx;

    this->unk_19C = 0;
    temp_a1 = &this->actor.world;
    this->unk_1A0 = temp_a1->pos;
    this->actor.shape.rot.y = 0x2AAA;
    this->unk_1AC = 0.0f;
    this->unk_19C = mCoBG_RegistMoveBg(this->unk_174, temp_a1, &this->actor.prevPos, &this->actor.shape.rot.y, 40.0f, 0,
                                       0, 0, 0, 0, 7, 80.0f);
}

void Mbg_Actor_dt(Actor* thisx, Game_Play* game_play UNUSED) {
    Mbg* this = (Mbg*)thisx;
    mCoBG_CrossOffMoveBg(this->unk_19C, thisx);
}

void Mbg_Actor_draw(Actor* thisx, Game_Play* game_play) {
    xyz_t sp3C;
    s16 sp3A;

    sp3C = thisx->world.pos;
    sp3A = thisx->shape.rot.y;
    OPEN_DISPS(game_play->state.gfxCtx);
    _texture_z_light_fog_prim(game_play->state.gfxCtx);
    Matrix_translate(sp3C.x, sp3C.y, sp3C.z, MTXMODE_NEW);
    Matrix_RotateY(sp3A, MTXMODE_APPLY);
    gSPMatrix(POLY_OPA_DISP++, _Matrix_to_Mtx_new(game_play->state.gfxCtx),
              G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(POLY_OPA_DISP++, D_80972F40_jp);
    CLOSE_DISPS(game_play->state.gfxCtx);
}

void Mbg_Actor_move(Actor* thisx, Game_Play* game_play UNUSED) {
    f32 temp_ft2;
    Mbg* this = (Mbg*)thisx;

    temp_ft2 = sinf_table(this->unk_1AC * 0.017453292f) * 60.0f;
    this->unk_1AC += 2.0f;
    if (this->unk_1AC > 360.0f) {
        do {
            this->unk_1AC -= 360.0f;
        } while (this->unk_1AC > 360.0f);
    }
    this->actor.shape.rot.y += 0x2F;
    this->actor.world.pos.x = this->unk_1A0.x + temp_ft2;
}
