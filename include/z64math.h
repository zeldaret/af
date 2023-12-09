#ifndef Z64MATH_H
#define Z64MATH_H

#include "ultra64.h"

#define VEC_SET(V, X, Y, Z) \
    V.x = X;                \
    V.y = Y;                \
    V.z = Z

typedef struct {
    /* 0x0 */ s16 x;
    /* 0x2 */ s16 z;
} Vec2s; // size = 0x4

typedef struct {
    /* 0x0 */ f32 x;
    /* 0x4 */ f32 z;
} Vec2f; // size = 0x8

typedef struct xyz_t {
    /* 0x0 */ f32 x;
    /* 0x4 */ f32 y;
    /* 0x8 */ f32 z;
} xyz_t; // size = 0xC

typedef struct {
    /* 0x0 */ u16 x;
    /* 0x2 */ u16 y;
    /* 0x4 */ u16 z;
} Vec3us; // size = 0x6

typedef struct {
    /* 0x0 */ s16 x;
    /* 0x2 */ s16 y;
    /* 0x4 */ s16 z;
} s_xyz; // size = 0x6

typedef struct {
    /* 0x0 */ s32 x;
    /* 0x4 */ s32 y;
    /* 0x8 */ s32 z;
} Vec3i; // size = 0xC

typedef float MtxF_t[4][4];
typedef union {
    MtxF_t mf;
    struct {
        float xx, yx, zx, wx, xy, yy, zy, wy, xz, yz, zz, wz, xw, yw, zw, ww;
    };
} MtxF; // size = 0x40

#define SQ(x) ((x) * (x))
#define CB(x) ((x) * (x) * (x))

#define IS_ZERO(f) (fabsf(f) < 0.008f)

// Calculate the floating point remainder of x / y.
#define FMOD(x, y) ((x) - ((s32)((x) * (1.0f / (y))) * (f32)(y)))

// Casting a float to an integer, when the float value is larger than what the integer type can hold,
// leads to undefined behavior. For example (f32)0x8000 doesn't fit in a s16, so it cannot be cast to s16.
// This isn't an issue with IDO, but is one with for example GCC.
// A partial workaround is to cast to s32 then s16, hoping all binang values used will fit a s32.
#define TRUNCF_BINANG(f) (s16)(s32)(f)

// Angle conversion macros
#define DEG_TO_RAD(degrees) ((degrees) * ((f32)M_PI / 180.0f))
#define DEG_TO_BINANG(degrees) TRUNCF_BINANG((degrees) * (0x8000 / 180.0f))
#define DEG_TO_BINANG_ALT(degrees) TRUNCF_BINANG(((degrees) / 180.0f) * 0x8000)
#define DEG_TO_BINANG_ALT2(degrees) TRUNCF_BINANG(((degrees) * 0x10000) / 360.0f)
#define DEG_TO_BINANG_ALT3(degrees) ((degrees) * (0x8000 / 180.0f))

#define RAD_TO_DEG(radians) ((radians) * (180.0f / (f32)M_PI))
#define RAD_TO_BINANG(radians) TRUNCF_BINANG((radians) * (0x8000 / (f32)M_PI))
#define RAD_TO_BINANG_ALT(radians) TRUNCF_BINANG(((radians) / (f32)M_PI) * 0x8000)
#define RAD_TO_BINANG_ALT2(radians) TRUNCF_BINANG(((radians) * 0x8000) / (f32)M_PI)

#define BINANG_TO_DEG(binang) ((f32)(binang) * (180.0f / 0x8000))
#define BINANG_TO_RAD(binang) ((f32)(binang) * ((f32)M_PI / 0x8000))
#define BINANG_TO_RAD_ALT(binang) (((f32)(binang) / 0x8000) * (f32)M_PI)
#define BINANG_TO_RAD_ALT2(binang) (((f32)(binang) * (f32)M_PI) / 0x8000)

// Angle arithmetic macros
#define BINANG_ROT180(angle) ((s16)(angle + 0x8000))
#define BINANG_SUB(a, b) ((s16)(a - b))
#define BINANG_ADD(a, b) ((s16)(a + b))

#endif
