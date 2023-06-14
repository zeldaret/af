/**
 * @file sys_matrix.c
 * @brief: Matrix system that mostly uses a matrix stack, and concerns affine transformations.
 *
 * @note The RSP matrix format (and hence the `MtxF` format) is column-major: vectors are presumed to be row vectors,
 * and matrices as a column of row vectors. This means that, for example, a translation matrix
 * \f[
 *  \begin{pmatrix}
 *      1 & 0 & 0 & x \\
 *      0 & 1 & 0 & y \\
 *      0 & 0 & 1 & z \\
 *      0 & 0 & 0 & 1
 *  \end{pmatrix}
 * \f]
 * will be stored as
 *
 *     { { 1, 0, 0, 0 },
 *       { 0, 1, 0, 0 },
 *       { 0, 0, 1, 0 },
 *       { x, y, z, 1 }, }
 *
 * @note As such, we label the elements in column-major order so we can follow the same conventions for multiplying
 * matrices as the rest of the world, i.e. that \f$ [AB]_{ij} = \sum_k A_{ik} B_{kj} \f$.
 *
 * This file is primarily concerned with matrices representing affine transformations, implemented using an augmented
 * matrix formalism,
 *
 * \f[
 *  \begin{pmatrix}
 *      A & b \\
 *      0 & 1
 *  \end{pmatrix}
 * \f]
 *
 * where \f$ A \f$ is a \f$ 3 \times 3 \f$ matrix (the *linear part*) and \f$ b \f$ a \f$ 3 \times 1 \f$ matrix, i.e. a
 * 3D vector (the *translation part*), and most of the functions assume that the matrices have this form.
 *
 * Throughout this file, `mode` indicates whether to multiply the matrix on top of the stack by the new construction
 * (APPLY), or to just overwrite it (NEW).
 */

#include "global.h"
#include "sys_matrix.h"
#include "game.h"
#include "z64math.h"
#include "gfx.h"

// clang-format off
Mtx Mtx_clear = gdSPDefMtx(
    1.0f, 0.0f, 0.0f, 0.0f,
    0.0f, 1.0f, 0.0f, 0.0f,
    0.0f, 0.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 0.0f, 1.0f
);
// clang-format on

MtxF MtxF_clear = { {
    { 1.0f, 0.0f, 0.0f, 0.0f },
    { 0.0f, 1.0f, 0.0f, 0.0f },
    { 0.0f, 0.0f, 1.0f, 0.0f },
    { 0.0f, 0.0f, 0.0f, 1.0f },
} };

MtxF* Matrix_stack;
MtxF* Matrix_now;

#define MATRIX_STACK_SIZE 20

/* Stack operations */

/**
 * @brief Create the matrix stack and set the pointer to the top of it.
 */
void new_Matrix(GameState* gameState) {
    Matrix_now = THA_alloc16(&gameState->heap, MATRIX_STACK_SIZE * sizeof(MtxF));
    Matrix_stack = Matrix_now;
}

/**
 * @brief Place a new matrix on the top of the stack and move the stack pointer up.
 */
void Matrix_push(void) {
    Matrix_copy_MtxF(&Matrix_now[1], Matrix_now);
    Matrix_now++;
}

/**
 * @brief Discard the top matrix on the stack and move stack pointer to the next one down.
 */
void Matrix_pull(void) {
    Matrix_now--;
}

/**
 * @brief Copy the top matrix from the stack.
 *
 * @param[out] dest Matrix into which to copy.
 */
void Matrix_get(MtxF* dest) {
    Matrix_copy_MtxF(dest, Matrix_now);
}

/**
 * @brief Overwrite the top matrix on the stack.
 *
 * @param[in] src Matrix from which to copy.
 */
void Matrix_put(MtxF* src) {
    Matrix_copy_MtxF(Matrix_now, src);
}

/**
 * @brief Return pointer to the top of the matrix stack.
 *
 * @return pointer to top matrix on the stack.
 */
MtxF* get_Matrix_now(void) {
    return Matrix_now;
}

/**
 * @brief General multiplication of current by a matrix.
 *      - APPLY: current * mf -> current
 *      - NEW: mf -> current
 *
 * @param mf Matrix to multiply by.
 * @param mode APPLY or NEW.
 */
void Matrix_mult(MtxF* mf, u8 mode) {
    MtxF* cmf = get_Matrix_now();

    if (mode == MTXMODE_APPLY) {
        Skin_Matrix_MulMatrix(cmf, mf, cmf);
    } else {
        Matrix_copy_MtxF(Matrix_now, mf);
    }
}

/**
 * @brief Right-multiply current by a translation matrix T.
 *      - APPLY: current * T -> current
 *      - NEW: T -> current
 *
 * T is given by
 *
 * \f[
 *  \begin{pmatrix}
 *      1 & 0 & 0 & x \\
 *      0 & 1 & 0 & y \\
 *      0 & 0 & 1 & z \\
 *      0 & 0 & 0 & 1
 *  \end{pmatrix} .
 * \f]
 *
 * @param x translation distance in the x direction.
 * @param y translation distance in the y direction.
 * @param z translation distance in the z direction.
 * @param mode APPLY or NEW.
 */
void Matrix_translate(f32 x, f32 y, f32 z, u8 mode) {
    MtxF* cmf = Matrix_now;
    f32 tempX;
    f32 tempY;

    if (mode == MTXMODE_APPLY) {
        tempX = cmf->xx;
        tempY = cmf->xy;
        cmf->xw += tempX * x + tempY * y + cmf->xz * z;
        tempX = cmf->yx;
        tempY = cmf->yy;
        cmf->yw += tempX * x + tempY * y + cmf->yz * z;
        tempX = cmf->zx;
        tempY = cmf->zy;
        cmf->zw += tempX * x + tempY * y + cmf->zz * z;
        tempX = cmf->wx;
        tempY = cmf->wy;
        cmf->ww += tempX * x + tempY * y + cmf->wz * z;
    } else {
        Skin_Matrix_SetTranslate(cmf, x, y, z);
    }
}

/**
 * @brief Right-multiply by the diagonal scale matrix S = diag(x,y,z,1).
 *      - APPLY: current * S -> current
 *      - NEW: S -> current
 *
 * S is given by
 *
 * \f[
 *  \begin{pmatrix}
 *      x & 0 & 0 & 0 \\
 *      0 & y & 0 & 0 \\
 *      0 & 0 & z & 0 \\
 *      0 & 0 & 0 & 1
 *  \end{pmatrix} .
 * \f]
 *
 * @param x scale in x direction.
 * @param y scale in y direction.
 * @param z scale in z direction.
 * @param mode APPLY or NEW.
 */
void Matrix_scale(f32 x, f32 y, f32 z, u8 mode) {
    MtxF* cmf = Matrix_now;

    if (mode == MTXMODE_APPLY) {
        cmf->xx *= x;
        cmf->yx *= x;
        cmf->zx *= x;
        cmf->xy *= y;
        cmf->yy *= y;
        cmf->zy *= y;
        cmf->xz *= z;
        cmf->yz *= z;
        cmf->zz *= z;
        cmf->wx *= x;
        cmf->wy *= y;
        cmf->wz *= z;
    } else {
        Skin_Matrix_SetScale(cmf, x, y, z);
    }
}

