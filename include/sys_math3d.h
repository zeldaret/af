#ifndef SYS_MATH_3D_H
#define SYS_MATH_3D_H

#include "ultra64.h"
#include "z64math.h"
#include "unk.h"

typedef struct Sphere {
    /* 0x0 */ s_xyz center;
    /* 0x6 */ s16 radius;
} Sphere; // size = 0x6

typedef struct Triangle {
    /* 0x00 */ xyz_t vertices[3];
} Triangle; // size = 0x24

typedef struct Triangle3 {
    /* 0x00 */ Triangle unk_00;
    /* 0x24 */ xyz_t unk_24;
    /* 0x30 */ f32 unk_30;
} Triangle3; // size = 0x34

typedef struct Pipe {
    /* 0x0 */ s16 radius;
    /* 0x2 */ s16 unk_2;
    /* 0x4 */ s16 yShift;
    /* 0x6 */ s_xyz pos;
} Pipe; // size = 0xC

// void Math3d_normalizeXyz_t();
// void func_800DA028_jp();
// void func_800DA148_jp();
// void Math3D_lineVsPosSuisenCross();
// void func_800DA4E0_jp();
// void func_800DA540_jp();
// void func_800DA720_jp();
// void Math3DInDivPos1();
// void Math3DInDivPos2();
// void M3D_getCos();
// void M3D_getCos2();
// void M3D_getRefVec();
// void func_800DA9E4_jp();
// void func_800DAA48_jp();
// void Math3DCheck3PointMinMaxAreaInside3D();
// void func_800DADAC_jp();
// void func_800DADC4_jp();
// void func_800DADE8_jp();
// void func_800DAE2C_jp();
// void func_800DAE5C_jp();
// void func_800DAE88_jp();
// void func_800DAEB0_jp();
// void Math3DLength();
// void func_800DAEF8_jp();
// void func_800DAF70_jp();
// void func_800DAFB0_jp();
// void func_800DAFF0_jp();
// void Math3DVectorProduct2Vec();
// void Math3DVectorProductXYZ();
// void func_800DB10C_jp();
// void func_800DB1B8_jp();
// void func_800DB368_jp();
// void func_800DB4E4_jp();
// void func_800DBF5C_jp();
// void func_800DC0C8_jp();
void Math3DPlane(xyz_t* arg0, xyz_t* arg1, xyz_t* arg2, f32* arg3, f32* arg4, f32* arg5, f32* arg6);
// void func_800DC268_jp();
// void func_800DC2A8_jp();
// void Math3DLengthPlaneAndPos();
// void func_800DC31C_jp();
// void func_800DC3A0_jp();
// void func_800DC6BC_jp();
// void func_800DC704_jp();
// void func_800DC754_jp();
// void func_800DC804_jp();
// void func_800DC8B0_jp();
// void func_800DC92C_jp();
// void func_800DCAA0_jp();
// void func_800DCB14_jp();
// void func_800DCE30_jp();
// void func_800DCE78_jp();
// void func_800DCF2C_jp();
// void func_800DCFA8_jp();
// void func_800DD130_jp();
// void func_800DD1A4_jp();
// void func_800DD4EC_jp();
// void func_800DD534_jp();
// void func_800DD5E8_jp();
// void func_800DD664_jp();
// void func_800DD7F0_jp();
// void func_800DD864_jp();
// void func_800DD940_jp();
// void func_800DDA48_jp();
// void func_800DDBAC_jp();
// void func_800DDC5C_jp();
// void func_800DDCAC_jp();
// void Math3D_sphereCrossLineSegment();
// void Math3D_sphereCrossTriangleCalc_cp();
s32 Math3D_sphereCrossTriangle3_cp(Sphere* sphere, Triangle3* triangle3, xyz_t* arg2);
// void func_800DE55C_jp();
// void func_800DE618_jp();
s32 Math3D_pipeCrossTriangle_cp(Pipe* pipe, Triangle* arg1, xyz_t* arg2);
// void func_800DF46C_jp();
// void func_800DF48C_jp();
s32 Math3D_sphereCrossSphere_cl(Sphere* sphere1, Sphere* sphere2, f32* arg2);
// void func_800DF4CC_jp();
s32 Math3D_sphereVsPipe_cl(Sphere* sphere, Pipe* pipe, f32* arg2);
// void func_800DF5C4_jp();
s32 Math3D_pipeVsPipe_cl(Pipe* pipe1, Pipe* pipe2, f32* arg2);
// void Math3D_pipeVsPipe_cl_cc();
// void func_800DF924_jp();
// void func_800DFCA4_jp();
// void func_800DFD10_jp();
// void func_800DFD7C_jp();
// void sMath_RotateY();
// void sMath_RotateX();
// void sMath_RotateZ();

extern xyz_t ZeroVec;

#endif
