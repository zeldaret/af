#include "m_skin_matrix.h"
#include "gfx.h"
#include "m_lib.h"
#include "libc/math.h"

void Skin_Matrix_PrjMulVector(MtxF* mf, xyz_t* src, xyz_t* xyzDest, f32* wDest) {
    xyzDest->x = mf->xw + ((src->x * mf->xx) + (src->y * mf->xy) + (src->z * mf->xz));
    xyzDest->y = mf->yw + ((src->x * mf->yx) + (src->y * mf->yy) + (src->z * mf->yz));
    xyzDest->z = mf->zw + ((src->x * mf->zx) + (src->y * mf->zy) + (src->z * mf->zz));
    *wDest = mf->ww + ((src->x * mf->wx) + (src->y * mf->wy) + (src->z * mf->wz));
}

void Skin_Matrix_MulVector(MtxF* mf, xyz_t* src, xyz_t* dest) {
    f32 mx = mf->xx;
    f32 my = mf->xy;
    f32 mz = mf->xz;
    f32 mw = mf->xw;

    dest->x = mw + ((src->x * mx) + (src->y * my) + (src->z * mz));
    mx = mf->yx;
    my = mf->yy;
    mz = mf->yz;
    mw = mf->yw;
    dest->y = mw + ((src->x * mx) + (src->y * my) + (src->z * mz));
    mx = mf->zx;
    my = mf->zy;
    mz = mf->zz;
    mw = mf->zw;
    dest->z = mw + ((src->x * mx) + (src->y * my) + (src->z * mz));
}

void Skin_Matrix_MulMatrix(MtxF* mfA, MtxF* mfB, MtxF* dest) {
    f32 cx;
    f32 cy;
    f32 cz;
    f32 cw;

    f32 rx = mfA->xx;
    f32 ry = mfA->xy;
    f32 rz = mfA->xz;
    f32 rw = mfA->xw;

    cx = mfB->xx;
    cy = mfB->yx;
    cz = mfB->zx;
    cw = mfB->wx;
    dest->xx = (rx * cx) + (ry * cy) + (rz * cz) + (rw * cw);

    cx = mfB->xy;
    cy = mfB->yy;
    cz = mfB->zy;
    cw = mfB->wy;
    dest->xy = (rx * cx) + (ry * cy) + (rz * cz) + (rw * cw);

    cx = mfB->xz;
    cy = mfB->yz;
    cz = mfB->zz;
    cw = mfB->wz;
    dest->xz = (rx * cx) + (ry * cy) + (rz * cz) + (rw * cw);

    cx = mfB->xw;
    cy = mfB->yw;
    cz = mfB->zw;
    cw = mfB->ww;
    dest->xw = (rx * cx) + (ry * cy) + (rz * cz) + (rw * cw);

    rx = mfA->yx;
    ry = mfA->yy;
    rz = mfA->yz;
    rw = mfA->yw;

    cx = mfB->xx;
    cy = mfB->yx;
    cz = mfB->zx;
    cw = mfB->wx;
    dest->yx = (rx * cx) + (ry * cy) + (rz * cz) + (rw * cw);

    cx = mfB->xy;
    cy = mfB->yy;
    cz = mfB->zy;
    cw = mfB->wy;
    dest->yy = (rx * cx) + (ry * cy) + (rz * cz) + (rw * cw);

    cx = mfB->xz;
    cy = mfB->yz;
    cz = mfB->zz;
    cw = mfB->wz;
    dest->yz = (rx * cx) + (ry * cy) + (rz * cz) + (rw * cw);

    cx = mfB->xw;
    cy = mfB->yw;
    cz = mfB->zw;
    cw = mfB->ww;
    dest->yw = (rx * cx) + (ry * cy) + (rz * cz) + (rw * cw);

    rx = mfA->zx;
    ry = mfA->zy;
    rz = mfA->zz;
    rw = mfA->zw;

    cx = mfB->xx;
    cy = mfB->yx;
    cz = mfB->zx;
    cw = mfB->wx;
    dest->zx = (rx * cx) + (ry * cy) + (rz * cz) + (rw * cw);

    cx = mfB->xy;
    cy = mfB->yy;
    cz = mfB->zy;
    cw = mfB->wy;
    dest->zy = (rx * cx) + (ry * cy) + (rz * cz) + (rw * cw);

    cx = mfB->xz;
    cy = mfB->yz;
    cz = mfB->zz;
    cw = mfB->wz;
    dest->zz = (rx * cx) + (ry * cy) + (rz * cz) + (rw * cw);

    cx = mfB->xw;
    cy = mfB->yw;
    cz = mfB->zw;
    cw = mfB->ww;
    dest->zw = (rx * cx) + (ry * cy) + (rz * cz) + (rw * cw);

    rx = mfA->wx;
    ry = mfA->wy;
    rz = mfA->wz;
    rw = mfA->ww;

    cx = mfB->xx;
    cy = mfB->yx;
    cz = mfB->zx;
    cw = mfB->wx;
    dest->wx = (rx * cx) + (ry * cy) + (rz * cz) + (rw * cw);

    cx = mfB->xy;
    cy = mfB->yy;
    cz = mfB->zy;
    cw = mfB->wy;
    dest->wy = (rx * cx) + (ry * cy) + (rz * cz) + (rw * cw);

    cx = mfB->xz;
    cy = mfB->yz;
    cz = mfB->zz;
    cw = mfB->wz;
    dest->wz = (rx * cx) + (ry * cy) + (rz * cz) + (rw * cw);

    cx = mfB->xw;
    cy = mfB->yw;
    cz = mfB->zw;
    cw = mfB->ww;
    dest->ww = (rx * cx) + (ry * cy) + (rz * cz) + (rw * cw);
}