/**
 * @brief Right-multiply by a rotation about the x axis
 *      - APPLY: current * R -> current
 *      - NEW: R -> current
 *
 * R is given by
 *
 * \f[
 *  \begin{pmatrix}
 *      1 & 0 & 0 & 0 \\
 *      0 & c & -s & 0 \\
 *      0 & s & c & 0 \\
 *      0 & 0 & 0 & 1
 *  \end{pmatrix}
 * \f]
 *
 * where \f$ c = \cos x, s = \sin x \f$.
 *
 * @param x rotation angle (binary).
 * @param mode APPLY or NEW.
 */
void Matrix_RotateX(s16 x, MatrixMode mode) {
    MtxF* cmf;
    f32 sin;
    f32 cos;
    f32 tempY;
    f32 tempZ;

    if (mode == MTXMODE_APPLY) {
        if (x != 0) {
            cmf = Matrix_now;

            sin = sin_s(x);
            cos = cos_s(x);

            tempY = cmf->xy;
            tempZ = cmf->xz;
            cmf->xy = tempY * cos + tempZ * sin;
            cmf->xz = tempZ * cos - tempY * sin;

            tempY = cmf->yy;
            tempZ = cmf->yz;
            cmf->yy = tempY * cos + tempZ * sin;
            cmf->yz = tempZ * cos - tempY * sin;

            tempY = cmf->zy;
            tempZ = cmf->zz;
            cmf->zy = tempY * cos + tempZ * sin;
            cmf->zz = tempZ * cos - tempY * sin;

            tempY = cmf->wy;
            tempZ = cmf->wz;
            cmf->wy = tempY * cos + tempZ * sin;
            cmf->wz = tempZ * cos - tempY * sin;
        }
    } else {
        cmf = Matrix_now;

        if (x != 0) {
            sin = sin_s(x);
            cos = cos_s(x);
        } else {
            sin = 0.0f;
            cos = 1.0f;
        }

        cmf->yx = 0.0f;
        cmf->zx = 0.0f;
        cmf->wx = 0.0f;
        cmf->xy = 0.0f;
        cmf->wy = 0.0f;
        cmf->xz = 0.0f;
        cmf->wz = 0.0f;
        cmf->xw = 0.0f;
        cmf->yw = 0.0f;
        cmf->zw = 0.0f;
        cmf->xx = 1.0f;
        cmf->ww = 1.0f;
        cmf->yy = cos;
        cmf->zz = cos;
        cmf->zy = sin;
        cmf->yz = -sin;
    }
}

/**
 * @brief Right-multiply by a rotation about the y axis
 *      - APPLY: current * R -> current
 *      - NEW: R -> current
 *
 * R is given by
 *
 * \f[
 *  \begin{pmatrix}
 *      c & 0 & s & 0 \\
 *      0 & 1 & 0 & 0 \\
 *      -s & 0 & c & 0 \\
 *      0 & 0 & 0 & 1
 *  \end{pmatrix}
 * \f]
 *
 * where \f$ c = \cos y, s = \sin y \f$.
 *
 * @param y rotation angle (binary).
 * @param mode APPLY or NEW.
 */
void Matrix_RotateY(s16 y, MatrixMode mode) {
    MtxF* cmf;
    f32 sin;
    f32 cos;
    f32 tempX;
    f32 tempZ;

    if (mode == MTXMODE_APPLY) {
        if (y != 0) {
            cmf = Matrix_now;

            sin = sin_s(y);
            cos = cos_s(y);

            tempX = cmf->xx;
            tempZ = cmf->xz;
            cmf->xx = tempX * cos - tempZ * sin;
            cmf->xz = tempX * sin + tempZ * cos;

            tempX = cmf->yx;
            tempZ = cmf->yz;
            cmf->yx = tempX * cos - tempZ * sin;
            cmf->yz = tempX * sin + tempZ * cos;

            tempX = cmf->zx;
            tempZ = cmf->zz;
            cmf->zx = tempX * cos - tempZ * sin;
            cmf->zz = tempX * sin + tempZ * cos;

            tempX = cmf->wx;
            tempZ = cmf->wz;
            cmf->wx = tempX * cos - tempZ * sin;
            cmf->wz = tempX * sin + tempZ * cos;
        }
    } else {
        cmf = Matrix_now;

        if (y != 0) {
            sin = sin_s(y);
            cos = cos_s(y);
        } else {
            sin = 0.0f;
            cos = 1.0f;
        }

        cmf->yx = 0.0f;
        cmf->wx = 0.0f;
        cmf->xy = 0.0f;
        cmf->zy = 0.0f;
        cmf->wy = 0.0f;
        cmf->yz = 0.0f;
        cmf->wz = 0.0f;
        cmf->xw = 0.0f;
        cmf->yw = 0.0f;
        cmf->zw = 0.0f;
        cmf->yy = 1.0f;
        cmf->ww = 1.0f;
        cmf->xx = cos;
        cmf->zz = cos;
        cmf->zx = -sin;
        cmf->xz = sin;
    }
}

/**
 * @brief Right-multiply by a rotation about the z axis.
 *      - APPLY: current * R -> current
 *      - NEW: R -> current
 *
 * R is given by
 *
 * \f[
 *  \begin{pmatrix}
 *      c & -s & 0 & 0 \\
 *      s & c & 0 & 0 \\
 *      0 & 0 & 1 & 0 \\
 *      0 & 0 & 0 & 1
 *  \end{pmatrix}
 * \f]
 *
 * where \f$ c = \cos z, s = \sin z \f$.
 *
 * @param z rotation angle (binary).
 * @param mode APPLY or NEW.
 */
void Matrix_RotateZ(s16 z, MatrixMode mode) {
    MtxF* cmf;
    f32 sin;
    f32 cos;
    f32 tempX;
    f32 tempY;
    f32 zero = 0.0;
    f32 one = 1.0;

    if (mode == MTXMODE_APPLY) {
        if (z != 0) {
            cmf = Matrix_now;

            sin = sin_s(z);
            cos = cos_s(z);

            tempX = cmf->xx;
            tempY = cmf->xy;
            cmf->xx = tempX * cos + tempY * sin;
            cmf->xy = tempY * cos - tempX * sin;

            tempX = cmf->yx;
            tempY = cmf->yy;
            cmf->yx = tempX * cos + tempY * sin;
            cmf->yy = tempY * cos - tempX * sin;

            tempX = cmf->zx;
            tempY = cmf->zy;
            cmf->zx = tempX * cos + tempY * sin;
            cmf->zy = tempY * cos - tempX * sin;

            tempX = cmf->wx;
            tempY = cmf->wy;
            cmf->wx = tempX * cos + tempY * sin;
            cmf->wy = tempY * cos - tempX * sin;
        }
    } else {
        cmf = Matrix_now;

        if (z != 0) {
            sin = sin_s(z);
            cos = cos_s(z);
        } else {
            sin = zero;
            cos = one;
        }

        cmf->zx = zero;
        cmf->wx = zero;
        cmf->zy = zero;
        cmf->wy = zero;
        cmf->xz = zero;
        cmf->yz = zero;
        cmf->wz = zero;
        cmf->xw = zero;
        cmf->yw = zero;
        cmf->zw = zero;
        cmf->zz = one;
        cmf->ww = one;
        cmf->xx = cos;
        cmf->yy = cos;
        cmf->yx = sin;
        cmf->xy = -sin;
    }
}

