#include "m_lib.h"
#include "game.h"
#include "libc/math.h"
#include "m_rcp.h"
#include "macros.h"
#include "sys_math.h"
#include "sys_math_atan.h"

ValueSetProc D_80107B00_jp[] = {
    ValueSet__s_char, ValueSet__u_char,      ValueSet__s_short, ValueSet__u_short,     ValueSet__s_int, ValueSet__u_int,
    ValueSet__float,  ValueSet__float_x1000, ValueSet__xyz_t,   ValueSet__xyz_t_x1000, ValueSet__s_xyz,
};

void mem_copy(u8* dest, u8* src, size_t len) {
    while (len != 0) {
        *dest = *src;
        src++;
        dest++;
        len--;
    }
}

void mem_clear(u8* ptr, size_t len, u8 value) {
    size_t i;

    // clang-format off
    for (i = 0; i < len; i++) {*ptr++ = value;}
    // clang-format on
}

s32 mem_cmp(u8* ptr1, u8* ptr2, size_t len) {
    while (len != 0) {
        if (*ptr1 != *ptr2) {
            return 0;
        }
        ptr1++;
        ptr2++;
        len--;
    }
    return 1;
}

f32 cos_s(s16 angle) {
    return coss(angle) * SHT_MINV;
}

f32 sin_s(s16 angle) {
    return sins(angle) * SHT_MINV;
}

s32 chase_angle(s16* pValue, s16 target, s16 step) {
    if (step != 0) {
        f32 updateScale = game_GameFrame_2F;

        if ((s16)(*pValue - target) > 0) {
            step = -step;
        }

        *pValue += (s16)(step * updateScale);

        if (((s16)(*pValue - target) * step) >= 0) {
            *pValue = target;
            return TRUE;
        }
    } else if (*pValue == target) {
        return TRUE;
    }

    return FALSE;
}

s32 chase_s(s16* pValue, s16 target, s16 step) {
    if (step) {
        if (*pValue > target) {
            step = -step;
        }

        *pValue += step;

        if ((step * (*pValue - target)) >= 0) {
            *pValue = target;
            return TRUE;
        }
    } else {
        if (*pValue == target) {
            return TRUE;
        }
    }
    return FALSE;
}

s32 chase_f(f32* pValue, f32 target, f32 step) {
    if (step) {
        if (*pValue > target) {
            step = -step;
        }

        *pValue += step;

        if ((step * (*pValue - target)) >= 0.0f) {
            *pValue = target;
            return TRUE;
        }
    } else {
        if (*pValue == target) {
            return TRUE;
        }
    }
    return FALSE;
}

s32 chase_angle2(s16* pValue, s16 limit, s16 step) {
    s16 prev = *pValue;

    *pValue += step;
    if (((s16)(*pValue - limit) * (s16)(prev - limit)) <= 0) {
        *pValue = limit;
        return 1;
    }

    return 0;
}

s32 chase_s2(s16* pValue, s16 limit, s16 step) {
    s16 prev = *pValue;

    *pValue += step;
    if ((*pValue - limit) * (prev - limit) <= 0) {
        *pValue = limit;
        return 1;
    }
    return 0;
}

s32 chase_s3(s16* pValue, s16 target, s16 step) {
    if (step) {
        s32 diff = target - *pValue;

        if (diff < 0) {
            step = -step;
        }

        if (diff >= 0x8000) {
            step = -step;
            diff = -0xFFFF - -diff;
        } else if (diff <= -0x8000) {
            step = -step;
            diff += 0xFFFF;
        }

        *pValue += step;

        if ((diff * step) <= 0) {
            *pValue = target;
            return TRUE;
        }

    } else if (target == *pValue) {
        return TRUE;
    }
    return FALSE;
}

s32 chase_f2(f32* pValue, f32 limit, f32 step) {
    f32 prev = *pValue;

    *pValue += step;
    if ((*pValue - limit) * (prev - limit) <= 0.0f) {
        *pValue = limit;
        return 1;
    }
    return 0;
}

