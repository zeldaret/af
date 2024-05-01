#include "ac_bee.h"
#include "m_actor_dlftbls.h"
#include "m_object.h"
#include "overlays/gamestates/ovl_play/m_play.h"
#include "overlays/actors/player_actor/m_player.h"
#include "m_field_info.h"
#include "libc/math.h"
#include "m_player_lib.h"
#include "m_rcp.h"
#include "macros.h"
#include "audio.h"

#include "objects/act_bee/act_bee.h"

#define THIS ((Bee*)thisx)

void aBEE_actor_ct(Actor* thisx, Game_Play* game_play);
void func_80A93DD0_jp(Actor* thisx, Game_Play* game_play);
void aBEE_actor_move(Actor* thisx, Game_Play* game_play);
void aBEE_actor_draw(Actor* thisx, Game_Play* game_play);

ActorProfile Bee_Profile = {
    /* */ ACTOR_BEE,
    /* */ ACTOR_PART_4,
    /* */ ACTOR_FLAG_10,
    /* */ 0x0000,
    /* */ OBJECT_ACT_BEE,
    /* */ sizeof(Bee),
    /* */ aBEE_actor_ct,
    /* */ func_80A93DD0_jp,
    /* */ aBEE_actor_move,
    /* */ aBEE_actor_draw,
    /* */ NULL,
};

void aBEE_setupAction(Bee*, s32, Game_Play*);

void aBEE_actor_ct(Actor* thisx, Game_Play* game_play) {
    Bee* this = THIS;
    SkeletonInfoR* skeletonInfo = &this->skeletonInfo;
    // Name Based on ac_fuusen
    xyz_t InitSize = { 0.0f, 0.0f, 0.0f };

    cKF_SkeletonInfo_R_ct(&this->skeletonInfo, &cKF_bs_r_act_bee, &cKF_ba_r_act_bee, this->jointTable,
                          this->morphTable);
    cKF_SkeletonInfo_R_init_standard_repeat(&this->skeletonInfo, Lib_SegmentedToVirtual(&cKF_ba_r_act_bee), 0);
    skeletonInfo->frameControl.currentFrame = 90.0f;
    cKF_SkeletonInfo_R_play(skeletonInfo);
    skeletonInfo->frameControl.speed = 0.0f;
    this->texScrollCounter2 = -0x8000;
    this->shapeFactor = 90.0f;
    xyz_t_move(&this->actor.scale, &InitSize);
    this->segment = game_play->objectExchangeBank.status[this->actor.unk_026].segment;
    this->actor.update = aBEE_actor_move;
    aBEE_setupAction(this, BEE_PROCESS_APPEAR, game_play);
}

// Original name unknown.
void func_80A93DD0_jp(UNUSED Actor* thisx, UNUSED Game_Play* game_play) {
}

void aBEE_appear_init(Bee* this, UNUSED Game_Play* game_play) {
    xyz_t Size_data = { 0.01f, 0.01f, 0.01f };

    xyz_t_move(&this->targetScale, &Size_data);
    common_data.unk_10A39 = 1;
}

// Original name unknown.
void func_80A93E38_jp(UNUSED Bee* this, UNUSED Game_Play* game_play) {
}

void aBEE_disappear_init(Bee* this, UNUSED Game_Play* game_play) {

    this->actor.speed = 9.7f;
    this->actor.shape.rot.x = this->actor.shape.rot.z = 0;
}

void aBEE_appear(Bee* this, Game_Play* game_play) {
    Player* player = get_player_actor_withoutCheck(game_play);

    this->targetHeight = player->actor.world.pos.y + 50.0f;
    this->alpha += 6;
    if (this->alpha >= 255) {
        this->alpha = 255;
    }
    this->actor.shape.rot.x = 0x7FFF;
    this->actor.shape.rot.z += 0x1000;

    // FAKE - Could use pointer to alpha throughout
    if (1) {}

    if (this->alpha == 255) {
        aBEE_setupAction(this, BEE_PROCESS_1, game_play);
    }
}