/**
 * @brief Rotate using ZYX Tait-Bryan angles.
 *      - APPLY: current Rz Ry Rx -> current
 *      - NEW: Rz Ry Rx -> current
 *
 * This means a (column) vector is first rotated around X, then around Y, then around Z, then (if `mode` is APPLY) gets
 * transformed by what the matrix was before adding the ZYX rotation.
 *
 * See previous functions for the forms of Rz, Ry, Rx
 *
 * @param x binary angle to rotate about x axis
 * @param y binary angle to rotate about y axis
 * @param z binary angle to rotate about z axis
 * @param mode APPLY or NEW
 */
void Matrix_rotateXYZ(s16 x, s16 y, s16 z, MatrixMode mode) {
    MtxF* cmf = Matrix_now;
    f32 temp1;
    f32 temp2;
    f32 sin;
    f32 cos;

    if (mode == MTXMODE_APPLY) {
        sin = sin_s(z);
        cos = cos_s(z);

        temp1 = cmf->xx;
        temp2 = cmf->xy;
        cmf->xx = temp1 * cos + temp2 * sin;
        cmf->xy = temp2 * cos - temp1 * sin;

        temp1 = cmf->yx;
        temp2 = cmf->yy;
        cmf->yx = temp1 * cos + temp2 * sin;
        cmf->yy = temp2 * cos - temp1 * sin;

        temp1 = cmf->zx;
        temp2 = cmf->zy;
        cmf->zx = temp1 * cos + temp2 * sin;
        cmf->zy = temp2 * cos - temp1 * sin;

        temp1 = cmf->wx;
        temp2 = cmf->wy;
        cmf->wx = temp1 * cos + temp2 * sin;
        cmf->wy = temp2 * cos - temp1 * sin;

        if (y != 0) {
            sin = sin_s(y);
            cos = cos_s(y);

            temp1 = cmf->xx;
            temp2 = cmf->xz;
            cmf->xx = temp1 * cos - temp2 * sin;
            cmf->xz = temp1 * sin + temp2 * cos;

            temp1 = cmf->yx;
            temp2 = cmf->yz;
            cmf->yx = temp1 * cos - temp2 * sin;
            cmf->yz = temp1 * sin + temp2 * cos;

            temp1 = cmf->zx;
            temp2 = cmf->zz;
            cmf->zx = temp1 * cos - temp2 * sin;
            cmf->zz = temp1 * sin + temp2 * cos;

            temp1 = cmf->wx;
            temp2 = cmf->wz;
            cmf->wx = temp1 * cos - temp2 * sin;
            cmf->wz = temp1 * sin + temp2 * cos;
        }

        if (x != 0) {
            sin = sin_s(x);
            cos = cos_s(x);

            temp1 = cmf->xy;
            temp2 = cmf->xz;
            cmf->xy = temp1 * cos + temp2 * sin;
            cmf->xz = temp2 * cos - temp1 * sin;

            temp1 = cmf->yy;
            temp2 = cmf->yz;
            cmf->yy = temp1 * cos + temp2 * sin;
            cmf->yz = temp2 * cos - temp1 * sin;

            temp1 = cmf->zy;
            temp2 = cmf->zz;
            cmf->zy = temp1 * cos + temp2 * sin;
            cmf->zz = temp2 * cos - temp1 * sin;

            temp1 = cmf->wy;
            temp2 = cmf->wz;
            cmf->wy = temp1 * cos + temp2 * sin;
            cmf->wz = temp2 * cos - temp1 * sin;
        }
    } else {
        Skin_Matrix_SetRotateXyz_s(cmf, x, y, z);
    }
}

/**
 * @brief Translate and rotate using ZYX Tait-Bryan angles.
 *      current T Rz Ry Rx -> current
 *
 * This means a (column) vector is first rotated around X, then around Y, then around Z, then translated, then gets
 * transformed by whatever the matrix was previously.
 *
 * @param translation vector by which to translate.
 * @param rot vector of rotation angles.
 */
void Matrix_softcv3_mult(Vec3f* translation, Vec3s* rot) {
    MtxF* cmf = Matrix_now;
    f32 sin = sin_s(rot->z);
    f32 cos = cos_s(rot->z);
    f32 temp1;
    f32 temp2;

    // No check for z != 0, presumably since translation is interleaved.
    temp1 = cmf->xx;
    temp2 = cmf->xy;
    cmf->xw += temp1 * translation->x + temp2 * translation->y + cmf->xz * translation->z;
    cmf->xx = temp1 * cos + temp2 * sin;
    cmf->xy = temp2 * cos - temp1 * sin;

    temp1 = cmf->yx;
    temp2 = cmf->yy;
    cmf->yw += temp1 * translation->x + temp2 * translation->y + cmf->yz * translation->z;
    cmf->yx = temp1 * cos + temp2 * sin;
    cmf->yy = temp2 * cos - temp1 * sin;

    temp1 = cmf->zx;
    temp2 = cmf->zy;
    cmf->zw += temp1 * translation->x + temp2 * translation->y + cmf->zz * translation->z;
    cmf->zx = temp1 * cos + temp2 * sin;
    cmf->zy = temp2 * cos - temp1 * sin;

    temp1 = cmf->wx;
    temp2 = cmf->wy;
    cmf->ww += temp1 * translation->x + temp2 * translation->y + cmf->wz * translation->z;
    cmf->wx = temp1 * cos + temp2 * sin;
    cmf->wy = temp2 * cos - temp1 * sin;

    if (rot->y != 0) {
        sin = sin_s(rot->y);
        cos = cos_s(rot->y);

        temp1 = cmf->xx;
        temp2 = cmf->xz;
        cmf->xx = temp1 * cos - temp2 * sin;
        cmf->xz = temp1 * sin + temp2 * cos;

        temp1 = cmf->yx;
        temp2 = cmf->yz;
        cmf->yx = temp1 * cos - temp2 * sin;
        cmf->yz = temp1 * sin + temp2 * cos;

        temp1 = cmf->zx;
        temp2 = cmf->zz;
        cmf->zx = temp1 * cos - temp2 * sin;
        cmf->zz = temp1 * sin + temp2 * cos;

        temp1 = cmf->wx;
        temp2 = cmf->wz;
        cmf->wx = temp1 * cos - temp2 * sin;
        cmf->wz = temp1 * sin + temp2 * cos;
    }

    if (rot->x != 0) {
        sin = sin_s(rot->x);
        cos = cos_s(rot->x);

        temp1 = cmf->xy;
        temp2 = cmf->xz;
        cmf->xy = temp1 * cos + temp2 * sin;
        cmf->xz = temp2 * cos - temp1 * sin;

        temp1 = cmf->yy;
        temp2 = cmf->yz;
        cmf->yy = temp1 * cos + temp2 * sin;
        cmf->yz = temp2 * cos - temp1 * sin;

        temp1 = cmf->zy;
        temp2 = cmf->zz;
        cmf->zy = temp1 * cos + temp2 * sin;
        cmf->zz = temp2 * cos - temp1 * sin;

        temp1 = cmf->wy;
        temp2 = cmf->wz;
        cmf->wy = temp1 * cos + temp2 * sin;
        cmf->wz = temp2 * cos - temp1 * sin;
    }
}

