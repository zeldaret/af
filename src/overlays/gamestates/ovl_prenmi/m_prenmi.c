#include "m_prenmi.h"
#include "libc/stdbool.h"
#include "irqmgr.h"
#include "viconfig.h"
#include "gfx.h"
#include "m_rcp.h"

void prenmi_move(Game_Prenmi* prenmi) {
    if (ResetStatus == 2 || prenmi->timer == 0) {
        ViConfig_UpdateVi(TRUE);
        STOP_GAMESTATE(&prenmi->state);
        SET_NEXT_GAMESTATE(&prenmi->state, NULL, 0);
    } else {
        prenmi->timer--;
    }
}

void prenmi_draw(Game_Prenmi* prenmi) {
    GraphicsContext* graph;
    f32 yPos;
    f32 time;

    graph = prenmi->state.gfxCtx;

    DisplayList_initialize(graph, 0, 0, 0, NULL);

    OPEN_POLY_OPA_DISP(graph);

    time = OS_CYCLES_TO_USEC(osGetTime() - ResetTime);

    gDPPipeSync(__polyOpa++);
    gDPSetOtherMode(__polyOpa++,
                    G_AD_DISABLE | G_CD_MAGICSQ | G_CK_NONE | G_TC_FILT | G_TF_POINT | G_TT_NONE | G_TL_TILE |
                        G_TD_CLAMP | G_TP_NONE | G_CYC_1CYCLE | G_PM_NPRIMITIVE,
                    G_AC_NONE | G_ZS_PRIM | G_RM_XLU_SURF | G_RM_XLU_SURF2);
    gDPSetCombineMode(__polyOpa++, G_CC_PRIMITIVE, G_CC_PRIMITIVE);

    // set opacity
    yPos = (time / 500000) * -200.0f + 250.0f;
    gDPSetPrimColor(__polyOpa++, 0, 0, 0xFF, 0xFF, 0xFF, (s32)yPos);

    // adjust size
    yPos = (time / 500000) * -15.0f + 127.0f;
    __polyOpa =
        gfx_gSPTextureRectangle1(__polyOpa, 0, (u32)(yPos * 4.0f), 0x500, (u32)((yPos + 1.0f) * 4.0f), 0, 0, 0, 0, 0);

    gDPPipeSync(__polyOpa++);
    CLOSE_POLY_OPA_DISP(prenmi->state.gfxCtx);
}

void prenmi_main(Game* game) {
    Game_Prenmi* prenmi = (Game_Prenmi*)game;
    GraphicsContext* graph;

    prenmi_move(prenmi);
    prenmi_draw(prenmi);

    prenmi->state.unk_A4 = true;
    { UNUSED s32 scopedTemp; }
    graph = game->gfxCtx;

    game_debug_draw_last(game, graph);
    game_draw_last(graph);
}

void prenmi_cleanup(UNUSED Game* game) {
}

void prenmi_init(Game* game) {
    Game_Prenmi* prenmi = (Game_Prenmi*)game;

    prenmi->state.main = &prenmi_main;
    prenmi->state.destroy = &prenmi_cleanup;
    prenmi->timer = 30;
    SetGameFrame(1);
}
