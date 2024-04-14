#include "ac_ball.h"
#include "m_actor_dlftbls.h"
#include "m_object.h"
#include "m_actor_shadow.h"
#include "overlays/gamestates/ovl_play/m_play.h"
#include "overlays/actors/player_actor/m_player.h"
#include "libc/math.h"
#include "m_npc.h"
#include "audio.h"
#include "6F2150.h"
#include "m_field_info.h"
#include "sys_math_atan.h"
#include "m_player_lib.h"
#include "macros.h"
#include "segment_symbols.h"

#include "objects/act_ball_b/act_ball_b.h"
#include "objects/act_ball_d/act_ball_d.h"
#include "objects/act_ball_s/act_ball_s.h"

#define THIS ((Ball*)thisx)

void aBALL_actor_ct(Actor* thisx, Game_Play* game_play);
void aBALL_actor_dt(Actor* thisx, Game_Play* game_play);
void aBALL_actor_move(Actor* thisx, Game_Play* game_play);
void aBALL_actor_draw(Actor* thisx, Game_Play* game_play);

void func_8096A86C_jp(void);
void aBALL_process_air(Ball* this, Game_Play* game_play);
void aBALL_process_ground(Ball* this, Game_Play* game_play);
void aBALL_process_ground_init(Ball* this, Game_Play* game_play);
void aBALL_process_air_water_init(Ball* this, Game_Play* game_play);
void aBALL_process_air_water(Ball* this, Game_Play* game_play);
void aBALL_process_ground_water_init(Ball* this, Game_Play* game_play);
void aBALL_process_ground_water(Ball* this, Game_Play* game_play);

static Ball* Global_Actor_p;

Gfx* ball_model_tbl[3] = {
    act_ball_b_model,
    act_ball_d_model,
    act_ball_s_model,
};

ActorProfile Ball_Profile = {
    /* */ ACTOR_BALL,
    /* */ ACTOR_PART_4,
    /* */ ACTOR_FLAG_10,
    /* */ 0x8001,
    /* */ GAMEPLAY_KEEP,
    /* */ sizeof(Ball),
    /* */ aBALL_actor_ct,
    /* */ aBALL_actor_dt,
    /* */ aBALL_actor_move,
    /* */ aBALL_actor_draw,
    /* */ NULL,
};

ClObjPipe_Init aBALL_CoInfoData = {
    { OC1_1 | OC1_TYPE_8 | OC1_TYPE_10 | OC1_TYPE_20, OC2_TYPE_20, COLSHAPE_PIPE },
    { ELEM_FLAG_1 },
    { { 0xD, 0x1E, -0xA, { 0, 0, 0 } } },
};

CollisionCheck_Status_Init aBALL_StatusData = {
    0, 0xD, 0x1E, -0xA, 100,
};

// Original name unknown.
s32 aBALL_secure_bank_area(Ball* this, Game_Play* game_play, s32 type) {
    size_t romSize;
    s32 bank;

    bank = game_play->objectExchangeBank.num;
    switch (type) {
        case BALL_TYPE_B:
            romSize = SEGMENT_ROM_SIZE(act_ball_b);
            break;
        case BALL_TYPE_D:
            romSize = SEGMENT_ROM_SIZE(act_ball_d);
            break;
        case BALL_TYPE_S:
            romSize = SEGMENT_ROM_SIZE(act_ball_s);
            break;
        default:
            romSize = SEGMENT_ROM_SIZE(act_ball_b);
            break;
    }

    if (mSc_secure_exchange_keep_bank(&game_play->objectExchangeBank, 0, romSize)) {
        this->segment = game_play->objectExchangeBank.status[bank].segment;
        return true;
    }
    return false;
}