/**
 * @brief Set current to a general translation and rotation using YXZ Tait-Bryan angles: T Ry Rx Rz -> current
 *
 * This means a (column) vector is first rotated around Y, then around X, then around Z, then translated, then gets
 * transformed by whatever the matrix was previously.
 *
 * @param x amount to translate in X direction.
 * @param y amount to translate in Y direction.
 * @param z amount to translate in Z direction.
 * @param rot vector of rotation angles.
 */
void Matrix_softcv3_load(f32 x, f32 y, f32 z, Vec3s* rot) {
    MtxF* cmf = Matrix_now;
    f32 sinY = sin_s(rot->y);
    f32 cosY = cos_s(rot->y);
    f32 cosTemp;
    f32 sinTemp;

    cmf->xx = cosY;
    cmf->zx = -sinY;
    cmf->xw = x;
    cmf->yw = y;
    cmf->zw = z;
    cmf->wx = 0.0f;
    cmf->wy = 0.0f;
    cmf->wz = 0.0f;
    cmf->ww = 1.0f;

    if (rot->x != 0) {
        sinTemp = sin_s(rot->x);
        cosTemp = cos_s(rot->x);

        cmf->zz = cosY * cosTemp;
        cmf->zy = cosY * sinTemp;
        cmf->xz = sinY * cosTemp;
        cmf->xy = sinY * sinTemp;
        cmf->yz = -sinTemp;
        cmf->yy = cosTemp;
    } else {
        cmf->zz = cosY;
        cmf->xz = sinY;
        cmf->yz = 0.0f;
        cmf->zy = 0.0f;
        cmf->xy = 0.0f;
        cmf->yy = 1.0f;
    }

    if (rot->z != 0) {
        sinTemp = sin_s(rot->z);
        cosTemp = cos_s(rot->z);

        sinY = cmf->xx;
        cosY = cmf->xy;
        cmf->xx = sinY * cosTemp + cosY * sinTemp;
        cmf->xy = cosY * cosTemp - sinY * sinTemp;

        sinY = cmf->zx;
        cosY = cmf->zy;
        cmf->zx = sinY * cosTemp + cosY * sinTemp;
        cmf->zy = cosY * cosTemp - sinY * sinTemp;

        cosY = cmf->yy;
        cmf->yx = cosY * sinTemp;
        cmf->yy = cosY * cosTemp;
    } else {
        cmf->yx = 0.0f;
    }
}

/**
 * @brief Converts a floating-point MtxF to a fixed-point RSP-compatible matrix.
 *
 * @param[in] src MtxF to convert.
 * @param[out] dest mtx to output to.
 *
 * @return dest
 */
Mtx* _MtxF_to_Mtx(MtxF* src, Mtx* dest) {
    s32 fp;
    u16* m1 = (u16*)&dest->m[0][0];
    u16* m2 = (u16*)&dest->m[2][0];

    fp = src->xx * 0x10000;
    m1[0] = (fp >> 0x10);
    m1[16 + 0] = fp & 0xFFFF;

    fp = src->yx * 0x10000;
    m1[1] = (fp >> 0x10);
    m1[16 + 1] = fp & 0xFFFF;

    fp = src->zx * 0x10000;
    m1[2] = (fp >> 0x10);
    m1[16 + 2] = fp & 0xFFFF;

    fp = src->wx * 0x10000;
    m1[3] = (fp >> 0x10);
    m1[16 + 3] = fp & 0xFFFF;

    fp = src->xy * 0x10000;
    m1[4] = (fp >> 0x10);
    m1[16 + 4] = fp & 0xFFFF;

    fp = src->yy * 0x10000;
    m1[5] = (fp >> 0x10);
    m1[16 + 5] = fp & 0xFFFF;

    fp = src->zy * 0x10000;
    m1[6] = (fp >> 0x10);
    m1[16 + 6] = fp & 0xFFFF;

    fp = src->wy * 0x10000;
    m1[7] = (fp >> 0x10);
    m1[16 + 7] = fp & 0xFFFF;

    fp = src->xz * 0x10000;
    m1[8] = (fp >> 0x10);
    m1[16 + 8] = fp & 0xFFFF;

    fp = src->yz * 0x10000;
    m1[9] = (fp >> 0x10);
    m2[9] = fp & 0xFFFF;

    fp = src->zz * 0x10000;
    m1[10] = (fp >> 0x10);
    m2[10] = fp & 0xFFFF;

    fp = src->wz * 0x10000;
    m1[11] = (fp >> 0x10);
    m2[11] = fp & 0xFFFF;

    fp = src->xw * 0x10000;
    m1[12] = (fp >> 0x10);
    m2[12] = fp & 0xFFFF;

    fp = src->yw * 0x10000;
    m1[13] = (fp >> 0x10);
    m2[13] = fp & 0xFFFF;

    fp = src->zw * 0x10000;
    m1[14] = (fp >> 0x10);
    m2[14] = fp & 0xFFFF;

    fp = src->ww * 0x10000;
    m1[15] = (fp >> 0x10);
    m2[15] = fp & 0xFFFF;
    return dest;
}

/**
 * @brief Converts current to a fixed-point RSP-compatible matrix.
 *
 * @param[out] dest mtx to output to.
 *
 * @return dest
 */
Mtx* _Matrix_to_Mtx(Mtx* dest) {
    return _MtxF_to_Mtx(Matrix_now, dest);
}

/**
 * @brief Converts current to a RSP-compatible matrix and saves it to allocated space in the OPA buffer.
 *
 * @param[in,out] gfxCtx Graphics context.
 *
 * @return allocated mtx.
 */
Mtx* _Matrix_to_Mtx_new(GraphicsContext* gfxCtx) {
    return _Matrix_to_Mtx(GRAPH_ALLOC(gfxCtx, sizeof(Mtx)));
}

/**
 * @brief Converts src to a RSP-compatible matrix and saves it to allocated space in the OPA buffer.
 *
 * @param[in] src MtxF to convert.
 * @param[in,out] gfxCtx Graphics context.
 *
 * @return allocated mtx.
 */
void _MtxF_to_Mtx_new(MtxF* src, GraphicsContext* gfxCtx) {
    _MtxF_to_Mtx(src, GRAPH_ALLOC(gfxCtx, sizeof(Mtx)));
}

