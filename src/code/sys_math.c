#include "sys_math.h"

u32 reverse_u32(u32 value) {
    u32 mask = 0x80000000;
    u32 result = 0;
    s32 i;

    for (i = 0; i < 32; i++) {
        if (value & mask) {
            result |= 1U << i;
        }
        mask >>= 1;
    }

    return result;
}

void init_rnd(void) {
    sqrand(reverse_u32(osGetCount()));
}

f32 ffact(f32 value) {
    s32 i;
    f32 result = 1.0f;

    for (i = (s32)value; i > 1; i--) {
        result *= i;
    }

    return result;
}

f32 ifact(s32 value) {
    extern f32 D_FLT_8010F460_jp[];
    extern f32 D_FLT_8010F490_jp;
    f32 result;
    s32 i;

    if (value >= 13) {
        result = D_FLT_8010F490_jp;
        for (i = 13; i <= value; i++) {
            result *= i;
        }
    } else {
        result = D_FLT_8010F460_jp[value];
    }

    return result;
}

f32 powi(f32 value, s32 exponent) {
    f32 result = 1.0f;

    while (exponent > 0) {
        exponent--;
        result *= value;
    }

    return result;
}

f32 sinf_table(f32 x) {
    extern const f32 RO_FLT_801180B0_jp;
    extern const f32 RO_FLT_801180B4_jp;

    return sins((s16)(x * RO_FLT_801180B0_jp)) * RO_FLT_801180B4_jp;
}

f32 cosf_table(f32 x) {
    extern const f32 RO_FLT_801180B8_jp;
    extern const f32 RO_FLT_801180BC_jp;

    return coss((s16)(x * RO_FLT_801180B8_jp)) * RO_FLT_801180BC_jp;
}

f32 tanf_table(f32 x) {
    extern const f32 RO_FLT_801180C0_jp;
    f32 sin = sinf_table(x);
    f32 cos = cosf_table(x);

    if ((cos >= 0.0f ? cos : -cos) < RO_FLT_801180C0_jp && (sin >= 0.0f ? sin : -sin) > 10.0f) {
        return 1000.0f;
    }

    return sin / cos;
}
