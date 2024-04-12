#include "global.h"
#include "gfx.h"
#include "m_rcp.h"
#include "m_debug_display.h"

typedef struct {
    /* 0x00 */ s16 drawType;  // indicates which draw function to use when displaying the object
    /* 0x04 */ void* drawArg; // segment address (display list or texture) passed to the draw function when called
} DebugDispObjectInfo;        // size = 0x8

typedef void (*DebugDispObject_DrawFunc)(DebugDispObject*, void*, Game_Play*);

extern u8* no_txt;
extern u8* nx_txt;
extern u8* np_txt;
extern u8* nt_txt;
extern Gfx darrow_model[];
extern Gfx camera_model[];

DebugDispObject* debug_display;

extern Gfx RCP_debug_texture_16x16_8[];

void Debug_Display_init(void) {
    debug_display = NULL;
}

DebugDispObject* Debug_Display_new(f32 posX, f32 posY, f32 posZ, s16 rotX, s16 rotY, s16 rotZ, f32 scaleX, f32 scaleY,
                                   f32 scaleZ, u8 red, u8 green, u8 blue, u8 alpha, s16 type, GraphicsContext* gfxCtx) {
    DebugDispObject* prevHead = debug_display;

    debug_display = GRAPH_ALLOC(gfxCtx, sizeof(DebugDispObject));
    debug_display->pos.x = posX;
    debug_display->pos.y = posY;
    debug_display->pos.z = posZ;
    debug_display->rot.x = rotX;
    debug_display->rot.y = rotY;
    debug_display->rot.z = rotZ;
    debug_display->scale.x = scaleX;
    debug_display->scale.y = scaleY;
    debug_display->scale.z = scaleZ;
    debug_display->color.r = red;
    debug_display->color.g = green;
    debug_display->color.b = blue;
    debug_display->color.a = alpha;
    debug_display->type = type;
    debug_display->next = prevHead;
    return debug_display;
}

void Debug_Display_output(Game_Play* game_play) {
    static DebugDispObject_DrawFunc debug_display_output_proc[] = {
        debug_display_output_sprite_16x16_I8,
        debug_display_output_polygon,
    };

    static DebugDispObjectInfo debug_display_shape_data[] = {
        { 0, &no_txt }, { 0, &nx_txt }, { 0, &np_txt }, { 0, &nt_txt }, { 1, darrow_model }, { 1, camera_model },
    };

    DebugDispObject* dispObj = debug_display;
    DebugDispObjectInfo* objInfo;

    while (dispObj != NULL) {
        objInfo = &debug_display_shape_data[dispObj->type];
        debug_display_output_proc[objInfo->drawType](dispObj, objInfo->drawArg, game_play);
        dispObj = dispObj->next;
    }
}

void debug_display_output_sprite_16x16_I8(DebugDispObject* dispObj, void* texture, Game_Play* game_play) {
    OPEN_DISPS(game_play->state.gfxCtx);

    softsprite_prim(game_play->state.gfxCtx);

    gDPSetPrimColor(POLY_XLU_DISP++, 0, 0, dispObj->color.r, dispObj->color.g, dispObj->color.b, dispObj->color.a);
    Matrix_translate(dispObj->pos.x, dispObj->pos.y, dispObj->pos.z, MTXMODE_NEW);
    Matrix_scale(dispObj->scale.x, dispObj->scale.y, dispObj->scale.z, MTXMODE_APPLY);
    Matrix_mult(&game_play->billboardMtxF, MTXMODE_APPLY);
    Matrix_rotateXYZ(dispObj->rot.x, dispObj->rot.y, dispObj->rot.z, MTXMODE_APPLY);

    gDPLoadTextureBlock(POLY_XLU_DISP++, texture, G_IM_FMT_I, G_IM_SIZ_8b, 16, 16, 0, G_TX_NOMIRROR | G_TX_WRAP,
                        G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);

    gSPMatrix(POLY_XLU_DISP++, _Matrix_to_Mtx_new(game_play->state.gfxCtx),
              G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

    gSPDisplayList(POLY_XLU_DISP++, RCP_debug_texture_16x16_8);

    CLOSE_DISPS(play->state.gfxCtx);
}

void debug_display_output_polygon(DebugDispObject* dispObj, void* dList, Game_Play* game_play) {
    static Lights1 material = gdSPDefLights1(128, 128, 128, 255, 255, 255, 73, 73, 73);

    OPEN_DISPS(game_play->state.gfxCtx);

    polygon_z_light_prim(game_play->state.gfxCtx);

    gDPSetPrimColor(POLY_XLU_DISP++, 0, 0, dispObj->color.r, dispObj->color.g, dispObj->color.b, dispObj->color.a);

    gSPSetLights1(POLY_XLU_DISP++, material);

    Matrix_softcv3_load(dispObj->pos.x, dispObj->pos.y, dispObj->pos.z, &dispObj->rot);
    Matrix_scale(dispObj->scale.x, dispObj->scale.y, dispObj->scale.z, MTXMODE_APPLY);
    gSPMatrix(POLY_XLU_DISP++, _Matrix_to_Mtx_new(game_play->state.gfxCtx),
              G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

    gSPDisplayList(POLY_XLU_DISP++, dList);
    CLOSE_DISPS(game_play->state.gfxCtx);
}