MtxF D_8010ED60_jp = { {
    { 1.0f, 0.0f, 0.0f, 0.0f },
    { 0.0f, 1.0f, 0.0f, 0.0f },
    { 0.0f, 0.0f, 1.0f, 0.0f },
    { 0.0f, 0.0f, 0.0f, 1.0f },
} };

void Skin_Matrix_getUnitMatrixPointer(MtxF** mtxP) {
    *mtxP = &D_8010ED60_jp;
}

void Skin_Matrix_SetUnitMatrix(MtxF* mf) {
    mf->xx = 1.0f;
    mf->yx = 0.0f;
    mf->zx = 0.0f;
    mf->wx = 0.0f;
    mf->xy = 0.0f;
    mf->yy = 1.0f;
    mf->zy = 0.0f;
    mf->wy = 0.0f;
    mf->xz = 0.0f;
    mf->yz = 0.0f;
    mf->zz = 1.0f;
    mf->wz = 0.0f;
    mf->xw = 0.0f;
    mf->yw = 0.0f;
    mf->zw = 0.0f;
    mf->ww = 1.0f;
}

void Skin_Matrix_Copy(MtxF* src, MtxF* dest) {
    dest->xx = src->xx;
    dest->yx = src->yx;
    dest->zx = src->zx;
    dest->wx = src->wx;
    dest->xy = src->xy;
    dest->yy = src->yy;
    dest->zy = src->zy;
    dest->wy = src->wy;
    dest->xz = src->xz;
    dest->yz = src->yz;
    dest->zz = src->zz;
    dest->wz = src->wz;
    dest->xw = src->xw;
    dest->yw = src->yw;
    dest->zw = src->zw;
    dest->ww = src->ww;
}

#define SWAP(type, a, b)  \
    {                     \
        type _temp = (a); \
        (a) = (b);        \
        (b) = _temp;      \
    }

