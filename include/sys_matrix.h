#ifndef SYS_MATRIX_H
#define SYS_MATRIX_H

#include "ultra64.h"
#include "game.h"
#include "z64math.h"

typedef enum {
    /* 0 */ MTXMODE_NEW,  // generates a new matrix
    /* 1 */ MTXMODE_APPLY // applies transformation to the current matrix
} MatrixMode;

void new_Matrix(GameState* gameState);
void Matrix_push(void);
void Matrix_pull(void);
void Matrix_get(MtxF* dest);
void Matrix_put(MtxF* src);
MtxF* get_Matrix_now(void);
void Matrix_mult(MtxF* mf, u8 mode);
void Matrix_translate(f32 x, f32 y, f32 z, u8 mode);
void Matrix_scale(f32 x, f32 y, f32 z, u8 mode);
void Matrix_RotateX(s16 x, MatrixMode mode);
void Matrix_RotateY(s16 y, MatrixMode mode);
void Matrix_RotateZ(s16 z, MatrixMode mode);
void Matrix_rotateXYZ(s16 x, s16 y, s16 z, MatrixMode mode);
void Matrix_softcv3_mult(Vec3f* translation, Vec3s* rot);
void Matrix_softcv3_load(f32 x, f32 y, f32 z, Vec3s* rot);
Mtx* _MtxF_to_Mtx(MtxF* src, Mtx* dest);
Mtx* _Matrix_to_Mtx(Mtx* dest);
Mtx* _Matrix_to_Mtx_new(GraphicsContext* gfxCtx);
void _MtxF_to_Mtx_new(MtxF* src, GraphicsContext* gfxCtx);
void Matrix_Position(Vec3f* src, Vec3f* dest);
void Matrix_Position_Zero(Vec3f* dest);
void Matrix_Position_VecX(f32 x, Vec3f* dest);
void Matrix_Position_VecY(f32 y, Vec3f* dest);
void Matrix_Position_VecZ(f32 z, Vec3f* dest);
void Matrix_copy_MtxF(MtxF* dest, MtxF* src);
// void Matrix_MtxtoMtxF();
// void Matrix_MtxF_Position2();
// void Matrix_reverse();
// void Matrix_rotate_scale_exchange();
// void Matrix_to_rotate_new();
// void Matrix_to_rotate2_new();
// void Matrix_RotateVector();
// void suMtxMakeTS();
// void suMtxMakeSRT();
// void suMtxMakeSRT_ZXY();

void SkinMatrix_MtxFMtxFMult(MtxF* mfB, MtxF* mfA, MtxF* dest); /* extern */
void Skin_Matrix_SetTranslate(MtxF* mf, f32 x, f32 y, f32 z);   /* extern */
void Skin_Matrix_SetScale(MtxF* mf, f32 x, f32 y, f32 z);       /* extern */
f32 cos_s(s16 angle);                                           /* extern */
f32 sin_s(s16 angle);                                           /* extern */
s16 Math_FAtan2F(f32 y, f32 x);

#endif