s32 chase_f3(f32* pValue, f32 target, f32 incrStep, f32 decrStep) {
    f32 step = (target >= *pValue) ? incrStep : decrStep;

    if (step != 0.0f) {
        if (target < *pValue) {
            step = -step;
        }

        *pValue += step;

        if (((*pValue - target) * step) >= 0) {
            *pValue = target;
            return 1;
        }
    } else if (target == *pValue) {
        return 1;
    }

    return 0;
}

void inter_float(f32* pValue, f32 arg1, s32 stepCount) {
    if (stepCount <= 0) {
        *pValue = arg1;
    } else {
        f32 diff = arg1 - *pValue;

        *pValue += diff / stepCount;
    }
}

void stick_ratio_set(f32* magnitude, s16* angle, Input* input) {
    f32 relX = input->rel.stick_x;
    f32 relY = input->rel.stick_y;

    *magnitude = sqrtf(SQ(relX) + SQ(relY));
    *magnitude = (*magnitude > 60.0f) ? 60.0f : *magnitude;

    *angle = atans_table(relY, -relX);
}

s16 get_random_timer(s16 base, s16 range) {
    return base + (s16)(RANDOM_F(range));
}

s16 get_random_pattern_timer(s16 base, s16 stride, s16 range) {
    return base + (s16)(RANDOM_F(range)) * stride;
}

void xyz_t_move(xyz_t* dest, xyz_t* src) {
    dest->x = src->x;
    dest->y = src->y;
    dest->z = src->z;
}

void xyz_t_move_s_xyz(xyz_t* dest, s_xyz* src) {
    dest->x = src->x;
    dest->y = src->y;
    dest->z = src->z;
}

void xyz_t_add(xyz_t* augend, xyz_t* addend, xyz_t* total) {
    total->x = augend->x + addend->x;
    total->y = augend->y + addend->y;
    total->z = augend->z + addend->z;
}

void xyz_t_sub(xyz_t* minuend, xyz_t* subtrahend, xyz_t* diff) {
    diff->x = minuend->x - subtrahend->x;
    diff->y = minuend->y - subtrahend->y;
    diff->z = minuend->z - subtrahend->z;
}

void xyz_t_sub_ss(xyz_t* dest, s_xyz* minuend, s_xyz* subtrahend) {
    dest->x = minuend->x - subtrahend->x;
    dest->y = minuend->y - subtrahend->y;
    dest->z = minuend->z - subtrahend->z;
}

void xyz_t_mult_v(xyz_t* multiplicand, f32 multiplier) {
    multiplicand->x *= multiplier;
    multiplicand->y *= multiplier;
    multiplicand->z *= multiplier;
}

f32 search_position_distance(xyz_t* subtrahend, xyz_t* minuend) {
    f32 diffX = minuend->x - subtrahend->x;
    f32 diffY = minuend->y - subtrahend->y;
    f32 diffZ = minuend->z - subtrahend->z;

    return sqrtf(SQ(diffX) + SQ(diffY) + SQ(diffZ));
}

f32 search_position_distance2(xyz_t* subtrahend, xyz_t* minuend, xyz_t* dest) {
    dest->x = minuend->x - subtrahend->x;
    dest->y = minuend->y - subtrahend->y;
    dest->z = minuend->z - subtrahend->z;

    return sqrtf(SQ(dest->x) + SQ(dest->y) + SQ(dest->z));
}

f32 search_position_distanceXZ(xyz_t* subtrahend, xyz_t* minuend) {
    f32 diffX = minuend->x - subtrahend->x;
    f32 diffZ = minuend->z - subtrahend->z;

    return sqrtf(SQ(diffX) + SQ(diffZ));
}

f32 search_position_high(xyz_t* subtrahend, xyz_t* minuend) {
    return minuend->y - subtrahend->y;
}

s16 search_position_angleY(xyz_t* subtrahend, xyz_t* minuend) {
    f32 diffX = minuend->x - subtrahend->x;
    f32 diffZ = minuend->z - subtrahend->z;

    return atans_table(diffZ, diffX);
}

s16 search_position_angleX(xyz_t* subtrahend, xyz_t* minuend) {
    f32 distXZ = search_position_distanceXZ(subtrahend, minuend);
    f32 diffY = subtrahend->y - minuend->y;

    return atans_table(distXZ, diffY);
}

