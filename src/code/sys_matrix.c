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

#include "sys_matrix.h"
#include "game.h"
#include "z64math.h"
#include "gfx.h"
#include "m_skin_matrix.h"
#include "libc64/math64.h"
#include "m_lib.h"

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

MtxF* Matrix_stack; // Bottom of the stack.
MtxF* Matrix_now;   // Top of the stack.

#define MATRIX_STACK_SIZE 20

/* Stack operations */

/**
 * Create the matrix stack and set the pointer to the top of it.
 */
void new_Matrix(Game* gameState) {
    Matrix_now = THA_alloc16(&gameState->heap, MATRIX_STACK_SIZE * sizeof(MtxF));
    Matrix_stack = Matrix_now;
}

/**
 * Place a new matrix on the top of the stack and move the stack pointer up.
 */
void Matrix_push(void) {
    Matrix_copy_MtxF(&Matrix_now[1], Matrix_now);
    Matrix_now++;
}

/**
 * Discard the top matrix on the stack and move stack pointer to the next one down.
 */
void Matrix_pull(void) {
    Matrix_now--;
}

/**
 * Copy the top matrix from the stack.
 *
 * @param[out] dest Matrix into which to copy.
 */
void Matrix_get(MtxF* dest) {
    Matrix_copy_MtxF(dest, Matrix_now);
}

/**
 * Overwrite the top matrix on the stack.
 *
 * @param[in] src Matrix from which to copy.
 */
void Matrix_put(MtxF* src) {
    Matrix_copy_MtxF(Matrix_now, src);
}

/**
 * Return pointer to the top of the matrix stack.
 *
 * @return pointer to top matrix on the stack.
 */
MtxF* get_Matrix_now(void) {
    return Matrix_now;
}

/**
 * General multiplication of the top matrix on the stack by another matrix.
 *
 * - APPLY: top * mf -> top
 * - NEW: mf -> top
 *
 * @param mf Matrix to multiply by.
 * @param mode APPLY or NEW.
 */
void Matrix_mult(MtxF* mf, u8 mode) {
    MtxF* top = get_Matrix_now();

    if (mode == MTXMODE_APPLY) {
        Skin_Matrix_MulMatrix(top, mf, top);
    } else {
        Matrix_copy_MtxF(Matrix_now, mf);
    }
}

