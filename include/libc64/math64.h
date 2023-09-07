#ifndef MATHF_H
#define MATHF_H

#include "ultra64.h"

f32 Math_FTanF(f32 x);
f32 Math_FFloorF(f32 x);
f32 Math_FCeilF(f32 x);
f32 Math_FRoundF(f32 x);
f32 Math_FTruncF(f32 x);
f32 Math_FNearbyIntF(f32 x);
f32 fatan(f32 x);
f32 fatan2(f32 y, f32 x);
f32 Math_FAsinF(f32 x);
f32 Math_FAcosF(f32 x);

extern s32 gFatanUseContFrac;

#endif
