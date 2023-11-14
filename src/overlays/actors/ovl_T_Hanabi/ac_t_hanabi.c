#include "ac_t_hanabi.h"
#include "m_actor_dlftbls.h"
#include "m_object.h"
#include "overlays/gamestates/ovl_play/m_play.h"
#include "m_rcp.h"

#define THIS ((T_Hanabi*)thisx)

void aTHB_actor_ct(Actor* thisx, Game_Play* game_play);
void aTHB_actor_dt(Actor* thisx, Game_Play* game_play);
void aTHB_actor_move(Actor* thisx, Game_Play* game_play);
void aTHB_actor_draw(Actor* thisx, Game_Play* game_play);

#if 0
ActorProfile T_Hanabi_Profile = {
    /* */ ACTOR_T_HANABI,
    /* */ ACTOR_PART_4,
    /* */ ACTOR_FLAG_10 | ACTOR_FLAG_20,
    /* */ 0x0000,
    /* */ OBJECT_53,
    /* */ sizeof(T_Hanabi),
    /* */ aTHB_actor_ct,
    /* */ aTHB_actor_dt,
    /* */ aTHB_actor_move,
    /* */ aTHB_actor_draw,
    /* */ NULL,
};
#endif

void func_80A1FEDC_jp(T_Hanabi* this, UNK_TYPE arg1);

// #pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_T_Hanabi/ac_t_hanabi/aTHB_actor_ct.s")
void aTHB_actor_ct(Actor* thisx, Game_Play* game_play UNUSED) {
    T_Hanabi* this = THIS;

    func_80A1FEDC_jp(this, 0);
}

// #pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_T_Hanabi/ac_t_hanabi/aTHB_actor_dt.s")
void aTHB_actor_dt(Actor* thisx UNUSED, Game_Play* game_play UNUSED) {
}

// #pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_T_Hanabi/ac_t_hanabi/func_80A1FE14_jp.s")
extern f32 D_80A20074_jp[]; //aim

//calc scale
void func_80A1FE14_jp(T_Hanabi* this, s32 arg1)
{
    xyz_t* scale = &this->toolActor.actor.scale;
    f32 sp18 = scale->x;
    // void *temp_v0;

    chase_f(&sp18, D_80A20074_jp[arg1], 0.1f);

    // temp_v0 = arg0 + 0x5C;
    scale->x = sp18;
    scale->y = sp18;
    scale->z = sp18;
}

// #pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_T_Hanabi/ac_t_hanabi/func_80A1FE7C_jp.s")
// takeout
void func_80A1FE7C_jp(T_Hanabi* this) {
    func_80A1FE14_jp(this, 0);
}

// #pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_T_Hanabi/ac_t_hanabi/func_80A1FE9C_jp.s")
// putaway
void func_80A1FE9C_jp(T_Hanabi* this) {
    func_80A1FE14_jp(this, 1);
}

// #pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_T_Hanabi/ac_t_hanabi/func_80A1FEBC_jp.s")
// destruct
void func_80A1FEBC_jp(T_Hanabi* this) {
    Actor_delete(&this->toolActor.actor);
}

// #pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_T_Hanabi/ac_t_hanabi/func_80A1FEDC_jp.s")
extern T_HanabiActionFunc D_80A2007C_jp[]; // process
extern f32 D_FLT_80A20090_jp[];  // start_scale

void func_80A1FEDC_jp(T_Hanabi* this, UNK_TYPE arg1) {
    f32 temp_fv0;

    this->unk1C8 = D_80A2007C_jp[arg1];
    this->unk1CC = arg1;
    temp_fv0 = D_FLT_80A20090_jp[arg1];
    this->toolActor.actor.scale.x = temp_fv0;
    this->toolActor.actor.scale.y = temp_fv0;
    this->toolActor.actor.scale.z = temp_fv0;
}

// #pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_T_Hanabi/ac_t_hanabi/aTHB_actor_move.s")
void aTHB_actor_move(Actor *thisx, Game_Play *game_play UNUSED)
{
    T_Hanabi* this = THIS;

    if (this->toolActor.unk1BC != this->unk1CC)
    {
        func_80A1FEDC_jp(this, this->toolActor.unk1BC);
    }

    this->unk1C8(this);
}

#define OPEN_POLY_OPA_DISPS()                 \
    {                                         \
        Gfx* __polyOpa = __gfxCtx->polyOpa.p; \
        int __opa_opened = 0;                 \
        while (0)

#define CLOSE_POLY_OPA_DISPS()           \
        __gfxCtx->polyOpa.p = __polyOpa; \
        (void)__opa_opened;              \
    }                                    \
    while (0)

// #pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_T_Hanabi/ac_t_hanabi/aTHB_actor_draw.s")
extern Gfx* D_6000080;
extern xyz_t D_80A200A4_jp;

void aTHB_actor_draw(Actor *thisx, Game_Play *game_play)
{
    T_Hanabi* this = THIS;
    GraphicsContext* gfxCtx = game_play->state.gfxCtx;

    if (this->toolActor.unk1B8 == 1)
    {
        Matrix_put(&this->toolActor.unk178);
        Matrix_Position(&D_80A200A4_jp, &this->toolActor.actor.world.pos);
        this->toolActor.unk1B8 = 0;
    }
    else
    {
        Matrix_translate(thisx->world.pos.x, thisx->world.pos.y, thisx->world.pos.z, MTXMODE_NEW);
        Matrix_scale(0.01f, 0.01f, 0.01f, MTXMODE_APPLY);
    }

    Matrix_scale(thisx->scale.x, thisx->scale.y, thisx->scale.z, MTXMODE_APPLY);
    func_800BD5E8_jp(gfxCtx);

    OPEN_DISPS(gfxCtx);
    OPEN_POLY_OPA_DISPS();

    gSPMatrix(__polyOpa++, _Matrix_to_Mtx_new(gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(__polyOpa++, &D_6000080);

    CLOSE_POLY_OPA_DISPS();
    CLOSE_DISPS(gfxCtx);
}