// Original name unknown. Possibly one of or a combination of aBEE_fly and aBEE_caught
void func_80A93EFC_jp(Bee* this, Game_Play* game_play) {
    UNUSED UNK_TYPE1 pad[0x4];
    Player* player;
    s16 angle;
    f32 yRot;
    f32 stepTargetOffset;
    Actor* sp68;
    s32 sp64;
    xyz_t sp58;
    f32 targetShapeFactor = 0.0f;

    player = get_player_actor_withoutCheck(game_play);
    sp68 = func_800B3B74_jp();
    sp64 = func_800B56D0_jp();
    add_calc_short_angle2(&this->actor.shape.rot.z, 0, 0.3f, 2000, 0);
    add_calc_short_angle2(&this->actor.shape.rot.x, 0, 0.3f, 2000, 0);
    if (&this->actor != sp68) {
        if (this->actor.shape.rot.x < 0x1001) {
            if (this->state != BEE_STATE_2) {

                if (((get_player_actor_withoutCheck((Game_Play*)gamePT)
                          ->unk_1234((Player*)get_player_actor_withoutCheck((Game_Play*)gamePT), (Game_Play*)gamePT) >
                      0.0f) ||
                     (func_800B3B24_jp(&sp58) != 0)) &&
                    (this->actor.xzDistToPlayer < 40.0f)) {
                    get_player_actor_withoutCheck((Game_Play*)gamePT)
                        ->unk_1238((Player*)get_player_actor_withoutCheck((Game_Play*)gamePT), (Game_Play*)gamePT,
                                   &this->actor, 1);
                } else {
                    get_player_actor_withoutCheck((Game_Play*)gamePT)
                        ->unk_1230((Player*)get_player_actor_withoutCheck((Game_Play*)gamePT), (Game_Play*)gamePT,
                                   &this->actor, 1, &this->actor.world.pos, 24.0f);
                }
            }
        } else {
            return;
        }
    }

    if (&this->actor == sp68) {
        if (this->unk_448 == 0) {
            Clip_unk_07C_unk_0_arg0 sp3C;
            sp3C.unk_00 = 8;
            xyz_t_move(&sp3C.unk_04, &this->actor.world.pos);
            sp3C.unk_10 = 0;
            sp3C.unk_14 = game_play;
            this->unk_448 = common_data.clip.unk_07C->unk_0(&sp3C, 1);
        } else if (func_800B3BBC_jp(this->unk_448, 0) != 0) {
            aBEE_setupAction(this, BEE_PROCESS_DISAPPEAR, game_play);
            return;
        }
    }

    if (this->unk_448 == 0) {
        if (func_800B5EA4_jp(game_play) != 0) {
            this->state = BEE_STATE_1;
        }

        if (this->state != BEE_STATE_2) {
            if ((this->state != BEE_STATE_0) || (this->actor.xzDistToPlayer < 30.0f)) {
                this->state = BEE_STATE_1;
                if (sp64 == 1) {
                    func_800B2AD0_jp((Game_Play*)gamePT);
                    this->state = BEE_STATE_2;
                } else if (sp64 == 2) {
                    aBEE_setupAction(this, BEE_PROCESS_DISAPPEAR, game_play);
                    return;
                }
            }
        } else if ((func_800B1CBC_jp((Game_Play*)gamePT) == 0x5E) != 0) {
            if (func_800B5718_jp() != 0) {
                aBEE_setupAction(this, BEE_PROCESS_DISAPPEAR, game_play);
                return;
            }
        } else {
            func_800B2AD0_jp((Game_Play*)gamePT);
        }
    }
    stepTargetOffset = fabsf(90.0f - this->shapeFactor);
    this->targetRotStep = 1600;
    if (this->state != BEE_STATE_0) {
        this->targetRotStep = 5000;
    }
    stepTargetOffset *= 7.5f;
    add_calc_short_angle2(&this->rotStep, this->targetRotStep - (s16)(stepTargetOffset), 0.4f, 500, 0);
    add_calc_short_angle2(&this->actor.world.rot.y, this->actor.yawTowardsPlayer, 0.4f, this->rotStep, 0);
    this->actor.shape.rot.y = this->actor.world.rot.y;

    angle = ABS((s16)(this->actor.world.rot.y - this->actor.yawTowardsPlayer));

    if (angle > -0x8000) {
        angle = 0;
    }

    this->targetSpeed = 2.9f;
    this->targetSpeed += fabsf((0x8000 - angle) / (0x8000 / 6));

    add_calc(&this->actor.speed, this->targetSpeed, 0.3f, 0.3f, 0.0f);
    this->heightAmplitudeCounter += 0x1200;
    this->targetHeight = player->actor.world.pos.y + 50.0f;
    this->targetHeight += sin_s(this->heightAmplitudeCounter) * 5.0f;

    yRot = this->actor.yawTowardsPlayer - this->actor.world.rot.y;
    targetShapeFactor = (yRot / 30.0f) + 90.0f;

    if (targetShapeFactor < 0.0f) {
        targetShapeFactor = 0.0f;
    } else if (targetShapeFactor > 180.0f) {
        targetShapeFactor = 180.0f;
    }
    add_calc(&this->shapeFactor, targetShapeFactor, 0.5f, 10.0f, 0.0f);
}

void aBEE_disappear(Bee* this, UNUSED Game_Play* game_play) {

    this->targetScale.x = 0.03f;
    this->targetScale.z = 0.03f;
    this->targetScale.y = 0.03f;
    this->alpha -= 30;
    if (this->alpha < 0) {
        this->alpha = 0;
        Actor_delete(&this->actor);
    }
}

void aBEE_setupAction(Bee* this, s32 processIndex, Game_Play* game_play) {
    static BeeActionFunc init_proc[3] = {
        aBEE_appear_init,
        func_80A93E38_jp,
        aBEE_disappear_init,
    };
    static BeeActionFunc act_proc[3] = {
        aBEE_appear,
        func_80A93EFC_jp,
        aBEE_disappear,
    };

    this->processNum = processIndex;
    this->process = act_proc[this->processNum];
    init_proc[this->processNum](this, game_play);
}