void ValueSet_process(u8* ptr, ValueSet* values) {
    do {
        D_80107B00_jp[values->type](ptr, values);
    } while ((values++)->cont);
}

void ValueSet__s_char(u8* ptr, ValueSet* value_set) {
    *(s8*)(ptr + value_set->offset) = value_set->value;
}

void ValueSet__u_char(u8* ptr, ValueSet* value_set) {
    *(u8*)(ptr + value_set->offset) = value_set->value;
}

void ValueSet__s_short(u8* ptr, ValueSet* value_set) {
    *(s16*)(ptr + value_set->offset) = value_set->value;
}

void ValueSet__u_short(u8* ptr, ValueSet* value_set) {
    *(u16*)(ptr + value_set->offset) = value_set->value;
}

void ValueSet__s_int(u8* ptr, ValueSet* value_set) {
    *(s32*)(ptr + value_set->offset) = value_set->value;
}

void ValueSet__u_int(u8* ptr, ValueSet* value_set) {
    *(u32*)(ptr + value_set->offset) = value_set->value;
}

void ValueSet__float(u8* ptr, ValueSet* value_set) {
    *(f32*)(ptr + value_set->offset) = value_set->value;
}

void ValueSet__float_x1000(u8* ptr, ValueSet* value_set) {
    *(f32*)(ptr + value_set->offset) = value_set->value / 1000.0f;
}

void ValueSet__xyz_t(u8* ptr, ValueSet* value_set) {
    xyz_t* vec = (xyz_t*)(ptr + value_set->offset);
    f32 val = value_set->value;

    vec->z = val;
    vec->y = val;
    vec->x = val;
}

void ValueSet__xyz_t_x1000(u8* ptr, ValueSet* value_set) {
    xyz_t* vec = (xyz_t*)(ptr + value_set->offset);
    f32 val = value_set->value / 1000.0f;

    vec->z = val;
    vec->y = val;
    vec->x = val;
}

void ValueSet__s_xyz(u8* ptr, ValueSet* value_set) {
    s_xyz* vec = (s_xyz*)(ptr + value_set->offset);
    s16 val = value_set->value;

    vec->z = val;
    vec->y = val;
    vec->x = val;
}

f32 add_calc(f32* pValue, f32 target, f32 fraction, f32 step, f32 minStep) {
    f32 negMinStep;
    f32 stepSize;

    if (*pValue != target) {
        stepSize = fraction * (target - *pValue);
        negMinStep = -minStep;

        if ((stepSize <= negMinStep) || (minStep <= stepSize)) {
            if (stepSize > step) {
                stepSize = step;
            } else if (stepSize < -step) {
                stepSize = -step;
            }

            *pValue += stepSize;

            if (stepSize > 0.0f) {
                if (*pValue > target) {
                    *pValue = target;
                }
            } else {
                if (*pValue < target) {
                    *pValue = target;
                }
            }
        } else {
            if (stepSize > 0.0f) {
                *pValue += minStep;
                if (*pValue > target) {
                    *pValue = target;
                }
            } else {
                *pValue += negMinStep;
                if (*pValue < target) {
                    *pValue = target;
                }
            }
        }
    }

    return target - *pValue;
}

void add_calc2(f32* pValue, f32 target, f32 fraction, f32 step) {
    f32 stepSize;
    if (*pValue != target) {
        stepSize = fraction * (target - *pValue);

        if (stepSize > step) {
            stepSize = step;
        } else if (stepSize < -step) {
            stepSize = -step;
        }

        *pValue += stepSize;
    }
}

void add_calc0(f32* pValue, f32 fraction, f32 step) {
    f32 stepSize = *pValue * fraction;

    if (stepSize > step) {
        stepSize = step;
    } else if (stepSize < -step) {
        stepSize = -step;
    }

    *pValue -= stepSize;
}

