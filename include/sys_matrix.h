#ifndef SYS_MATRIX_H
#define SYS_MATRIX_H

#include "ultra64.h"
#include "z64math.h"

struct GraphicsContext;
struct Game;

typedef enum {
    /* 0 */ MTXMODE_NEW,  // generates a new matrix
    /* 1 */ MTXMODE_APPLY // applies transformation to the current matrix
} MatrixMode;

void new_Matrix(struct Game* game);
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
void Matrix_softcv3_mult(xyz_t* translation, s_xyz* rot);
void Matrix_softcv3_load(f32 x, f32 y, f32 z, s_xyz* rot);
Mtx* _MtxF_to_Mtx(MtxF* src, Mtx* dest);
Mtx* _Matrix_to_Mtx(Mtx* dest);
Mtx* _Matrix_to_Mtx_new(struct GraphicsContext* gfxCtx);
void _MtxF_to_Mtx_new(MtxF* src, struct GraphicsContext* gfxCtx);
void Matrix_Position(xyz_t* src, xyz_t* dest);
void Matrix_Position_Zero(xyz_t* dest);
void Matrix_Position_VecX(f32 x, xyz_t* dest);
void Matrix_Position_VecY(f32 y, xyz_t* dest);
void Matrix_Position_VecZ(f32 z, xyz_t* dest);
void Matrix_copy_MtxF(MtxF* dest, MtxF* src);
void Matrix_MtxtoMtxF(Mtx* src, MtxF* dest);
void Matrix_MtxF_Position2(xyz_t* src, xyz_t* dest, MtxF* mf);
void Matrix_reverse(MtxF* mf);
void Matrix_rotate_scale_exchange(MtxF* mf);
void Matrix_to_rotate_new(MtxF* src, s_xyz* dest, s32 nonUniformScale);
void Matrix_to_rotate2_new(MtxF* src, s_xyz* dest, s32 nonUniformScale);
void Matrix_RotateVector(s16 angle, xyz_t* axis, u8 mode);
void suMtxMakeTS(Mtx* mtx, f32 scaleX, f32 scaleY, f32 scaleZ, f32 translateX, f32 translateY, f32 translateZ);
void suMtxMakeSRT(Mtx* mtx, f32 scaleX, f32 scaleY, f32 scaleZ, s16 rotX, s16 rotY, s16 rotZ, f32 translateX,
                  f32 translateY, f32 translateZ);
void suMtxMakeSRT_ZXY(Mtx* mtx, f32 scaleX, f32 scaleY, f32 scaleZ, s16 rotX, s16 rotY, s16 rotZ, f32 translateX,
                      f32 translateY, f32 translateZ);

extern Mtx Mtx_clear;

#endif
