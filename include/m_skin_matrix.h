#ifndef M_SKIN_MATRIX_H
#define M_SKIN_MATRIX_H

#include "ultra64.h"
#include "z64math.h"

void Skin_Matrix_PrjMulVector(MtxF* mf, Vec3f* src, Vec3f* xyzDest, f32* wDest);
// void Skin_Matrix_MulVector();
void Skin_Matrix_MulMatrix(MtxF* mfB, MtxF* mfA, MtxF* dest);
// void Skin_Matrix_getUnitMatrixPointer();
// void Skin_Matrix_SetUnitMatrix();
// void Skin_Matrix_Copy();
// void Skin_Matrix_InverseMatrix();
void Skin_Matrix_SetScale(MtxF* mf, f32 x, f32 y, f32 z);
void Skin_Matrix_SetRotateXyz_s(MtxF* mf, s16 roll, s16 pitch, s16 yaw);
// void Skin_Matrix_SetRotateZxy_s();
void Skin_Matrix_SetTranslate(MtxF* mf, f32 x, f32 y, f32 z);
// void Skin_Matrix_SetSrtMatrix();
// void Skin_Matrix_SetSRzxyTMatrix();
// void Skin_Matrix_SetRtMatrix();
// void Skin_Matrix_vec2svec();
// void Skin_Matrix_svec2vec();
// void Skin_Matrix_to_Mtx();
// void Skin_Matrix_to_Mtx_new();
// void Skin_Matrix_SetFreeVecRotMatrix();
// void Skin_Matrix_SetQuaternion();
// void Skin_Matrix_setRotateX();
// void Skin_Matrix_mulRotateX();
// void Skin_Matrix_setRotateY();
// void Skin_Matrix_mulRotateY();
// void Skin_Matrix_setRotateZ();
// void Skin_Matrix_mulRotateZ();

#endif
