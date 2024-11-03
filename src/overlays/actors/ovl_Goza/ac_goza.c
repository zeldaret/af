#include "global.h"
#include "ac_goza.h"
#include "m_actor_dlftbls.h"
#include "m_object.h"
#include "overlays/gamestates/ovl_play/m_play.h"
#include "overlays/actors/player_actor/m_player.h"
#include "m_player_lib.h"
#include "m_field_info.h"
#include "m_demo.h"
#include "m_rcp.h"
#include "macros.h"
#include "gfx.h"

#include "objects/object_00D5E000/obj_e_goza/obj_e_goza.h"

#define THIS ((Goza*)thisx)

void aGOZ_actor_ct(Actor* thisx, Game_Play* game_play);
void aGOZ_actor_dt(Actor* thisx, Game_Play* game_play);
void aGOZ_actor_init(Actor* thisx, Game_Play* game_play);
void aGOZ_actor_draw(Actor* thisx, Game_Play* game_play);
void aGOZ_set_bgOffset(Goza* this, s32 heightTableIndex);
void aGOZ_setup_action(Goza* this, s32 processIndex);

ActorProfile Goza_Profile = {
    /* */ ACTOR_GOZA,
    /* */ ACTOR_PART_0,
    /* */ 0,
    /* */ 0x582A,
    /* */ GAMEPLAY_KEEP,
    /* */ sizeof(Goza),
    /* */ aGOZ_actor_ct,
    /* */ aGOZ_actor_dt,
    /* */ aGOZ_actor_init,
    /* */ aGOZ_actor_draw,
    /* */ NULL,
};

extern Vtx obj_e_goza_shadow_v[];
extern Gfx obj_e_goza_shadowT_model[];
u8 aGOZ_shadow_vtx_fix_flg_table[] = { 1, 0, 0, 1, 0, 1, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1 };
ShadowData aGOZ_shadow_data = { 24, aGOZ_shadow_vtx_fix_flg_table, 60.0f, obj_e_goza_shadow_v,
                                obj_e_goza_shadowT_model };

void aGOZ_actor_ct(Actor* thisx, Game_Play* game_play UNUSED) {
    Goza* this = THIS;

    aGOZ_setup_action(this, 0);
    aGOZ_set_bgOffset(this, 1);
}

void aGOZ_actor_dt(Actor* thisx, Game_Play* game_play UNUSED) {
    Goza* this = THIS;

    common_data.clip.structureClip->removeInstanceProc(common_data.clip.structureClip->objectSegmentTable,
                                                       ARRAY_COUNT(common_data.clip.structureClip->objectSegmentTable),
                                                       STRUCTURE_TYPE_GOZA, &this->structureActor.actor);

    common_data.clip.structureClip->removeInstanceProc(common_data.clip.structureClip->paletteSegmentTable,
                                                       ARRAY_COUNT(common_data.clip.structureClip->paletteSegmentTable),
                                                       STRUCTURE_PALETTE_GOZA, &this->structureActor.actor);

    common_data.clip.structureClip->removeInstanceProc(common_data.clip.structureClip->shadowSegmentTable,
                                                       ARRAY_COUNT(common_data.clip.structureClip->shadowSegmentTable),
                                                       STRUCTURE_TYPE_GOZA, &this->structureActor.actor);
}

