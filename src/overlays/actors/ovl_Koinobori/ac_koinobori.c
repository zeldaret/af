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

#define THIS ((Koinobori*)thisx)

void aKOI_actor_ct(Actor* thisx, Game_Play* game_play);
void aKOI_actor_dt(Actor* thisx, Game_Play* game_play);
void aKOI_actor_init(Actor* thisx, Game_Play* game_play);
void aKOI_actor_draw(Actor* thisx, Game_Play* game_play);
void aKOI_set_bgOffset(Koinobori *this, s32 processIndex);
void aKOI_setup_action(Koinobori *this, s32 processIndex);

#if 0
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
#endif

extern BaseSkeletonR D_601F22C;

void aKOI_actor_ct(Actor *thisx, Game_Play *game_play UNUSED)
{
    Koinobori* this = THIS;

    gSegments[6] = OS_K0_TO_PHYSICAL(common_data.unk_10098->unk_AC(0x27));
    cKF_SkeletonInfo_R_ct(&this->skeletonInfo, &D_601F22C, 0, this->jointTable, this->morphTable);
    aKOI_set_bgOffset(this, 1);
    aKOI_setup_action(this, 0);
    cKF_SkeletonInfo_R_play(&this->skeletonInfo);
}

void aKOI_actor_dt(Actor *thisx, Game_Play *game_play UNUSED)
{
    Koinobori* this = THIS;

    common_data.unk_10098->unk_A8(&common_data.unk_10098->unk_B0, 8, 0x27, &this->actor);
    common_data.unk_10098->unk_A8(&common_data.unk_10098->unk_454, 9, 0x50, &this->actor);
    common_data.unk_10098->unk_A8(&common_data.unk_10098->unk_86C, 8, 0x27, &this->actor);
    cKF_SkeletonInfo_R_dt(&this->skeletonInfo);
}

void aKOI_set_bgOffset(Koinobori *this UNUSED, s32 processIndex UNUSED)
{

}

void aKOI_wait(Koinobori *this UNUSED, s32 processIndex UNUSED)
{

}

extern BaseAnimationR D_601F6D4;
extern KoinoboriActionFunc D_80A93AB0_jp[];

void aKOI_setup_action(Koinobori *this, s32 processIndex)
{
    cKF_SkeletonInfo_R_init(&this->skeletonInfo, this->skeletonInfo.skeleton, &D_601F6D4, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, ANIMATION_REPEAT, NULL);
    this->unk2A0 = D_80A93AB0_jp[processIndex];
    this->unk2B4 = processIndex;
}

void aKOI_actor_move(Actor *thisx, Game_Play* game_play)
{
    Koinobori* this = THIS;
    s32 pad UNUSED;
    Player* player = get_player_actor_withoutCheck(game_play);
    s32 sp40;
    s32 sp3C;
    s32 sp38;
    s32 sp34;
    s32 pad2 UNUSED;

    mFI_Wpos2BlockNum(&sp40, &sp3C, this->actor.world.pos);
    mFI_Wpos2BlockNum(&sp38, &sp34, player->actor.world.pos);
    if ((mDemo_Check(1, &player->actor) == 0) && (mDemo_Check(5, &player->actor) == 0) && ((sp40 != sp38) || (sp3C != sp34)))
    {
        Actor_delete(&this->actor);
        return;
    }
    gSegments[6] = OS_K0_TO_PHYSICAL(common_data.unk_10098->unk_AC(0x27));
    cKF_SkeletonInfo_R_play(&this->skeletonInfo);
    this->unk2A0(this, game_play);
    sAdo_OngenPos(this, 0x35, &this->actor.world.pos);
}

void aKOI_actor_init(Actor *thisx, Game_Play *game_play)
{
    Koinobori* this = THIS;

    mFI_SetFG_common(0xF100, this->actor.home.pos, 0);
    aKOI_actor_move(thisx, game_play);
    this->actor.update = aKOI_actor_move;
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

extern ShadowData D_80A93A9C_jp; // aKOI_shadow_data
extern u8 D_80A93AB4_jp[]; // aKOI_obj_e_koinobori_a_pal
extern u8 D_80A93AD4_jp[]; // obj_e_koinobori_b_pal

void aKOI_actor_draw(Actor *thisx, Game_Play *game_play)
{
    GraphicsContext *gfxCtx = game_play->state.gfxCtx;
    Koinobori* this = THIS;
    Mtx *mtx;
    s32 pad UNUSED;
    s32 object;
    s32 palette;

    mtx = GRAPH_ALLOC_NO_ALIGN(gfxCtx, this->skeletonInfo.skeleton->unk01 * sizeof(Mtx));
    if (mtx != NULL)
    {
        object = common_data.unk_10098->unk_AC(0x27);
        palette = common_data.unk_10098->unk_450(0x50);

        // _texture_z_light_fog_prim_npc
        func_800BD5E8_jp(gfxCtx);
        OPEN_DISPS(gfxCtx);
        OPEN_POLY_OPA_DISPS();
        gSPSegment(__polyOpa++, 0x08, palette);
        gSPSegment(__polyOpa++, 0x09, Lib_SegmentedToVirtual(&D_80A93AD4_jp));
        gSPSegment(__polyOpa++, 0x0A, Lib_SegmentedToVirtual(&D_80A93AB4_jp));
        gSegments[6] = OS_K0_TO_PHYSICAL(object);
        gSPSegment(__polyOpa++, 0x06, object);
        CLOSE_POLY_OPA_DISPS();
        CLOSE_DISPS(gfxCtx);
        if (1){}
        cKF_Si3_draw_R_SV(game_play, &this->skeletonInfo, mtx, NULL, NULL, this);
        common_data.unk_10080->unk_04(game_play, &D_80A93A9C_jp, 0x27);
    }
}