// Original name unknown.
void func_80A9449C_jp(Bee* this, Game_Play* game_play) {
    UNUSED UNK_TYPE1 pad[0x4];
    void* segment;

    segment = game_play->objectExchangeBank.status[this->actor.unk_026].segment;
    if (segment != this->segment) {
        SkeletonInfoR* skeletonInfo = &this->skeletonInfo;
        skeletonInfo->skeleton = Lib_SegmentedToVirtual(&cKF_bs_r_act_bee);
        skeletonInfo->animation = Lib_SegmentedToVirtual(&cKF_ba_r_act_bee);
        this->segment = segment;
    }
}

void aBEE_actor_move(Actor* thisx, Game_Play* game_play) {
    // Original name unknown.
    static f32 SizeFraction[3] = {
        0.1f,
        0.1f,
        0.1f,
    };
    // Original name unknown.
    static f32 SizeStep[3] = {
        0.005f,
        0.005f,
        0.01f,
    };
    Bee* this = THIS;
    SkeletonInfoR* skeletonInfo = &this->skeletonInfo;
    f32 scaleFactor;

    func_80A9449C_jp(this, game_play);
    sAdo_OngenPos((uintptr_t) & this->actor, 0x30, &this->actor.world.pos);
    if (!(this->actor.world.pos.x < 0.0f) || !(this->actor.world.pos.z < 0.0f)) {
        if ((this->state == BEE_STATE_2) || (mFI_GetPlayerWade() == 0)) {
            Actor_position_moveF(&this->actor);
        }
        this->process(this, game_play);
        if ((this->processNum == BEE_PROCESS_APPEAR) || (this->processNum == BEE_PROCESS_DISAPPEAR)) {
            add_calc(&this->actor.scale.x, this->targetScale.x, SizeFraction[this->processNum],
                     SizeStep[this->processNum], 0.0f);
            add_calc(&this->actor.scale.y, this->targetScale.y, SizeFraction[this->processNum],
                     SizeStep[this->processNum], 0.0f);
            add_calc(&this->actor.scale.z, this->targetScale.z, SizeFraction[this->processNum],
                     SizeStep[this->processNum], 0.0f);
        } else {
            scaleFactor = fabsf(90.0f - this->shapeFactor);
            this->targetScale.x = ((scaleFactor / 360.0f) + 0.75f) * 0.01f;
            this->targetScale.y = ((scaleFactor / 360.0f) + 0.75f) * 0.01f;
            this->targetScale.z = ((1.5f - (scaleFactor / 180.0f)) * 0.01f);
            add_calc(&this->actor.scale.x, this->targetScale.x, 0.2f, 0.01f, 0.0f);
            add_calc(&this->actor.scale.y, this->targetScale.y, 0.2f, 0.01f, 0.0f);
            add_calc(&this->actor.scale.z, this->targetScale.z, 0.2f, 0.01f, 0.0f);
        }
        this->texScrollCounter1 += 1000;
        this->texScrollCounter2 -= 1000;
        skeletonInfo->frameControl.currentFrame = this->shapeFactor;
        cKF_SkeletonInfo_R_play(skeletonInfo);
        skeletonInfo->frameControl.speed = 0.0f;
        add_calc(&this->actor.world.pos.y, this->targetHeight, 0.3f, 3.0f, 0.0f);
    }
}

void aBEE_actor_draw(Actor* thisx, Game_Play* game_play) {
    Bee* this = THIS;
    s32 mtxIndex = game_play->state.frameCounter & 1;
    UNUSED UNK_TYPE1 pad[0x8];
    Gfx* texScroll;

    if (!(this->actor.world.pos.x < 0.0f) && !(this->actor.world.pos.z < 0.0f)) {
        func_80A9449C_jp(this, game_play);
        texScroll = two_tex_scroll(game_play->state.gfxCtx, 0, (s32)(sin_s(this->texScrollCounter1) * 90.0f),
                                   (s32)(cos_s(this->texScrollCounter1) * 90.0f), 32, 32, 1,
                                   (s32)(cos_s(this->texScrollCounter2) * 90.0f),
                                   (s32)(sin_s(this->texScrollCounter2) * 90.0f), 32, 32);
        if (texScroll != 0) {
            Matrix_push();
            _texture_z_light_fog_prim_xlu(game_play->state.gfxCtx);
            Setpos_HiliteReflect_xlu_init(&this->actor.world.pos, game_play);

            OPEN_POLY_XLU_DISP(game_play->state.gfxCtx);
            gDPSetPrimColor(__polyXlu++, 0, 255, 0, 0, 0, this->alpha);
            gSPSegment(__polyXlu++, 0x08, texScroll);
            CLOSE_POLY_XLU_DISP(game_play->state.gfxCtx);
            cKF_Si3_draw_R_SV(game_play, &this->skeletonInfo, this->mtx[mtxIndex], NULL, NULL, this);
            Matrix_pull();
        }
    }
}