/**
 * @brief Calculates current * (src,1) and writes its components to dest.
 *
 * This assumes that current has the form
 *
 * \f[
 *  M =
 *  \begin{pmatrix}
 *      A & b \\
 *      0 & 1
 *  \end{pmatrix}
 * \f]
 *
 * where A is \f$ 3 \times 3 \f$ and b \f$ 3 \times 1 \f$, and so calculates
 *
 * \f[
 *  MX =
 *  \begin{pmatrix}
 *      A & b \\
 *      0 & 1
 *  \end{pmatrix}
 *  \begin{pmatrix}
 *      x \\
 *      1
 *  \end{pmatrix}
 *  =
 *  \begin{pmatrix}
 *      Ax + b \\
 *      1
 *  \end{pmatrix}
 * \f]
 *
 * and discards the extra w component (1).
 *
 * @param[in] src input vector
 * @param[out] dest output vector
 */
void Matrix_Position(Vec3f* src, Vec3f* dest) {
    MtxF* cmf = Matrix_now;

    dest->x = cmf->xw + (cmf->xx * src->x + cmf->xy * src->y + cmf->xz * src->z);
    dest->y = cmf->yw + (cmf->yx * src->x + cmf->yy * src->y + cmf->yz * src->z);
    dest->z = cmf->zw + (cmf->zx * src->x + cmf->zy * src->y + cmf->zz * src->z);
}

/**
 * @brief Multiply the vector `(0, 0, 0, 1)` by current.
 *
 * Can also see it as obtaining the translation vector part of current, but the former interpretation is consistent with
 * the other functions nearby.
 *
 * @note Special case of Matrix_Position() with `src = { 0, 0, 0 }`; the same assumptions apply.
 *
 * @param[out] dest output vector.
 */
void Matrix_Position_Zero(Vec3f* dest) {
    MtxF* cmf = Matrix_now;

    dest->x = cmf->xw;
    dest->y = cmf->yw;
    dest->z = cmf->zw;
}

/**
 * @brief Multiply the vector `(x, 0, 0, 1)` by current.
 *
 * I.e. calculate \f$ A(x, 0, 0) + b \f$.
 *
 * @note Special case of Matrix_Position() with `src = { x, 0, 0 }`; the same assumptions apply.
 *
 * @param[in] x multiplier of unit vector in x direction.
 * @param[out] dest output vector.
 */
void Matrix_Position_VecX(f32 x, Vec3f* dest) {
    MtxF* cmf = Matrix_now;

    dest->x = cmf->xw + cmf->xx * x;
    dest->y = cmf->yw + cmf->yx * x;
    dest->z = cmf->zw + cmf->zx * x;
}

/**
 * @brief Multiply the vector `(0, y, 0, 1)` by current.
 *
 * I.e. calculate \f$ A(0, y, 0) + b \f$.
 *
 * @note Special case of Matrix_Position() with `src = { 0, y, 0 }`; the same assumptions apply.
 *
 * @param[in] y multiplier of unit vector in y direction.
 * @param[out] dest output vector.
 */
void Matrix_Position_VecY(f32 y, Vec3f* dest) {
    MtxF* cmf = Matrix_now;

    dest->x = cmf->xw + cmf->xy * y;
    dest->y = cmf->yw + cmf->yy * y;
    dest->z = cmf->zw + cmf->zy * y;
}

/**
 * @brief Multiply the vector `(0, 0, z, 1)` by current.
 *
 * I.e. calculate \f$ A(0, 0, z) + b \f$.
 *
 * @note Special case of Matrix_Position() with `src = { 0, 0, z }`; the same assumptions apply.
 *
 * @param[in] z multiplier of unit vector in z direction.
 * @param[out] dest output vector.
 */
void Matrix_Position_VecZ(f32 z, Vec3f* dest) {
    MtxF* cmf = Matrix_now;

    dest->x = cmf->xw + cmf->xz * z;
    dest->y = cmf->yw + cmf->yz * z;
    dest->z = cmf->zw + cmf->zz * z;
}

/**
 * @brief Copies the matrix src into dest.
 *
 * @param[out] dest matrix to copy to.
 * @param[in] src matrix to copy from.
 */
void Matrix_copy_MtxF(MtxF* dest, MtxF* src) {
    s32 i;

    for (i = 0; i < 4; i++) {
        dest->mf[i][0] = src->mf[i][0];
        dest->mf[i][1] = src->mf[i][1];
        dest->mf[i][2] = src->mf[i][2];
        dest->mf[i][3] = src->mf[i][3];
    }
}

/**
 * @brief Converts fixed-point RSP-compatible matrix to an MtxF.
 *
 * @param[in] src mtx to convert
 * @param[out] dest MtxF to output to
 */
void Matrix_MtxtoMtxF(Mtx* src, MtxF* dest) {
    u16* m1 = (u16*)&src->m[0][0];
    u16* m2 = (u16*)&src->m[2][0];

    dest->xx = ((m1[0] << 0x10) | m2[0]) * (1 / (f32)0x10000);
    dest->yx = ((m1[1] << 0x10) | m2[1]) * (1 / (f32)0x10000);
    dest->zx = ((m1[2] << 0x10) | m2[2]) * (1 / (f32)0x10000);
    dest->wx = ((m1[3] << 0x10) | m2[3]) * (1 / (f32)0x10000);
    dest->xy = ((m1[4] << 0x10) | m2[4]) * (1 / (f32)0x10000);
    dest->yy = ((m1[5] << 0x10) | m2[5]) * (1 / (f32)0x10000);
    dest->zy = ((m1[6] << 0x10) | m2[6]) * (1 / (f32)0x10000);
    dest->wy = ((m1[7] << 0x10) | m2[7]) * (1 / (f32)0x10000);
    dest->xz = ((m1[8] << 0x10) | m2[8]) * (1 / (f32)0x10000);
    dest->yz = ((m1[9] << 0x10) | m2[9]) * (1 / (f32)0x10000);
    dest->zz = ((m1[10] << 0x10) | m2[10]) * (1 / (f32)0x10000);
    dest->wz = ((m1[11] << 0x10) | m2[11]) * (1 / (f32)0x10000);
    dest->xw = ((m1[12] << 0x10) | m2[12]) * (1 / (f32)0x10000);
    dest->yw = ((m1[13] << 0x10) | m2[13]) * (1 / (f32)0x10000);
    dest->zw = ((m1[14] << 0x10) | m2[14]) * (1 / (f32)0x10000);
    dest->ww = ((m1[15] << 0x10) | m2[15]) * (1 / (f32)0x10000);
}

/**
 * @brief Calculates mf * (src,1) and writes its components to dest.
 *
 * This is the same as Matrix_Position() but using a specified matrix rather than the current one; the same
 * assumptions apply.
 *
 * @param[in] src input vector
 * @param[out] dest output vector
 * @param[in] mf matrix to multiply by
 */
void Matrix_MtxF_Position2(Vec3f* src, Vec3f* dest, MtxF* mf) {
    dest->x = mf->xw + (mf->xx * src->x + mf->xy * src->y + mf->xz * src->z);
    dest->y = mf->yw + (mf->yx * src->x + mf->yy * src->y + mf->yz * src->z);
    dest->z = mf->zw + (mf->zx * src->x + mf->zy * src->y + mf->zz * src->z);
}

