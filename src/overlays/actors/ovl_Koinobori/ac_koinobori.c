#include "global.h"
#include "ac_koinobori.h"
#include "m_actor_dlftbls.h"
#include "m_object.h"
#include "overlays/gamestates/ovl_play/m_play.h"
#include "c_keyframe.h"
#include "m_player_lib.h"
#include "69E2C0.h"
#include "m_field_info.h"
#include "audio.h"
#include "overlays/actors/player_actor/m_player.h"
#include "m_rcp.h"
#include "objects/object_00D5E000/obj_e_koinobori/obj_e_koinobori.h"

#define THIS ((Koinobori*)thisx)

void aKOI_actor_ct(Actor* thisx, Game_Play* game_play);
void aKOI_actor_dt(Actor* thisx, Game_Play* game_play);
void aKOI_actor_init(Actor* thisx, Game_Play* game_play);
void aKOI_actor_draw(Actor* thisx, Game_Play* game_play);
void aKOI_set_bgOffset(Koinobori* this, s32 processIndex);
void aKOI_setup_action(Koinobori* this, s32 processIndex);

ActorProfile Koinobori_Profile = {
    /* */ ACTOR_KOINOBORI,
    /* */ ACTOR_PART_0,
    /* */ 0,
    /* */ 0x5839,
    /* */ GAMEPLAY_KEEP,
    /* */ sizeof(Koinobori),
    /* */ aKOI_actor_ct,
    /* */ aKOI_actor_dt,
    /* */ aKOI_actor_init,
    /* */ aKOI_actor_draw,
    /* */ NULL,
};

u8 aKOI_shadow_vtx_fix_flg_table[] = { 0x01, 0x00, 0x00, 0x01, 0x01, 0x00, 0x00, 0x01 };
extern Vtx obj_e_koinobori_shadow_v[];
extern Gfx obj_e_koinobori_shadowT_model[];
ShadowData aKOI_shadow_data = { 8, aKOI_shadow_vtx_fix_flg_table, 60.0f, obj_e_koinobori_shadow_v,
                                obj_e_koinobori_shadowT_model };

void aKOI_actor_ct(Actor* thisx, Game_Play* game_play UNUSED) {
    Koinobori* this = THIS;

    gSegments[6] = OS_K0_TO_PHYSICAL(common_data.clip.structureClip->getObjectSegment(STRUCTURE_TYPE_KOINOBORI));
    cKF_SkeletonInfo_R_ct(&this->structureActor.skeletonInfo, &cKF_bs_r_obj_e_koinobori, 0,
                          this->structureActor.jointTable, this->structureActor.morphTable);
    aKOI_set_bgOffset(this, 1);
    aKOI_setup_action(this, 0);
    cKF_SkeletonInfo_R_play(&this->structureActor.skeletonInfo);
}

void aKOI_actor_dt(Actor* thisx, Game_Play* game_play UNUSED) {
    Koinobori* this = THIS;

    common_data.clip.structureClip->removeInstanceProc(common_data.clip.structureClip->objectSegmentTable,
                                                       ARRAY_COUNT(common_data.clip.structureClip->objectSegmentTable),
                                                       STRUCTURE_TYPE_KOINOBORI, &this->structureActor.actor);
    common_data.clip.structureClip->removeInstanceProc(common_data.clip.structureClip->paletteSegmentTable,
                                                       ARRAY_COUNT(common_data.clip.structureClip->paletteSegmentTable),
                                                       STRUCTURE_PALETTE_KOINOBORI, &this->structureActor.actor);
    common_data.clip.structureClip->removeInstanceProc(common_data.clip.structureClip->shadowSegmentTable,
                                                       ARRAY_COUNT(common_data.clip.structureClip->shadowSegmentTable),
                                                       STRUCTURE_TYPE_KOINOBORI, &this->structureActor.actor);
    cKF_SkeletonInfo_R_dt(&this->structureActor.skeletonInfo);
}

void aKOI_set_bgOffset(Koinobori* this UNUSED, s32 processIndex UNUSED) {
}

void aKOI_wait(Koinobori* this UNUSED, Game_Play* game_play UNUSED) {
}