s32 Skin_Matrix_InverseMatrix(MtxF* src, MtxF* dest) {
    MtxF mfCopy;
    s32 i;
    f32 temp1;
    s32 thisCol;
    s32 thisRow;

    Skin_Matrix_Copy(src, &mfCopy);
    Skin_Matrix_SetUnitMatrix(dest);
    for (thisCol = 0; thisCol < 4; thisCol++) {
        thisRow = thisCol;
        while ((thisRow < 4) && (fabsf(mfCopy.mf[thisCol][thisRow]) < 0.0005f)) {
            thisRow++;
        }
        if (thisRow == 4) {
            return 2;
        }

        if (thisRow != thisCol) {
            for (i = 0; i < 4; i++) {
                SWAP(f32, mfCopy.mf[i][thisRow], mfCopy.mf[i][thisCol]);
                SWAP(f32, dest->mf[i][thisRow], dest->mf[i][thisCol]);
            }
        }

        temp1 = mfCopy.mf[thisCol][thisCol];
        for (i = 0; i < 4; i++) {
            mfCopy.mf[i][thisCol] /= temp1;
            dest->mf[i][thisCol] /= temp1;
        }

        for (thisRow = 0; thisRow < 4; thisRow++) {
            if (thisRow != thisCol) {
                temp1 = mfCopy.mf[thisCol][thisRow];
                for (i = 0; i < 4; i++) {
                    mfCopy.mf[i][thisRow] -= mfCopy.mf[i][thisCol] * temp1;
                    dest->mf[i][thisRow] -= dest->mf[i][thisCol] * temp1;
                }
            }
        }
    }
    return 0;
}

void Skin_Matrix_SetScale(MtxF* mf, f32 x, f32 y, f32 z) {
    mf->yx = 0.0f;
    mf->zx = 0.0f;
    mf->wx = 0.0f;
    mf->xy = 0.0f;
    mf->zy = 0.0f;
    mf->wy = 0.0f;
    mf->xz = 0.0f;
    mf->yz = 0.0f;
    mf->wz = 0.0f;
    mf->xw = 0.0f;
    mf->yw = 0.0f;
    mf->zw = 0.0f;
    mf->ww = 1.0f;
    mf->xx = x;
    mf->yy = y;
    mf->zz = z;
}

void Skin_Matrix_SetRotateXyz_s(MtxF* mf, s16 x, s16 y, s16 z) {
    f32 cos;
    f32 sinZ = sin_s(z);
    f32 cosZ = cos_s(z);
    f32 xy;
    f32 sin;
    f32 xz;
    f32 yy;
    f32 yz;

    mf->yy = cosZ;
    mf->xy = -sinZ;
    mf->wx = mf->wy = mf->wz = 0;
    mf->xw = mf->yw = mf->zw = 0;
    mf->ww = 1;

    if (y != 0) {
        sin = sin_s(y);
        cos = cos_s(y);

        mf->xx = cosZ * cos;
        mf->xz = cosZ * sin;

        mf->yx = sinZ * cos;
        mf->yz = sinZ * sin;
        mf->zx = -sin;
        mf->zz = cos;

    } else {
        mf->xx = cosZ;
        if (1) {}
        if (1) {}
        xz = sinZ;
        mf->yx = sinZ;
        mf->zx = mf->xz = mf->yz = 0;
        mf->zz = 1;
    }

    if (x != 0) {
        sin = sin_s(x);
        cos = cos_s(x);

        xy = mf->xy;
        xz = mf->xz;
        mf->xy = (xy * cos) + (xz * sin);
        mf->xz = (xz * cos) - (xy * sin);

        if (1) {}
        yz = mf->yz;
        yy = mf->yy;
        mf->yy = (yy * cos) + (yz * sin);
        mf->yz = (yz * cos) - (yy * sin);

        if (cos) {}
        mf->zy = mf->zz * sin;
        mf->zz = mf->zz * cos;
    } else {
        mf->zy = 0;
    }
}