/**
 * @brief Overwrite the linear part of mf with its transpose (ignores the translational part).
 *
 * Viz.,
 *
 * \f[
 *  \begin{pmatrix}
 *      A & b \\
 *      0 & 1
 *  \end{pmatrix}
 *  \longrightarrow
 *  \begin{pmatrix}
 *      A^T & b \\
 *      0 & 1
 *  \end{pmatrix}
 * \f]
 *
 * @param[in,out] mf matrix to transpose
 */
void Matrix_reverse(MtxF* mf) {
    f32 temp;

    temp = mf->yx;
    mf->yx = mf->xy;
    mf->xy = temp;

    temp = mf->zx;
    mf->zx = mf->xz;
    mf->xz = temp;

    temp = mf->zy;
    mf->zy = mf->yz;
    mf->yz = temp;
}

/**
 * @brief Decompose the linear part A of current into B * S, where B has normalised columns and S is diagonal, and
 * replace B by `mf`.
 *
 * Since B is typically a rotation matrix, and the linear part R * S to `mf` * S, this operation can be
 * seen as replacing the B rotation with `mf`, hence the function name.
 *
 * @param[in] mf matrix whose linear part will replace the normalised part of A.
 */
void Matrix_rotate_scale_exchange(MtxF* mf) {
    MtxF* cmf = Matrix_now;
    f32 acc;
    f32 component;
    f32 curColNorm;

    // compute the Euclidean norm of the first column of the current matrix
    acc = cmf->xx;
    acc *= acc;
    component = cmf->yx;
    acc += SQ(component);
    component = cmf->zx;
    acc += SQ(component);
    curColNorm = sqrtf(acc);

    cmf->xx = mf->xx * curColNorm;
    cmf->yx = mf->yx * curColNorm;
    cmf->zx = mf->zx * curColNorm;

    // second column
    acc = cmf->xy;
    acc *= acc;
    component = cmf->yy;
    acc += SQ(component);
    component = cmf->zy;
    acc += SQ(component);
    curColNorm = sqrtf(acc);

    cmf->xy = mf->xy * curColNorm;
    cmf->yy = mf->yy * curColNorm;
    cmf->zy = mf->zy * curColNorm;

    // third column
    acc = cmf->xz;
    acc *= acc;
    component = cmf->yz;
    acc += SQ(component);
    component = cmf->zz;
    acc += SQ(component);
    curColNorm = sqrtf(acc);

    cmf->xz = mf->xz * curColNorm;
    cmf->yz = mf->yz * curColNorm;
    cmf->zz = mf->zz * curColNorm;
}

/**
 * @brief Extract the YXZ Tait-Bryan rotation angles from the linear part \f$ A \f$ of a matrix.
 *
 * \f$ A \f$ should have orthogonal columns; the most general matrix of this form can be written as \f$ RS \f$
 * with \f$ S \f$ a scale matrix.
 *
 * If A has columns with the same norm (such as if it is just a rotation matrix), it is sufficient (and faster) to use
 * `nonUniformScale` off: `nonUniformScale` being set enables extraction of the angles from a matrix with columns that
 * are orthogonal but have different scales, at the cost of requiring extra calculation.
 *
 * @param[in] src Matrix to extract angles from.
 * @param[out] dest vector to write angles to.
 * @param[in] nonUniformScale boolean: true enables handling matrices with differently-scaled columns.
 */
void Matrix_to_rotate_new(MtxF* src, Vec3s* dest, s32 nonUniformScale) {
    f32 temp;
    f32 temp2;
    f32 temp3;
    f32 temp4;

    temp = src->xz;
    temp *= temp;
    temp += SQ(src->zz);
    dest->x = (Math_FAtan2F(-src->yz, sqrtf(temp))) * 10430.378f;

    if ((dest->x == 0x4000) || (dest->x == -0x4000)) {
        // cos(x) = 0 if either of these is true, and we get gimbal locking
        // (https://en.wikipedia.org/wiki/Gimbal_lock#Loss_of_a_degree_of_freedom_with_Euler_angles); fix z to make y
        // well-defined.
        dest->z = 0;

        dest->y = Math_FAtan2F(-src->zx, src->xx) * 10430.378f;
    } else {
        dest->y = Math_FAtan2F(src->xz, src->zz) * 10430.378f;

        if (!nonUniformScale) {
            // assume the columns have the same normalisation
            dest->z = Math_FAtan2F(src->yx, src->yy) * 10430.378f;
        } else {
            temp = src->xx;
            temp2 = src->zx;
            temp3 = src->zy;

            // find norm of the first column
            temp *= temp;
            temp += SQ(temp2);
            temp2 = src->yx;
            temp += SQ(temp2);
            // temp = xx^2+zx^2+yx^2 == 1 for a rotation matrix
            temp = sqrtf(temp);
            temp = temp2 / temp; // yx in normalised column

            // find norm of the second column
            temp2 = src->xy;
            temp2 *= temp2;
            temp2 += SQ(temp3);
            temp3 = src->yy;
            temp2 += SQ(temp3);
            // temp2 = xy^2+zy^2+yy^2 == 1 for a rotation matrix
            temp2 = sqrtf(temp2);
            temp2 = temp3 / temp2; // yy in normalised column

            // for a rotation matrix, temp == yx and temp2 == yy which is the same as in the !nonUniformScale branch
            dest->z = Math_FAtan2F(temp, temp2) * 10430.378f;
        }
    }
}

/**
 * @brief Extract the ZYX Tait-Bryan rotation angles from the linear part \f$ A \f$ of a matrix.
 *
 * \f$ A \f$ should have orthogonal columns; the most general matrix of this form can be written as \f$ RS \f$
 * with \f$ S \f$ a scale matrix.
 *
 * If A has columns with the same norm (such as if it is just a rotation matrix), it is sufficient (and faster) to use
 * `nonUniformScale` off: `nonUniformScale` being set enables extraction of the angles from a matrix with columns that
 * are orthogonal but have different scales, at the cost of requiring extra calculation.
 *
 * @param[in] src Matrix to extract angles from.
 * @param[out] dest vector to write angles to.
 * @param[in] nonUniformScale boolean: true enables handling matrices with unnormalised columns.
 *
 * See Matrix_to_rotate_new() for full inline documentation.
 */
void Matrix_to_rotate2_new(MtxF* src, Vec3s* dest, s32 nonUniformScale) {
    f32 temp;
    f32 temp2;
    f32 temp3;
    f32 temp4;

    temp = src->xx;
    temp *= temp;
    temp += SQ(src->yx);
    dest->y = Math_FAtan2F(-src->zx, sqrtf(temp)) * 10430.378f;

    if ((dest->y == 0x4000) || (dest->y == -0x4000)) {
        dest->x = 0;
        dest->z = Math_FAtan2F(-src->xy, src->yy) * 10430.378f;
    } else {
        dest->z = Math_FAtan2F(src->yx, src->xx) * 10430.378f;

        if (!nonUniformScale) {
            dest->x = Math_FAtan2F(src->zy, src->zz) * 10430.378f;
        } else {
            temp = src->xy;
            temp2 = src->yy;
            temp3 = src->yz;

            temp *= temp;
            temp += SQ(temp2);
            temp2 = src->zy;
            temp += SQ(temp2);
            temp = sqrtf(temp);
            temp = temp2 / temp;

            temp2 = src->xz;
            temp2 *= temp2;
            temp2 += SQ(temp3);
            temp3 = src->zz;
            temp2 += SQ(temp3);
            temp2 = sqrtf(temp2);
            temp2 = temp3 / temp2;

            dest->x = Math_FAtan2F(temp, temp2) * 10430.378f;
        }
    }
}

