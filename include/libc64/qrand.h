#ifndef LIBC64_QRAND_H
#define LIBC64_QRAND_H

#include "ultra64.h"


u32 qrand(void);
void sqrand(u32 seed);
f32 fqrand(void);
f32 fqrand2(void);
void sqrand_r(u32* p, u32 val);
u32 qrand_r(u32* p);
f32 fqrand_r(u32* p);
f32 fqrand2_r(u32* p);

#endif