/**
 * Right-multiply the top matrix on the stack by a translation matrix T.
 *
 * - APPLY: top * T -> top
 * - NEW: T -> top
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
    MtxF* top = Matrix_now;
    f32 tempX;
    f32 tempY;

    if (mode == MTXMODE_APPLY) {
        tempX = top->xx;
        tempY = top->xy;
        top->xw += tempX * x + tempY * y + top->xz * z;
        tempX = top->yx;
        tempY = top->yy;
        top->yw += tempX * x + tempY * y + top->yz * z;
        tempX = top->zx;
        tempY = top->zy;
        top->zw += tempX * x + tempY * y + top->zz * z;
        tempX = top->wx;
        tempY = top->wy;
        top->ww += tempX * x + tempY * y + top->wz * z;
    } else {
        Skin_Matrix_SetTranslate(top, x, y, z);
    }
}

/**
 * Right-multiply the top matrix on the stack by the diagonal scale matrix S = diag(x,y,z,1).
 *
 * - APPLY: top * S -> top
 * - NEW: S -> top
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
    MtxF* top = Matrix_now;

    if (mode == MTXMODE_APPLY) {
        top->xx *= x;
        top->yx *= x;
        top->zx *= x;
        top->xy *= y;
        top->yy *= y;
        top->zy *= y;
        top->xz *= z;
        top->yz *= z;
        top->zz *= z;
        top->wx *= x;
        top->wy *= y;
        top->wz *= z;
    } else {
        Skin_Matrix_SetScale(top, x, y, z);
    }
}

/**
 * Right-multiply the top matrix on the stack by a rotation about the x axis
 *
 * - APPLY: top * R -> top
 * - NEW: R -> top
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
    MtxF* top;
    f32 sin;
    f32 cos;
    f32 tempY;
    f32 tempZ;

    if (mode == MTXMODE_APPLY) {
        if (x != 0) {
            top = Matrix_now;

            sin = sin_s(x);
            cos = cos_s(x);

            tempY = top->xy;
            tempZ = top->xz;
            top->xy = tempY * cos + tempZ * sin;
            top->xz = tempZ * cos - tempY * sin;

            tempY = top->yy;
            tempZ = top->yz;
            top->yy = tempY * cos + tempZ * sin;
            top->yz = tempZ * cos - tempY * sin;

            tempY = top->zy;
            tempZ = top->zz;
            top->zy = tempY * cos + tempZ * sin;
            top->zz = tempZ * cos - tempY * sin;

            tempY = top->wy;
            tempZ = top->wz;
            top->wy = tempY * cos + tempZ * sin;
            top->wz = tempZ * cos - tempY * sin;
        }
    } else {
        top = Matrix_now;

        if (x != 0) {
            sin = sin_s(x);
            cos = cos_s(x);
        } else {
            sin = 0.0f;
            cos = 1.0f;
        }

        top->yx = 0.0f;
        top->zx = 0.0f;
        top->wx = 0.0f;
        top->xy = 0.0f;
        top->wy = 0.0f;
        top->xz = 0.0f;
        top->wz = 0.0f;
        top->xw = 0.0f;
        top->yw = 0.0f;
        top->zw = 0.0f;
        top->xx = 1.0f;
        top->ww = 1.0f;
        top->yy = cos;
        top->zz = cos;
        top->zy = sin;
        top->yz = -sin;
    }
}

/**
 * Right-multiply the top matrix on the stack by a rotation about the y axis
 *
 * - APPLY: top * R -> top
 * - NEW: R -> top
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
    MtxF* top;
    f32 sin;
    f32 cos;
    f32 tempX;
    f32 tempZ;

    if (mode == MTXMODE_APPLY) {
        if (y != 0) {
            top = Matrix_now;

            sin = sin_s(y);
            cos = cos_s(y);

            tempX = top->xx;
            tempZ = top->xz;
            top->xx = tempX * cos - tempZ * sin;
            top->xz = tempX * sin + tempZ * cos;

            tempX = top->yx;
            tempZ = top->yz;
            top->yx = tempX * cos - tempZ * sin;
            top->yz = tempX * sin + tempZ * cos;

            tempX = top->zx;
            tempZ = top->zz;
            top->zx = tempX * cos - tempZ * sin;
            top->zz = tempX * sin + tempZ * cos;

            tempX = top->wx;
            tempZ = top->wz;
            top->wx = tempX * cos - tempZ * sin;
            top->wz = tempX * sin + tempZ * cos;
        }
    } else {
        top = Matrix_now;

        if (y != 0) {
            sin = sin_s(y);
            cos = cos_s(y);
        } else {
            sin = 0.0f;
            cos = 1.0f;
        }

        top->yx = 0.0f;
        top->wx = 0.0f;
        top->xy = 0.0f;
        top->zy = 0.0f;
        top->wy = 0.0f;
        top->yz = 0.0f;
        top->wz = 0.0f;
        top->xw = 0.0f;
        top->yw = 0.0f;
        top->zw = 0.0f;
        top->yy = 1.0f;
        top->ww = 1.0f;
        top->xx = cos;
        top->zz = cos;
        top->zx = -sin;
        top->xz = sin;
    }
}

/**
 * Right-multiply the top matrix on the stack by a rotation about the z axis.
 *
 * - APPLY: top * R -> top
 * - NEW: R -> top
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
    MtxF* top;
    f32 sin;
    f32 cos;
    f32 tempX;
    f32 tempY;
    f32 zero = 0.0;
    f32 one = 1.0;

    if (mode == MTXMODE_APPLY) {
        if (z != 0) {
            top = Matrix_now;

            sin = sin_s(z);
            cos = cos_s(z);

            tempX = top->xx;
            tempY = top->xy;
            top->xx = tempX * cos + tempY * sin;
            top->xy = tempY * cos - tempX * sin;

            tempX = top->yx;
            tempY = top->yy;
            top->yx = tempX * cos + tempY * sin;
            top->yy = tempY * cos - tempX * sin;

            tempX = top->zx;
            tempY = top->zy;
            top->zx = tempX * cos + tempY * sin;
            top->zy = tempY * cos - tempX * sin;

            tempX = top->wx;
            tempY = top->wy;
            top->wx = tempX * cos + tempY * sin;
            top->wy = tempY * cos - tempX * sin;
        }
    } else {
        top = Matrix_now;

        if (z != 0) {
            sin = sin_s(z);
            cos = cos_s(z);
        } else {
            sin = zero;
            cos = one;
        }

        top->zx = zero;
        top->wx = zero;
        top->zy = zero;
        top->wy = zero;
        top->xz = zero;
        top->yz = zero;
        top->wz = zero;
        top->xw = zero;
        top->yw = zero;
        top->zw = zero;
        top->zz = one;
        top->ww = one;
        top->xx = cos;
        top->yy = cos;
        top->yx = sin;
        top->xy = -sin;
    }
}

/**
 * Rotate the top matrix on the stack using ZYX Tait-Bryan angles.
 *
 * - APPLY: top Rz Ry Rx -> top
 * - NEW: Rz Ry Rx -> top
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
    MtxF* top = Matrix_now;
    f32 temp1;
    f32 temp2;
    f32 sin;
    f32 cos;

    if (mode == MTXMODE_APPLY) {
        sin = sin_s(z);
        cos = cos_s(z);

        temp1 = top->xx;
        temp2 = top->xy;
        top->xx = temp1 * cos + temp2 * sin;
        top->xy = temp2 * cos - temp1 * sin;

        temp1 = top->yx;
        temp2 = top->yy;
        top->yx = temp1 * cos + temp2 * sin;
        top->yy = temp2 * cos - temp1 * sin;

        temp1 = top->zx;
        temp2 = top->zy;
        top->zx = temp1 * cos + temp2 * sin;
        top->zy = temp2 * cos - temp1 * sin;

        temp1 = top->wx;
        temp2 = top->wy;
        top->wx = temp1 * cos + temp2 * sin;
        top->wy = temp2 * cos - temp1 * sin;

        if (y != 0) {
            sin = sin_s(y);
            cos = cos_s(y);

            temp1 = top->xx;
            temp2 = top->xz;
            top->xx = temp1 * cos - temp2 * sin;
            top->xz = temp1 * sin + temp2 * cos;

            temp1 = top->yx;
            temp2 = top->yz;
            top->yx = temp1 * cos - temp2 * sin;
            top->yz = temp1 * sin + temp2 * cos;

            temp1 = top->zx;
            temp2 = top->zz;
            top->zx = temp1 * cos - temp2 * sin;
            top->zz = temp1 * sin + temp2 * cos;

            temp1 = top->wx;
            temp2 = top->wz;
            top->wx = temp1 * cos - temp2 * sin;
            top->wz = temp1 * sin + temp2 * cos;
        }

        if (x != 0) {
            sin = sin_s(x);
            cos = cos_s(x);

            temp1 = top->xy;
            temp2 = top->xz;
            top->xy = temp1 * cos + temp2 * sin;
            top->xz = temp2 * cos - temp1 * sin;

            temp1 = top->yy;
            temp2 = top->yz;
            top->yy = temp1 * cos + temp2 * sin;
            top->yz = temp2 * cos - temp1 * sin;

            temp1 = top->zy;
            temp2 = top->zz;
            top->zy = temp1 * cos + temp2 * sin;
            top->zz = temp2 * cos - temp1 * sin;

            temp1 = top->wy;
            temp2 = top->wz;
            top->wy = temp1 * cos + temp2 * sin;
            top->wz = temp2 * cos - temp1 * sin;
        }
    } else {
        Skin_Matrix_SetRotateXyz_s(top, x, y, z);
    }
}
/**
 * Translate and rotate the top matrix on the stack using ZYX Tait-Bryan angles.
 *
 * top T Rz Ry Rx -> top
 *
 * This means a (column) vector is first rotated around X, then around Y, then around Z, then translated, then gets
 * transformed by whatever the matrix was previously.
 *
 * @param translation vector by which to translate.
 * @param rot vector of rotation angles.
 */
