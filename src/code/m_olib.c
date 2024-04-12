#include "global.h"
#include "m_olib.h"

/**
 * Calculates the distances between `a` and `b`
 */
f32 distance_between(xyz_t* a, xyz_t* b) {
    f32 dx = a->x - b->x;
    f32 dy = a->y - b->y;
    f32 dz = a->z - b->z;

    return sqrtf(SQ(dx) + SQ(dy) + SQ(dz));
}

/**
 * Calculates the distances between `a` and `b`, and outputs the vector
 * created by the difference into `dest`
 */
f32 distance_between2(xyz_t* a, xyz_t* b, xyz_t* dest) {
    dest->x = a->x - b->x;
    dest->y = a->y - b->y;
    dest->z = a->z - b->z;

    return sqrtf(SQ(dest->x) + SQ(dest->y) + SQ(dest->z));
}

/**
 * Calculates the distances on the xz plane between `a` and `b`
 */
f32 distance_2d(xyz_t* a, xyz_t* b) {
    return sqrtf(SQ(a->x - b->x) + SQ(a->z - b->z));
}

/**
 * Clamps `val` to a maximum of -`min` as `val` approaches zero, and a minimum of
 * `min` as `val` approaches zero
 */
f32 never_zero(f32 val, f32 min) {
    if (val < 0.0f) {
        return CLAMP_MAX(val, -min);
    } else {
        return CLAMP_MIN(val, min);
    }
}

/**
 * Clamps `val` to a minimum of -`max` as `val` approaches -`max`, and a maximum of `max`
 * as `val` approaches `max`
 */
f32 limiter(f32 val, f32 max) {
    if (val < 0.0f) {
        return CLAMP_MIN(val, -max);
    } else {
        return CLAMP_MAX(val, max);
    }
}

/**
 * Takes the difference of points b and a, and creates a normal vector
 */
xyz_t unitvector_by_2pos(xyz_t* a, xyz_t* b) {
    xyz_t v1;
    xyz_t v2;
    f32 dist;

    v1.x = b->x - a->x;
    v1.y = b->y - a->y;
    v1.z = b->z - a->z;

    dist = never_zero(sqrtf(SQXYZ(v1)), 0.01f);

    v2.x = v1.x / dist;
    v2.y = v1.y / dist;
    v2.z = v1.z / dist;

    return v2;
}

/**
 * Takes the spherical coordinate `sph`, and converts it into a x,y,z position
 */
xyz_t spolar2world(VecSph* sph) {
    xyz_t v;
    f32 sinPitch;
    f32 cosPitch = cos_s(sph->pitch);
    f32 sinYaw;
    f32 cosYaw = cos_s(sph->yaw);

    sinPitch = sin_s(sph->pitch);
    sinYaw = sin_s(sph->yaw);

    v.x = sph->r * sinPitch * sinYaw;
    v.y = sph->r * cosPitch;
    v.z = sph->r * sinPitch * cosYaw;

    return v;
}

/**
 * Takes the geographic point `geo` and converts it into a x,y,z position
 */
xyz_t sglobe2world(VecGeo* geo) {
    VecSph sph;

    sph.r = geo->r;
    sph.pitch = 0x3FFF - geo->pitch;
    sph.yaw = geo->yaw;

    return spolar2world(&sph);
}

/**
 * Takes the point `vec`, and converts it into a spherical coordinate
 */
VecSph world2spolar(xyz_t* vec) {
    VecSph sph;
    f32 distXZSq = SQ(vec->x) + SQ(vec->z);
    f32 distXZ = sqrtf(distXZSq);

    if ((distXZ == 0.0f) && (vec->y == 0.0f)) {
        sph.pitch = 0;
    } else {
        sph.pitch = CAM_DEG_TO_BINANG(RAD_TO_DEG(fatan2(distXZ, vec->y)));
    }

    sph.r = sqrtf(SQ(vec->y) + distXZSq);
    if ((vec->x == 0.0f) && (vec->z == 0.0f)) {
        sph.yaw = 0;
    } else {
        sph.yaw = CAM_DEG_TO_BINANG(RAD_TO_DEG(fatan2(vec->x, vec->z)));
    }

    return sph;
}

/**
 * Takes the point `vec`, and converts it to a geographic coordinate
 */
VecGeo world2sglobe(xyz_t* vec) {
    VecSph sph = world2spolar(vec);

    sph.pitch = 0x3FFF - sph.pitch;

    return sph;
}

/**
 * Takes the differences of positions `a` and `b`, and converts them to spherical coordinates
 */
VecSph spolar_by_2pos(xyz_t* a, xyz_t* b) {
    xyz_t diff;

    diff.x = b->x - a->x;
    diff.y = b->y - a->y;
    diff.z = b->z - a->z;

    return world2spolar(&diff);
}

/**
 * Takes the difference of positions `a` and `b`, and converts them to geographic coordinates
 */
VecGeo sglobe_by_2pos(xyz_t* a, xyz_t* b) {
    xyz_t diff;

    diff.x = b->x - a->x;
    diff.y = b->y - a->y;
    diff.z = b->z - a->z;

    return world2sglobe(&diff);
}

/**
 * Gets the pitch/yaw of the vector formed from `b`-`a`, result is in radians
 */
xyz_t radianxy_by_2pos(xyz_t* a, xyz_t* b) {
    xyz_t anglesRad;

    anglesRad.x = fatan2(b->z - a->z, b->y - a->y);
    anglesRad.y = fatan2(b->x - a->x, b->z - a->z);
    anglesRad.z = 0.0f;

    return anglesRad;
}

/**
 * Gets the pitch/yaw of the vector formed from `b`-`a`, result is in degrees
 */
xyz_t degreexy_by_2pos(xyz_t* a, xyz_t* b) {
    xyz_t anglesRad = radianxy_by_2pos(a, b);
    xyz_t anglesDegrees;

    anglesDegrees.x = RAD_TO_DEG(anglesRad.x);
    anglesDegrees.y = RAD_TO_DEG(anglesRad.y);
    anglesDegrees.z = 0.0f;

    return anglesDegrees;
}

/**
 * Gets the pitch/yaw of the vector formed from `b`-`a`, result is in binary degrees
 */
s_xyz sanglexy_by_2pos(xyz_t* a, xyz_t* b) {
    xyz_t anglesRad = radianxy_by_2pos(a, b);
    s_xyz anglesBinAng;

    anglesBinAng.x = CAM_DEG_TO_BINANG(RAD_TO_DEG(anglesRad.x));
    anglesBinAng.y = CAM_DEG_TO_BINANG(RAD_TO_DEG(anglesRad.y));
    anglesBinAng.z = 0.0f;

    return anglesBinAng;
}
