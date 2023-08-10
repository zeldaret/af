#ifndef LIBC64_FP_H
#define LIBC64_FP_H

#include "ultra64.h"

// void floorf();
// void floor();
// void lfloorf();
// void lfloor();
// void ceilf();
// void ceil();
// void lceilf();
// void lceil();
// void truncf();
// void trunc();
// void ltruncf();
// void ltrunc();
// void nearbyintf();
f64 nearbyint(f64 x);
// void lnearbyintf();
// void lnearbyint();
// void roundf();
// void round();
// void lroundf();
// void lround();

extern f32 qNaN0x3FFFFF;
extern f32 qNaN0x10000;
extern f32 sNaN0x3FFFFF;

#endif
