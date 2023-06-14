#ifndef Z64MATH_H
#define Z64MATH_H

#include "ultra64.h"

#define VEC_SET(V,X,Y,Z) V.x=X;V.y=Y;V.z=Z

typedef struct {
    /* 0x0 */ s16 x;
    /* 0x2 */ s16 z;
} Vec2s; // size = 0x4

typedef struct {
    /* 0x0 */ f32 x;
    /* 0x4 */ f32 z;
} Vec2f; // size = 0x8

typedef struct {
    /* 0x0 */ f32 x;
    /* 0x4 */ f32 y;
    /* 0x8 */ f32 z;
} Vec3f; // size = 0xC

typedef struct {
    /* 0x0 */ u16 x;
    /* 0x2 */ u16 y;
    /* 0x4 */ u16 z;
} Vec3us; // size = 0x6

typedef struct {
    /* 0x0 */ s16 x;
    /* 0x2 */ s16 y;
    /* 0x4 */ s16 z;
} Vec3s; // size = 0x6

typedef struct {
    /* 0x0 */ s32 x;
    /* 0x4 */ s32 y;
    /* 0x8 */ s32 z;
} Vec3i; // size = 0xC

typedef float MtxF_t[4][4];
typedef union {
    MtxF_t mf;
    struct {
        float xx, yx, zx, wx,
              xy, yy, zy, wy,
              xz, yz, zz, wz,
              xw, yw, zw, ww;
    };
} MtxF; // size = 0x40

#define SQ(x) ((x) * (x))
#define CB(x) ((x) * (x) * (x))

#endif
