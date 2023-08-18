#ifndef SYS_MATH_H
#define SYS_MATH_H

#include "ultra64.h"
#include "libc64/qrand.h"

/* Macro to generate a random float in the range of [0, n) */
#define RANDOM_F(n) (fqrand() * (f32)(n))
#define RANDOM_F2(n) ((f32)(n) * fqrand())

/* Macro to generate a random integer in the range of [0, n) */
#define RANDOM(n) ((s32)RANDOM_F(n))
#define RANDOM2(n) ((s32)RANDOM_F2(n))

// void reverse_u32();
// void init_rnd();
// void ffact();
// void ifact();
// void powi();
// void sinf_table();
// void cosf_table();
// void tanf_table();

#endif
