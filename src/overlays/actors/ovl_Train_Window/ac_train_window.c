#include "ac_train_window.h"
#include "m_actor_dlftbls.h"
#include "m_object.h"
#include "evw_anime.h"
#include "m_rcp.h"
#include "overlays/gamestates/ovl_play/m_play.h"

void Train_Window_Actor_ct(Actor* thisx, Game_Play* game_play);
void Train_Window_Actor_dt(Actor* thisx, Game_Play* game_play);
void Train_Window_Actor_move(Actor* thisx, Game_Play* game_play);
void Train_Window_Actor_draw(Actor* thisx, Game_Play* play);

#if 0
ActorProfile Train_Window_Profile = {
    /* */ ACTOR_TRAIN_WINDOW,
    /* */ ACTOR_PART_0,
    /* */ ACTOR_FLAG_10 | ACTOR_FLAG_20,
    /* */ 0x8011,
    /* */ OBJECT_41,
    /* */ sizeof(Train_Window),
    /* */ Train_Window_Actor_ct,
    /* */ Train_Window_Actor_dt,
    /* */ Train_Window_Actor_move,
    /* */ Train_Window_Actor_draw,
    /* */ NULL,
};
#endif

// TODO: Import data

extern Gfx rom_train_out_bgsky_model[];
extern Gfx rom_train_out_bgcloud_modelT[];
extern Gfx rom_train_out_shineglass_modelT[];

extern u8 till_data[15][2];
extern u16 aTrainWindow_tree_pal_table[15][16];

extern EvwAnimeUnk aTrainWindow_evw_anime_data;

s32 aTrainWindow_NoDraw(Actor* thisx, Game* game);
s32 aTrainWindow_DrawGoneOutTunnel(Actor* thisx, Game* game);
s32 aTrainWindow_DrawInTunnel(Actor* thisx, Game* game);

s32 aTrainWindow_GetTreePalletIdx(void) {
    s32 i;
    lbRTC_month_t month = common_data.time.rtcTime.month;
    lbRTC_day_t day = common_data.time.rtcTime.day;

    for (i = 0; i < 15; i++) {
        if (month < till_data[i][0]) {
            return i;
        }

        if (month == till_data[i][0] && day <= till_data[i][1]) {
            return i;
        }
    }

    return 0;
}

void Train_Window_Actor_ct(Actor* thisx, UNUSED Game_Play* play) {
    Train_Window* this = (Train_Window*)thisx;

    if (common_data.sceneNo == 15) {
        this->drawType = aTrainWindow_NoDraw;
        this->singleScrollX = 0;
        this->singleScrollY = 0;
        this->twoScrollX1 = 0;
        this->twoScrollY1 = 0;
        this->twoScrollX2 = 0;
        this->twoScrollY2 = 0;
        this->scrollSpeed = 0.07f;
    } else {
        this->drawType = aTrainWindow_DrawGoneOutTunnel;
        this->singleScrollX = 1000;
        this->singleScrollY = 0;
        this->twoScrollX1 = 1000;
        this->twoScrollY1 = 0;
        this->twoScrollX2 = 0;
        this->twoScrollY2 = 0;
        this->scrollSpeed = 1.0f;
    }
    this->paletteId = aTrainWindow_GetTreePalletIdx();
    this->currentPalette = aTrainWindow_tree_pal_table[this->paletteId];
    this->treeScrollX = 500;
    this->treeScrollY = 0;
    this->pos.x = 0;
    this->pos.y = 0;
    this->pos.z = 0;
    this->xluAlpha = 254.0f;
}

void Train_Window_Actor_dt(UNUSED Actor* thisx, UNUSED Game_Play* play) {
}

u8 aTW_GetNowAlpha(void) {
    if ((common_data.time.nowSec >= 14400) && (common_data.time.nowSec < 72000)) {
        if (common_data.time.nowSec < 43200) {
            UNUSED f32 scopedTemp;
            return ((void)0, 255.0f) * ((f32)(common_data.time.nowSec - 14400) / 28800.0f);
        } else {
            return 255.0f * (1.0f - ((f32)(common_data.time.nowSec - 43200) / 28800.0f));
        }
    } else if (common_data.time.nowSec < 14400) {
        UNUSED f32 scopedTemp;
        return (1.0f - (0.5f + ((f32)common_data.time.nowSec / 28800.0f))) * 200.0f;
    } else {
        return ((f32)(common_data.time.nowSec - 72000) / 28800.0f) * ((void)0, 200.0f);
    }
}

void Train_Window_Actor_move(Actor* thisx, UNUSED Game_Play* play) {
    Train_Window* this = (Train_Window*)thisx;
    add_calc(&this->xluAlpha, aTW_GetNowAlpha(), this->scrollSpeed, 50.0f, 1.0f);
}

