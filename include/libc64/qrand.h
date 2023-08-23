#ifndef LIBC64_QRAND_H
#define LIBC64_QRAND_H

#include "ultra64.h"

/* Macro to generate a random float in the range of [0, n) */
#define RANDOM_F(n) (fqrand() * (f32)(n))
#define RANDOM_F2(n) ((f32)(n) * fqrand())

/* Macro to generate a random integer in the range of [0, n) */
#define RANDOM(n) ((s32)RANDOM_F(n))
#define RANDOM2(n) ((s32)RANDOM_F2(n))

u32 qrand(void);
void sqrand(u32 seed);
f32 fqrand(void);
f32 fqrand2(void);
void sqrand_r(u32* p, u32 val);
u32 qrand_r(u32* p);
f32 fqrand_r(u32* p);
f32 fqrand2_r(u32* p);

#endif