void Matrix_softcv3_mult(Vec3f* translation, Vec3s* rot) {
    MtxF* top = Matrix_now;
    f32 sin = sin_s(rot->z);
    f32 cos = cos_s(rot->z);
    f32 temp1;
    f32 temp2;

    // No check for z != 0, presumably since translation is interleaved.
    temp1 = top->xx;
    temp2 = top->xy;
    top->xw += temp1 * translation->x + temp2 * translation->y + top->xz * translation->z;
    top->xx = temp1 * cos + temp2 * sin;
    top->xy = temp2 * cos - temp1 * sin;

    temp1 = top->yx;
    temp2 = top->yy;
    top->yw += temp1 * translation->x + temp2 * translation->y + top->yz * translation->z;
    top->yx = temp1 * cos + temp2 * sin;
    top->yy = temp2 * cos - temp1 * sin;

    temp1 = top->zx;
    temp2 = top->zy;
    top->zw += temp1 * translation->x + temp2 * translation->y + top->zz * translation->z;
    top->zx = temp1 * cos + temp2 * sin;
    top->zy = temp2 * cos - temp1 * sin;

    temp1 = top->wx;
    temp2 = top->wy;
    top->ww += temp1 * translation->x + temp2 * translation->y + top->wz * translation->z;
    top->wx = temp1 * cos + temp2 * sin;
    top->wy = temp2 * cos - temp1 * sin;

    if (rot->y != 0) {
        sin = sin_s(rot->y);
        cos = cos_s(rot->y);

        temp1 = top->xx;
        temp2 = top->xz;
        top->xx = temp1 * cos - temp2 * sin;
        top->xz = temp1 * sin + temp2 * cos;

        temp1 = top->yx;
        temp2 = top->yz;
        top->yx = temp1 * cos - temp2 * sin;
        top->yz = temp1 * sin + temp2 * cos;

        temp1 = top->zx;
        temp2 = top->zz;
        top->zx = temp1 * cos - temp2 * sin;
        top->zz = temp1 * sin + temp2 * cos;

        temp1 = top->wx;
        temp2 = top->wz;
        top->wx = temp1 * cos - temp2 * sin;
        top->wz = temp1 * sin + temp2 * cos;
    }

    if (rot->x != 0) {
        sin = sin_s(rot->x);
        cos = cos_s(rot->x);

        temp1 = top->xy;
        temp2 = top->xz;
        top->xy = temp1 * cos + temp2 * sin;
        top->xz = temp2 * cos - temp1 * sin;

        temp1 = top->yy;
        temp2 = top->yz;
        top->yy = temp1 * cos + temp2 * sin;
        top->yz = temp2 * cos - temp1 * sin;

        temp1 = top->zy;
        temp2 = top->zz;
        top->zy = temp1 * cos + temp2 * sin;
        top->zz = temp2 * cos - temp1 * sin;

        temp1 = top->wy;
        temp2 = top->wz;
        top->wy = temp1 * cos + temp2 * sin;
        top->wz = temp2 * cos - temp1 * sin;
    }
}

