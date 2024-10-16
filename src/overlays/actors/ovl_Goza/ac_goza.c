#include "global.h"
#include "ac_goza.h"
#include "m_actor_dlftbls.h"
#include "m_object.h"
#include "overlays/gamestates/ovl_play/m_play.h"
#include "overlays/actors/player_actor/m_player.h"
#include "m_player_lib.h"
#include "m_field_info.h"
#include "69E2C0.h"
#include "m_rcp.h"
#include "macros.h"
#include "gfx.h"

#include "objects/object_00D5E000/obj_e_goza/obj_e_goza.h"

#define THIS ((Goza*)thisx)

void aGOZ_actor_ct(Actor* thisx, Game_Play* game_play);
void aGOZ_actor_dt(Actor* thisx, Game_Play* game_play);
void aGOZ_actor_init(Actor* thisx, Game_Play* game_play);
void aGOZ_actor_draw(Actor* thisx, Game_Play* game_play);
void aGOZ_set_bgOffset(Goza* this, s32 processIndex);
void aGOZ_setup_action(Goza* this, s32 processIndex);

#if 0
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
#endif

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

extern mCoBG_unkStruct2 D_80A767C0_jp[];
extern mCoBG_unkStruct2* D_80A76800_jp[];
extern f32 D_FLT_80A76808_jp[3];
extern f32 D_FLT_80A76814_jp[3];

void aGOZ_set_bgOffset(Goza* this, s32 processIndex) {
    s32 i;
    xyz_t pos;
    mCoBG_unkStruct2* offsetTable = D_80A76800_jp[processIndex];
    
    for (i = 0; i < 3; i++) {
        pos.z = D_FLT_80A76814_jp[i] + this->structureActor.actor.home.pos.z;
        
        pos.x = D_FLT_80A76808_jp[0] + this->structureActor.actor.home.pos.x;
        mCoBG_SetPluss5PointOffset_file(pos, *offsetTable, "../ac_goza_move.c_inc", 0x5D);
        offsetTable++;
        pos.x = D_FLT_80A76808_jp[1] + this->structureActor.actor.home.pos.x;
        mCoBG_SetPluss5PointOffset_file(pos, *offsetTable, "../ac_goza_move.c_inc", 0x61);
        offsetTable++;
        pos.x = D_FLT_80A76808_jp[2] + this->structureActor.actor.home.pos.x;
        mCoBG_SetPluss5PointOffset_file(pos, *offsetTable, "../ac_goza_move.c_inc", 0x65);
        offsetTable++;
    }
}

void aGOZ_wait(Goza* this UNUSED, Game_Play* game_play UNUSED) {
}

extern GozaActionFunc process[];

void aGOZ_setup_action(Goza* this, s32 processIndex) {
    // TODO: replace extern with static
    // static GozaActionFunc process[] = { aGOZ_wait };

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
    
    if ((mDemo_Check(1, &player->actor) == 0) && (mDemo_Check(5, &player->actor) == 0) &&
        ((gozaBlockX != playerBlockX) || (gozaBlockZ != playerBlockZ))) {
        Actor_delete(&goza->actor);
    } else {
        ((GozaActionFunc)goza->process)(this, game_play);
    }
}

void aGOZ_actor_init(Actor *thisx, Game_Play *game_play) {
    Goza* this = THIS;
    StructureActor* goza = &this->structureActor;
    
    mFI_SetFG_common(0xF0F4, goza->actor.home.pos, FALSE);
    aGOZ_actor_move(&goza->actor, game_play);
    goza->actor.update = aGOZ_actor_move;
}
/* Warning: struct struct_8085E9B0 is not defined (only forward-declared) */
/* Warning: struct SceneDmaStatus is not defined (only forward-declared) */

extern Vtx obj_e_goza_shadow_v;
// TODO: change extern below to explicit (not static)
// u8 aGOZ_shadow_vtx_fix_flg_table[0x18] = { 1, 0, 0, 1, 0, 1, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1 };
// ShadowData aGOZ_shadow_data = { 0x18, aGOZ_shadow_vtx_fix_flg_table, 60.0f, &obj_e_goza_shadow_v, (Gfx *)0x06001358 };
// 
// TODO: give 0x06001358 symbol obj_e_goza_shadowT_model in undefined_syms.ld
// (possible complication: address in undefined_syms.ld is different)
extern u8 aGOZ_shadow_vtx_fix_flg_table;
extern ShadowData aGOZ_shadow_data;


void aGOZ_actor_draw(Actor *thisx, Game_Play *game_play) {
    GraphicsContext* gfxCtx = game_play->state.gfxCtx;
    u32 object = common_data.clip.structureClip->getObjectSegment(STRUCTURE_TYPE_GOZA);
    u16* palette = common_data.clip.structureClip->getPalSegment(STRUCTURE_PALETTE_GOZA);
    Mtx *mtx =_Matrix_to_Mtx_new(gfxCtx);

    _texture_z_light_fog_prim_shadow(gfxCtx);
    
    OPEN_SHADOW_DISP(gfxCtx);
    gSPSegment(__shadow_gfx++, G_MWO_SEGMENT_8, palette);
    gSegments[6] = (uintptr_t)OS_PHYSICAL_TO_K0(object);
    gSPSegment(__shadow_gfx++, G_MWO_SEGMENT_6, object);
    gDPSetPrimColor(__shadow_gfx++, 0, 0x80, 0xff, 0xff, 0xff, 0xff);

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
/* Warning: struct struct_8085E9B0 is not defined (only forward-declared) */
/* Warning: struct SceneDmaStatus is not defined (only forward-declared) */
/* Warning: struct WeatherClip is not defined (only forward-declared) */
/* Warning: struct Clip_unk_07C_unk_0_arg0 is not defined (only forward-declared) */
/* Warning: struct FurnitureActor is not defined (only forward-declared) */
/* Warning: struct ToolClip is not defined (only forward-declared) */