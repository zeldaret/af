#ifndef M_LIGHTS_H
#define M_LIGHTS_H

#include "ultra64.h"
#include "z64math.h"
#include "unk.h"
#include "color.h"
#include "gbi.h"

struct GraphicsContext;
struct Game_Play;

typedef struct LightPoint {
    /* 0x0 */ s16 x;
    /* 0x2 */ s16 y;
    /* 0x4 */ s16 z;
    /* 0x6 */ u8 color[3];
    /* 0x9 */ u8 drawGlow;
    /* 0xA */ s16 radius;
} LightPoint; // size = 0xC

typedef struct LightDiffuse {
    /* 0x0 */ s8 x;
    /* 0x1 */ s8 y;
    /* 0x2 */ s8 z;
    /* 0x3 */ u8 color[3];
} LightDiffuse; // size = 0x6

typedef union {
    LightPoint point;
    LightDiffuse diffuse;
} LightParams; // size = 0xC

typedef struct Lights {
    /* 0x00 */ u8 type;
    /* 0x04 */ LightParams lights;
} Lights; // size = 0x10

typedef struct LightNode {
    /* 0x0 */ Lights* info;
    /* 0x4 */ struct LightNode* prev;
    /* 0x8 */ struct LightNode* next;
} LightNode; // size = 0xC

typedef struct LightBuffer {
    /* 0x00 */ s32 current;
    /* 0x04 */ s32 idx;
    /* 0x08 */ LightNode lights[32];
} LightBuffer; // size = 0x188

typedef struct LightsN {
    /* 0x00 */ u8 diffuse_count;
    /* 0x08 */ Lightsn lights;
}LightsN; // size = 0x80

typedef struct Global_light {
    /* 0x0 */ LightNode* list;
    /* 0x4 */ u8 ambientColor[3];
    /* 0x7 */ u8 fogColor[3];
    /* 0xA */ s16 fogNear;
    /* 0xC */ s16 fogFar; 
} Global_light; // size = 0x10

typedef void (*light_point_proc)(LightsN*, LightParams*, Vec3f*);
typedef void (*light_P_point_proc)(LightsN*, LightParams*, Vec3f*);

void point_data_set(Lights* lights, s16 x, s16 y, s16 z, u8 r, u8 g, u8 b, s16 radius, s32 type);
void Light_point_ct(Lights* lights, s16 x, s16 y, s16 z, u8 r, u8 g, u8 b, s16 radius);
void Light_point2_ct(Lights* lights, s16 x, s16 y, s16 z, u8 r, u8 g, u8 b, s16 radius);
void Light_point_color_set(Lights* lights, u8 r, u8 g, u8 b, s16 radius);
void Light_diffuse_ct(Lights* lights, s8 x, s8 y, s8 z, u8 r, u8 g, u8 b);
void LightsN_ct(LightsN* lights, u8 r, u8 g, u8 b);
void LightsN_disp(LightsN* lights, struct GraphicsContext* gfxCtx);
Light* LightsN_new_diffuse(LightsN* lights);
void LightsN__point_proc(LightsN* lights, LightParams* lightInfo, Vec3f* point);
void LightsN__P_point_proc(LightsN* lights, LightParams* lightInfo, Vec3f* pos);
void LightsN__diffuse_proc(LightsN* lights, LightParams* lightInfo, Vec3f* pos);
void LightsN_list_check(LightsN* lights, LightNode* node, Vec3f* pos);
LightNode* Light_list_buf_new(void);
void Light_list_buf_delete(LightNode* lightNode);
void Global_light_ct(Global_light* glight);
void Global_light_ambient_set(Global_light* glight, u8 r, u8 g, u8 b);
void Global_light_fog_set(Global_light* glight, u8 r, u8 g, u8 b, s16 near, s16 far);
LightsN* Global_light_read(Global_light* glight, struct GraphicsContext* gfxCtx);
void Global_light_list_ct(Global_light* glight);
void Global_light_list_dt(Global_light* glight);
LightNode* Global_light_list_new(struct Game_Play* play, Global_light* glight, Lights* light);
void Global_light_list_delete(Global_light* glight, LightNode* lightNode);
LightsN* new_Lights(struct GraphicsContext* gfxCtx, u8 ambient_r, u8 ambient_g, u8 ambient_b, u8 count, u8 light_r,
                          u8 light_g, u8 light_b, s8 dir_x, s8 dir_y, s8 dir_z);
LightsN* new_LightsN(struct GraphicsContext* gfxCtx, u8 r, u8 g, u8 b);
void Light_list_point_draw(struct Game_Play* gamePlay);

#endif