/**
 * Set the top matrix on the stack to a general translation and rotation matrix using YXZ Tait-Bryan angles: T Ry Rx Rz
 * -> top
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
    MtxF* top = Matrix_now;
    f32 sinY = sin_s(rot->y);
    f32 cosY = cos_s(rot->y);
    f32 cosTemp;
    f32 sinTemp;

    top->xx = cosY;
    top->zx = -sinY;
    top->xw = x;
    top->yw = y;
    top->zw = z;
    top->wx = 0.0f;
    top->wy = 0.0f;
    top->wz = 0.0f;
    top->ww = 1.0f;

    if (rot->x != 0) {
        sinTemp = sin_s(rot->x);
        cosTemp = cos_s(rot->x);

        top->zz = cosY * cosTemp;
        top->zy = cosY * sinTemp;
        top->xz = sinY * cosTemp;
        top->xy = sinY * sinTemp;
        top->yz = -sinTemp;
        top->yy = cosTemp;
    } else {
        top->zz = cosY;
        top->xz = sinY;
        top->yz = 0.0f;
        top->zy = 0.0f;
        top->xy = 0.0f;
        top->yy = 1.0f;
    }

    if (rot->z != 0) {
        sinTemp = sin_s(rot->z);
        cosTemp = cos_s(rot->z);

        sinY = top->xx;
        cosY = top->xy;
        top->xx = sinY * cosTemp + cosY * sinTemp;
        top->xy = cosY * cosTemp - sinY * sinTemp;

        sinY = top->zx;
        cosY = top->zy;
        top->zx = sinY * cosTemp + cosY * sinTemp;
        top->zy = cosY * cosTemp - sinY * sinTemp;

        cosY = top->yy;
        top->yx = cosY * sinTemp;
        top->yy = cosY * cosTemp;
    } else {
        top->yx = 0.0f;
    }
}

/**
 * Converts a floating-point MtxF to a fixed-point RSP-compatible matrix.
 *
 * Fixed-point numbers are split into an integer and a fractional scaling factor. For optimization reasons, the
 * RSP matrix format groups all the integer parts together into the first 8 words, and the fractional parts into the
 * last 8 words.
 *
 * @param[in] src MtxF to convert.
 * @param[out] dest mtx to output to.
 *
 * @return dest
 */
Mtx* _MtxF_to_Mtx(MtxF* src, Mtx* dest) {
    s32 fp;
    u16* intPart = (u16*)&dest->m[0][0];
    u16* fracPart = (u16*)&dest->m[2][0];

    fp = src->xx * 0x10000;
    intPart[0] = (fp >> 0x10);
    fracPart[0] = fp & 0xFFFF;

    fp = src->yx * 0x10000;
    intPart[1] = (fp >> 0x10);
    fracPart[1] = fp & 0xFFFF;

    fp = src->zx * 0x10000;
    intPart[2] = (fp >> 0x10);
    fracPart[2] = fp & 0xFFFF;

    fp = src->wx * 0x10000;
    intPart[3] = (fp >> 0x10);
    fracPart[3] = fp & 0xFFFF;

    fp = src->xy * 0x10000;
    intPart[4] = (fp >> 0x10);
    fracPart[4] = fp & 0xFFFF;

    fp = src->yy * 0x10000;
    intPart[5] = (fp >> 0x10);
    fracPart[5] = fp & 0xFFFF;

    // Ideally these three would use fracPart instead of intPart, but it's required to match.
    fp = src->zy * 0x10000;
    intPart[6] = (fp >> 0x10);
    intPart[22] = fp & 0xFFFF;

    fp = src->wy * 0x10000;
    intPart[7] = (fp >> 0x10);
    intPart[23] = fp & 0xFFFF;

    fp = src->xz * 0x10000;
    intPart[8] = (fp >> 0x10);
    intPart[24] = fp & 0xFFFF;

    fp = src->yz * 0x10000;
    intPart[9] = (fp >> 0x10);
    fracPart[9] = fp & 0xFFFF;

    fp = src->zz * 0x10000;
    intPart[10] = (fp >> 0x10);
    fracPart[10] = fp & 0xFFFF;

    fp = src->wz * 0x10000;
    intPart[11] = (fp >> 0x10);
    fracPart[11] = fp & 0xFFFF;

    fp = src->xw * 0x10000;
    intPart[12] = (fp >> 0x10);
    fracPart[12] = fp & 0xFFFF;

    fp = src->yw * 0x10000;
    intPart[13] = (fp >> 0x10);
    fracPart[13] = fp & 0xFFFF;

    fp = src->zw * 0x10000;
    intPart[14] = (fp >> 0x10);
    fracPart[14] = fp & 0xFFFF;

    fp = src->ww * 0x10000;
    intPart[15] = (fp >> 0x10);
    fracPart[15] = fp & 0xFFFF;
    return dest;
}