s32 aTrainWindow_OperateScrollLimit(s32 a, s32 b, s32 c) {
    if (b != 0) {
        if (b > 0) {
            a += b;
            if (a > c) {
                a = c;
            }
        } else if (b < 0) {
            a += b;
            if (a < c) {
                a = c;
            }
        }
    }
    return a;
}

Gfx* aTrainWindow_TileScroll(u32* x, u32* y, s32 xamt, s32 yamt, s32 xend, s32 yend, s32 width, s32 height,
                             GraphicsContext** graph) {
    *x = aTrainWindow_OperateScrollLimit(*x, xamt, xend);
    *y = aTrainWindow_OperateScrollLimit(*y, yamt, yend);

    return tex_scroll2(*graph, *x, *y, width, height);
}

Gfx* aTrainWindow_TileScroll2(u32* x1, u32* y1, s32 x1amt, s32 y1amt, s32 x1end, s32 y1end, s32 width1, s32 height1,
                              u32* x2, u32* y2, s32 x2amt, s32 y2amt, s32 x2end, s32 y2end, s32 width2, s32 height2,
                              GraphicsContext** graph) {
    *x1 = aTrainWindow_OperateScrollLimit(*x1, x1amt, x1end);
    *y1 = aTrainWindow_OperateScrollLimit(*y1, y1amt, y1end);
    *x2 = aTrainWindow_OperateScrollLimit(*x2, x2amt, x2end);
    *y2 = aTrainWindow_OperateScrollLimit(*y2, y2amt, y2end);

    return two_tex_scroll(*graph, 0, *x1, *y1, width1, height1, 1, *x2, *y2, width2, height2);
}
s32 aTrainWindow_DrawGoneOutTunnel(Actor* thisx, Game* game) {
    Train_Window* this = (Train_Window*)thisx;
    Gfx* ssc;
    Gfx* tsc;
    GraphicsContext** graph = &game->gfxCtx;

    ssc = aTrainWindow_TileScroll(&this->singleScrollX, &this->singleScrollY, 0, 0, 1000, 0, 64, 32, graph);
    tsc = aTrainWindow_TileScroll2(&this->twoScrollX1, &this->twoScrollY1, 0, 0, 1000, 0, 64, 8, &this->twoScrollX2,
                                   &this->twoScrollY2, 0, 0, 0, 0, 16, 16, graph);

    if ((ssc == NULL) || (tsc == NULL)) {
        return 0;
    } else {
        OPEN_DISPS(*graph);
        if (!this->paletteId) {}
        gSPSegment(POLY_OPA_DISP++, 11, ssc);
        gSPSegment(POLY_XLU_DISP++, 11, ssc);

        gSPSegment(POLY_OPA_DISP++, 12, tsc);
        gSPSegment(POLY_XLU_DISP++, 12, tsc);

        CLOSE_DISPS(*graph);

        return 1;
    }
}

s32 aTrainWindow_DrawGoingOutTunnel(Actor* thisx, Game* game) {
    Train_Window* this = (Train_Window*)thisx;
    Gfx* ssc;
    Gfx* tsc;

    GraphicsContext** graph = &game->gfxCtx;

    ssc = aTrainWindow_TileScroll(&this->singleScrollX, &this->singleScrollY, 30, 0, 1000, 0, 64, 32, graph);
    tsc = aTrainWindow_TileScroll2(&this->twoScrollX1, &this->twoScrollY1, 30, 0, 1000, 0, 64, 8, &this->twoScrollX2,
                                   &this->twoScrollY2, 0, 0, 0, 0, 16, 16, graph);

    if ((ssc == NULL) || (tsc == NULL)) {
        return 0;
    } else {
        OPEN_DISPS(*graph);
        if (!this->paletteId) {}
        gSPSegment(POLY_OPA_DISP++, 11, ssc);
        gSPSegment(POLY_XLU_DISP++, 11, ssc);
        gSPSegment(POLY_OPA_DISP++, 12, tsc);
        if (1) {
            gSPSegment(POLY_XLU_DISP++, 12, tsc);

            CLOSE_DISPS(*graph);

            if (((s32)this->singleScrollX == 1000) && ((s32)this->twoScrollX1 == 1000)) {
                this->drawType = aTrainWindow_DrawGoneOutTunnel;
                this->paletteId = aTrainWindow_GetTreePalletIdx();
                this->currentPalette = aTrainWindow_tree_pal_table[this->paletteId];
            }

            return 1;
        }
    }
}

s32 aTrainWindow_NoDraw(Actor* thisx, UNUSED Game* game) {
    Train_Window* this = (Train_Window*)thisx;

    this->drawType = aTrainWindow_DrawInTunnel;
    return 0;
}

