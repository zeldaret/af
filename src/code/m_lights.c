#include "global.h"
#include "m_lights.h"
#include "gfx.h"
#include "macros.h"
#include "sys_matrix.h"
#include "overlays/gamestates/ovl_play/m_play.h"
#include "m_rcp.h"

extern Gfx D_400AA00[]; // point_light_init_model
extern Gfx D_400AA40[]; // point_light_model

LightBuffer light_list_buf;

void point_data_set(Lights* lights, s16 x, s16 y, s16 z, u8 r, u8 g, u8 b, s16 radius, s32 type) {
    lights->type = type;
    lights->lights.point.x = x;
    lights->lights.point.y = y;
    lights->lights.point.z = z;
    Light_point_color_set(lights, r, g, b, radius);
}

void Light_point_ct(Lights* lights, s16 x, s16 y, s16 z, u8 r, u8 g, u8 b, s16 radius) {
    point_data_set(lights, x, y, z, r, g, b, radius, 0);
}

void Light_point2_ct(Lights* lights, s16 x, s16 y, s16 z, u8 r, u8 g, u8 b, s16 radius) {
    point_data_set(lights, x, y, z, r, g, b, radius, 2);
}

void Light_point_color_set(Lights* lights, u8 r, u8 g, u8 b, s16 radius) {
    lights->lights.point.color[0] = r;
    lights->lights.point.color[1] = g;
    lights->lights.point.color[2] = b;
    lights->lights.point.radius = radius;
}

void Light_diffuse_ct(Lights* lights, s8 x, s8 y, s8 z, u8 r, u8 g, u8 b) {
    lights->type = 1;
    lights->lights.diffuse.x = x;
    lights->lights.diffuse.y = y;
    lights->lights.diffuse.z = z;
    lights->lights.diffuse.color[0] = r;
    lights->lights.diffuse.color[1] = g;
    lights->lights.diffuse.color[2] = b;
}

void LightsN_ct(LightsN* lights, u8 r, u8 g, u8 b) {
    lights->lights.a.l.col[0] = lights->lights.a.l.colc[0] = r;
    lights->lights.a.l.col[1] = lights->lights.a.l.colc[1] = g;
    lights->lights.a.l.col[2] = lights->lights.a.l.colc[2] = b;
    lights->diffuse_count = 0;
}

void LightsN_disp(LightsN* lights, GraphicsContext* gfxCtx) {
    Light* light;
    s32 i;
    Gfx* opaGfx;
    Gfx* xluGfx;

    OPEN_DISPS(gfxCtx);

    opaGfx = POLY_OPA_DISP;
    xluGfx = POLY_XLU_DISP;

    gSPNumLights(opaGfx++, lights->diffuse_count);
    gSPNumLights(xluGfx++, lights->diffuse_count);

    light = lights->lights.l;

    for (i = 0; i < lights->diffuse_count;) {
        i++;
        gSPLight(opaGfx++, light, i);
        gSPLight(xluGfx++, light, i);
        light++;
    }

    i++;
    gSPLight(opaGfx++, &lights->lights.a.l, i);
    gSPLight(xluGfx++, &lights->lights.a.l, i);

    POLY_OPA_DISP = opaGfx;
    POLY_XLU_DISP = xluGfx;

    CLOSE_DISPS(gfxCtx);
}

Light* LightsN_new_diffuse(LightsN* lights) {
    if (lights->diffuse_count >= ARRAY_COUNT(lights->lights.l)) {
        return NULL;
    }

    return &lights->lights.l[lights->diffuse_count++];
}

void LightsN__point_proc(LightsN* lights, LightParams* lightInfo, Vec3f* point) {
    f32 xdiff;
    f32 ydiff;
    f32 zdiff;
    f32 pointd;
    f32 rad;
    Light* light;

    if ((point != NULL) && (lightInfo->point.radius > 0)) {
        xdiff = lightInfo->point.x - point->x;
        ydiff = lightInfo->point.y - point->y;
        zdiff = lightInfo->point.z - point->z;
        pointd = SQ(xdiff) + SQ(ydiff) + SQ(zdiff);

        rad = lightInfo->point.radius;

        if (pointd < SQ(rad)) {
            light = LightsN_new_diffuse(lights);

            if (light != NULL) {
                pointd = sqrtf(pointd);
                rad = pointd / rad;
                rad = 1 - SQ(rad);

                light->l.col[0] = light->l.colc[0] = (s8)(lightInfo->point.color[0] * rad);
                light->l.col[1] = light->l.colc[1] = (s8)(lightInfo->point.color[1] * rad);
                light->l.col[2] = light->l.colc[2] = (s8)(lightInfo->point.color[2] * rad);

                rad = (pointd < 1) ? 120.0f : 120.0f / pointd;

                light->l.dir[0] = xdiff * rad;
                light->l.dir[1] = ydiff * rad;
                light->l.dir[2] = zdiff * rad;
            }
        }
    }
}