void aKOI_setup_action(Koinobori* this, s32 processIndex) {
    static KoinoboriActionFunc process[] = { aKOI_wait };

    cKF_SkeletonInfo_R_init(&this->structureActor.skeletonInfo, this->structureActor.skeletonInfo.skeleton,
                            &cKF_ba_r_obj_e_koinobori, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, ANIMATION_REPEAT, NULL);
    this->structureActor.process = process[processIndex];
    this->structureActor.unk_2B4 = processIndex;
}

void aKOI_actor_move(Actor* thisx, Game_Play* game_play) {
    Koinobori* this = THIS;
    UNUSED s32 pad;
    Player* player = get_player_actor_withoutCheck(game_play);
    s32 blockX;
    s32 blockY;
    s32 playerBlockX;
    s32 playerBlockY;
    UNUSED s32 pad2;

    mFI_Wpos2BlockNum(&blockX, &blockY, this->structureActor.actor.world.pos);
    mFI_Wpos2BlockNum(&playerBlockX, &playerBlockY, player->actor.world.pos);

    if ((mDemo_Check(1, &player->actor) == 0) && (mDemo_Check(5, &player->actor) == 0) &&
        ((blockX != playerBlockX) || (blockY != playerBlockY))) {
        Actor_delete(&this->structureActor.actor);
        return;
    }

    gSegments[6] = OS_K0_TO_PHYSICAL(common_data.clip.structureClip->getObjectSegment(STRUCTURE_TYPE_KOINOBORI));
    cKF_SkeletonInfo_R_play(&this->structureActor.skeletonInfo);
    ((KoinoboriActionFunc)this->structureActor.process)(this, game_play);
    sAdo_OngenPos((uintptr_t)this, 0x35, &this->structureActor.actor.world.pos);
}

void aKOI_actor_init(Actor* thisx, Game_Play* game_play) {
    Koinobori* this = THIS;

    mFI_SetFG_common(0xF100, this->structureActor.actor.home.pos, 0);
    aKOI_actor_move(&this->structureActor.actor, game_play);
    this->structureActor.actor.update = aKOI_actor_move;
}

extern u16 aKOI_obj_e_koinobori_a_pal[];
extern u16 obj_e_koinobori_b_pal[];
#include "assets/jp/overlays/actors/ovl_Koinobori/aKOI_obj_e_koinobori_a_pal.palette.inc.c"
#include "assets/jp/overlays/actors/ovl_Koinobori/obj_e_koinobori_b_pal.palette.inc.c"

void aKOI_actor_draw(Actor* thisx, Game_Play* game_play) {
    GraphicsContext* gfxCtx = game_play->state.gfxCtx;
    Koinobori* this = THIS;
    Mtx* mtx;
    UNUSED s32 pad;
    s32 object;
    u16* palette;

    mtx = GRAPH_ALLOC_NO_ALIGN(gfxCtx, this->structureActor.skeletonInfo.skeleton->unk01 * sizeof(Mtx));
    if (mtx != NULL) {
        object = common_data.clip.structureClip->getObjectSegment(STRUCTURE_TYPE_KOINOBORI);
        palette = common_data.clip.structureClip->getPalSegment(STRUCTURE_PALETTE_KOINOBORI);
        _texture_z_light_fog_prim_npc(gfxCtx);
        OPEN_POLY_OPA_DISP(gfxCtx);
        gSPSegment(__polyOpa++, 0x08, palette);
        gSPSegment(__polyOpa++, 0x09, Lib_SegmentedToVirtual(&obj_e_koinobori_b_pal));
        gSPSegment(__polyOpa++, 0x0A, Lib_SegmentedToVirtual(&aKOI_obj_e_koinobori_a_pal));
        gSegments[6] = OS_K0_TO_PHYSICAL(object);
        gSPSegment(__polyOpa++, 0x06, object);
        CLOSE_POLY_OPA_DISP(gfxCtx);
        cKF_Si3_draw_R_SV(game_play, &this->structureActor.skeletonInfo, mtx, NULL, NULL, this);
        common_data.clip.unk_074->unk_04(game_play, &aKOI_shadow_data, 0x27);
    }
}
