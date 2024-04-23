#include "ac_tama.h"
#include "m_actor_dlftbls.h"
#include "m_object.h"
#include "m_actor_shadow.h"
#include "overlays/gamestates/ovl_play/m_play.h"
#include "overlays/actors/player_actor/m_player.h"
#include "m_player_lib.h"
#include "libc/math.h"
#include "69E2C0.h"
#include "m_field_info.h"
#include "code_variables.h"
#include "m_rcp.h"

#include "objects/object_00D5E000/obj_e_kago_r/obj_e_kago_r.h"
#include "objects/object_00D5E000/obj_e_kago_w/obj_e_kago_w.h"

#define THIS ((Tama*)thisx)

void aTAM_actor_ct(Actor* thisx, Game_Play* game_play);
void aTAM_actor_dt(Actor* thisx, Game_Play* game_play);
void aTAM_actor_init(Actor* thisx, Game_Play* game_play);
void aTAM_actor_draw(Actor* thisx, Game_Play* game_play);

ActorProfile Tama_Profile = {
    /* */ ACTOR_TAMA,
    /* */ ACTOR_PART_0,
    /* */ 0,
    /* */ 0x5833,
    /* */ GAMEPLAY_KEEP,
    /* */ sizeof(Tama),
    /* */ aTAM_actor_ct,
    /* */ aTAM_actor_dt,
    /* */ aTAM_actor_init,
    /* */ aTAM_actor_draw,
    /* */ NULL,
};

void aTAM_setup_action(Tama*, s32);

void aTAM_actor_ct(Actor* thisx, UNUSED Game_Play* game_play) {
    Tama* this = THIS;

    this->type = this->actor.fgName - 0x5833;
    this->structureType = this->type + 0x23;
    this->structurePalette = this->type + 0x4C;
    aTAM_setup_action(this, TAM_PROCESS_WAIT);
}

void aTAM_actor_dt(Actor* thisx, UNUSED Game_Play* game_play) {
    Tama* this = THIS;

    common_data.clip.unk_08C->unk_A8(&common_data.clip.unk_08C->unk_B0, 8, this->structureType, &this->actor);
    common_data.clip.unk_08C->unk_A8(&common_data.clip.unk_08C->unk_454, 9, this->structurePalette, &this->actor);
    common_data.clip.unk_08C->unk_A8(&common_data.clip.unk_08C->unk_86C, 8, this->structureType, &this->actor);
}

void aTAM_wait(UNUSED Tama* this, UNUSED Game_Play* game_play) {
}

void aTAM_setup_action(Tama* this, s32 processIndex) {
    static TamaActionFunc process[] = { aTAM_wait };
    this->process = process[processIndex];
    this->processNum = processIndex;
}

void aTAM_actor_move(Actor* thisx, Game_Play* game_play) {
    UNUSED UNK_TYPE1 pad[0x4];
    Tama* this = THIS;
    Player* player = get_player_actor_withoutCheck(game_play);
    s32 xBlock;
    s32 yBlock;
    s32 playerXBlock;
    s32 playerYBlock;

    mFI_Wpos2BlockNum(&xBlock, &yBlock, this->actor.world.pos);
    mFI_Wpos2BlockNum(&playerXBlock, &playerYBlock, player->actor.world.pos);
    if ((mDemo_Check(1, &player->actor) == 0) && (mDemo_Check(5, &player->actor) == 0) &&
        ((xBlock != playerXBlock) || (yBlock != playerYBlock))) {
        Actor_delete(&this->actor);
    } else {
        this->process(this, game_play);
    }
}

void aTAM_actor_init(Actor* thisx, Game_Play* game_play) {
    Tama* this = THIS;

    mFI_SetFG_common(0xF0FC, this->actor.home.pos, 0);
    aTAM_actor_move(&this->actor, game_play);
    this->actor.update = aTAM_actor_move;
}

#define OPEN_CUSTOM_POLY_OPA()                \
    {                                         \
        Gfx* __polyOpa = __gfxCtx->polyOpa.p; \
        int __opa_opened = 0;                 \
        do {                                  \
        } while (0)

#define CLOSE_CUSTOM_POLY_OPA()      \
    __gfxCtx->polyOpa.p = __polyOpa; \
    (void)__opa_opened;              \
    }                                \
    do {                             \
    } while (0)

void aTAM_actor_draw(Actor* thisx, Game_Play* game_play) {
    static Gfx* model[2] = { kago_r_ball_DL_model, kago_w_ball_DL_model };
    GraphicsContext* gfxCtx = game_play->state.gfxCtx;
    Tama* this = THIS;
    u32 object = common_data.clip.unk_08C->unk_AC(this->structureType);
    u16* palette = common_data.clip.unk_08C->unk_450(this->structurePalette);
    Mtx* mtx;

    _texture_z_light_fog_prim(gfxCtx);

    OPEN_DISPS(gfxCtx);
    OPEN_CUSTOM_POLY_OPA();
    gSPSegment(__polyOpa++, 0x08, palette);
    gSegments[6] = (uintptr_t)OS_PHYSICAL_TO_K0(object);
    gSPSegment(__polyOpa++, 0x06, object);
    Matrix_translate(0.0f, 0.0f, 4000.0f, 1);
    mtx = _Matrix_to_Mtx_new(gfxCtx);
    if (mtx != NULL) {
        gSPMatrix(__polyOpa++, mtx, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPDisplayList(__polyOpa++, model[this->type]);
        CLOSE_CUSTOM_POLY_OPA();
    }
    CLOSE_DISPS(gfxCtx);
}