// Original name unknown.
void func_80968AF4_jp(Ball* this, s32 type) {
    RomOffset romStart;
    RomOffset romEnd;

    switch (type) {
        case BALL_TYPE_B:
            romStart = SEGMENT_ROM_START(act_ball_b);
            romEnd = SEGMENT_ROM_END(act_ball_b);
            break;
        case BALL_TYPE_D:
            romStart = SEGMENT_ROM_START(act_ball_d);
            romEnd = SEGMENT_ROM_END(act_ball_d);
            break;
        case BALL_TYPE_S:
            romStart = SEGMENT_ROM_START(act_ball_s);
            romEnd = SEGMENT_ROM_END(act_ball_s);
            break;
        default:
            romStart = SEGMENT_ROM_START(act_ball_b);
            romEnd = SEGMENT_ROM_END(act_ball_b);
            break;
    }
    if ((romStart != NULL) && (romEnd != NULL)) {
        DmaMgr_RequestSyncDebug(this->segment, romStart, romEnd - romStart, "../ac_ball.c", 0x11D);
    }
}

s32 aBALL_Random_pos_set(xyz_t* pos) {
    s32 xMax;
    s32 zMax;
    s32 utX;
    s32 utZ;
    s32 xIncrement;
    s32 zIncrement;
    s32 x;
    s32 z;
    s32 i;
    s32 j;

    xMax = mFI_GetBlockXMax();
    zMax = mFI_GetBlockZMax();
    x = RANDOM_F(xMax);
    z = RANDOM_F(zMax);

    for (i = 0; i < xMax; i++) {
        for (j = 0; j < zMax; j++) {
            if (!mFI_CheckBlockKind_OR(x, z, 0x8023) && mNpc_GetMakeUtNuminBlock_hard_area(&utX, &utZ, x, z, 2) == 1) {
                mFI_BkandUtNum2CenterWpos(pos, x, z, utX, utZ);
                return true;
            }

            zIncrement = z + 1;
            z = zMax;

            if (z == zIncrement) {
                z = 0;
            } else {
                z = zIncrement;
            }
        }

        xIncrement = x + 1;
        x = xMax;

        if (x == xIncrement) {
            x = 0;
        } else {
            x = xIncrement;
        }
    }

    return false;
}

void aBALL_actor_ct(Actor* thisx, Game_Play* game_play) {
    Ball* this = THIS;
    UNK_TYPE1 pad[0x4];

    Global_Actor_p = this;
    if ((common_data.unk_10A6C.x == 0.0f) && (common_data.unk_10A6C.y == 0.0f) && (common_data.unk_10A6C.z == 0.0f)) {

        if (!aBALL_Random_pos_set(&this->actor.world.pos)) {
            this->actor.world.pos = this->actor.home.pos;
        }
        common_data.unk_10A78 = RANDOM_F(3);
        common_data.unk_10A6C = this->actor.world.pos;
        this->type = common_data.unk_10A78;
    } else {
        this->actor.world.pos = common_data.unk_10A6C;
        this->type = common_data.unk_10A78;
    }
    aBALL_secure_bank_area(this, game_play, this->type);
    func_80968AF4_jp(this, this->type);
    common_data.clip.unk_0D0 = func_8096A86C_jp;
    Shape_Info_init(&this->actor, 0.0f, mAc_ActorShadowEllipse, 9.0f, 17.0f);
    ClObjPipe_ct(game_play, &this->collider);
    ClObjPipe_set5(game_play, &this->collider, &this->actor, &aBALL_CoInfoData);
    CollisionCheck_Status_set3(&this->actor.colStatus, &aBALL_StatusData);
    this->bounceTimer = 3;
    aBALL_process_ground_init(this, game_play);
    this->colliderActor = 0;
    this->actor.terminalVelocity = -20.0f;
    this->actor.gravity = 0.6f;
    this->actor.speed = 0.0f;
    this->maxSpeed = 0.0f;
    this->acceleration = 0.12f;
    this->actor.scale.x = 0.01f;
    this->actor.scale.y = 0.01f;
    this->actor.scale.z = 0.01f;
    this->speed = 0.0f;
    this->unk_20A = 0;
}

