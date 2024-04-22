#include "ac_airplane.h"
#include "m_actor_dlftbls.h"
#include "m_object.h"
#include "overlays/gamestates/ovl_play/m_play.h"
#include "overlays/actors/player_actor/m_player.h"
#include "m_player_lib.h"
#include "m_actor_shadow.h"
#include "macros.h"
#include "m_rcp.h"

#include "objects/glider/glider.h"

#define THIS ((Airplane*)thisx)

void Airplane_Actor_ct(Actor* thisx, Game_Play* game_play);
void Airplane_Actor_dt(Actor* thisx, Game_Play* game_play);
void Airplane_Actor_move(Actor* thisx, Game_Play* game_play);
void Airplane_Actor_draw(Actor* thisx, Game_Play* game_play);

ActorProfile Airplane_Profile = {
    /* */ ACTOR_AIRPLANE,
    /* */ ACTOR_PART_4,
    /* */ ACTOR_FLAG_10 | ACTOR_FLAG_20,
    /* */ 0x8000,
    /* */ OBJECT_GLIDER,
    /* */ sizeof(Airplane),
    /* */ Airplane_Actor_ct,
    /* */ Airplane_Actor_dt,
    /* */ Airplane_Actor_move,
    /* */ Airplane_Actor_draw,
    /* */ NULL,
};

void Airplane_Actor_ct(Actor* thisx, UNUSED Game_Play* game_play) {
    Airplane* this = THIS;

    Shape_Info_init(thisx, 0.0f, mAc_ActorShadowEllipse, 6.5f, 6.5f);

    this->state = Ap_STATE_STOP_FLY_MOVE;
    this->speed = 6.2f;
    this->actor.speed = 6.2f;
    this->ySpeed = 0.0f;
    this->yRot = RAD_TO_DEG(BINANG_TO_RAD(thisx->world.rot.y));
    this->groundTimer = 0;
    this->windFrame = 0;
    this->windChangeFrame = 0;
    this->wind = NULL;
    this->zRot = 0.0f;
    this->xRot = 0.0f;
    this->targetYRot = this->yRot;
    this->startYRot = this->yRot;

    this->actor.world.pos.y = mCoBG_GetBgY_AngleS_FromWpos(0, this->actor.world.pos, -5.5f);
}

void Airplane_Actor_dt(Actor* thisx, UNUSED Game_Play* game_play) {
    UNUSED Airplane* this = THIS;
}

