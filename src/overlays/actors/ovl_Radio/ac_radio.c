#include "ac_radio.h"
#include "m_actor_dlftbls.h"
#include "m_object.h"
#include "overlays/gamestates/ovl_play/m_play.h"
#include "macros.h"
#include "m_field_info.h"
#include "src/overlays/actors/player_actor/m_player.h"
#include "m_player_lib.h"
#include "overlays/actors/ovl_Structure/ac_structure.h"
#include "gfx.h"
#include "m_rcp.h"

void aRAD_actor_ct(Actor* thisx, Game_Play* game_play);
void aRAD_actor_dt(Actor* thisx, Game_Play* game_play);
void aRAD_actor_init(Actor* thisx, Game_Play* game_play);
void aRAD_actor_draw(Actor* thisx, Game_Play* game_play);

void aRAD_animate(Radio* this, Game_Play* game_play);
void aRAD_setup_action(Radio* this, s32 processId);
void func_80A769E4_jp(Radio* this, s32 arg1);
void func_80A76B4C_jp(Actor* thisx, Game_Play* game_play);

/* original `.data` order:
 * - Radio_Profile
 * - aRAD_shadow_vtx_fix_flg_table
 * - aRAD_shadow_data
 * - aRAD_clip_offset
 * - aRAD_processes
 */

ActorProfile Radio_Profile = {
    /* */ ACTOR_RADIO,
    /* */ ACTOR_PART_0,
    /* */ 0,
    /* */ 0x582B,
    /* */ GAMEPLAY_KEEP,
    /* */ sizeof(Radio),
    /* */ aRAD_actor_ct,
    /* */ aRAD_actor_dt,
    /* */ aRAD_actor_init,
    /* */ aRAD_actor_draw,
    /* */ NULL,
};

extern Vtx aRAD_shadow_vertices[];
extern Gfx aRAD_shadow_model[];

static u8 aRAD_shadow_vtx_fix_flg_table[] = { 1, 0, 0, 1, 0, 1, 1, 0 };
static ShadowData aRAD_shadow_data = { 0x00000008, aRAD_shadow_vtx_fix_flg_table, 60.0f, aRAD_shadow_vertices,
                                       aRAD_shadow_model };

void aRAD_actor_ct(Actor* thisx, Game_Play* game_play UNUSED) {
    Radio* this = (Radio*)thisx;
    aRAD_setup_action(this, RADIO_PROCESS_ANIMATE);
    this->timer = 0;
    func_80A769E4_jp(this, 1);
}

void aRAD_actor_dt(Actor* thisx, Game_Play* game_play UNUSED) {
    // TODO: macro these calls as `*_REMOVE_*(type, actor)`
    common_data.clip.structureClip->removeInstanceProc(common_data.clip.structureClip->objectSegmentTable,
                                                       ARRAY_COUNT(common_data.clip.structureClip->objectSegmentTable),
                                                       STRUCTURE_TYPE_RADIO, thisx);
    common_data.clip.structureClip->removeInstanceProc(common_data.clip.structureClip->paletteSegmentTable,
                                                       ARRAY_COUNT(common_data.clip.structureClip->paletteSegmentTable),
                                                       STRUCTURE_PALETTE_RADIO, thisx);
    common_data.clip.structureClip->removeInstanceProc(common_data.clip.structureClip->shadowSegmentTable,
                                                       ARRAY_COUNT(common_data.clip.structureClip->shadowSegmentTable),
                                                       STRUCTURE_TYPE_RADIO, thisx);
}

void func_80A769E4_jp(Radio* this, s32 arg1) {
    // @note: dropping arg1 gets this function matching by itself too, but would break `aRAD_actor_ct`
    if (arg1) {} //! FAKE; just like in `aKAG_set_bgOffset`
    mCoBG_SetPlussOffset(this->actor.home.pos, 3, 100);
}

void aRAD_animate(Radio* this, Game_Play* game_play) {
    // come to think of it
    // - it's a morning aerobics radio
    // - that does something every 18 frames
    // looks like a notes particles emitter
    static xyz_t aRAD_clip_offset = { 2.0f, 0.0f, -10.0f };
    xyz_t offsetLocal = aRAD_clip_offset;
    xyz_t clipPos;
    if (this->timer >= 18) {
        this->timer = 0;
        Matrix_push();
        Matrix_translate(this->actor.world.pos.x, this->actor.world.pos.y, this->actor.world.pos.z, 0);
        Matrix_Position(&offsetLocal, &clipPos);
        Matrix_pull();
        // according to other call sites:
        // - `135 degrees` is a y-axis rotation
        // - `0x582B` is an "fgName"
        //   - it is the same value as `ActorProfile.unk_08`
        //   - should they be named the same?
        common_data.clip.unk_090->unk_00(0x20, clipPos, 1, DEG_TO_BINANG(135), game_play, 0x582B, 1, 0);
    }
    this->timer += 1;
}

void aRAD_setup_action(Radio* this, s32 processId) {
    static RadioActionFunc aRAD_processes[] = { aRAD_animate };
    this->process = aRAD_processes[processId];
    this->processId = processId;
}

void func_80A76B4C_jp(Actor* thisx, Game_Play* game_play) {
    Radio* this = (Radio*)thisx;
    UNUSED s32 pad;
    Player* player = get_player_actor_withoutCheck(game_play);

    s32 thisBlockX;
    s32 thisBlockZ;
    s32 playerBlockX;
    s32 playerBlockZ;

    mFI_Wpos2BlockNum(&thisBlockX, &thisBlockZ, thisx->world.pos);
    mFI_Wpos2BlockNum(&playerBlockX, &playerBlockZ, player->actor.world.pos);
    if ((mDemo_Check(1, &player->actor) == 0) && (mDemo_Check(5, &player->actor) == 0) &&
        ((thisBlockX != playerBlockX) || (thisBlockZ != playerBlockZ))) {
        Actor_delete(thisx);
        return;
    }
    this->process(this, game_play);
}

void aRAD_actor_init(Actor* thisx, Game_Play* game_play) {
    mFI_SetFG_common(0xF0F5, thisx->home.pos, 0);
    func_80A76B4C_jp(thisx, game_play);
    thisx->update = func_80A76B4C_jp;
}

void aRAD_actor_draw(UNUSED Actor* thisx, Game_Play* game_play) {
    extern Gfx aRAD_model[];
    GraphicsContext* gfxCtx = game_play->state.gfxCtx;
    s32 object = common_data.clip.structureClip->getObjectSegment(STRUCTURE_TYPE_RADIO);
    u16* palette = common_data.clip.structureClip->getPalSegment(STRUCTURE_PALETTE_RADIO);
    Mtx* mtx = _Matrix_to_Mtx_new(gfxCtx);
    if (mtx != NULL) {
        _texture_z_light_fog_prim_npc(gfxCtx);
        OPEN_POLY_OPA_DISP(gfxCtx);
        gSPSegment(__polyOpa++, 0x08, palette);
        gSegments[6] = (uintptr_t)OS_PHYSICAL_TO_K0(object);
        gSPSegment(__polyOpa++, 0x06, object);
        gSPMatrix(__polyOpa++, mtx, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPDisplayList(__polyOpa++, &aRAD_model);
        CLOSE_POLY_OPA_DISP(gfxCtx);
        // this function draws shadows only at the moment across several actors
        common_data.clip.unk_074->unk_04(game_play, &aRAD_shadow_data, 0x1C);
    }
}