void Skin_Matrix_SetRotateZxy_s(MtxF* mf, s16 x, s16 y, s16 z) {
    f32 cos;
    f32 sinY = sin_s(y);
    f32 cosY = cos_s(y);
    f32 zx;
    f32 sin;
    f32 zy;
    f32 xx;
    f32 xy;

    mf->xx = cosY;
    mf->zx = -sinY;
    mf->wz = 0;
    mf->wy = 0;
    mf->wx = 0;
    mf->zw = 0;
    mf->yw = 0;
    mf->xw = 0;
    mf->ww = 1;

    if (x != 0) {
        sin = sin_s(x);
        cos = cos_s(x);

        mf->zz = cosY * cos;
        mf->zy = cosY * sin;

        mf->xz = sinY * cos;
        mf->xy = sinY * sin;
        mf->yz = -sin;
        mf->yy = cos;

    } else {
        mf->zz = cosY;
        if (1) {}
        if (1) {}
        xy = sinY;
        mf->xz = sinY;
        mf->xy = mf->zy = mf->yz = 0;
        mf->yy = 1;
    }

    if (z != 0) {
        sin = sin_s(z);
        cos = cos_s(z);
        xx = mf->xx;
        xy = mf->xy;
        mf->xx = (xx * cos) + (xy * sin);
        mf->xy = xy * cos - (xx * sin);
        if (1) {}
        zy = mf->zy;
        zx = mf->zx;
        mf->zx = (zx * cos) + (zy * sin);
        mf->zy = (zy * cos) - (zx * sin);
        if (cos) {}
        mf->yx = mf->yy * sin;
        mf->yy = mf->yy * cos;
    } else {
        mf->yx = 0;
    }
}

void Skin_Matrix_SetTranslate(MtxF* mf, f32 x, f32 y, f32 z) {
    mf->yx = 0.0f;
    mf->zx = 0.0f;
    mf->wx = 0.0f;
    mf->xy = 0.0f;
    mf->zy = 0.0f;
    mf->wy = 0.0f;
    mf->xz = 0.0f;
    mf->yz = 0.0f;
    mf->wz = 0.0f;
    mf->xx = 1.0f;
    mf->yy = 1.0f;
    mf->zz = 1.0f;
    mf->ww = 1.0f;
    mf->xw = x;
    mf->yw = y;
    mf->zw = z;
}

void Skin_Matrix_SetSrtMatrix(MtxF* dest, f32 scaleX, f32 scaleY, f32 scaleZ, s16 rotX, s16 rotY, s16 rotZ,
                              f32 translateX, f32 translateY, f32 translateZ) {
    MtxF mft1;
    MtxF mft2;

    Skin_Matrix_SetTranslate(dest, translateX, translateY, translateZ);
    Skin_Matrix_SetRotateXyz_s(&mft1, rotX, rotY, rotZ);
    Skin_Matrix_MulMatrix(dest, &mft1, &mft2);
    Skin_Matrix_SetScale(&mft1, scaleX, scaleY, scaleZ);
    Skin_Matrix_MulMatrix(&mft2, &mft1, dest);
}

void Skin_Matrix_SetSRzxyTMatrix(MtxF* dest, f32 scaleX, f32 scaleY, f32 scaleZ, s16 rotX, s16 rotY, s16 rotZ,
                                 f32 translateX, f32 translateY, f32 translateZ) {
    MtxF mft1;
    MtxF mft2;

    Skin_Matrix_SetTranslate(dest, translateX, translateY, translateZ);
    Skin_Matrix_SetRotateZxy_s(&mft1, rotX, rotY, rotZ);
    Skin_Matrix_MulMatrix(dest, &mft1, &mft2);
    Skin_Matrix_SetScale(&mft1, scaleX, scaleY, scaleZ);
    Skin_Matrix_MulMatrix(&mft2, &mft1, dest);
}

void Skin_Matrix_SetRtMatrix(MtxF* dest, s16 rotX, s16 rotY, s16 rotZ, f32 translateX, f32 translateY, f32 translateZ) {
    MtxF rotation;
    MtxF translation;

    Skin_Matrix_SetTranslate(&translation, translateX, translateY, translateZ);
    Skin_Matrix_SetRotateXyz_s(&rotation, rotX, rotY, rotZ);
    Skin_Matrix_MulMatrix(&translation, &rotation, dest);
}

void Skin_Matrix_vec2svec(xyz_t* src, s_xyz* dest) {
    dest->x = src->x;
    dest->y = src->y;
    dest->z = src->z;
}

void Skin_Matrix_svec2vec(s_xyz* src, xyz_t* dest) {
    dest->x = src->x;
    dest->y = src->y;
    dest->z = src->z;
}