/**
 * Converts the top matrix on the stack to a fixed-point RSP-compatible matrix.
 *
 * @param[out] dest mtx to output to.
 *
 * @return dest
 */
Mtx* _Matrix_to_Mtx(Mtx* dest) {
    return _MtxF_to_Mtx(Matrix_now, dest);
}

/**
 * Converts the top matrix on the stack to a RSP-compatible matrix and saves it to allocated space in the OPA buffer.
 *
 * @param[in,out] gfxCtx Graphics context.
 *
 * @return allocated mtx.
 */
Mtx* _Matrix_to_Mtx_new(GraphicsContext* gfxCtx) {
    return _Matrix_to_Mtx(GRAPH_ALLOC(gfxCtx, sizeof(Mtx)));
}

/**
 * Converts src to a RSP-compatible matrix and saves it to allocated space in the OPA buffer.
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
 * Calculates top * (src,1) and writes its components to dest.
 *
 * This assumes that the top matrix on the stack has the form
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
    MtxF* top = Matrix_now;

    dest->x = top->xw + (top->xx * src->x + top->xy * src->y + top->xz * src->z);
    dest->y = top->yw + (top->yx * src->x + top->yy * src->y + top->yz * src->z);
    dest->z = top->zw + (top->zx * src->x + top->zy * src->y + top->zz * src->z);
}

/**
 * Multiply the vector `(0, 0, 0, 1)` by the top matrix on the stack.
 *
 * Can also see it as obtaining the translation vector part of the top matrix, but the former interpretation is
 * consistent with the other functions nearby.
 *
 * @note Special case of Matrix_Position() with `src = { 0, 0, 0 }`; the same assumptions apply.
 *
 * @param[out] dest output vector.
 */
void Matrix_Position_Zero(Vec3f* dest) {
    MtxF* top = Matrix_now;

    dest->x = top->xw;
    dest->y = top->yw;
    dest->z = top->zw;
}

/**
 * Multiply the vector `(x, 0, 0, 1)` by the top matrix on the stack.
 *
 * I.e. calculate \f$ A(x, 0, 0) + b \f$.
 *
 * @note Special case of Matrix_Position() with `src = { x, 0, 0 }`; the same assumptions apply.
 *
 * @param[in] x multiplier of unit vector in x direction.
 * @param[out] dest output vector.
 */
void Matrix_Position_VecX(f32 x, Vec3f* dest) {
    MtxF* top = Matrix_now;

    dest->x = top->xw + top->xx * x;
    dest->y = top->yw + top->yx * x;
    dest->z = top->zw + top->zx * x;
}

/**
 * Multiply the vector `(0, y, 0, 1)` by the top matrix on the stack.
 *
 * I.e. calculate \f$ A(0, y, 0) + b \f$.
 *
 * @note Special case of Matrix_Position() with `src = { 0, y, 0 }`; the same assumptions apply.
 *
 * @param[in] y multiplier of unit vector in y direction.
 * @param[out] dest output vector.
 */
void Matrix_Position_VecY(f32 y, Vec3f* dest) {
    MtxF* top = Matrix_now;

    dest->x = top->xw + top->xy * y;
    dest->y = top->yw + top->yy * y;
    dest->z = top->zw + top->zy * y;
}

/**
 * Multiply the vector `(0, 0, z, 1)` by the top matrix on the stack.
 *
 * I.e. calculate \f$ A(0, 0, z) + b \f$.
 *
 * @note Special case of Matrix_Position() with `src = { 0, 0, z }`; the same assumptions apply.
 *
 * @param[in] z multiplier of unit vector in z direction.
 * @param[out] dest output vector.
 */
void Matrix_Position_VecZ(f32 z, Vec3f* dest) {
    MtxF* top = Matrix_now;

    dest->x = top->xw + top->xz * z;
    dest->y = top->yw + top->yz * z;
    dest->z = top->zw + top->zz * z;
}

/**
 * Copies the matrix src into dest.
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
 * Converts a fixed-point RSP-compatible matrix to an MtxF.
 *
 * @see _MtxF_to_Mtx
 *
 * @param[in] src mtx to convert
 * @param[out] dest MtxF to output to
 */
