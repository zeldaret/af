#ifndef M_LIGHTS_H
#define M_LIGHTS_H

#include "ultra64.h"
#include "color.h"

struct GraphicsContext;

typedef struct {
    /* 0x0 */ s16 x;
    /* 0x2 */ s16 y;
    /* 0x4 */ s16 z;
    /* 0x6 */ u8 color[3];
    /* 0x9 */ u8 drawGlow;
    /* 0xA */ s16 radius;
} LightPoint; // size = 0xC

typedef struct {
    /* 0x0 */ s8 x;
    /* 0x1 */ s8 y;
    /* 0x2 */ s8 z;
    /* 0x3 */ u8 color[3];
} LightDirectional; // size = 0x6

typedef union LightParams {
    LightPoint point;
    LightDirectional dir;
} LightParams; // size = 0xC

typedef struct LightInfo {
    /* 0x0 */ u8 type;
    /* 0x2 */ LightParams params;
} LightInfo; // size = 0xE

typedef struct LightNode {
    /* 0x0 */ LightInfo* info;
    /* 0x4 */ struct LightNode* prev;
    /* 0x8 */ struct LightNode* next;
} LightNode; // size = 0xC

typedef struct LightContext {
    /* 0x0 */ LightNode* listHead;
    /* 0x4 */ Color_RGB8 ambient;
    /* 0x7 */ Color_RGB8 fogColor;
    /* 0xA */ s16 fogNear; // how close until fog starts taking effect. range 0 - 996
    /* 0xC */ s16 zFar; // draw distance. range 0 - 12800
} LightContext; // size = 0x10

typedef struct LightsN {
    /* 0x00 */ u8 diffuse_count;
    /* 0x08 */ Ambient a;
    /* 0x10 */ Light l[7];
} LightsN; // size = 0x80

// void func_8009B1E0_jp();
// void func_8009B23C_jp();
// void func_8009B2A0_jp();
// void func_8009B308_jp();
// void func_8009B33C_jp();
// void func_8009B394_jp();
void LightsN_disp(LightsN* arg0, struct GraphicsContext* gfxCtx);
// void func_8009B504_jp();
// void func_8009B534_jp();
// void func_8009B72C_jp();
// void func_8009B81C_jp();
void func_8009B884_jp(LightsN* arg0, LightNode* arg1, s32 arg2);
// void func_8009B954_jp();
// void func_8009B9E0_jp();
void func_8009BA28_jp(LightContext* arg0);
// void func_8009BA94_jp();
// void func_8009BAC0_jp();
LightsN* Global_light_read(LightContext* arg0, struct GraphicsContext* gfxCtx);
// void func_8009BB34_jp();
// void func_8009BB40_jp();
// void func_8009BB8C_jp();
// void func_8009BBEC_jp();
// void func_8009BC48_jp();
// void func_8009BD90_jp();
// void Light_list_point_draw();

#endif
