#include "libc64/math64.h"
#include "libc/stdbool.h"
#include "libc/math.h"
#include "libc64/fp.h"

s32 gFatanUseContFrac;

f32 Math_FTanF(f32 x) {
    return sinf(x) / cosf(x);
}

f32 Math_FFloorF(f32 x) {
    return floorf(x);
}

f32 Math_FCeilF(f32 x) {
    return ceilf(x);
}

f32 Math_FRoundF(f32 x) {
    return roundf(x);
}

f32 Math_FTruncF(f32 x) {
    return truncf(x);
}

f32 Math_FNearbyIntF(f32 x) {
    return nearbyintf(x);
}

f32 Math_FAtanTaylorQF(f32 x) {
    static const f32 coeffs[] = {
        -1.0f / 3, +1.0f / 5, -1.0f / 7, +1.0f / 9, -1.0f / 11, +1.0f / 13, -1.0f / 15, +1.0f / 17, 0.0f,
    };

    f32 poly = x;
    f32 sq = x * x;
    f32 exp = x * sq;
    const f32* c = coeffs;
    f32 term;

    while (true) {
        term = *c++ * exp;
        if ((poly + term) == poly) {
            break;
        }
        poly = poly + term;
        exp = exp * sq;
    }

    return poly;
}

f32 Math_FAtanTaylorF(f32 x) {
    f32 t;
    f32 q;

    if (x > 0.0f) {
        t = x;
    } else if (x < 0.0f) {
        t = -x;
    } else if (x == 0.0f) {
        return 0.0f;
    } else {
        return qNaN0x10000;
    }

    if (t <= (M_SQRT2 - 1.0f)) {
        return Math_FAtanTaylorQF(x);
    }

    if (t >= (M_SQRT2 + 1.0f)) {
        q = ((f32)M_PI / 2) - Math_FAtanTaylorQF(1.0f / t);
    } else {
        q = ((f32)M_PI / 4) - Math_FAtanTaylorQF((1.0f - t) / (1.0f + t));
    }

    if (x > 0.0f) {
        return q;
    } else {
        return -q;
    }
}

f32 Math_FAtanContFracF(f32 x) {
    s32 sector;
    f32 z;
    f32 conv;
    f32 sq;
    s32 i;

    if ((x >= -1.0f) && (x <= 1.0f)) {
        sector = 0;
    } else if (x > 1.0f) {
        sector = 1;
        x = 1.0f / x;
    } else if (x < -1.0f) {
        sector = -1;
        x = 1.0f / x;
    } else {
        return qNaN0x10000;
    }

    sq = x * x;
    conv = 0.0f;
    z = 8.0f;
    for (i = 8; i != 0; i--) {
        conv = z * z * sq / (2.0f * z + 1.0f + conv);
        z -= 1.0f;
    }
    conv = x / (1.0f + conv);

    if (sector == 0) {
        return conv;
    } else if (sector > 0) {
        return ((f32)M_PI / 2) - conv;
    } else {
        return -((f32)M_PI / 2) - conv;
    }
}

f32 fatan(f32 x) {
    if (!gFatanUseContFrac) {
        return Math_FAtanTaylorF(x);
    } else {
        return Math_FAtanContFracF(x);
    }
}

f32 fatan2(f32 y, f32 x) {
    if (x == 0.0f) {
        if (y == 0.0f) {
            return 0.0f;
        } else if (y > 0.0f) {
            return (f32)M_PI / 2;
        } else if (y < 0.0f) {
            return -((f32)M_PI / 2);
        } else {
            return qNaN0x10000;
        }
    } else if (x >= 0.0f) {
        return fatan(y / x);
    } else if (y < 0.0f) {
        return fatan(y / x) - (f32)M_PI;
    } else {
        return (f32)M_PI - fatan(-(y / x));
    }
}

f32 Math_FAsinF(f32 x) {
    return fatan2(x, sqrtf(1.0f - (x * x)));
}

f32 Math_FAcosF(f32 x) {
    return ((f32)M_PI / 2) - Math_FAsinF(x);
}
