#include "m_roll_lib.h"
#include "z64math.h"
#include "m_field_info.h"
#include "m_field_make.h"
#include "overlays/gamestates/ovl_play/m_play.h"
#include "overlays/actors/player_actor/m_player.h"
#include "m_player_lib.h"
#include "sys_math_atan.h"
#include "m_collision_bg.h"
#include "69E2C0.h"
#include "macros.h"

void mRlib_spdXZ_to_spdF_Angle(xyz_t* speed, f32* speedf, s16* angle) {
    f32 x = speed->x;
    f32 z = speed->z;

    speedf[0] = sqrtf(x * x + z * z);
    angle[0] = atans_table(z, x);
}

void mRlib_spdF_Angle_to_spdXZ(xyz_t* speed, f32* speedf, s16* angle) {
    speed->x = speedf[0] * sin_s(angle[0]);
    speed->z = speedf[0] * cos_s(angle[0]);
}

s32 mRlib_position_move_for_sloop(Actor* actor, s_xyz* slopeAngle) {
    UNUSED s32 pad;
    f32 y;
    f32 x;
    f32 z;

    if (actor->colCheck.colResult.onGround && (slopeAngle->x != 0 || slopeAngle->z != 0)) {
        x = (actor->velocity.x * ABS(cos_s(slopeAngle->z)));
        y = actor->velocity.y;
        z = (actor->velocity.z * ABS(cos_s(slopeAngle->x)));

        actor->world.pos.x += x + actor->colStatus.displacement.x;
        actor->world.pos.y += y + actor->colStatus.displacement.y;
        actor->world.pos.z += z + actor->colStatus.displacement.z;

        return TRUE;
    } else {
        Actor_position_move(actor);
        return FALSE;
    }
}

s32 mRlib_Get_norm_Clif(Actor* actor, xyz_t* norm) {
    s16 angles[2];
    s16 angle;
    f32 percent;
    s32 i;

    if (mCoBG_CheckAttribute_BallRolling(angles, &actor->world.pos)) {

        for (i = 0; i < 2; i++) {
            percent = mCoBG_CheckBallRollingArea(angles[i], &actor->world.pos);

            if (percent > 0.0f && percent < 0.5f) {
                xyz_t rot;
                xyz_t pos;
                angle = angles[i] + DEG_TO_BINANG_ALT2(90.0f);
                pos = *norm;

                rot.x = sin_s(angle);
                rot.y = 0.0f;
                rot.z = cos_s(angle);

                Matrix_RotateVector(DEG_TO_BINANG_ALT4((0.5f - percent) * 80.0f), &rot, 0);
                Matrix_Position(&pos, norm);

                return TRUE;
            }
        }
    }
    return FALSE;
}

void mRlib_Roll_Matrix_to_s_xyz(Actor* actor, s_xyz* rot, s16 angle) {
    MtxF matrix;
    xyz_t axis;

    axis.x = cos_s(actor->world.rot.y);
    axis.z = -sin_s(actor->world.rot.y);
    axis.y = 0.0f;

    Matrix_RotateVector(angle, &axis, 0);
    Matrix_rotateXYZ(rot->x, rot->y, rot->z, 1);
    Matrix_get(&matrix);
    Matrix_to_rotate2_new(&matrix, rot, 0);
}

s16 mRlib_Get_HitWallAngleY(Actor* actor) {
    u16 angle = actor->colCheck.wallInfo[0].angleY;
    u16 angle2;
    s16 median;

    if (actor->colCheck.colResult.unk3 != 1) {
        angle2 = actor->colCheck.wallInfo[1].angleY;
        median = (angle + angle2) >> 1;

        if (ABS(angle - angle2) > 0x8000) {
            median += 0x8000;
        }
    } else {
        median = angle;
    }

    return median;
}

void mRlib_Station_step_modify_to_wall(Actor* actor) {
    s_xyz angle;
    f32 z;

    mCoBG_GetBgY_AngleS_FromWpos(&angle, actor->world.pos, 0.0f);

    if (angle.x >= DEG_TO_BINANG_ALT2(45.0f)) {
        actor->colCheck.colResult.hitWall |= 3;
        z = FI_UT_WORLDSIZE_Z_F + ((s32)(actor->world.pos.z / FI_UT_WORLDSIZE_Z_F) * FI_UT_WORLDSIZE_Z);
        actor->colCheck.wallInfo[0].angleY = 0.0f;
        actor->colCheck.colResult.unk3 = 1;
        actor->world.pos.z = z;
    }
}

s32 mRlib_Set_Position_Check(Actor* actor) {
    s32 bx;
    s32 bz;
    s32 utX;
    s32 utZ;
    s32 set;
    s32 ofsX;
    s32 ofsZ;

    mFI_Wpos2BkandUtNuminBlock(&bx, &bz, &utX, &utZ, actor->world.pos);

    set = mNpc_CheckNpcSet(bx, bz, utX, utZ);
    if (set == FALSE) {
        for (ofsX = -1; ofsX < 2; ofsX++) {
            for (ofsZ = -1; ofsZ < 2; ofsZ++) {
                if ((ofsX != 0 || ofsZ != 0) && (utX + ofsX) < UT_X_NUM && (utX + ofsX) > 0 &&
                    (utZ + ofsZ) < UT_Z_NUM && (utZ + ofsZ) > 0) {
                    set = mNpc_CheckNpcSet(bx, bz, utX + ofsX, utZ + ofsZ);
                }

                if (set == TRUE) {
                    f32 y = actor->world.pos.y;

                    mFI_BkandUtNum2CenterWpos(&actor->world.pos, bx, bz, utX + ofsX, utZ + ofsZ);
                    actor->world.pos.y = y;

                    return set;
                }
            }
        }
    }

    return set;
}