void Skin_Matrix_to_Mtx(MtxF* src, Mtx* dest) {
    s32 tempX;
    u16* m1 = (u16*)&dest->m[0][0];
    u16* m2 = (u16*)&dest->m[2][0];

    tempX = src->xx * 0x10000;
    m1[0] = (tempX >> 0x10);
    m1[16 + 0] = tempX & 0xFFFF;

    tempX = src->yx * 0x10000;
    m1[1] = (tempX >> 0x10);
    m1[16 + 1] = tempX & 0xFFFF;

    tempX = src->zx * 0x10000;
    m1[2] = (tempX >> 0x10);
    m1[16 + 2] = tempX & 0xFFFF;

    tempX = src->wx * 0x10000;
    m1[3] = (tempX >> 0x10);
    m1[16 + 3] = tempX & 0xFFFF;

    tempX = src->xy * 0x10000;
    m1[4] = (tempX >> 0x10);
    m1[16 + 4] = tempX & 0xFFFF;

    tempX = src->yy * 0x10000;
    m1[5] = (tempX >> 0x10);
    m1[16 + 5] = tempX & 0xFFFF;

    tempX = src->zy * 0x10000;
    m1[6] = (tempX >> 0x10);
    m1[16 + 6] = tempX & 0xFFFF;

    tempX = src->wy * 0x10000;
    m1[7] = (tempX >> 0x10);
    m1[16 + 7] = tempX & 0xFFFF;

    tempX = src->xz * 0x10000;
    m1[8] = (tempX >> 0x10);
    m1[16 + 8] = tempX & 0xFFFF;

    tempX = src->yz * 0x10000;
    m1[9] = (tempX >> 0x10);
    m2[9] = tempX & 0xFFFF;

    tempX = src->zz * 0x10000;
    m1[10] = (tempX >> 0x10);
    m2[10] = tempX & 0xFFFF;

    tempX = src->wz * 0x10000;
    m1[11] = (tempX >> 0x10);
    m2[11] = tempX & 0xFFFF;

    tempX = src->xw * 0x10000;
    m1[12] = (tempX >> 0x10);
    m2[12] = tempX & 0xFFFF;

    tempX = src->yw * 0x10000;
    m1[13] = (tempX >> 0x10);
    m2[13] = tempX & 0xFFFF;

    tempX = src->zw * 0x10000;
    m1[14] = (tempX >> 0x10);
    m2[14] = tempX & 0xFFFF;

    tempX = src->ww * 0x10000;
    m1[15] = (tempX >> 0x10);
    m2[15] = tempX & 0xFFFF;
}

Mtx* Skin_Matrix_to_Mtx_new(GraphicsContext* gfxctx, MtxF* src) {
    Mtx* mtx = GRAPH_ALLOC(gfxctx, sizeof(Mtx));

    if (mtx == NULL) {
        return NULL;
    }
    Skin_Matrix_to_Mtx(src, mtx);
    return mtx;
}

void Skin_Matrix_SetFreeVecRotMatrix(MtxF* mf, s16 angle, f32 axisX, f32 axisY, f32 axisZ) {
    f32 sinA;
    f32 cosA;
    f32 xx;
    f32 yy;
    f32 zz;
    f32 xy;
    f32 yz;
    f32 xz;
    UNUSED s32 pad;

    sinA = sin_s(angle);
    cosA = cos_s(angle);

    xx = axisX * axisX;
    yy = axisY * axisY;
    zz = axisZ * axisZ;
    xy = axisX * axisY;
    yz = axisY * axisZ;
    xz = axisX * axisZ;

    mf->xx = (1.0f - xx) * cosA + xx;
    mf->yx = (1.0f - cosA) * xy + axisZ * sinA;
    mf->zx = (1.0f - cosA) * xz - axisY * sinA;
    mf->wx = 0.0f;

    mf->xy = (1.0f - cosA) * xy - axisZ * sinA;
    mf->yy = (1.0f - yy) * cosA + yy;
    mf->zy = (1.0f - cosA) * yz + axisX * sinA;
    mf->wy = 0.0f;

    mf->xz = (1.0f - cosA) * xz + axisY * sinA;
    mf->yz = (1.0f - cosA) * yz - axisX * sinA;
    mf->zz = (1.0f - zz) * cosA + zz;
    mf->wz = 0.0f;

    mf->xw = mf->yw = mf->zw = 0.0f;
    mf->ww = 1.0f;
}