f32 add_calc_a(f32* pValue, f32 target, f32 fraction, f32 step, f32 minStep) {
    f32 stepSize = 0.0f;
    f32 diff = target - *pValue;

    if (target != *pValue) {
        if (diff > 180.0f) {
            diff = -(360.0f - diff);
        } else if (diff < -180.0f) {
            diff = 360.0f + diff;
        }

        stepSize = diff * fraction;

        if ((stepSize >= minStep) || (stepSize <= -minStep)) {
            if (step < stepSize) {
                stepSize = step;
            } else if (stepSize < -step) {
                stepSize = -step;
            }

            *pValue += stepSize;

            if (stepSize > 0.0f) {
                if (target < *pValue) {
                    *pValue = target;
                }
            } else if (*pValue < target) {
                *pValue = target;
            }
        } else {
            if (stepSize > 0.0f) {
                stepSize = minStep;
                *pValue += stepSize;
                if (target < *pValue) {
                    *pValue = target;
                }
            } else {
                stepSize = -minStep;
                *pValue += -minStep;
                if (*pValue < target) {
                    *pValue = target;
                }
            }
        }
    }
    if (*pValue >= 360.0f) {
        *pValue -= 360.0f;
    }
    if (*pValue < 0.0f) {
        *pValue += 360.0f;
    }
    return stepSize;
}

s16 add_calc_short_angle2(s16* pValue, s16 target, f32 fraction, s16 step, s16 minStep) {
    s16 stepSize = 0;
    s16 diff = target - *pValue;

    if (*pValue != target) {
        stepSize = (s32)(diff * fraction);

        if ((minStep < stepSize) || (stepSize < -minStep)) {
            if (step < stepSize) {
                stepSize = step;
            } else if (stepSize < -step) {
                stepSize = -step;
            }

            *pValue += stepSize;

            if (stepSize > 0) {
                if ((s16)(target - *pValue) < 0) {
                    *pValue = target;
                }
            } else {
                if ((s16)(target - *pValue) > 0) {
                    *pValue = target;
                }
            }
        } else {
            if (diff >= 0) {
                *pValue += minStep;
                if ((s16)(target - *pValue) < 0) {
                    *pValue = target;
                }
            } else {
                *pValue -= minStep;
                if ((s16)(target - *pValue) > 0) {
                    *pValue = target;
                }
            }
        }
    }
    return target - *pValue;
}

s16 add_calc_short_angle3(s16* pValue, s16 target, f32 fraction, s16 maxStep, s16 minStep) {
    f32 stepSize;
    s32 uTarget;
    s32 newValue;
    s32 uValue;

    if (target != *pValue) {
        uValue = (u16)*pValue;
        uTarget = (u16)target;

        if (uValue > uTarget) {
            uTarget += 0x10000;
        }

        stepSize = (uTarget - uValue) * fraction;

        if (stepSize > maxStep) {
            stepSize = maxStep;
        } else if (stepSize < minStep) {
            stepSize = minStep;
        }

        newValue = uValue + (s32)stepSize;
        if (newValue > uTarget) {
            newValue = uTarget;
        }
        *pValue = newValue;
    }

    return target - *pValue;
}

void adds(s16* pValue, s16 target, s16 scale, s16 maxStep) {
    s16 diff = target - *pValue;
    diff /= scale;

    if (diff > maxStep) {
        *pValue += maxStep;
        return;
    }

    if (diff < -maxStep) {
        *pValue -= maxStep;
        return;
    }

    *pValue += diff;
}

void rgba_t_move(Color_RGBA8* dest, Color_RGBA8* src) {
    dest->r = src->r;
    dest->g = src->g;
    dest->b = src->b;
    dest->a = src->a;
}

s32 none_proc1() {
    return 0;
}

void none_proc2(Actor* actor UNUSED, Game_Play* play UNUSED) {
}