s32 aTrainWindow_DrawInTunnel(Actor* thisx, Game* game) {
    Train_Window* this = (Train_Window*)thisx;
    Gfx* ssc;
    Gfx* tsc;

    ssc = aTrainWindow_TileScroll(&this->singleScrollX, &this->singleScrollY, 0, 0, 1000, 0, 64, 32, &game->gfxCtx);
    tsc = aTrainWindow_TileScroll2(&this->twoScrollX1, &this->twoScrollY1, 0, 0, 1000, 0, 64, 8, &this->twoScrollX2,
                                   &this->twoScrollY2, 0, 0, 0, 0, 16, 16, &game->gfxCtx);

    if ((ssc == NULL) || (tsc == NULL)) {
        return 0;
    } else {
        OPEN_DISPS(game->gfxCtx);
        if (!this->paletteId) {}
        gSPSegment(POLY_OPA_DISP++, 11, ssc);
        gSPSegment(POLY_XLU_DISP++, 11, ssc);

        gSPSegment(POLY_OPA_DISP++, 12, tsc);
        gSPSegment(POLY_XLU_DISP++, 12, tsc);

        CLOSE_DISPS(game->gfxCtx);

        if (common_data.sunlightFlag != 0) {
            this->paletteId = aTrainWindow_GetTreePalletIdx();
            this->currentPalette = aTrainWindow_tree_pal_table[this->paletteId];
            this->drawType = aTrainWindow_DrawGoingOutTunnel;
        }
        return 1;
    }
}

void aTrainWindow_SetLightPrimColorDetail(Game* game, u8 l, u8 polyAlpha, u8 xluAlpha) {
    Game_Play* play = (Game_Play*)game;
    u8 color[3];
    s32 i;
    s32 current;

    for (i = 0; i < 3; i++) {
        current = play->glight.ambientColor[i] + play->kankyo.sunColor[i];
        if (current < 0) {
            current = 0;
        } else if (current >= 256) {
            current = 255;
        }
        color[i] = current;
    }

    OPEN_DISPS(game->gfxCtx);
    gDPSetPrimColor(POLY_OPA_DISP++, 0, l, color[0], color[1], color[2], polyAlpha);
    gDPSetPrimColor(POLY_XLU_DISP++, 0, l, color[0], color[1], color[2], xluAlpha);
    CLOSE_DISPS(game->gfxCtx);
}

void aTrainWindow_SetTreeTextureScroll(Actor* thisx, Game* game) {
    Train_Window* this = (Train_Window*)thisx;
    Gfx* tree;
    GraphicsContext** graphp = &game->gfxCtx;

    this->treeScrollX += 10;

    tree = tex_scroll2(*graphp, this->treeScrollX, this->treeScrollY, 128, 32);

    OPEN_DISPS(*graphp);

    gSPSegment(POLY_XLU_DISP++, 8, tree);

    CLOSE_DISPS(*graphp);
}

void Train_Window_Actor_draw(Actor* thisx, Game_Play* play) {
    Train_Window* this = (Train_Window*)thisx;
    UNUSED s32 pad;

    if (1) {}
    OPEN_DISPS(play->state.gfxCtx);
    Matrix_translate(0.0f, 0.0f, 0.0f, FALSE);
    Matrix_scale(0.05f, 0.05f, 0.05f, TRUE);

    gSPMatrix(POLY_OPA_DISP++, _Matrix_to_Mtx_new(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPMatrix(POLY_XLU_DISP++, _Matrix_to_Mtx_new(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

    if (this->drawType(thisx, &play->state) != 0) {
        _texture_z_light_fog_prim(play->state.gfxCtx);
        _texture_z_light_fog_prim_xlu(play->state.gfxCtx);
        if (1) {}
        aTrainWindow_SetLightPrimColorDetail(&play->state, 127, 255, this->xluAlpha);
        gSPSegment(POLY_XLU_DISP++, 10, this->currentPalette);
        if (1) {}
        Evw_Anime_Set(&play->state, &aTrainWindow_evw_anime_data);

        aTrainWindow_SetLightPrimColorDetail(&play->state, 255, 255, this->xluAlpha);
        gSPDisplayList(POLY_OPA_DISP++, rom_train_out_bgsky_model);
        aTrainWindow_SetLightPrimColorDetail(&play->state, this->xluAlpha, 255, this->xluAlpha);
        gSPDisplayList(POLY_XLU_DISP++, rom_train_out_bgcloud_modelT);
        aTrainWindow_SetTreeTextureScroll(thisx, &play->state);
        aTrainWindow_SetLightPrimColorDetail(&play->state, 127, 255, this->xluAlpha);
        gSPDisplayList(POLY_XLU_DISP++, rom_train_out_shineglass_modelT);
    }
    CLOSE_DISPS(play->state.gfxCtx);
}