/**
 * @brief Rotate by binary angle `angle` about `axis`, which is assumed to be a unit vector.
 *
 * @param angle rotation angle (binary).
 * @param axis axis about which to rotate, must be a unit vector.
 * @param mode APPLY or NEW.
 */
void Matrix_RotateVector(s16 angle, Vec3f* axis, u8 mode) {
    MtxF* curm;
    f32 sin;
    f32 cos;
    f32 versin;
    f32 temp1; // component x
    f32 temp2; // component y
    f32 temp3; // component z
    f32 temp4; // component q?

    if (mode == 1) {
        if (angle != 0) {
            curm = Matrix_now;

            sin = sin_s(angle);
            cos = cos_s(angle);
            temp1 = curm->xx;
            temp2 = curm->xy;
            temp3 = curm->xz;
            temp4 = (axis->x * temp1 + axis->y * temp2 + axis->z * temp3) * (1.0f - cos);
            curm->xx = temp1 * cos + axis->x * temp4 + sin * (temp2 * axis->z - temp3 * axis->y);
            curm->xy = temp2 * cos + axis->y * temp4 + sin * (temp3 * axis->x - temp1 * axis->z);
            curm->xz = temp3 * cos + axis->z * temp4 + sin * (temp1 * axis->y - temp2 * axis->x);

            temp1 = curm->yx;
            temp2 = curm->yy;
            temp3 = curm->yz;
            temp4 = (axis->x * temp1 + axis->y * temp2 + axis->z * temp3) * (1.0f - cos);
            curm->yx = temp1 * cos + axis->x * temp4 + sin * (temp2 * axis->z - temp3 * axis->y);
            curm->yy = temp2 * cos + axis->y * temp4 + sin * (temp3 * axis->x - temp1 * axis->z);
            curm->yz = temp3 * cos + axis->z * temp4 + sin * (temp1 * axis->y - temp2 * axis->x);

            temp1 = curm->zx;
            temp2 = curm->zy;
            temp3 = curm->zz;
            temp4 = (axis->x * temp1 + axis->y * temp2 + axis->z * temp3) * (1.0f - cos);
            curm->zx = temp1 * cos + axis->x * temp4 + sin * (temp2 * axis->z - temp3 * axis->y);
            curm->zy = temp2 * cos + axis->y * temp4 + sin * (temp3 * axis->x - temp1 * axis->z);
            curm->zz = temp3 * cos + axis->z * temp4 + sin * (temp1 * axis->y - temp2 * axis->x);
        }
    } else {
        curm = Matrix_now;

        if (angle != 0) {
            sin = sin_s(angle);
            cos = cos_s(angle);
            versin = 1.0f - cos;

            curm->xx = axis->x * axis->x * versin + cos;
            curm->yy = axis->y * axis->y * versin + cos;
            curm->zz = axis->z * axis->z * versin + cos;

            if (0) {}

            temp2 = axis->x * versin * axis->y;
            temp3 = axis->z * sin;
            curm->yx = temp2 + temp3;
            curm->xy = temp2 - temp3;

            temp2 = axis->x * versin * axis->z;
            temp3 = axis->y * sin;
            curm->zx = temp2 - temp3;
            curm->xz = temp2 + temp3;

            temp2 = axis->y * versin * axis->z;
            temp3 = axis->x * sin;
            curm->zy = temp2 + temp3;
            curm->yz = temp2 - temp3;

            curm->wx = 0.0f;
            curm->wy = 0.0f;
            curm->wz = 0.0f;
            curm->xw = 0.0f;
            curm->yw = 0.0f;
            curm->zw = 0.0f;
            curm->ww = 1.0f;
        } else {
            curm->yx = 0.0f;
            curm->zx = 0.0f;
            curm->wx = 0.0f;
            curm->xy = 0.0f;
            curm->zy = 0.0f;
            curm->wy = 0.0f;
            curm->xz = 0.0f;
            curm->yz = 0.0f;
            curm->wz = 0.0f;
            curm->xw = 0.0f;
            curm->yw = 0.0f;
            curm->zw = 0.0f;
            curm->xx = 1.0f;
            curm->yy = 1.0f;
            curm->zz = 1.0f;
            curm->ww = 1.0f;
        }
    }
}

//todo full comment
void suMtxMakeTS(Mtx* mtx, f32 scaleX, f32 scaleY, f32 scaleZ, f32 translateX, f32 translateY, f32 translateZ) {
    struct {
        s16 intPart[4][4];
        u16 fracPart[4][4];
    }* mu = (void*)mtx;
    s32 fp;

    fp = scaleX * 0x10000;
    mtx->m[0][0] = fp;
    mu->intPart[0][1] = 0;
    mtx->m[0][1] = 0;
    mtx->m[2][0] = (u32)fp << 16;

    fp = scaleY * 0x10000;
    mtx->m[2][1] = 0;
    mtx->m[0][2] = (u32)fp >> 16;
    mtx->m[0][3] = 0;
    mtx->m[2][2] = fp & 0xFFFF;
    mtx->m[2][3] = 0;

    fp = scaleZ * 0x10000;
    mtx->m[1][0] = 0;
    mtx->m[1][1] = fp;
    mu->intPart[2][3] = 0;
    mtx->m[3][0] = 0;
    mtx->m[3][1] = (u32)fp << 16;

    fp = translateX * 0x10000;
    mu->intPart[3][0] = ((u32)fp >> 16) & 0xFFFF;
    mu->fracPart[3][0] = fp & 0xFFFF;

    fp = translateY * 0x10000;
    mu->intPart[3][1] = ((u32)fp >> 16) & 0xFFFF;
    mu->fracPart[3][1] = fp & 0xFFFF;

    fp = translateZ * 0x10000;
    mu->intPart[3][2] = ((u32)fp >> 16) & 0xFFFF;
    mu->intPart[3][3] = 1;
    mtx->m[3][3] = (u32)fp << 16;
}

