#ifndef M_OLIB_H
#define M_OLIB_H

#include "ultra64.h"
#include "m_lib.h"
#include "libc64/math64.h"
#include "m_camera2.h"

f32 distance_between(xyz_t* a, xyz_t* b);
f32 distance_between2(xyz_t* a, xyz_t* b, xyz_t* dest);
f32 distance_2d(xyz_t* a, xyz_t* b);
f32 never_zero(f32 val, f32 min);
f32 limiter(f32 val, f32 max);
xyz_t unitvector_by_2pos(xyz_t* a, xyz_t* b);
xyz_t spolar2world(VecSph* sph);
xyz_t sglobe2world(VecGeo* geo);
VecSph world2spolar(xyz_t* vec);
VecGeo world2sglobe(xyz_t* vec);
VecSph spolar_by_2pos(xyz_t* a, xyz_t* b);
VecGeo sglobe_by_2pos(xyz_t* a, xyz_t* b);
xyz_t radianxy_by_2pos(xyz_t* a, xyz_t* b);
xyz_t degreexy_by_2pos(xyz_t* a, xyz_t* b);
s_xyz sanglexy_by_2pos(xyz_t* a, xyz_t* b);

#endif