void aBALL_actor_dt(Actor* thisx, Game_Play* game_play) {
    Ball* this = THIS;

    if ((this->unk_208 & BALL_208_FLAG_1) || (this->unk_208 & BALL_208_FLAG_2) ||
        !mRlib_Set_Position_Check(&this->actor)) {
        common_data.unk_10A6C = ZeroVec;
    } else {
        common_data.unk_10A6C = this->actor.world.pos;
    }
    common_data.clip.unk_0D0 = NULL;
    ClObjPipe_dt(game_play, &this->collider);
}

void aBALL_position_move(Ball* this) {
    xyz_t slopeAngle;

    mCoBG_GetBgY_AngleS_FromWpos(&slopeAngle, this->actor.world.pos, 0.0f);

    if (this->actor.colResult.onGround || this->actor.colResult.inWater) {
        chase_f(&this->actor.speed, this->maxSpeed, this->acceleration);
    }

    if (!(this->unk_208 & BALL_208_FLAG_2)) {
        mRlib_spdF_Angle_to_spdXZ(&this->actor.velocity, &this->actor.speed, &this->actor.world.rot.y);
        chase_f(&this->actor.velocity.y, this->actor.terminalVelocity, this->actor.gravity);
        mRlib_position_move_for_sloop(&this->actor, &slopeAngle);
        if (this->actor.world.pos.z < 840.0f) {
            this->actor.world.pos.z = 840.0f;
        }
    }
}

void aBALL_BGcheck(Ball* this) {
    UNK_TYPE1 pad[0x4];
    f32 yVelocity;
    s32 hitWall;
    s16 wallAngle;
    s16 rot;
    xyz_t velocity;
    f32 sin;
    f32 cos;
    f32 sinCos;
    f32 speed;
    f32 adjustedSpeed;
    s32 rotMagnitude;

    yVelocity = this->actor.velocity.y;

    if ((this->process == aBALL_process_air_water) || (this->process == aBALL_process_ground_water) ||
        (this->actor.colResult.unk5 == 0xB)) {
        mCoBG_BgCheckControll(&this->bgPos, &this->actor, 12.0f, -12.0f, 0, 1, 0);
        this->actor.world.pos.x += this->bgPos.x;
        this->actor.world.pos.z += this->bgPos.z;
    } else {
        mCoBG_BgCheckControll(&this->bgPos, &this->actor, 12.0f, -12.0f, 0, 0, 0);
        mRlib_Station_step_modify_to_wall(&this->actor);
    }

    if (((this->process == aBALL_process_air) || (this->process == aBALL_process_air_water)) &&
        this->actor.colResult.onGround) {
        if (this->bounceTimer < 3) {
            do {
                this->bounceTimer++;
            } while (0);

            if (this->actor.colResult.inWater) {
                this->actor.velocity.y = 0.2f;
            } else {
                this->actor.velocity.y = -yVelocity * 0.7f;
            }
        }
    }

    hitWall = this->actor.colResult.hitWall;
    if (hitWall & 1) {
        wallAngle = mRlib_Get_HitWallAngleY(&this->actor);
        rot = this->actor.world.rot.y - wallAngle - 0x8000;
        rotMagnitude = ABS(rot);
        if (rotMagnitude < 0x4000) {
            velocity = this->actor.velocity;
            sin = sin_s(wallAngle);
            cos = cos_s(wallAngle);
            sinCos = sin * cos;
            speed = -((velocity.z * cos) + (velocity.x * sin));
            adjustedSpeed = (speed * 0.07f) + 1.2f;
            if (speed > 1.0f) {
                sAdo_OngenTrgStartSpeed(0x26, &this->actor.world.pos, speed);
            }
            this->actor.velocity.z =
                ((1.0f - (adjustedSpeed * cos * cos)) * velocity.z) - (velocity.x * adjustedSpeed * sinCos);
            this->actor.velocity.x =
                (-velocity.z * adjustedSpeed * sinCos) + (velocity.x * (1.0f - (adjustedSpeed * sin * sin)));
            mRlib_spdXZ_to_spdF_Angle(&this->actor.velocity, &this->actor.speed, &this->actor.world.rot.y);
        }
    }
}