void Cheap_gfx_display(Game_Play* play, Gfx* dl) {
    //! FAKE
    if ((!(&play->state)) && (!(&play->state))) {}

    OPEN_DISPS(play->state.gfxCtx);

    _texture_z_light_fog_prim(play->state.gfxCtx);

    gSPMatrix(POLY_OPA_DISP++, _Matrix_to_Mtx_new(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

    gSPDisplayList(POLY_OPA_DISP++, dl);

    CLOSE_DISPS(play->state.gfxCtx);
}

void Cheap_gfx_display_xlu(Game_Play* play, Gfx* dl) {
    //! FAKE
    if ((!(&play->state)) && (!(&play->state))) {}

    OPEN_DISPS(play->state.gfxCtx);

    _texture_z_light_fog_prim_xlu(play->state.gfxCtx);

    gSPMatrix(POLY_XLU_DISP++, _Matrix_to_Mtx_new(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

    gSPDisplayList(POLY_XLU_DISP++, dl);

    CLOSE_DISPS(play->state.gfxCtx);
}

s32 _Game_play_isPause(Game_Play* play) {
    return play->pause.enabled != 0;
}

void* Lib_SegmentedToVirtual(void* ptr) {
    return SEGMENTED_TO_K0(ptr);
}

void* Lib_SegmentedToVirtualNull(void* ptr) {
    if (((uintptr_t)ptr >> 28) == 0) {
        return ptr;
    } else {
        return SEGMENTED_TO_K0(ptr);
    }
}

void* PhysicalToVirtual(uintptr_t ptr) {
    if (ptr == 0) {
        return 0;
    }

    return OS_PHYSICAL_TO_K0(ptr);
}

void* PhysicalToVirtualNull(uintptr_t ptr) {
    if (ptr == 0) {
        return 0;
    }

    return OS_PHYSICAL_TO_K0(ptr);
}

f32 check_percent_abs(f32 x, f32 min, f32 max, f32 scale, s32 shiftMin) {
    if ((-min <= x) && (x <= min)) {
        return 0.0f;
    }
    if (x >= max) {
        return 1.0f;
    }
    if (x <= -max) {
        return -1.0f;
    }
    if (shiftMin) {
        if (x > 0.0f) {
            return (x - min) * scale;
        } else {
            return (x + min) * scale;
        }
    } else {
        return x * scale;
    }
}

f32 get_percent_forAccelBrake(f32 x, f32 min, f32 max, f32 accelRange, f32 brakeRange) {
    f32 percent;
    f32 range;
    f32 cur;
    f32 scale;

    if (x >= max) {
        return 1.0f;
    }
    if (x <= min) {
        return 0.0f;
    }

    cur = x - min;
    range = max - min;

    if (range < accelRange + brakeRange) {
        return 0.0f;
    }

    scale = 1.0f / (2.0f * range - accelRange - brakeRange);

    if (accelRange != 0.0f) {
        if (cur <= accelRange) {
            percent = scale * cur * cur;
            percent /= accelRange;
            return percent;
        } else {
            percent = scale * accelRange;
        }
    } else {
        percent = 0.0f;
    }

    if (cur <= range - brakeRange) {
        percent += (scale * 2.0f) * (cur - accelRange);
        return percent;
    }

    percent += 2.0f * scale * (range - accelRange - brakeRange);

    if (brakeRange != 0.0f) {
        percent += scale * brakeRange;
        if (cur < range) {
            f32 left = range - cur;

            percent -= scale * left * left / brakeRange;
        }
    }
    return percent;
}

void Game_play_Projection_Trans(Game_Play* play, xyz_t* src, xyz_t* dst) {
    f32 temp_f0;

    Matrix_mult(&play->viewProjectionMtxF, 0);
    Matrix_Position(src, dst);
    temp_f0 =
        play->viewProjectionMtxF.ww + ((play->viewProjectionMtxF.wx * src->x) + (play->viewProjectionMtxF.wy * src->y) +
                                       (play->viewProjectionMtxF.wz * src->z));
    dst->x = ((dst->x / temp_f0) * 160.0f) + 160.0f;
    dst->y = 120.0f - ((dst->y / temp_f0) * 120.0f);
}

f32 get_percent(s32 max, s32 min, s32 x) {
    f32 denom;
    f32 percent;

    percent = 1.0f;
    if (x < min) {
        percent = 0.0f;
    } else if (x < max) {
        denom = (f32)(max - min);
        if (denom != 0.0f) {
            percent = (f32)(x - min) / denom;
            if (percent > 1.0f) {
                percent = 1.0f;
            }
        }
    }
    return percent;
}
