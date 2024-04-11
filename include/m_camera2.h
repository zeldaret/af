#ifndef M_CAMERA_H
#define M_CAMERA_H

// these two angle conversion macros are slightly inaccurate
#define CAM_DEG_TO_BINANG(degrees) (s16)((degrees) * ((f32)0xFFFF / 360) + .5f)
#define CAM_BINANG_TO_DEG(binang) ((f32)(binang) * (360.0001525f / 0xFFFF))

#endif