void aBALL_OBJcheck(Ball* this) {
    s32 playerWade;
    Actor* colliderActor;
    s16 collidingAngle;
    f32 totalMomentum;
    f32 ballSpeed;
    f32 colliderSpeed;
    f32 colliderMomentum;
    f32 cos;
    UNK_TYPE1 pad[0x4];
    f32 sin;

    playerWade = mFI_GetPlayerWade();

    if (this->collider.base.prop.ocFlags1 & OC1_2) {
        xyz_t colliderVelocity;
        f32 xVelocityDiff;
        f32 zVelocityDiff;
        f32 newXVelocity;
        f32 newZVelocity;
        UNK_TYPE1 pad2[0x4];

        this->collider.base.prop.ocFlags1 &= ~OC1_2;

        colliderActor = this->collider.base.oc;
        if (mQst_CheckSoccerTarget(this->colliderActor)) {

            mQst_NextSoccer(this->colliderActor);
            this->actor.speed = 0.0f;
            this->actor.velocity = ZeroVec;
        } else if ((colliderActor != NULL) && (!(this->unk_208 & BALL_208_FLAG_2)) &&
                   ((playerWade != 1) && (playerWade != 2))) {

            if (colliderActor != this->colliderActor) {

                colliderVelocity = colliderActor->velocity;
                this->colliderActor = colliderActor;
                collidingAngle = atans_table(this->actor.world.pos.z - colliderActor->world.pos.z,
                                             this->actor.world.pos.x - colliderActor->world.pos.x);
                sin = sin_s(collidingAngle);
                cos = cos_s(collidingAngle);
                ballSpeed = (this->actor.velocity.x * sin) + (cos * this->actor.velocity.z);

                colliderSpeed = sqrtf(SQ(colliderVelocity.x) + SQ(colliderVelocity.z));

                xyz_t_mult_v(&colliderVelocity, (24.0f / 180.0f) * colliderSpeed * 0.9f + 0.1f);

                colliderMomentum = (sin * colliderVelocity.x) + (cos * colliderVelocity.z);
                totalMomentum = ABS_F(ballSpeed + colliderMomentum);

                xVelocityDiff = sin_s(collidingAngle) * totalMomentum;
                zVelocityDiff = cos_s(collidingAngle) * totalMomentum;
                newXVelocity = this->actor.velocity.x + xVelocityDiff;
                newZVelocity = this->actor.velocity.z + zVelocityDiff;
                ballSpeed = sqrtf(SQ(newXVelocity) + SQ(newZVelocity));
                ballSpeed = CLAMP_MAX(ballSpeed, 11.0f);

                if (this->actor.colResult.onGround) {
                    f32 speedFactor;
                    s16 verticalAngle;

                    if (this->actor.speed == 0.0f) {

                        speedFactor = ballSpeed / 11.0f;
                        verticalAngle =
                            DEG_TO_BINANG_ALT3(((fqrand2() * (35.0f * speedFactor)) + (90.0f * speedFactor)));

                        this->actor.speed = cos_s(verticalAngle) * ballSpeed;
                        this->actor.velocity.y = sin_s(verticalAngle) * ballSpeed;
                    } else {
                        this->actor.speed = ballSpeed * 0.75f;
                    }
                } else {
                    this->actor.speed = ballSpeed * 0.75f;
                }

                this->actor.world.rot.y = atans_table(newZVelocity, newXVelocity);
                this->actor.speed *= 0.9f;
                sAdo_OngenTrgStartSpeed(0x25, &this->actor.world.pos, this->actor.speed);

            } else {
                xyz_t newVelocity;
                xyz_t displacement;

                displacement = this->actor.colStatus.displacement;
                xyz_t_add(&this->actor.velocity, &displacement, &newVelocity);
                if ((playerWade != 1) && (playerWade != 2)) {

                    this->actor.speed = sqrtf(SQ(newVelocity.x) + SQ(newVelocity.z));
                    this->actor.speed = CLAMP_MAX(this->actor.speed, 11.0f);

                    this->actor.world.rot.y = atans_table(newVelocity.z, newVelocity.x);
                }
            }
        } else {
            this->colliderActor = NULL;
        }
    } else {
        this->colliderActor = NULL;
    }
}

