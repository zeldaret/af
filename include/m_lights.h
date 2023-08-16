#ifndef M_LIGHTS_H
#define M_LIGHTS_H

#include "ultra64.h"
#include "z64math.h"
#include "unk.h"
#include "color.h"

struct GraphicsContext;
struct PlayState;

typedef struct Lights {
    /* 0x00 */ UNK_TYPE1 unk_00[0x80];
} Lights; // size = 0x80

typedef struct LightNode {
    /* 0x00 */ char unk00[0xC];
} LightNode; // size = 0xC

typedef struct LightContext {
    /* 0x0 */ LightNode* listHead;
    /* 0x4 */ Color_RGB8 ambient;
    /* 0x7 */ Color_RGB8 fogColor;
    /* 0xA */ s16 fogNear; // how close until fog starts taking effect. range 0 - 996
    /* 0xC */ s16 zFar; // draw distance. range 0 - 12800
} LightContext; // size = 0x10

// void func_8009B1E0_jp();
// void func_8009B23C_jp();
// void func_8009B2A0_jp();
// void func_8009B308_jp();
// void func_8009B33C_jp();
// void func_8009B394_jp();
void LightsN_disp(Lights* light, struct GraphicsContext* gfxCtx);
// void func_8009B504_jp();
// void func_8009B534_jp();
// void func_8009B72C_jp();
// void func_8009B81C_jp();
void LightsN_list_check(Lights* light, LightNode* lightNode, Vec3f* arg2);
// void func_8009B954_jp();
// void func_8009B9E0_jp();
void Global_light_ct(LightContext* arg0);
// void func_8009BA94_jp();
// void func_8009BAC0_jp();
Lights* Global_light_read(LightContext* lightCtx, struct GraphicsContext* gfxCtx);
// void func_8009BB34_jp();
// void func_8009BB40_jp();
// void func_8009BB8C_jp();
// void func_8009BBEC_jp();
// void func_8009BC48_jp();
// void func_8009BD90_jp();
void Light_list_point_draw(struct PlayState* play);

#endif