void Matrix_MtxtoMtxF(Mtx* src, MtxF* dest) {
    u16* intPart = (u16*)&src->m[0][0];
    u16* fracPart = (u16*)&src->m[2][0];

    dest->xx = ((intPart[0] << 0x10) | fracPart[0]) * (1 / (f32)0x10000);
    dest->yx = ((intPart[1] << 0x10) | fracPart[1]) * (1 / (f32)0x10000);
    dest->zx = ((intPart[2] << 0x10) | fracPart[2]) * (1 / (f32)0x10000);
    dest->wx = ((intPart[3] << 0x10) | fracPart[3]) * (1 / (f32)0x10000);
    dest->xy = ((intPart[4] << 0x10) | fracPart[4]) * (1 / (f32)0x10000);
    dest->yy = ((intPart[5] << 0x10) | fracPart[5]) * (1 / (f32)0x10000);
    dest->zy = ((intPart[6] << 0x10) | fracPart[6]) * (1 / (f32)0x10000);
    dest->wy = ((intPart[7] << 0x10) | fracPart[7]) * (1 / (f32)0x10000);
    dest->xz = ((intPart[8] << 0x10) | fracPart[8]) * (1 / (f32)0x10000);
    dest->yz = ((intPart[9] << 0x10) | fracPart[9]) * (1 / (f32)0x10000);
    dest->zz = ((intPart[10] << 0x10) | fracPart[10]) * (1 / (f32)0x10000);
    dest->wz = ((intPart[11] << 0x10) | fracPart[11]) * (1 / (f32)0x10000);
    dest->xw = ((intPart[12] << 0x10) | fracPart[12]) * (1 / (f32)0x10000);
    dest->yw = ((intPart[13] << 0x10) | fracPart[13]) * (1 / (f32)0x10000);
    dest->zw = ((intPart[14] << 0x10) | fracPart[14]) * (1 / (f32)0x10000);
    dest->ww = ((intPart[15] << 0x10) | fracPart[15]) * (1 / (f32)0x10000);
}

/**
 * Calculates mf * (src,1) and writes its components to dest.
 *
 * This is the same as Matrix_Position() but using a specified matrix rather than the top matrix; the same
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
 * Overwrite the linear part of a matrix with its transpose (ignores the translational part).
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
 * Decompose the linear part A of the top matrix on the stack into B * S, where B has normalised columns and S is
 * diagonal, and replace B by `mf`.
 *
 * Since B is typically a rotation matrix, and the linear part R * S to `mf` * S, this operation can be
 * seen as replacing the B rotation with `mf`, hence the function name.
 *
 * @param[in] mf matrix whose linear part will replace the normalised part of A.
 */
void Matrix_rotate_scale_exchange(MtxF* mf) {
    MtxF* top = Matrix_now;
    f32 acc;
    f32 component;
    f32 curColNorm;

    // compute the Euclidean norm of the first column of the top matrix
    acc = top->xx;
    acc *= acc;
    component = top->yx;
    acc += SQ(component);
    component = top->zx;
    acc += SQ(component);
    curColNorm = sqrtf(acc);

    top->xx = mf->xx * curColNorm;
    top->yx = mf->yx * curColNorm;
    top->zx = mf->zx * curColNorm;

    // second column
    acc = top->xy;
    acc *= acc;
    component = top->yy;
    acc += SQ(component);
    component = top->zy;
    acc += SQ(component);
    curColNorm = sqrtf(acc);

    top->xy = mf->xy * curColNorm;
    top->yy = mf->yy * curColNorm;
    top->zy = mf->zy * curColNorm;

    // third column
    acc = top->xz;
    acc *= acc;
    component = top->yz;
    acc += SQ(component);
    component = top->zz;
    acc += SQ(component);
    curColNorm = sqrtf(acc);

    top->xz = mf->xz * curColNorm;
    top->yz = mf->yz * curColNorm;
    top->zz = mf->zz * curColNorm;
}

/**
 * Extract the YXZ Tait-Bryan rotation angles from the linear part \f$ A \f$ of a matrix.
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

    temp = src->xz;
    temp *= temp;
    temp += SQ(src->zz);
    dest->x = RAD_TO_BINANG(fatan2(-src->yz, sqrtf(temp)));

    if ((dest->x == 0x4000) || (dest->x == -0x4000)) {
        // cos(x) = 0 if either of these is true, and we get gimbal locking
        // (https://en.wikipedia.org/wiki/Gimbal_lock#Loss_of_a_degree_of_freedom_with_Euler_angles); fix z to make y
        // well-defined.
        dest->z = 0;

        dest->y = RAD_TO_BINANG(fatan2(-src->zx, src->xx));
    } else {
        dest->y = RAD_TO_BINANG(fatan2(src->xz, src->zz));

        if (!nonUniformScale) {
            // assume the columns have the same normalisation
            dest->z = RAD_TO_BINANG(fatan2(src->yx, src->yy));
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
            dest->z = RAD_TO_BINANG(fatan2(temp, temp2));
        }
    }
}

/**
 * Extract the ZYX Tait-Bryan rotation angles from the linear part \f$ A \f$ of a matrix.
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

    temp = src->xx;
    temp *= temp;
    temp += SQ(src->yx);
    dest->y = RAD_TO_BINANG(fatan2(-src->zx, sqrtf(temp)));

    if ((dest->y == 0x4000) || (dest->y == -0x4000)) {
        dest->x = 0;
        dest->z = RAD_TO_BINANG(fatan2(-src->xy, src->yy));
    } else {
        dest->z = RAD_TO_BINANG(fatan2(src->yx, src->xx));

        if (!nonUniformScale) {
            dest->x = RAD_TO_BINANG(fatan2(src->zy, src->zz));
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

            dest->x = RAD_TO_BINANG(fatan2(temp, temp2));
        }
    }
}

/**
 * Rotate the top matrix on the stack by binary angle `angle` about `axis`, which is assumed to be a unit vector.
 *
 * @param angle rotation angle (binary).
 * @param axis axis about which to rotate, must be a unit vector.
 * @param mode APPLY or NEW.
 */