void Skin_Matrix_SetQuaternion(MtxF* mf, f32* q) {
    f32 n;
    f32 xNorm;
    f32 yNorm;
    f32 zNorm;
    f32 wxNorm;
    f32 wyNorm;
    f32 wzNorm;
    f32 xxNorm;
    f32 xyNorm;
    f32 xzNorm;
    f32 yyNorm;
    f32 yzNorm;
    f32 zzNorm;

    n = 2.0f / ((q[3] * q[3]) + ((q[2] * q[2]) + ((q[1] * q[1]) + (q[0] * q[0]))));
    xNorm = q[0] * n;
    yNorm = q[1] * n;
    zNorm = q[2] * n;

    wxNorm = q[3] * xNorm;
    wyNorm = q[3] * yNorm;
    wzNorm = q[3] * zNorm;
    xxNorm = q[0] * xNorm;
    xyNorm = q[0] * yNorm;
    xzNorm = q[0] * zNorm;
    yyNorm = q[1] * yNorm;
    yzNorm = q[1] * zNorm;
    zzNorm = q[2] * zNorm;

    mf->xx = (1.0f - (yyNorm + zzNorm));
    mf->yx = (xyNorm + wzNorm);
    mf->zx = (xzNorm - wyNorm);
    mf->wx = 0.0f;
    mf->xy = (xyNorm - wzNorm);
    mf->yy = (1.0f - (xxNorm + zzNorm));
    mf->zy = (yzNorm + wxNorm);
    mf->wy = 0.0f;
    mf->xz = (yzNorm + wyNorm);
    mf->yz = (yzNorm - wxNorm);
    mf->zz = (1.0f - (xxNorm + yyNorm));
    mf->wz = 0.0f;
    mf->xw = 0.0f;
    mf->yw = 0.0f;
    mf->ww = 1.0f;
    mf->zw = 0.0f;
}

void Skin_Matrix_setRotateX(MtxF* mf, s16 x) {
    f32 sin;
    f32 cos;

    if (x != 0) {
        sin = sin_s(x);
        cos = cos_s(x);
    } else {
        sin = 0.0f;
        cos = 1.0f;
    }
    mf->yx = 0.0f;
    mf->zx = 0.0f;
    mf->wx = 0.0f;
    mf->xy = 0.0f;
    mf->wy = 0.0f;
    mf->xz = 0.0f;
    mf->wz = 0.0f;
    mf->xw = 0.0f;
    mf->yw = 0.0f;
    mf->zw = 0.0f;
    mf->xx = 1.0f;
    mf->ww = 1.0f;
    mf->yy = cos;
    mf->zz = cos;
    mf->zy = sin;
    mf->yz = -sin;
}

void Skin_Matrix_mulRotateX(MtxF* cmf, s16 x) {
    if (x != 0) {
        f32 sin = sin_s(x);
        f32 cos = cos_s(x);
        f32 tempX;
        f32 tempZ;

        tempX = cmf->mf[1][0];
        tempZ = cmf->mf[2][0];
        cmf->mf[1][0] = (tempX * cos) + (tempZ * sin);
        cmf->mf[2][0] = (tempZ * cos) - (tempX * sin);
        tempZ = cmf->mf[2][1];
        tempX = cmf->mf[1][1];

        cmf->mf[1][1] = (tempX * cos) + (tempZ * sin);
        cmf->mf[2][1] = (tempZ * cos) - (tempX * sin);

        tempZ = cmf->mf[2][2];
        tempX = cmf->mf[1][2];
        cmf->mf[1][2] = (tempX * cos) + (tempZ * sin);
        cmf->mf[2][2] = (tempZ * cos) - (tempX * sin);

        tempZ = cmf->mf[2][3];
        tempX = cmf->mf[1][3];
        cmf->mf[1][3] = (tempX * cos) + (tempZ * sin);
        cmf->mf[2][3] = (tempZ * cos) - (tempX * sin);
    }
}

