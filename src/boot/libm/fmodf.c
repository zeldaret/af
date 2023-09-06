#include "libm/fmodf.h"

f32 fmodf(f32 x, f32 y) {
    s32 n;

    if (y == 0.0f) {
        return 0.0f;
    }

    n = x / y;
    return x - (n * y);
}