s32 mRlib_HeightGapCheck_And_ReversePos(Actor* actor) {
    s32 bx;
    s32 bz;
    s32 utX;
    s32 utZ;

    if (mFI_GetPlayerWade() == 2 && mCoBG_ExistHeightGap_KeepAndNow_Detail(actor->world.pos)) {
        if (mRlib_Set_Position_Check(actor) != FALSE) {
            actor->velocity.y = 0.0f;
        } else {
            mFI_Wpos2BkandUtNuminBlock(&bx, &bz, &utX, &utZ, actor->world.pos);

            if (mNpc_GetMakeUtNuminBlock_hard_area(&utX, &utZ, bx, bz, 0)) {
                f32 y = actor->world.pos.y;

                mFI_BkandUtNum2CenterWpos(&actor->world.pos, bx, bz, utX, utZ);
                actor->world.pos.y = y;
                actor->velocity.y = 0.0f;

                return TRUE;
            }
            return FALSE;
        }
    }

    return TRUE;
}

s32 mRlib_Hole_check(Actor* actor) {
    u16* unitFG = mFI_GetUnitFG(actor->world.pos);

    if (unitFG != NULL && ((unitFG[0] >= 0x11 && unitFG[0] <= 0x29) || unitFG[0] == 0x5D)) {
        return TRUE;
    }

    return FALSE;
}

s32 mRlib_Get_ground_norm_inHole(Actor* actor, xyz_t* norm, f32* dist, s16* angleY, s16* angleRate, f32 rate) {
    if (mRlib_Hole_check(actor) != FALSE) {
        xyz_t centerPos;

        mFI_Wpos2UtCenterWpos(&centerPos, actor->world.pos);
        dist[0] = search_position_distance(&actor->world.pos, &centerPos);
        angleRate[0] = DEG_TO_BINANG_ALT4((dist[0] * 90.0f) * 0.0325f);
        angleRate[0] = (angleRate[0] * rate);
        angleY[0] = atans_table(actor->world.pos.z - centerPos.z, actor->world.pos.x - centerPos.x);

        norm->x = (-cos_s(angleRate[0])) * sin_s(angleY[0]);
        norm->y = -sin_s(angleRate[0]);
        norm->z = (-cos_s(angleRate[0])) * cos_s(angleY[0]);

        return TRUE;
    } else {
        dist[0] = 0.0f;

        return FALSE;
    }
}

s32 mRlib_PSnowmanTouchCheck(const xyz_t* wpos) {
    if (ABS(wpos->x) < FI_UT_WORLDSIZE_X_F && ABS(wpos->z) < FI_UT_WORLDSIZE_Z_F && ABS(wpos->y) < FI_UT_BASE_SIZE_F) {
        return TRUE;
    }

    return FALSE;
}

s32 mRlib_PSnowmanBreakCheck(Actor* actor, Game_Play* play, f32* speed) {
    Player* player = get_player_actor_withoutCheck(play);
    xyz_t posDiff;
    f32 y = actor->world.pos.y;

    actor->world.pos.y = mCoBG_GetBgY_OnlyCenter_FromWpos2(actor->world.pos, 0.0f);
    xyz_t_sub(&actor->world.pos, &player->actor.world.pos, &posDiff);
    actor->world.pos.y = y;

    if (mRlib_PSnowmanTouchCheck(&posDiff)) {
        if (Math3d_normalizeXyz_t(&posDiff)) {
            xyz_t velocity = player->actor.velocity;
            f32 dist = (posDiff.x * velocity.x) + (posDiff.z * velocity.z);

            if (dist > 0.0f) {
                speed[0] += dist;
            } else {
                add_calc0(speed, 30.0f / 100.0f, 20.0f);
            }
            if (speed[0] > 200.0f) {
                return TRUE;
            }
        } else {
            add_calc0(speed, 30.0f / 100.0f, 20.0f);
        }
    } else {
        add_calc0(speed, 30.0f / 100.0f, 20.0f);
    }
    return FALSE;
}

s32 mRlib_PSnowmanBreakNeckSwing(f32 f0, f32 scale, s16* angleY) {
    s16 rotX;
    s16 rotZ;
    s16 angle;

    if (f0 > 20.0f) {
        angleY[0] += (s16)((f0 * 40.0f));
        angle = angleY[0] & 0x7000;
        rotX = (4.5f * f0) * sin_s(angle);
        rotZ = (4.5f * f0) * cos_s(angle);

        Matrix_translate(0.0f, -1400.0f * scale, 0.0f, 1);
        Matrix_rotateXYZ(rotX, 0, rotZ, 1);
        Matrix_translate(0.0f, 1400.0f * scale, 0.0f, 1);
    }
}

s32 mRlib_PSnowman_NormalTalk(Actor* actor, Game_Play* play, f32* speed, void* proc) {
    if (mDemo_Check(7, actor) == FALSE) {
        f32 y;

        if (mRlib_PSnowmanBreakCheck(actor, play, speed) != FALSE) {
            return FALSE;
        }
        y = actor->world.pos.y;
        actor->world.pos.y = mCoBG_GetBgY_AngleS_FromWpos(NULL, actor->world.pos, 0.0f);
        mDemo_Request(7, actor, proc);
        actor->world.pos.y = y;
    } else {
        add_calc0(speed, 3.0f / 10.0f, 20.0f);
    }

    return TRUE;
}