void aBALL_House_Tree_Rev_Check(Ball* this) {
    if (mRlib_HeightGapCheck_And_ReversePos() != 1) {
        this->unk_208 |= BALL_208_FLAG_1;
        Actor_delete(&this->actor);
    }
}

void aBALL_process_air_init(Ball* this, Game_Play* game_play) {
    xyz_t* pos;
    f32 slopeAngle;

    pos = &this->actor.world.pos;
    slopeAngle = mCoBG_GetBgY_AngleS_FromWpos(NULL, this->actor.world.pos, 0.0f);
    this->actor.shape.drawShadow = 1;
    if ((this->process == aBALL_process_ground) && ((this->actor.world.pos.y - slopeAngle) > 20.0f)) {
        sAdo_OngenTrgStart(0x43D, pos);
    }
    this->process = aBALL_process_air;
}

void aBALL_process_air(Ball* this, Game_Play* game_play) {

    this->acceleration = 0.0f;
    add_calc0(&this->height, 0.5f, 100.0f);
    this->actor.terminalVelocity = -20.0f;
    this->actor.gravity = 0.6f;
    this->speed = this->actor.speed;
    if (this->actor.colResult.onGround) {
        if (this->actor.colResult.inWater) {
            aBALL_process_ground_water_init(this, game_play);
        } else {
            aBALL_process_ground_init(this, game_play);
        }
    } else if (this->actor.colResult.inWater) {
        aBALL_process_air_water_init(this, game_play);
    }
}

void aBALL_process_ground_init(Ball* this, Game_Play* game_play) {
    this->actor.shape.drawShadow = 1;
    if (this->actor.velocity.y > 0.0f) {
        this->process = aBALL_process_air;
    } else {
        this->process = aBALL_process_ground;
    }
}

