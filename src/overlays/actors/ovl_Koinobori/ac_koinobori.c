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

#define THIS ((Koinobori*)thisx)

void aKOI_actor_ct(Actor* thisx, Game_Play* game_play);
void aKOI_actor_dt(Actor* thisx, Game_Play* game_play);
void aKOI_actor_init(Actor* thisx, Game_Play* game_play);
void aKOI_actor_draw(Actor* thisx, Game_Play* game_play);
void func_80A9369C_jp(Koinobori *this, s32 processIndex);
void func_80A936BC_jp(Koinobori *this, s32 processIndex);

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

// #pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Koinobori/ac_koinobori/aKOI_actor_ct.s")
extern BaseSkeletonR D_601F22C;

void aKOI_actor_ct(Actor *thisx, Game_Play *game_play)
{
    Koinobori* this = THIS;

    gSegments[6] = OS_K0_TO_PHYSICAL(common_data.unk_10098->unk_AC(0x27));
    cKF_SkeletonInfo_R_ct(&this->skeletonInfo, &D_601F22C, 0, this->jointTable, this->morphTable);
    func_80A9369C_jp(this, 1);
    func_80A936BC_jp(this, 0);
    cKF_SkeletonInfo_R_play(&this->skeletonInfo);
}

// #pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Koinobori/ac_koinobori/aKOI_actor_dt.s")
void aKOI_actor_dt(Actor *thisx, Game_Play *game_play)
{
    Koinobori* this = THIS;

    common_data.unk_10098->unk_A8(&common_data.unk_10098->unk_B0, 8, 0x27, this);
    common_data.unk_10098->unk_A8(&common_data.unk_10098->unk_454, 9, 0x50, this);
    common_data.unk_10098->unk_A8(&common_data.unk_10098->unk_86C, 8, 0x27, this);
    cKF_SkeletonInfo_R_dt(&this->skeletonInfo);
}

// #pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Koinobori/ac_koinobori/func_80A9369C_jp.s")
void func_80A9369C_jp(Koinobori *this, s32 processIndex)
{

}

// #pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Koinobori/ac_koinobori/func_80A936AC_jp.s")
void func_80A936AC_jp(Koinobori *this, s32 processIndex)
{

}

// #pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Koinobori/ac_koinobori/func_80A936BC_jp.s")
extern BaseAnimationR D_601F6D4;
extern KoinoboriActionFunc D_80A93AB0_jp[];

void func_80A936BC_jp(Koinobori *this, s32 processIndex)
{
    cKF_SkeletonInfo_R_init(&this->skeletonInfo, this->skeletonInfo.skeleton, &D_601F6D4, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, ANIMATION_REPEAT, NULL);
    this->unk2A0 = D_80A93AB0_jp[processIndex];
    this->unk2B4 = processIndex;
}

// #pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Koinobori/ac_koinobori/func_80A9373C_jp.s")
void func_80A9373C_jp(Koinobori* this, Game_Play* game_play)
{
    s32 pad[2];
    Player* player = get_player_actor_withoutCheck(game_play);
    s32 sp40;
    s32 sp3C;
    s32 sp38;
    s32 sp34;
    s32 pad2;

    mFI_Wpos2BlockNum(&sp40, &sp3C, this->actor.world.pos);
    mFI_Wpos2BlockNum(&sp38, &sp34, player->actor.world.pos);
    if ((mDemo_Check(1, player) == 0) && (mDemo_Check(5, player) == 0) && ((sp40 != sp38) || (sp3C != sp34)))
    {
        Actor_delete(&this->actor);
        return;
    }
    gSegments[6] = OS_K0_TO_PHYSICAL(common_data.unk_10098->unk_AC(0x27));
    cKF_SkeletonInfo_R_play(&this->skeletonInfo);
    this->unk2A0(this, game_play);
    sAdo_OngenPos(this, 0x35, &this->actor.world.pos);
}

// #pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Koinobori/ac_koinobori/aKOI_actor_init.s")
void aKOI_actor_init(Actor *thisx, Game_Play *game_play)
{
    Koinobori* this = THIS;

    mFI_SetFG_common(0xF100, this->actor.home.pos, 0);
    func_80A9373C_jp(thisx, game_play);
    this->actor.update = func_80A9373C_jp;
}

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Koinobori/ac_koinobori/aKOI_actor_draw.s")