void LightsN__P_point_proc(LightsN* lights, LightParams* lightInfo, UNUSED Vec3f* pos) {
    if (lightInfo->point.radius > 0) {
        Light* light = LightsN_new_diffuse(lights);

        if (light != NULL) {
            f32 kq = lightInfo->point.radius;
            kq = 4500000 / SQ(kq);

            if (kq > 255) {
                kq = 255;
            } else if (kq < 20) {
                kq = 20;
            }

            light->l.col[0] = lightInfo->point.color[0];
            light->l.colc[0] = light->l.col[0];

            light->l.col[1] = lightInfo->point.color[1];
            light->l.colc[1] = light->l.col[1];

            light->l.col[2] = lightInfo->point.color[2];
            light->l.colc[2] = light->l.col[2];

            light->p.pos[0] = lightInfo->point.x;
            light->p.pos[1] = lightInfo->point.y;
            light->p.pos[2] = lightInfo->point.z;

            light->p.kc = 8;
            light->p.kl = -1;
            light->p.kq = (s32)kq;
        }
    }
}

void LightsN__diffuse_proc(LightsN* lights, LightParams* lightInfo, UNUSED Vec3f* pos) {
    Light* light = LightsN_new_diffuse(lights);

    if (light != NULL) {
        light->l.col[0] = light->l.colc[0] = lightInfo->diffuse.color[0];
        light->l.col[1] = light->l.colc[1] = lightInfo->diffuse.color[1];
        light->l.col[2] = light->l.colc[2] = lightInfo->diffuse.color[2];
        light->l.dir[0] = lightInfo->diffuse.x;
        light->l.dir[1] = lightInfo->diffuse.y;
        light->l.dir[2] = lightInfo->diffuse.z;
    }
}

void LightsN_list_check(LightsN* lights, LightNode* node, Vec3f* pos) {
    static light_point_proc poslight_type_proc[] = {
        LightsN__point_proc,
        LightsN__diffuse_proc,
        LightsN__point_proc,
    };
    static light_P_point_proc light_type_proc[] = {
        LightsN__P_point_proc,
        LightsN__diffuse_proc,
        LightsN__P_point_proc,
    };

    if (pos == NULL) {
        while (node != NULL) {
            light_type_proc[node->info->type](lights, &node->info->lights, pos);
            node = node->next;
        }
    } else {
        while (node != NULL) {
            poslight_type_proc[node->info->type](lights, &node->info->lights, pos);
            node = node->next;
        }
    }
}

LightNode* Light_list_buf_new(void) {
    LightNode* lightNode;

    if (light_list_buf.current >= ARRAY_COUNT(light_list_buf.lights)) {
        return NULL;
    }

    lightNode = &light_list_buf.lights[light_list_buf.idx];

    while (lightNode->info != NULL) {
        light_list_buf.idx++;
        if (light_list_buf.idx < ARRAY_COUNT(light_list_buf.lights)) {
            lightNode++;
        } else {
            light_list_buf.idx = 0;
            lightNode = &light_list_buf.lights[0];
        }
    }
    light_list_buf.current++;
    return lightNode;
}

void Light_list_buf_delete(LightNode* lightNode) {
    if (lightNode != NULL) {
        light_list_buf.current--;
        lightNode->info = NULL;
        light_list_buf.idx = (lightNode - light_list_buf.lights) / (s32)sizeof(LightNode);
    }
}

void Global_light_ct(Global_light* glight) {
    Global_light_list_ct(glight);
    Global_light_ambient_set(glight, 0x50, 0x50, 0x50);
    Global_light_fog_set(glight, 0, 0, 0, 0x3E4, 0x640);
    bzero(&light_list_buf, sizeof(LightBuffer));
}

void Global_light_ambient_set(Global_light* glight, u8 r, u8 g, u8 b) {
    glight->ambientColor[0] = r;
    glight->ambientColor[1] = g;
    glight->ambientColor[2] = b;
}

void Global_light_fog_set(Global_light* glight, u8 r, u8 g, u8 b, s16 near, s16 far) {
    glight->fogColor[0] = r;
    glight->fogColor[1] = g;
    glight->fogColor[2] = b;
    glight->fogNear = near;
    glight->fogFar = far;
}