//todo full comment
// S(RxRyRz)T where S is a scale matrix, Rx/Ry/Rz are rotations about the x/y/z axes, and T is a translation
void suMtxMakeSRT(Mtx* mtx, f32 scaleX, f32 scaleY, f32 scaleZ, s16 rotX, s16 rotY, s16 rotZ, f32 translateX,
                  f32 translateY, f32 translateZ) {
    s32 fp;
    struct {
        s16 intPart[4][4];
        u16 fracPart[4][4];
    }* mu = (void*)mtx;
    f32 sinX = sin_s(rotX);
    f32 sinY = sin_s(rotY); // sp+38
    f32 sinZ = sin_s(rotZ); // sp+34
    f32 cosX = cos_s(rotX); // sp+30
    f32 cosY = cos_s(rotY); // sp+2C
    f32 cosZ = cos_s(rotZ);

    fp = cosY * cosZ * scaleX * 0x10000;
    mu->intPart[0][0] = ((u32)fp >> 0x10) & 0xFFFF;
    mu->fracPart[0][0] = fp & 0xFFFF;

    fp = cosY * sinZ * scaleX * 0x10000;
    mu->intPart[0][1] = ((u32)fp >> 0x10) & 0xFFFF;
    mu->fracPart[0][1] = fp & 0xFFFF;

    fp = -sinY * scaleX * 0x10000;
    mu->intPart[0][2] = ((u32)fp >> 0x10) & 0xFFFF;
    mu->fracPart[0][2] = fp & 0xFFFF;

    fp = ((sinX * sinY * cosZ) - (cosX * sinZ)) * scaleY * 0x10000;
    mu->intPart[1][0] = ((u32)fp >> 0x10) & 0xFFFF;
    mu->fracPart[1][0] = fp & 0xFFFF;

    fp = ((sinX * sinY * sinZ) + (cosX * cosZ)) * scaleY * 0x10000;
    mu->intPart[1][1] = ((u32)fp >> 0x10) & 0xFFFF;
    mu->fracPart[1][1] = fp & 0xFFFF;

    fp = sinX * cosY * scaleY * 0x10000;
    mu->intPart[1][2] = ((u32)fp >> 0x10) & 0xFFFF;
    mu->fracPart[1][2] = fp & 0xFFFF;

    fp = ((cosX * sinY * cosZ) + (sinX * sinZ)) * scaleZ * 0x10000;
    mu->intPart[2][0] = ((u32)fp >> 0x10) & 0xFFFF;
    mu->fracPart[2][0] = fp & 0xFFFF;

    fp = ((cosX * sinY * sinZ) - (sinX * cosZ)) * scaleZ * 0x10000;
    mu->intPart[2][1] = ((u32)fp >> 0x10) & 0xFFFF;
    mu->fracPart[2][1] = fp & 0xFFFF;

    fp = cosX * cosY * scaleZ * 0x10000;
    mu->intPart[2][2] = ((u32)fp >> 0x10) & 0xFFFF;
    mu->fracPart[2][2] = fp & 0xFFFF;

    fp = translateX * 0x10000;
    mu->intPart[3][0] = ((u32)fp >> 0x10) & 0xFFFF;
    mu->fracPart[3][0] = fp & 0xFFFF;

    fp = translateY * 0x10000;
    mu->intPart[3][1] = ((u32)fp >> 0x10) & 0xFFFF;
    mu->fracPart[3][1] = fp & 0xFFFF;

    fp = translateZ * 0x10000;
    mu->intPart[3][2] = ((u32)fp >> 0x10) & 0xFFFF;
    mu->fracPart[3][2] = fp & 0xFFFF;

    mu->intPart[0][3] = mu->intPart[1][3] = mu->intPart[2][3] = 0;
    mu->fracPart[0][3] = mu->fracPart[1][3] = mu->fracPart[2][3] = 0;
    mu->intPart[3][3] = 1;
    mu->fracPart[3][3] = 0;
}

//todo full comment
// S(RzRxRy)T where S is a scale matrix, Rx/Ry/Rz are rotations, and T is a translation
void suMtxMakeSRT_ZXY(Mtx* mtx, f32 scaleX, f32 scaleY, f32 scaleZ, s16 rotX, s16 rotY, s16 rotZ, f32 translateX,
                      f32 translateY, f32 translateZ) {
    s32 fp;
    struct {
        s16 intPart[4][4];
        u16 fracPart[4][4];
    }* mu = (void*)mtx;
    f32 sinX = sin_s(rotX); // sp+4C
    f32 sinY = sin_s(rotY); // likely sp+48
    f32 sinZ = sin_s(rotZ); // sp+44
    f32 cosX = cos_s(rotX); // sp+40
    f32 cosY = cos_s(rotY); // sp+3C
    f32 cosZ = cos_s(rotZ); // likely sp+38

    fp = ((cosY * cosZ) + (sinX * sinY * sinZ)) * scaleX * 0x10000;
    mu->intPart[0][0] = ((u32)fp >> 0x10) & 0xFFFF;
    mu->fracPart[0][0] = fp & 0xFFFF;

    fp = cosX * sinZ * scaleX * 0x10000;
    mu->intPart[0][1] = ((u32)fp >> 0x10) & 0xFFFF;
    mu->fracPart[0][1] = fp & 0xFFFF;

    fp = (-(sinY * cosZ) + (sinX * cosY * sinZ)) * scaleX * 0x10000;
    mu->intPart[0][2] = ((u32)fp >> 0x10) & 0xFFFF;
    mu->fracPart[0][2] = fp & 0xFFFF;

    fp = (-(cosY * sinZ) + (sinX * sinY * cosZ)) * scaleY * 0x10000;
    mu->intPart[1][0] = ((u32)fp >> 0x10) & 0xFFFF;
    mu->fracPart[1][0] = fp & 0xFFFF;

    fp = cosX * cosZ * scaleY * 0x10000;
    mu->intPart[1][1] = ((u32)fp >> 0x10) & 0xFFFF;
    mu->fracPart[1][1] = fp & 0xFFFF;

    fp = ((sinY * sinZ) + (sinX * cosY * cosZ)) * scaleY * 0x10000;
    mu->intPart[1][2] = ((u32)fp >> 0x10) & 0xFFFF;
    mu->fracPart[1][2] = fp & 0xFFFF;

    fp = cosX * sinY * scaleZ * 0x10000;
    mu->intPart[2][0] = ((u32)fp >> 0x10) & 0xFFFF;
    mu->fracPart[2][0] = fp & 0xFFFF;

    fp = -sinX * scaleZ * 0x10000;
    mu->intPart[2][1] = ((u32)fp >> 0x10) & 0xFFFF;
    mu->fracPart[2][1] = fp & 0xFFFF;

    fp = cosX * cosY * scaleZ * 0x10000;
    mu->intPart[2][2] = ((u32)fp >> 0x10) & 0xFFFF;
    mu->fracPart[2][2] = fp & 0xFFFF;

    fp = translateX * 0x10000;
    mu->intPart[3][0] = ((u32)fp >> 0x10) & 0xFFFF;
    mu->fracPart[3][0] = fp & 0xFFFF;

    fp = translateY * 0x10000;
    mu->intPart[3][1] = ((u32)fp >> 0x10) & 0xFFFF;
    mu->fracPart[3][1] = fp & 0xFFFF;

    fp = translateZ * 0x10000;
    mu->intPart[3][2] = ((u32)fp >> 0x10) & 0xFFFF;
    mu->fracPart[3][2] = fp & 0xFFFF;

    mu->intPart[0][3] = mu->intPart[1][3] = mu->intPart[2][3] = 0;
    mu->fracPart[0][3] = mu->fracPart[1][3] = mu->fracPart[2][3] = 0;
    mu->intPart[3][3] = 1;
    mu->fracPart[3][3] = 0;
}
