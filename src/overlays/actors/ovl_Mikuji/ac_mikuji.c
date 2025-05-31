#include "ac_mikuji.h"
#include "m_actor_dlftbls.h"
#include "m_object.h"
#include "m_player_lib.h"
#include "overlays/actors/player_actor/m_player.h"
#include "overlays/gamestates/ovl_play/m_play.h"
#include "m_demo.h"
#include "gfx.h"
#include "m_field_info.h"
#include "m_rcp.h"
#include "macros.h"
#include "code_variables.h"

void aMIK_actor_ct(Actor* actor, Game_Play* game_play);
void aMIK_actor_dt(Actor* actor, Game_Play* game_play);
void aMIK_actor_init(Actor* actor, Game_Play* play);
void aMIK_actor_draw(Actor* thisx, Game_Play* play);

ActorProfile Mikuji_Profile = {
    /* */ ACTOR_MIKUJI,
    /* */ ACTOR_PART_0,
    /* */ 0,
    /* */ 0x5830,
    /* */ GAMEPLAY_KEEP,
    /* */ sizeof(Mikuji),
    /* */ aMIK_actor_ct,
    /* */ aMIK_actor_dt,
    /* */ aMIK_actor_init,
    /* */ aMIK_actor_draw,
    /* */ NULL,
};

extern Vtx obj_e_mikuji_shadow_v[];
extern Gfx obj_e_mikuji_shadow_model[];

u8 aMIK_shadow_vtx_fix_flg_table[] = { 1, 0, 0, 1, 0, 1, 1, 0 };

ShadowData aMIK_shadow_data = {
    8, aMIK_shadow_vtx_fix_flg_table, 60.0f, obj_e_mikuji_shadow_v, obj_e_mikuji_shadow_model,
};

extern Gfx mikuji_DL_model[];

void aMIK_set_bgOffset(Mikuji* mikuji, s32 offs);
void aMIK_setup_action(Mikuji* mikuji, s32 action);

void aMIK_actor_ct(Actor* actor, UNUSED Game_Play* play) {
    Mikuji* mikuji = (Mikuji*)actor;
    aMIK_setup_action(mikuji, MIKUJI_ACTION_WAIT);
    aMIK_set_bgOffset(mikuji, 1);
}

void aMIK_actor_dt(Actor* actor, UNUSED Game_Play* play) {
    Mikuji* mikuji = (Mikuji*)actor;

    common_data.clip.structureClip->removeInstanceProc(common_data.clip.structureClip->objectSegmentTable,
                                                       ARRAY_COUNT(common_data.clip.structureClip->objectSegmentTable),
                                                       STRUCTURE_TYPE_MIKUJI, &mikuji->structureActor.actor);
    common_data.clip.structureClip->removeInstanceProc(common_data.clip.structureClip->paletteSegmentTable,
                                                       ARRAY_COUNT(common_data.clip.structureClip->paletteSegmentTable),
                                                       STRUCTURE_PALETTE_MIKUJI, &mikuji->structureActor.actor);
    common_data.clip.structureClip->removeInstanceProc(common_data.clip.structureClip->shadowSegmentTable,
                                                       ARRAY_COUNT(common_data.clip.structureClip->shadowSegmentTable),
                                                       STRUCTURE_TYPE_MIKUJI, &mikuji->structureActor.actor);
}

void aMIK_set_bgOffset(Mikuji* mikuji, s32 offs) {
    static mCoBG_unkStruct2 height_table_ct[] = {
        { 0x64, 2, 0, 2, 2, 2, 1 },
        { 0x64, 6, 6, 6, 6, 0, 1 },
        { 0x64, 2, 2, 0, 2, 2, 1 },
        { 0x64, 2, 2, 2, 0, 2, 1 },
    };
    static mCoBG_unkStruct2* height_table[] = { height_table_ct, height_table_ct };
    static f32 addX[] = { 0.0f, 40.0f };
    static f32 addZ[] = { 40.0f, 80.0f };

    mCoBG_unkStruct2* offset;
    xyz_t pos;
    s32 i;

    offset = height_table[offs];

    for (i = 0; i < 2; i++) {
        pos.z = mikuji->structureActor.actor.home.pos.z + addZ[i];
        pos.x = mikuji->structureActor.actor.home.pos.x + addX[0];
        mCoBG_SetPluss5PointOffset_file(pos, *offset, "../ac_mikuji_move.c_inc", 79);
        offset++;
        pos.x = mikuji->structureActor.actor.home.pos.x + addX[1];
        mCoBG_SetPluss5PointOffset_file(pos, *offset, "../ac_mikuji_move.c_inc", 83);
        offset++;
    }
}

void aMIK_wait(UNUSED Mikuji* mikuji, UNUSED Game_Play* play) {
}

void aMIK_setup_action(Mikuji* mikuji, s32 action) {
    static MikujiActionFunc process[] = {
        aMIK_wait,
    };
    mikuji->structureActor.process = process[action];
    mikuji->structureActor.unk_2B8 = action;
}

void aMIK_actor_move(Actor* actor, Game_Play* play) {
    Mikuji* mikuji = (Mikuji*)actor;
    UNUSED s32 pad;

    Player* player = get_player_actor_withoutCheck(play);
    s32 worldBx;
    s32 worldBz;
    s32 playerBx;
    s32 playerBz;

    mFI_Wpos2BlockNum(&worldBx, &worldBz, actor->world.pos);
    mFI_Wpos2BlockNum(&playerBx, &playerBz, player->actor.world.pos);

    if (mDemo_Check(1, &player->actor) == FALSE && mDemo_Check(5, &player->actor) == FALSE &&
        (worldBx != playerBx || worldBz != playerBz)) {
        Actor_delete(actor);
    } else {
        ((MikujiActionFunc)(mikuji->structureActor.process))(mikuji, play);
    }
}

void aMIK_actor_init(Actor* actor, Game_Play* play) {
    mFI_SetFG_common(0xF0F9, actor->home.pos, 0);
    aMIK_actor_move(actor, play);
    actor->update = &aMIK_actor_move;
}

void aMIK_actor_draw(UNUSED Actor* actor, Game_Play* play) {
    GraphicsContext* graph = play->state.gfxCtx;
    s32 obj;
    u16* pal;
    Mtx* cur;

    obj = common_data.clip.structureClip->getObjectSegment(STRUCTURE_TYPE_MIKUJI);
    pal = common_data.clip.structureClip->getPalSegment(STRUCTURE_PALETTE_MIKUJI);

    cur = _Matrix_to_Mtx_new(graph);

    if (cur != NULL) {
        _texture_z_light_fog_prim_npc(graph);
        OPEN_POLY_OPA_DISP(graph);
        gSPSegment(__polyOpa++, G_MWO_SEGMENT_8, pal);
        SegmentBaseAddress[6] = OS_K0_TO_PHYSICAL(obj);
        gSPSegment(__polyOpa++, G_MWO_SEGMENT_6, obj);

        gSPMatrix(__polyOpa++, cur, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPDisplayList(__polyOpa++, mikuji_DL_model);
        CLOSE_POLY_OPA_DISP(graph);
        common_data.clip.unk_074->unk_04(play, &aMIK_shadow_data, 32);
    }
}