void Skin_Matrix_setRotateY(MtxF* mf, s16 y) {
    f32 sin;
    f32 cos;

    if (y != 0) {
        sin = sin_s(y);
        cos = cos_s(y);
    } else {
        sin = 0.0f;
        cos = 1.0f;
    }
    mf->yx = 0.0f;
    mf->zx = 0.0f;
    mf->wx = 0.0f;
    mf->xy = 0.0f;
    mf->zy = 0.0f;
    mf->wy = 0.0f;
    mf->yz = 0.0f;
    mf->wz = 0.0f;
    mf->xw = 0.0f;
    mf->yw = 0.0f;
    mf->zw = 0.0f;
    mf->yy = 1.0f;
    mf->ww = 1.0f;
    mf->xx = cos;
    mf->zz = cos;
    mf->zx = -sin;
    mf->xz = sin;
}

void Skin_Matrix_mulRotateY(MtxF* cmf, s16 y) {
    if (y != 0) {
        f32 sin = sin_s(y);
        f32 cos = cos_s(y);
        f32 tempY;
        f32 tempZ;

        tempY = cmf->mf[0][0];
        tempZ = cmf->mf[2][0];
        cmf->mf[0][0] = (tempY * cos) - (tempZ * sin);
        cmf->mf[2][0] = (tempY * sin) + (tempZ * cos);

        tempY = cmf->mf[0][1];
        tempZ = cmf->mf[2][1];
        cmf->mf[0][1] = (tempY * cos) - (tempZ * sin);
        cmf->mf[2][1] = (tempY * sin) + (tempZ * cos);

        tempY = cmf->mf[0][2];
        tempZ = cmf->mf[2][2];
        cmf->mf[0][2] = (tempY * cos) - (tempZ * sin);
        cmf->mf[2][2] = (tempY * sin) + (tempZ * cos);

        tempY = cmf->mf[0][3];
        tempZ = cmf->mf[2][3];
        cmf->mf[0][3] = (tempY * cos) - (tempZ * sin);
        cmf->mf[2][3] = (tempY * sin) + (tempZ * cos);
    }
}

void Skin_Matrix_setRotateZ(MtxF* mf, s16 z) {
    f32 sin;
    f32 cos;

    if (z != 0) {
        sin = sin_s(z);
        cos = cos_s(z);
    } else {
        sin = 0.0f;
        cos = 1.0f;
    }
    mf->zx = 0.0f;
    mf->wx = 0.0f;
    mf->zy = 0.0f;
    mf->wy = 0.0f;
    mf->xz = 0.0f;
    mf->yz = 0.0f;
    mf->wz = 0.0f;
    mf->xw = 0.0f;
    mf->yw = 0.0f;
    mf->zw = 0.0f;
    mf->zz = 1.0f;
    mf->ww = 1.0f;
    mf->xx = cos;
    mf->yy = cos;
    mf->yx = sin;
    mf->xy = -sin;
}

void Skin_Matrix_mulRotateZ(MtxF* cmf, s16 z) {
    if (z != 0) {
        f32 sin = sin_s(z);
        f32 cos = cos_s(z);
        f32 tempY;
        f32 tempX;

        tempX = cmf->mf[0][0];
        tempY = cmf->mf[1][0];
        cmf->mf[0][0] = (tempX * cos) + (tempY * sin);
        cmf->mf[1][0] = (tempY * cos) - (tempX * sin);

        tempX = cmf->mf[0][1];
        tempY = cmf->mf[1][1];

        cmf->mf[0][1] = (tempX * cos) + (tempY * sin);
        cmf->mf[1][1] = (tempY * cos) - (tempX * sin);

        tempX = cmf->mf[0][2];
        tempY = cmf->mf[1][2];
        cmf->mf[0][2] = (tempX * cos) + (tempY * sin);
        cmf->mf[1][2] = (tempY * cos) - (tempX * sin);

        tempX = cmf->mf[0][3];
        tempY = cmf->mf[1][3];
        cmf->mf[0][3] = (tempX * cos) + (tempY * sin);
        cmf->mf[1][3] = (tempY * cos) - (tempX * sin);
    }
}
