#ifndef M_SKIN_MATRIX_H
#define M_SKIN_MATRIX_H

#include "ultra64.h"
#include "z64math.h"

struct GraphicsContext;

void Skin_Matrix_PrjMulVector(MtxF* mf, xyz_t* src, xyz_t* xyzDest, f32* wDest);
void Skin_Matrix_MulVector(MtxF* mf, xyz_t* src, xyz_t* dest);
void Skin_Matrix_MulMatrix(MtxF* mfA, MtxF* mfB, MtxF* dest);
void Skin_Matrix_getUnitMatrixPointer(MtxF** mtxP);
void Skin_Matrix_SetUnitMatrix(MtxF* mf);
void Skin_Matrix_Copy(MtxF* src, MtxF* dest);
s32 Skin_Matrix_InverseMatrix(MtxF* src, MtxF* dest);
void Skin_Matrix_SetScale(MtxF* mf, f32 x, f32 y, f32 z);
void Skin_Matrix_SetRotateXyz_s(MtxF* mf, s16 x, s16 y, s16 z);
void Skin_Matrix_SetRotateZxy_s(MtxF* mf, s16 x, s16 y, s16 z);
void Skin_Matrix_SetTranslate(MtxF* mf, f32 x, f32 y, f32 z);
void Skin_Matrix_SetSrtMatrix(MtxF* dest, f32 scaleX, f32 scaleY, f32 scaleZ, s16 rotX, s16 rotY, s16 rotZ,
                              f32 translateX, f32 translateY, f32 translateZ);
void Skin_Matrix_SetSRzxyTMatrix(MtxF* dest, f32 scaleX, f32 scaleY, f32 scaleZ, s16 rotX, s16 rotY, s16 rotZ,
                                 f32 translateX, f32 translateY, f32 translateZ);
void Skin_Matrix_SetRtMatrix(MtxF* dest, s16 rotX, s16 rotY, s16 rotZ, f32 translateX, f32 translateY, f32 translateZ);
void Skin_Matrix_vec2svec(xyz_t* src, s_xyz* dest);
void Skin_Matrix_svec2vec(s_xyz* src, xyz_t* dest);
void Skin_Matrix_to_Mtx(MtxF* src, Mtx* dest);
Mtx* Skin_Matrix_to_Mtx_new(struct GraphicsContext* gfxctx, MtxF* src);
void Skin_Matrix_SetFreeVecRotMatrix(MtxF* mf, s16 angle, f32 axisX, f32 axisY, f32 axisZ);
void Skin_Matrix_SetQuaternion(MtxF* mf, f32* q);
void Skin_Matrix_setRotateX(MtxF* mf, s16 x);
void Skin_Matrix_mulRotateX(MtxF* cmf, s16 x);
void Skin_Matrix_setRotateY(MtxF* mf, s16 y);
void Skin_Matrix_mulRotateY(MtxF* cmf, s16 y);
void Skin_Matrix_setRotateZ(MtxF* mf, s16 z);
void Skin_Matrix_mulRotateZ(MtxF* cmf, s16 z);


#endif