LightsN* Global_light_read(Global_light* glight, struct GraphicsContext* gfxCtx) {
    return new_LightsN(gfxCtx, glight->ambientColor[0], glight->ambientColor[1], glight->ambientColor[2]);
}

void Global_light_list_ct(Global_light* glight) {
    glight->list = NULL;
}

void Global_light_list_dt(Global_light* glight) {
    while (glight->list != NULL) {
        Global_light_list_delete(glight, glight->list);
        glight->list = glight->list->next;
    }
}

LightNode* Global_light_list_new(UNUSED Game_Play* play, Global_light* glight, Lights* light) {
    LightNode* newNode = Light_list_buf_new();

    if (newNode != NULL) {
        newNode->info = light;
        newNode->prev = NULL;
        newNode->next = glight->list;
        if (glight->list != NULL) {
            glight->list->prev = newNode;
        }
        glight->list = newNode;
    }
    return newNode;
}

void Global_light_list_delete(Global_light* glight, LightNode* lightNode) {
    if (lightNode != NULL) {
        if (lightNode->prev != NULL) {
            lightNode->prev->next = lightNode->next;
        } else {
            glight->list = lightNode->next;
        }
        if (lightNode->next != NULL) {
            lightNode->next->prev = lightNode->prev;
        }
        Light_list_buf_delete(lightNode);
    }
}

LightsN* new_Lights(GraphicsContext* gfxCtx, u8 ambient_r, u8 ambient_g, u8 ambient_b, u8 count, u8 light_r, u8 light_g,
                    u8 light_b, s8 dir_x, s8 dir_y, s8 dir_z) {
    LightsN* lights = GRAPH_ALLOC(gfxCtx, sizeof(LightsN) * 1);
    s32 i;

    lights->lights.a.l.col[0] = lights->lights.a.l.colc[0] = ambient_r;
    lights->lights.a.l.col[1] = lights->lights.a.l.colc[1] = ambient_g;
    lights->lights.a.l.col[2] = lights->lights.a.l.colc[2] = ambient_b;
    lights->diffuse_count = count;

    for (i = 0; i < count; i++) {
        lights->lights.l[i].l.col[0] = lights->lights.l[i].l.colc[0] = light_r;
        lights->lights.l[i].l.col[1] = lights->lights.l[i].l.colc[1] = light_g;
        lights->lights.l[i].l.col[2] = lights->lights.l[i].l.colc[2] = light_b;

        lights->lights.l[i].l.dir[0] = dir_x;
        lights->lights.l[i].l.dir[1] = dir_y;
        lights->lights.l[i].l.dir[2] = dir_z;
    }

    LightsN_disp(lights, gfxCtx);
    return lights;
}

LightsN* new_LightsN(GraphicsContext* gfxCtx, u8 r, u8 g, u8 b) {
    LightsN* lights = GRAPH_ALLOC(gfxCtx, sizeof(LightsN) * 1);

    lights->lights.a.l.col[0] = r;
    lights->lights.a.l.colc[0] = r;
    lights->lights.a.l.col[1] = g;
    lights->lights.a.l.colc[1] = g;
    lights->lights.a.l.col[2] = b;
    lights->lights.a.l.colc[2] = b;
    lights->diffuse_count = 0;
    return lights;
}

void Light_list_point_draw(Game_Play* game_play) {
    LightNode* lightNode = game_play->glight.list;
    Gfx* gfx;

    OPEN_DISPS(game_play->state.gfxCtx);
    gfx = func_800BD7C0_jp(POLY_XLU_DISP);

    gDPSetAlphaDither(gfx++, G_AD_NOISE);
    gDPSetColorDither(gfx++, G_CD_MAGICSQ);
    gSPDisplayList(gfx++, D_400AA00);

    while (lightNode != NULL) {
        LightParams* lightParams = &lightNode->info->lights;

        if ((lightNode->info->type == 2) && lightParams->point.drawGlow) {
            f32 rad = SQ(lightParams->point.radius) * 0.0000026f;

            gDPSetPrimColor(gfx++, 0, 0, lightParams->point.color[0], lightParams->point.color[1],
                            lightParams->point.color[2], 50);

            Matrix_translate(lightParams->point.x, lightParams->point.y, lightParams->point.z, 0);
            Matrix_scale(rad, rad, rad, 1);

            gSPMatrix(gfx++, _Matrix_to_Mtx_new(game_play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
            gSPDisplayList(gfx++, D_400AA40);
        }
        lightNode = lightNode->next;
    }

    POLY_XLU_DISP = gfx;

    CLOSE_DISPS(game_play->state.gfxCtx);
}
