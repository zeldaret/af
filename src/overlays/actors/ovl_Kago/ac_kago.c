#include "ac_kago.h"
#include "m_actor_dlftbls.h"
#include "m_object.h"
#include "overlays/gamestates/ovl_play/m_play.h"
#include "overlays/actors/player_actor/m_player.h"
#include "69E2C0.h"
#include "m_field_info.h"
#include "m_player_lib.h"
#include "m_rcp.h"
#include "macros.h"
#include "code_variables.h"

#include "objects/object_00D5E000/obj_e_kago_r/obj_e_kago_r.h"
#include "objects/object_00D5E000/obj_e_kago_w/obj_e_kago_w.h"

#define THIS ((Kago*)thisx)

void aKAG_actor_ct(Actor* thisx, Game_Play* game_play);
void aKAG_actor_dt(Actor* thisx, Game_Play* game_play);
void aKAG_actor_init(Actor* thisx, Game_Play* game_play);
void aKAG_actor_draw(Actor* thisx, Game_Play* game_play);

void aKAG_set_bgOffset(Kago*, s32);
void aKAG_setup_action(Kago*, s32);

ActorProfile Kago_Profile = {
    /* */ ACTOR_KAGO,
    /* */ ACTOR_PART_0,
    /* */ 0,
    /* */ 0x5835,
    /* */ GAMEPLAY_KEEP,
    /* */ sizeof(Kago),
    /* */ aKAG_actor_ct,
    /* */ aKAG_actor_dt,
    /* */ aKAG_actor_init,
    /* */ aKAG_actor_draw,
    /* */ NULL,
};

void aKAG_actor_ct(Actor* thisx, UNUSED Game_Play* game_play) {
    Kago* this = THIS;

    this->structureActor.unk_2B4 = this->structureActor.actor.fgName - 0x5835;
    this->structureActor.structureType = this->structureActor.unk_2B4 + STRUCTURE_TYPE_SPORTSFAIR_A;
    this->structureActor.structurePalette = this->structureActor.unk_2B4 + STRUCTURE_PALETTE_SPORTSFAIR_A;
    aKAG_setup_action(this, KAG_PROCESS_WAIT);
    aKAG_set_bgOffset(this, 1);
}

void aKAG_actor_dt(Actor* thisx, UNUSED Game_Play* game_play) {
    Kago* this = THIS;

    common_data.clip.structureClip->removeInstanceProc(common_data.clip.structureClip->objectSegmentTable,
                                                       ARRAY_COUNT(common_data.clip.structureClip->objectSegmentTable),
                                                       this->structureActor.structureType, &this->structureActor.actor);
    common_data.clip.structureClip->removeInstanceProc(common_data.clip.structureClip->paletteSegmentTable,
                                                       ARRAY_COUNT(common_data.clip.structureClip->paletteSegmentTable),
                                                       this->structureActor.structurePalette,
                                                       &this->structureActor.actor);
    common_data.clip.structureClip->removeInstanceProc(common_data.clip.structureClip->shadowSegmentTable,
                                                       ARRAY_COUNT(common_data.clip.structureClip->shadowSegmentTable),
                                                       this->structureActor.structureType, &this->structureActor.actor);
}

void aKAG_set_bgOffset(Kago* this, s32 id) {
    id = id == 0 ? 10 : 10;
    mCoBG_SetPlussOffset(this->structureActor.actor.home.pos, id, 100);
}

void aKAG_wait(UNUSED Kago* this, UNUSED Game_Play* game_play) {
}

u8 aKAG_shadow_vtx_fix_flg_table[] = { 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 0, 0, 1, 0, 0, 0 };

extern Vtx obj_e_kago_shadow_v[];
extern Gfx obj_e_kago_shadow_model[];

ShadowData aKAG_shadow_data = { 13, aKAG_shadow_vtx_fix_flg_table, 60.0f, obj_e_kago_shadow_v,
                                obj_e_kago_shadow_model };

void aKAG_setup_action(Kago* this, s32 processIndex) {
    static KagoActionFunc process[] = { &aKAG_wait };

    this->structureActor.process = process[processIndex];
    this->structureActor.unk_2B8 = processIndex;
}

void aKAG_actor_move(Actor* thisx, Game_Play* game_play) {
    UNUSED UNK_TYPE1 pad[0x4];
    Kago* this = THIS;
    Player* player = get_player_actor_withoutCheck(game_play);
    s32 xBlock;
    s32 yBlock;
    s32 playerXBlock;
    s32 playerYBlock;

    mFI_Wpos2BlockNum(&xBlock, &yBlock, this->structureActor.actor.world.pos);
    mFI_Wpos2BlockNum(&playerXBlock, &playerYBlock, player->actor.world.pos);
    if ((mDemo_Check(1, &player->actor) == 0) && (mDemo_Check(5, &player->actor) == 0) &&
        ((xBlock != playerXBlock) || (yBlock != playerYBlock))) {
        Actor_delete(&this->structureActor.actor);
    } else {
        ((KagoActionFunc)this->structureActor.process)(this, game_play);
    }
}

void aKAG_actor_init(Actor* thisx, Game_Play* game_play) {
    Kago* this = THIS;

    mFI_SetFG_common(0xF0FD, this->structureActor.actor.home.pos, 0);
    aKAG_actor_move(&this->structureActor.actor, game_play);
    this->structureActor.actor.update = aKAG_actor_move;
}

void aKAG_actor_draw(Actor* thisx, Game_Play* game_play) {
    static Gfx* model[] = { kago_r_DL_model, kago_w_DL_model };
    GraphicsContext* gfxCtx = game_play->state.gfxCtx;
    Kago* this = THIS;
    u32 object = common_data.clip.structureClip->getObjectSegment(this->structureActor.structureType);
    u16* palette = common_data.clip.structureClip->getPalSegment(this->structureActor.structurePalette);
    Mtx* mtx;

    mtx = _Matrix_to_Mtx_new(gfxCtx);
    if (mtx != NULL) {
        _texture_z_light_fog_prim(gfxCtx);
        OPEN_POLY_OPA_DISP(gfxCtx);
        gSPSegment(__polyOpa++, 0x08, palette);
        gSegments[6] = (uintptr_t)OS_PHYSICAL_TO_K0(object);
        gSPSegment(__polyOpa++, 0x06, object);
        gSPMatrix(__polyOpa++, mtx, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPDisplayList(__polyOpa++, model[this->structureActor.unk_2B4]);
        CLOSE_POLY_OPA_DISP(gfxCtx);
        common_data.clip.unk_074->unk_04(game_play, &aKAG_shadow_data, this->structureActor.structureType);
    }
}