void Matrix_RotateVector(s16 angle, Vec3f* axis, u8 mode) {
    MtxF* top;
    f32 sin;
    f32 cos;
    f32 versin;
    f32 temp1;
    f32 temp2;
    f32 temp3;
    f32 temp4;

    if (mode == 1) {
        if (angle != 0) {
            top = Matrix_now;

            sin = sin_s(angle);
            cos = cos_s(angle);
            temp1 = top->xx;
            temp2 = top->xy;
            temp3 = top->xz;
            temp4 = (axis->x * temp1 + axis->y * temp2 + axis->z * temp3) * (1.0f - cos);
            top->xx = temp1 * cos + axis->x * temp4 + sin * (temp2 * axis->z - temp3 * axis->y);
            top->xy = temp2 * cos + axis->y * temp4 + sin * (temp3 * axis->x - temp1 * axis->z);
            top->xz = temp3 * cos + axis->z * temp4 + sin * (temp1 * axis->y - temp2 * axis->x);

            temp1 = top->yx;
            temp2 = top->yy;
            temp3 = top->yz;
            temp4 = (axis->x * temp1 + axis->y * temp2 + axis->z * temp3) * (1.0f - cos);
            top->yx = temp1 * cos + axis->x * temp4 + sin * (temp2 * axis->z - temp3 * axis->y);
            top->yy = temp2 * cos + axis->y * temp4 + sin * (temp3 * axis->x - temp1 * axis->z);
            top->yz = temp3 * cos + axis->z * temp4 + sin * (temp1 * axis->y - temp2 * axis->x);

            temp1 = top->zx;
            temp2 = top->zy;
            temp3 = top->zz;
            temp4 = (axis->x * temp1 + axis->y * temp2 + axis->z * temp3) * (1.0f - cos);
            top->zx = temp1 * cos + axis->x * temp4 + sin * (temp2 * axis->z - temp3 * axis->y);
            top->zy = temp2 * cos + axis->y * temp4 + sin * (temp3 * axis->x - temp1 * axis->z);
            top->zz = temp3 * cos + axis->z * temp4 + sin * (temp1 * axis->y - temp2 * axis->x);
        }
    } else {
        top = Matrix_now;

        if (angle != 0) {
            sin = sin_s(angle);
            cos = cos_s(angle);
            versin = 1.0f - cos;

            top->xx = axis->x * axis->x * versin + cos;
            top->yy = axis->y * axis->y * versin + cos;
            top->zz = axis->z * axis->z * versin + cos;

            if (0) {}

            temp2 = axis->x * versin * axis->y;
            temp3 = axis->z * sin;
            top->yx = temp2 + temp3;
            top->xy = temp2 - temp3;

            temp2 = axis->x * versin * axis->z;
            temp3 = axis->y * sin;
            top->zx = temp2 - temp3;
            top->xz = temp2 + temp3;

            temp2 = axis->y * versin * axis->z;
            temp3 = axis->x * sin;
            top->zy = temp2 + temp3;
            top->yz = temp2 - temp3;

            top->wx = 0.0f;
            top->wy = 0.0f;
            top->wz = 0.0f;
            top->xw = 0.0f;
            top->yw = 0.0f;
            top->zw = 0.0f;
            top->ww = 1.0f;
        } else {
            top->yx = 0.0f;
            top->zx = 0.0f;
            top->wx = 0.0f;
            top->xy = 0.0f;
            top->zy = 0.0f;
            top->wy = 0.0f;
            top->xz = 0.0f;
            top->yz = 0.0f;
            top->wz = 0.0f;
            top->xw = 0.0f;
            top->yw = 0.0f;
            top->zw = 0.0f;
            top->xx = 1.0f;
            top->yy = 1.0f;
            top->zz = 1.0f;
            top->ww = 1.0f;
        }
    }
}

/**
 * Writes a combined translation and scale matrix to a fixed-point RSP-compatible matrix.
 *
 * @see _MtxF_to_Mtx
 *
 * @param mtx: output matrix.
 * @param scaleX: amount to scale in X direction.
 * @param scaleY: amount to scale in Y direction.
 * @param scaleZ: amount to scale in Z direction.
 * @param translateX: amount to translate in X direction.
 * @param translateY: amount to translate in Y direction.
 * @param translateZ: amount to translate in Z direction.
 */