void aGOZ_set_bgOffset(Goza* this, s32 heightTableIndex) {
    // clang-format off
    static mCoBG_unkStruct2 height_table_ct[] = {
        { 0x64, 0, 0, 0, 0, 0, 0 },
        { 0x64, 0, 0, 0, 0, 0, 0 },
        { 0x64, 0, 0, 0, 0, 0, 0 },
        { 0x64, 2, 2, 2, 2, 2, 0 },
        { 0x64, 2, 2, 2, 2, 2, 0 },
        { 0x64, 2, 2, 2, 2, 2, 0 },
        { 0x64, 0, 0, 0, 0, 0, 0 },
        { 0x64, 0, 0, 0, 0, 0, 0 },
        { 0x64, 0, 0, 0, 0, 0, 0 }
    };
    // clang-format on
    static mCoBG_unkStruct2* height_table[] = { height_table_ct, height_table_ct };
    static f32 addX[] = { -40.0f, 0.0f, 40.0f };
    static f32 addZ[] = { -40.0f, 0.0f, 40.0f };

    s32 i;
    xyz_t pos;
    mCoBG_unkStruct2* offsetTable = height_table[heightTableIndex];

    for (i = 0; i < ARRAY_COUNT(addZ); i++) {
        pos.z = addZ[i] + this->structureActor.actor.home.pos.z;

        pos.x = addX[0] + this->structureActor.actor.home.pos.x;
        mCoBG_SetPluss5PointOffset_file(pos, *offsetTable, "../ac_goza_move.c_inc", 93);
        offsetTable++;
        pos.x = addX[1] + this->structureActor.actor.home.pos.x;
        mCoBG_SetPluss5PointOffset_file(pos, *offsetTable, "../ac_goza_move.c_inc", 97);
        offsetTable++;
        pos.x = addX[2] + this->structureActor.actor.home.pos.x;
        mCoBG_SetPluss5PointOffset_file(pos, *offsetTable, "../ac_goza_move.c_inc", 101);
        offsetTable++;
    }
}

void aGOZ_wait(Goza* this UNUSED, Game_Play* game_play UNUSED) {
}

void aGOZ_setup_action(Goza* this, s32 processIndex) {
    static GozaActionFunc process[] = { aGOZ_wait };

    this->structureActor.process = process[processIndex];
}

void aGOZ_actor_move(Actor* thisx, Game_Play* game_play) {
    Goza* this = THIS;
    StructureActor* goza = &this->structureActor;
    Player* player = get_player_actor_withoutCheck(game_play);
    s32 gozaBlockX;
    s32 gozaBlockZ;
    s32 playerBlockX;
    s32 playerBlockZ;

    mFI_Wpos2BlockNum(&gozaBlockX, &gozaBlockZ, goza->actor.world.pos);
    mFI_Wpos2BlockNum(&playerBlockX, &playerBlockZ, player->actor.world.pos);

    if (!mDemo_Check(1, &player->actor) && !mDemo_Check(5, &player->actor) &&
        ((gozaBlockX != playerBlockX) || (gozaBlockZ != playerBlockZ))) {
        Actor_delete(&goza->actor);
    } else {
        ((GozaActionFunc)goza->process)(this, game_play);
    }
}

void aGOZ_actor_init(Actor* thisx, Game_Play* game_play) {
    Goza* this = THIS;
    StructureActor* goza = &this->structureActor;

    mFI_SetFG_common(0xF0F4, goza->actor.home.pos, FALSE);
    aGOZ_actor_move(&goza->actor, game_play);
    goza->actor.update = aGOZ_actor_move;
}

void aGOZ_actor_draw(Actor* thisx, Game_Play* game_play) {
    GraphicsContext* gfxCtx = game_play->state.gfxCtx;
    u32 object = common_data.clip.structureClip->getObjectSegment(STRUCTURE_TYPE_GOZA);
    u16* palette = common_data.clip.structureClip->getPalSegment(STRUCTURE_PALETTE_GOZA);
    Mtx* mtx = _Matrix_to_Mtx_new(gfxCtx);

    _texture_z_light_fog_prim_shadow(gfxCtx);

    OPEN_SHADOW_DISP(gfxCtx);
    gSPSegment(__shadow_gfx++, G_MWO_SEGMENT_8, palette);
    gSegments[6] = (uintptr_t)OS_PHYSICAL_TO_K0(object);
    gSPSegment(__shadow_gfx++, G_MWO_SEGMENT_6, object);
    gDPSetPrimColor(__shadow_gfx++, 0, 0x80, 255, 255, 255, 255);

    mtx = _Matrix_to_Mtx_new(gfxCtx);

    if (mtx != NULL) {
        gSPMatrix(__shadow_gfx++, mtx, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPDisplayList(__shadow_gfx++, goza_DL_model);
    }

    CLOSE_SHADOW_DISP(gfxCtx);

    if (mtx != NULL) {
        common_data.clip.unk_074->unk_04(game_play, &aGOZ_shadow_data, STRUCTURE_TYPE_GOZA);
    }
}