void aBALL_process_ground(Ball* this, Game_Play* game_play) {
    s8 pad[0x4];
    xyz_t bgNorm;
    f32 distance;
    s16 angleRate;
    s16 yAngle;
    s32 var_v0;
    f32 xSpeed;
    f32 zSpeed;

    mCoBG_GetBgNorm_FromWpos(&bgNorm, this->actor.world.pos);
    if (mRlib_Get_ground_norm_inHole(&this->actor, &bgNorm, &distance, &yAngle, &angleRate, 1.0f)) {
        f32 targetHeight;

        targetHeight = (distance - 40.0f) - 5.0f;
        if (!(targetHeight < 0)) {
            targetHeight = 0;
        }
        targetHeight *= 25.0f;
        add_calc(&this->height, targetHeight, 0.5f, 200.0f, 5.0f);
        this->actor.velocity.x *= 0.7f;
        this->actor.velocity.z *= 0.7f;
        if (distance < 1.0f) {
            xSpeed = ABS_F(this->actor.velocity.x);

            if (xSpeed < 1.0f) {
                zSpeed = ABS_F(this->actor.velocity.z);

                if (zSpeed < 1.0f) {
                    this->unk_208 |= BALL_208_FLAG_2;
                    this->collider.attribute.dim.unk_2 = 0x14;
                    this->collider.attribute.dim.radius = 0x12;
                    this->actor.colStatus.mass = 0xFE;
                    this->actor.speed = 0.0f;
                    return;
                }
            }
        }
    } else {
        mRlib_Get_norm_Clif(&this->actor, &bgNorm);
        add_calc0(&this->height, 0.5f, 100.0f);
    }

    if (!(fabsf(bgNorm.x) < 0.008f) || !(fabsf(bgNorm.z) < 0.008f)) {
        if (Math3d_normalizeXyz_t(&bgNorm)) {
            this->actor.velocity.x += 1.35f * bgNorm.x;
            this->actor.velocity.z += 1.35f * bgNorm.z;
            mRlib_spdXZ_to_spdF_Angle(&this->actor.velocity, &this->maxSpeed, &this->actor.world.rot.y);
            if (this->maxSpeed < 8.0f) {
                this->maxSpeed = this->maxSpeed;
            } else {
                this->maxSpeed = 8.0f;
            }
            this->acceleration = 0.1f;
        }
    } else {
        this->maxSpeed = 0.0f;
        this->acceleration = 0.12f;
    }

    this->actor.terminalVelocity = -20.0f;
    this->actor.gravity = 0.6f;
    this->speed = this->actor.speed;
    if (this->actor.colResult.inWater || this->actor.colResult.unk5 == 0xB) {
        if (this->actor.colResult.onGround) {
            aBALL_process_ground_water_init(this, game_play);
        } else {
            this->bounceTimer = 0;
            aBALL_process_air_water_init(this, game_play);
        }
    } else if (!this->actor.colResult.onGround) {
        this->bounceTimer = 0;
        aBALL_process_air_init(this, game_play);
        return;
    }

    if (!(game_play->state.frameCounter & 7) && this->actor.colResult.unk5 == 9) {
        if (this->actor.speed > 1.0f) {

            if (this->actor.speed > 4.0f) {
                var_v0 = 1;
            } else {
                var_v0 = 0;
            }

            common_data.clip.unk_090->unk_00(0x33, this->actor.world.pos, 1, this->actor.world.rot.y, game_play,
                                             this->actor.fgName, 0, var_v0);
        }
    }
}

// TODO: this function includes an unreferenced float. It was forced to be in this function to
// be able to build and match the file. It needs to be figured out where to put this float and
// how to handle this when this file gets decompiled.

// RO_FLT_8096A96C_jp 0.200000003

s16 angl_add_table[2] = {
    0x100,
    0x400,
};

void aBALL_set_spd_relations_in_water(Ball* this, Game_Play* game_play) {
    UNK_TYPE1 pad[0x4];
    xyz_t flowPos;
    s16 yRot;
    f32 waterHeight;
    s32 yDiffAngle;

    waterHeight = mCoBG_GetWaterHeight_File(this->actor.world.pos, "../ac_ball.c", 0x3B5);
    add_calc0(&this->height, 0.5f, 100.0f);
    mCoBG_GetWaterFlow(&flowPos, this->actor.colResult.unk5);
    yRot = atans_table(flowPos.z, flowPos.x);
    yDiffAngle = ABS((s16)(this->actor.world.rot.y - yRot));

    chase_angle(&this->actor.world.rot.y, yRot, angl_add_table[((yDiffAngle > 0x4000))]);
    if (this->actor.world.pos.y < waterHeight) {
        this->actor.terminalVelocity = 1.0f;
    } else {
        this->actor.terminalVelocity = -1.0f;
    }

    if (this->waterTimer < 0x20) {
        if ((!(game_play->state.frameCounter & 3) && (this->waterTimer < 0x10)) ||
            !(game_play->state.frameCounter & 7)) {
            common_data.clip.unk_090->unk_00(0x45, this->actor.world.pos, 1, this->actor.world.rot.y, game_play,
                                             this->actor.fgName, 1, 0);
        }
        this->waterTimer++;
    }
    this->actor.gravity = 0.2f;
    this->acceleration = 0.2f;
    this->maxSpeed = 1.0f;
}

void aBALL_process_air_water_init(Ball* this, Game_Play* game_play) {
    this->actor.shape.drawShadow = 0;
    this->process = aBALL_process_air_water;
}