void suMtxMakeTS(Mtx* mtx, f32 scaleX, f32 scaleY, f32 scaleZ, f32 translateX, f32 translateY, f32 translateZ) {
    struct {
        s16 intPart[4][4];
        u16 fracPart[4][4];
    }* mu = (void*)mtx;
    s32 fp;

    fp = scaleX * 0x10000;
    mtx->m[0][0] = fp;            // intpart xx = scaleX. This overwrites xy
    mu->intPart[0][1] = 0;        // intpart xy = 0. Sets xy back to 0
    mtx->m[0][1] = 0;             // intpart xz, xw = 0
    mtx->m[2][0] = (u32)fp << 16; // fracpart xx = scaleX
    mtx->m[2][1] = 0;             // fracpart xy = 0

    fp = scaleY * 0x10000;
    mtx->m[0][2] = (u32)fp >> 16; // intpart yy = scaleY
    mtx->m[0][3] = 0;             // intpart yz = 0
    mtx->m[2][2] = fp & 0xFFFF;   // fracpart yy = scaleY
    mtx->m[2][3] = 0;             // fracpart yz = 0

    fp = scaleZ * 0x10000;
    mtx->m[1][0] = 0;             // intpart zx, zy = 0
    mtx->m[1][1] = fp;            // intpart zz = scaleZ
    mu->intPart[2][3] = 0;        // intpart zw = 0
    mtx->m[3][0] = 0;             // fracpart zx, zy = 0
    mtx->m[3][1] = (u32)fp << 16; // fracpart zz = scaleZ

    // wx = translateX
    fp = translateX * 0x10000;
    mu->intPart[3][0] = ((u32)fp >> 16) & 0xFFFF;
    mu->fracPart[3][0] = fp & 0xFFFF;

    // wy = translateY
    fp = translateY * 0x10000;
    mu->intPart[3][1] = ((u32)fp >> 16) & 0xFFFF;
    mu->fracPart[3][1] = fp & 0xFFFF;

    // wz = translateZ
    fp = translateZ * 0x10000;
    mu->intPart[3][2] = ((u32)fp >> 16) & 0xFFFF;
    // ww = 1
    mu->intPart[3][3] = 1;
    mtx->m[3][3] = (u32)fp << 16;
}

/**
 * Writes a combined scale, rotation (x, y, z), and translation matrix to a fixed-point RSP-compatible matrix.
 *
 * @see _MtxF_to_Mtx
 *
 * @param mtx: output matrix.
 * @param scaleX: amount to scale in X direction.
 * @param scaleY: amount to scale in Y direction.
 * @param scaleZ: amount to scale in Z direction.
 * @param rotX: binary angle to rotate about X axis.
 * @param rotY: binary angle to rotate about Y axis.
 * @param rotZ: binary angle to rotate about Z axis.
 * @param translateX: amount to translate in X direction.
 * @param translateY: amount to translate in Y direction.
 * @param translateZ: amount to translate in Z direction.
 */
void suMtxMakeSRT(Mtx* mtx, f32 scaleX, f32 scaleY, f32 scaleZ, s16 rotX, s16 rotY, s16 rotZ, f32 translateX,
                  f32 translateY, f32 translateZ) {
    struct {
        s16 intPart[4][4];
        u16 fracPart[4][4];
    }* mu = (void*)mtx;
    s32 fp;
    f32 sinX = sin_s(rotX);
    f32 sinY = sin_s(rotY);
    f32 sinZ = sin_s(rotZ);
    f32 cosX = cos_s(rotX);
    f32 cosY = cos_s(rotY);
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

/**
 * Writes a combined scale, rotation (z, x, y), and translation matrix to a fixed-point RSP-compatible matrix.
 *
 * @see _MtxF_to_Mtx
 *
 * @param mtx: output matrix.
 * @param scaleX: amount to scale in X direction.
 * @param scaleY: amount to scale in Y direction.
 * @param scaleZ: amount to scale in Z direction.
 * @param rotX: binary angle to rotate about X axis.
 * @param rotY: binary angle to rotate about Y axis.
 * @param rotZ: binary angle to rotate about Z axis.
 * @param translateX: amount to translate in X direction.
 * @param translateY: amount to translate in Y direction.
 * @param translateZ: amount to translate in Z direction.
 */
void suMtxMakeSRT_ZXY(Mtx* mtx, f32 scaleX, f32 scaleY, f32 scaleZ, s16 rotX, s16 rotY, s16 rotZ, f32 translateX,
                      f32 translateY, f32 translateZ) {
    struct {
        s16 intPart[4][4];
        u16 fracPart[4][4];
    }* mu = (void*)mtx;
    s32 fp;
    f32 sinX = sin_s(rotX);
    f32 sinY = sin_s(rotY);
    f32 sinZ = sin_s(rotZ);
    f32 cosX = cos_s(rotX);
    f32 cosY = cos_s(rotY);
    f32 cosZ = cos_s(rotZ);

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
