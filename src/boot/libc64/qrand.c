#include "libc64/qrand.h"

u32 __qrand_itemp;
u32 __qrand_idum = 1;

u32 qrand(void) {
    __qrand_idum = __qrand_idum * 0x19660D + 0x3C6EF35F;
    return __qrand_idum;
}

void sqrand(u32 seed) {
    __qrand_idum = seed;
}

f32 fqrand(void) {
    __qrand_idum = __qrand_idum * 0x19660D + 0x3C6EF35F;
    __qrand_itemp = __qrand_idum >> 9 | 0x3F800000;
    return *(float*)&__qrand_itemp - 1.0f;
}

f32 fqrand2(void) {
    __qrand_idum = __qrand_idum * 0x19660D + 0x3C6EF35F;
    __qrand_itemp = __qrand_idum >> 9 | 0x3F800000;
    return *(float*)&__qrand_itemp - 1.5f;
}

void sqrand_r(u32* p, u32 val) {
    *p = val;
}

u32 qrand_r(u32* p) {
    u32 t = *p * 0x19660D + 0x3C6EF35F;

    *p = t;
    return t;
}

f32 fqrand_r(u32* p) {
    u32 t = *p * 0x19660D + 0x3C6EF35F;

    __qrand_itemp = (*p = t) >> 9 | 0x3F800000;
    return *(float*)&__qrand_itemp - 1.0f;
}

f32 fqrand2_r(u32* p) {
    u32 t = *p * 0x19660D + 0x3C6EF35F;

    __qrand_itemp = (*p = t) >> 9 | 0x3F800000;
    return *(float*)&__qrand_itemp - 1.5f;
}