void aBALL_process_air_water(Ball* this, Game_Play* game_play) {

    aBALL_set_spd_relations_in_water(this, game_play);
    add_calc0(&this->height, 0.5f, 100.0f);

    // Perhaps a macro?
    {
        f32 speed = this->speed;
        speed -= 0.5f;
        speed = CLAMP_MIN(speed, 0.0f);
        this->speed = speed;
    }

    if (common_data.clip.unk_0A8 != NULL) {
        common_data.clip.unk_0A8->unk_0C(&this->actor.world.pos, 20.0f, 1);
    }

    if (this->actor.colResult.onGround) {
        if (this->actor.colResult.inWater) {
            aBALL_process_ground_water_init(this, game_play);
        } else if (this->actor.colResult.unk5 != 0xB) {
            aBALL_process_ground_init(this, game_play);
        }
    } else if (!this->actor.colResult.inWater) {
        aBALL_process_air_init(this, game_play);
    }
}

void aBALL_process_ground_water_init(Ball* this, Game_Play* game_play) {
    this->actor.shape.drawShadow = 0;
    this->waterTimer = 0;
    this->process = aBALL_process_ground_water;
}

void aBALL_process_ground_water(Ball* this, Game_Play* game_play) {
    f32 height;
    u32 unitAttribute;
    xyz_t* bgPos;

    unitAttribute = this->actor.colResult.unk5;

    aBALL_set_spd_relations_in_water(this, game_play);
    this->speed = this->actor.speed;

    if (common_data.clip.unk_0A8 != NULL) {
        common_data.clip.unk_0A8->unk_0C(&this->actor.world.pos, 20.0f, 1);
    }
    if (this->actor.colResult.onGround) {
        if (!this->actor.colResult.inWater && (unitAttribute != 0xB) && (unitAttribute != 0x16)) {
            aBALL_process_ground_init(this, game_play);
        }
    } else if (!this->actor.colResult.inWater) {
        aBALL_process_air_init(this, game_play);
    } else {
        aBALL_process_air_water_init(this, game_play);
    }

    if ((unitAttribute == 0xB) || (unitAttribute == 0x16)) {
        bgPos = &this->bgPos;
        this->actor.world.pos.y += (0.5f * bgPos->y);

        if (unitAttribute == 0x16) {
            height = ABS(bgPos->y);

            if (height < 1.0f) {
                aBALL_process_ground_init(this, game_play);
            }
        }
    }
}

void aBALL_calc_axis(Ball* this) {
    f32 yVelocityFactor;
    s16 angle;

    angle = this->actor.speed * 869.63904f;
    if ((this->process == aBALL_process_air_water) || (this->process == aBALL_process_ground_water)) {
        yVelocityFactor = ((-1.0f) - this->actor.velocity.y) / (-2.0f);
        angle *= sin_s(DEG_TO_BINANG((60.0f * yVelocityFactor) + 30.0f));
    }
    mRlib_Roll_Matrix_to_s_xyz(&this->actor, &this->ballRot, angle);
}

s32 aBALL_player_angle_distance_check(Ball* this, Player* player) {
    f32 distance;
    s16 yRot;

    distance = search_position_distance(&this->actor.world.pos, &player->actor.world.pos);
    yRot = player->actor.shape.rot.y - search_position_angleY(&player->actor.world.pos, &this->actor.world.pos);
    if (distance < 60.0f) {

        if (ABS(yRot) < 0x2000) {
            return 1;
        }
    }
    return 0;
}