void Airplane_Actor_draw(Actor* thisx, Game_Play* game_play) {
    Airplane* this = THIS;

    if ((this->state != Ap_STATE_PLAYER_CATCH) && (this->state != Ap_STATE_START_FLY_MOVE)) {
        OPEN_DISPS(game_play->state.gfxCtx);
        _texture_z_light_fog_prim(game_play->state.gfxCtx);
        Matrix_RotateX(RAD_TO_BINANG(DEG_TO_RAD(this->xRot)), MTXMODE_APPLY);
        Matrix_RotateZ(RAD_TO_BINANG(DEG_TO_RAD(this->zRot)), MTXMODE_APPLY);
        Matrix_scale(50.0f, 50.0f, 50.0f, 1);
        gSPMatrix(POLY_OPA_DISP++, _Matrix_to_Mtx_new(game_play->state.gfxCtx),
                  G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPDisplayList(POLY_OPA_DISP++, glider_model);
        CLOSE_DISPS(game_play->state.gfxCtx);
    }
}

void aAp_RubberMove(f32* pValue, f32 target, f32 step) {
    *pValue = *pValue + ((target - *pValue) * step);
}

void aAp_FallByWall(Airplane* this) {
    if (this->actor.colResult.hitWall != 0) {
        this->state = Ap_STATE_FALL_FLY_MOVE;
    }
}

void aAp_GroundFriction(Airplane* this, Game_Play* game_play) {

    if (this->actor.colResult.onGround) {
        aAp_RubberMove(&this->speed, 0.0f, 0.6f);
        if (this->speed < 1.0f) {
            this->state = Ap_STATE_STOP_FLY_MOVE;
            this->speed = 0.0f;
            if (this->groundTimer >= 5) {
                this->groundTimer = 0;
                common_data.clip.unk_090->unk_00(1, this->actor.world.pos, 1, this->actor.world.rot.y, game_play,
                                                 this->actor.fgName, 0, 8);
            }
            this->groundTimer++;
        }
    }
}

void aAp_FreeFlyMove(Airplane* this, Game_Play* game_play) {

    aAp_RubberMove(&this->speed, 3.0f, 0.01f);
    aAp_RubberMove(&this->xRot, 19.0f, 0.045f);
    aAp_RubberMove(&this->zRot, 0.0f, 0.05f);
    aAp_GroundFriction(this, game_play);
    aAp_FallByWall(this);
}

void aAp_SomerFlyMove(Airplane* this, Game_Play* game_play) {
    f32 xAngle;

    switch (this->tiltState) {
        case Ap_TILT_DOWN:
            aAp_RubberMove(&this->xRot, -89.0f, 0.2f);
            aAp_RubberMove(&this->speed, 9.0f, 0.1f);
            if (this->xRot < -87.0f) {
                this->tiltState = Ap_TILT_UP;
                this->xRot = 60.0f;
            }
            break;
        case Ap_TILT_UP:
            aAp_RubberMove(&this->xRot, 0.0f, 0.04f);
            aAp_RubberMove(&this->speed, 10.0f, 0.1f);
            xAngle = ABS(this->xRot);

            if (xAngle < 3.0f) {
                this->state = Ap_STATE_FREE_FLY_MOVE;
                this->tiltState = Ap_TILT_DOWN;
            }
            aAp_GroundFriction(this, game_play);
            break;
        default:
            break;
    }
    aAp_FallByWall(this);
}

s32 aAp_SelectFly(Airplane* this, s32 joystickY) {
    u32 rand = RANDOM(7);

    if (joystickY > 67) {
        if (rand % 2) {
            this->state = Ap_STATE_FALL_FLY_MOVE2;
        } else {
            this->state = Ap_STATE_SOMER_FLY_MOVE;
            this->tiltState = Ap_TILT_DOWN;
        }
    } else {
        this->state = Ap_STATE_FREE_FLY_MOVE;
    }
    return 1;
}

void aAp_StartFlyMove(Airplane* this, Game_Play* game_play) {
    static s16 goal_angle_random[8] = {
        0x093E, 0x07D2, 0xFBBC, 0xF6C2, 0x0000, 0x1110, 0xEFA6, 0x105A,
    };
    static s16 goal_angle_random2[8] = {
        0x31C4, 0x1FFE, 0xDC74, 0xE002, 0xD558, 0x2AA8, 0x238C, 0x0000,
    };
    UNUSED UNK_TYPE1 pad[0x4];
    s32 joystickY = getJoystick_Y();
    Player* player = get_player_actor_withoutCheck(game_play);
    s32 randIndex = RANDOM_F(8);
    s16* goalAngle;
    UNUSED UNK_TYPE1 pad2[0x4];
    s32 joystickYMagnitude;

    if ((joystickY - this->joystickY) > 30) {
        joystickYMagnitude = ABS(this->joystickY);
        this->speed = ABS_F((f32)this->joystickY) * (7.0f / 80.0f) + 3.0f;

        aAp_SelectFly(this, joystickYMagnitude);
        goalAngle = (joystickYMagnitude > 50) ? goal_angle_random2 : goal_angle_random;
        this->actor.world.pos.y = player->actor.world.pos.y + 25.0f;
        this->actor.world.pos.x = player->actor.world.pos.x;
        this->actor.world.pos.z = player->actor.world.pos.z;
        this->yRot = RAD_TO_DEG(BINANG_TO_RAD(player->actor.shape.rot.y));
        this->targetYRot = RAD_TO_DEG(BINANG_TO_RAD(goalAngle[randIndex])) + this->yRot;
        this->xRot = this->speed * -(60.0f / 7.0f) + 30.0f;
        this->zRot = 0.0f;
        this->ySpeed = 0.0f;
        mPlib_request_main_wait_type3(game_play);
    }
}

void aAp_PlayerCatch(UNUSED Airplane* this, UNUSED Game_Play* game_play) {
}

void aAp_StopFlyMove(Airplane* this, UNUSED Game_Play* game_play) {
    this->speed = 0.0f;
    if ((this->actor.xzDistToPlayer <= 30.0f) && chkTrigger(A_BUTTON)) {
        this->state = Ap_STATE_PLAYER_CATCH;
    }
}

void aAp_FallFlyMove(Airplane* this, Game_Play* game_play) {
    aAp_RubberMove(&this->xRot, 60.0f, 0.04f);
    aAp_RubberMove(&this->speed, 5.0f, 0.02f);
    this->actor.world.pos.y -= 0.15f;
    if (this->actor.colResult.onGround) {
        common_data.clip.unk_090->unk_00(1, this->actor.world.pos, 1, this->actor.world.rot.y, game_play,
                                         this->actor.fgName, 0, 8);
        this->state = Ap_STATE_STOP_FLY_MOVE;
    }
}

void aAp_FallFlyMove2(Airplane* this, Game_Play* game_play) {
    aAp_RubberMove(&this->xRot, 70.0f, 0.15f);
    aAp_RubberMove(&this->speed, 10.0f, 0.02f);
    this->actor.world.pos.y -= 0.15f;
    if (this->actor.colResult.onGround) {
        common_data.clip.unk_090->unk_00(1, this->actor.world.pos, 1, this->actor.world.rot.y, game_play,
                                         this->actor.fgName, 0, 8);
        this->state = Ap_STATE_STOP_FLY_MOVE;
    }
}

void aAp_LeanAirplane(Airplane* this) {
    if (this->state == Ap_STATE_FREE_FLY_MOVE) {
        aAp_RubberMove(&this->zRot, 0.0f, 0.05f);
    } else if (this->yRot < this->startYRot) {
        aAp_RubberMove(&this->zRot, 50.0f, 0.05f);
    } else {
        aAp_RubberMove(&this->zRot, -50.0f, 0.05f);
    }
}

static xyz_t wind1 = { 2.0f, 1.0f, 4.0f };
static xyz_t wind2 = { -3.0f, -4.0f, -7.0f };
static xyz_t wind3 = { 4.0f, -3.0f, 1.0f };
static xyz_t wind4 = { -1.0f, 3.0f, -4.0f };

static xyz_t* wind_table[4] = {
    &wind1,
    &wind2,
    &wind3,
    &wind4,
};

static s32 wind_change_frame_table[10] = {
    300, 20, 500, 1000, 100, 700, 20, 200, 80, 70,
};

void aAp_WindSystem(Actor* thisx, UNUSED Game_Play* game_play) {
    Airplane* this = THIS;
    xyz_t direction = { 0.0f, 1.0f, 0.0f };
    s32 randWindTableIndex;
    s32 randWindFrameIndex;

    this->windFrame++;
    if (this->windFrame > this->windChangeFrame) {
        randWindTableIndex = RANDOM_F(4);
        randWindFrameIndex = RANDOM_F(10);
        this->windFrame = 0;
        this->windChangeFrame = wind_change_frame_table[randWindFrameIndex];
        this->wind = wind_table[randWindTableIndex];
    }

    if (this->state != Ap_STATE_STOP_FLY_MOVE && this->state != Ap_STATE_START_FLY_MOVE &&
        this->state != Ap_STATE_PLAYER_CATCH && this->wind) {
        sMath_RotateX(&direction, DEG_TO_RAD(this->xRot));
        sMath_RotateZ(&direction, DEG_TO_RAD(this->zRot));
        sMath_RotateY(&direction, DEG_TO_RAD(this->yRot));
    }
}

void aAp_CommonHandle(Actor* actor, Airplane* this, Game_Play* game_play) {

    aAp_LeanAirplane(this);
    actor->speed = cosf_table(DEG_TO_RAD(this->xRot)) * this->speed;
    this->ySpeed = sinf_table(DEG_TO_RAD(this->xRot)) * this->speed;

    actor->world.pos.y -= this->ySpeed;
    actor->world.rot.y = RAD_TO_BINANG(DEG_TO_RAD(this->yRot));
    actor->shape.rot.y = RAD_TO_BINANG(DEG_TO_RAD(this->yRot));
    Actor_position_moveF(actor);

    this->joystickX = getJoystick_X();
    this->joystickY = getJoystick_Y();

    switch (this->state) {
        case Ap_STATE_START_FLY_MOVE:
        case Ap_STATE_PLAYER_CATCH:
            actor->shape.drawShadow = 0;
            break;
        case Ap_STATE_FREE_FLY_MOVE:
        case Ap_STATE_FALL_FLY_MOVE:
        case Ap_STATE_FALL_FLY_MOVE2:
        case Ap_STATE_SOMER_FLY_MOVE:
            aAp_RubberMove(&this->yRot, this->targetYRot, 0.07f);
            actor->shape.drawShadow = 1;
            break;
        default:
            actor->shape.drawShadow = 1;
            break;
    }
    aAp_WindSystem(actor, game_play);
}

void aAp_ZbuttonChangeStatus(Airplane* this, Game_Play* game_play) {
    if (chkButton(Z_TRIG)) {
        if (this->state == Ap_STATE_PLAYER_CATCH) {
            mPlib_request_main_refuse_type1(game_play);
            this->state = Ap_STATE_START_FLY_MOVE;
        }
    } else if (this->state == Ap_STATE_START_FLY_MOVE) {
        mPlib_request_main_wait_type3(game_play);
        this->state = Ap_STATE_PLAYER_CATCH;
    }
}

f32 aAp_GetBgCheckOffsetY(s16 state) {
    if ((state == Ap_STATE_FALL_FLY_MOVE) || (state == Ap_STATE_STOP_FLY_MOVE)) {
        return -5.5f;
    }
    return 0.0f;
}

void Airplane_Actor_move(Actor* thisx, Game_Play* game_play) {
    static AirplaneActionFunc AirplaneMove[] = {
        aAp_FreeFlyMove,  aAp_FallFlyMove, aAp_FallFlyMove2, aAp_SomerFlyMove,
        aAp_StartFlyMove, aAp_StopFlyMove, aAp_PlayerCatch,
    };
    Airplane* this = THIS;

    this->startYRot = this->yRot;
    AirplaneMove[this->state](this, game_play);
    aAp_ZbuttonChangeStatus(this, game_play);
    aAp_CommonHandle(&this->actor, this, game_play);
    mCoBG_BgCheckControll(0, &this->actor, 15.0f, aAp_GetBgCheckOffsetY(this->state), 0, 0, 0);
}