void aBALL_status_check(Ball* this, Game_Play* game_play) {
    s32 i;

    if (this->unk_208 & BALL_208_FLAG_4) {
        Player* player;
        player = get_player_actor_withoutCheck(game_play);
        this->unk_208 &= ~BALL_208_FLAG_4;
        if ((aBALL_player_angle_distance_check(this, player)) || (fabsf(this->actor.speed) < 0.008f)) {
            this->actor.world.rot.y = player->actor.shape.rot.y;
            this->actor.speed = 2.0f;
            this->actor.velocity.y = 4.5f;
            if (this->unk_208 & BALL_208_FLAG_2) {
                this->collider.attribute.dim.unk_2 = 0x1E;
                this->collider.attribute.dim.radius = 0xD;
                this->unk_208 &= ~BALL_208_FLAG_2;
                this->actor.colStatus.mass = 0x64;
            }
        }
    }
    if (this->unk_208 & BALL_208_FLAG_8) {
        this->unk_208 &= ~BALL_208_FLAG_8;
        if (!(this->unk_208 & BALL_208_FLAG_2)) {
            Player* player;
            player = get_player_actor_withoutCheck(game_play);
            if ((aBALL_player_angle_distance_check(this, player)) || (fabsf(this->actor.speed) < 0.008f)) {
                this->actor.world.rot.y = player->actor.shape.rot.y + 0x2000;
                this->actor.speed = 4.5f;
                this->actor.velocity.y = 3.0f;
            }
        }
    }
    if (!(this->unk_208 & BALL_208_FLAG_1)) {
        if (this->actor.colResult.inWater) {
            sAdo_OngenTrgStart(0x27, &this->actor.world.pos);
            this->unk_208 |= BALL_208_FLAG_1;
            if (common_data.clip.unk_0A8 != NULL) {
                common_data.clip.unk_0A8->unk_0C(&this->actor.world.pos, 20.0f, 0);
            }
            this->collider.attribute.dim.unk_2 = 0xA;
            common_data.clip.unk_090->unk_00(0x3A, this->actor.world.pos, 1, 0, game_play, this->actor.fgName, 1, 0);

            for (i = 2; i < 6; i++) {
                common_data.clip.unk_090->unk_00(0x3B, this->actor.world.pos, 1, this->actor.world.rot.y, game_play,
                                                 this->actor.fgName, 0, i | 0x3000);
            }
        }
    }
}

void aBALL_actor_move(Actor* thisx, Game_Play* game_play) {
    UNK_TYPE1 pad[0x4];
    Ball* this = THIS;

    aBALL_House_Tree_Rev_Check(this);
    if (!((this->actor.flags) & ACTOR_FLAG_40)) {
        if ((this->actor.colResult.inWater) || (this->unk_208 & BALL_208_FLAG_2)) {
            Actor_delete(&this->actor);
        }
        if (this->actor.speed == 0.0f) {
            return;
        }
    }

    common_data.unk_10A6C = this->actor.world.pos;
    aBALL_position_move(this);
    this->process(this, game_play);
    aBALL_BGcheck(this);
    aBALL_OBJcheck(this);

    CollisionCheck_Uty_ActorWorldPosSetPipeC(&this->actor, &this->collider);
    CollisionCheck_setOC(game_play, &game_play->unk_2138, &this->collider.base);
    aBALL_calc_axis(this);
    aBALL_status_check(this, game_play);
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

void aBALL_actor_draw(Actor* thisx, Game_Play* game_play) {
    GraphicsContext* gfxCtx = game_play->state.gfxCtx;
    Ball* this = THIS;

    OPEN_DISPS(gfxCtx);
    OPEN_CUSTOM_POLY_OPA();
    gSPSegment(__polyOpa++, 0x06, this->segment);
    Matrix_translate(0.0f, this->height, 0.0f, 1);
    Matrix_rotateXYZ(this->ballRot.x, this->ballRot.y, this->ballRot.z, MTXMODE_APPLY);
    gDPPipeSync(__polyOpa++);
    gSPMatrix(__polyOpa++, _Matrix_to_Mtx_new(gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(__polyOpa++, ball_model_tbl[this->type]);
    CLOSE_CUSTOM_POLY_OPA();
    CLOSE_DISPS(gfxCtx);
}

// Original name unknown.
void func_8096A86C_jp(void) {
    if ((common_data.clip.unk_0D0 != NULL) && (Global_Actor_p != NULL)) {
        func_80968AF4_jp(Global_Actor_p, Global_Actor_p->type);
    }
}
