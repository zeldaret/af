#include "m_cpedit.h"
#include "gfx.h"
#include "overlays/gamestates/ovl_trademark/m_trademark.h"
#include "code_variables.h"
#include "macros.h"
#include "sys_matrix.h"
#include "6B3DC0.h"
#include "m_rcp.h"

// madeup name
void cpedit_main(Game* game) {
    Game_CPEdit* edit = (Game_CPEdit*)game;
    GraphicsContext* graph;
    edit->unk208(edit);

    graph = edit->state.gfxCtx;

    game_debug_draw_last(&edit->state, graph);
    game_draw_last(graph);
}

void func_80804930_jp(Game_CPEdit* edit) {
    UNUSED s32 pad[2];
    Submenu* submenu;
    GraphicsContext* graph = edit->state.gfxCtx;
    void* segment = edit->bank.status[0].segment;

    mCon_main(&edit->state);
    submenu = &edit->submenu;
    mSM_submenu_move(submenu);

    if (submenu->moveProcIndex == MSM_MOVE_PROC_END) {
        STOP_GAMESTATE((Game*)edit);
        SET_NEXT_GAMESTATE((Game*)edit, trademark_init, sizeof(Game_Trademark));
    }

    SegmentBaseAddress[4] = OS_K0_TO_PHYSICAL(segment);

    OPEN_DISPS(graph);

    gSPSegment(POLY_OPA_DISP++, G_MWO_SEGMENT_0, NULL);
    gSPSegment(POLY_XLU_DISP++, G_MWO_SEGMENT_0, NULL);

    gSPSegment(OVERLAY_DISP++, G_MWO_SEGMENT_0, NULL);
    gSPSegment(FONT_DISP++, G_MWO_SEGMENT_0, NULL);
    gSPSegment(SHADOW_DISP++, G_MWO_SEGMENT_0, NULL);

    gSPSegment(POLY_OPA_DISP++, G_MWO_SEGMENT_4, segment);
    gSPSegment(POLY_XLU_DISP++, G_MWO_SEGMENT_4, segment);

    gSPSegment(OVERLAY_DISP++, G_MWO_SEGMENT_4, segment);
    gSPSegment(FONT_DISP++, G_MWO_SEGMENT_4, segment);
    gSPSegment(SHADOW_DISP++, G_MWO_SEGMENT_4, segment);

    DisplayList_initialize(graph, 0, 0, 0, NULL);

    gDPPipeSync(POLY_OPA_DISP++);

    CLOSE_DISPS(graph);

    showView(&edit->view, 15);
    mSM_submenu_draw(submenu, (struct Game_Play*)edit);
}

void func_80804ADC_jp(Game_CPEdit* edit) {
    edit->unk208 = func_80804930_jp;
    edit->submenu.moveProcIndex = MSM_MOVE_PROC_PREWAIT;
    edit->submenu.programId = SUBMENU_PROGRAM_19;
    edit->submenu.unk_00 = 4;
    func_800924CC_jp(NULL, NULL, NULL);
    SetGameFrame(2);
}

// madeup name
void cpedit_cleanup(Game* game) {
    Game_CPEdit* edit = (Game_CPEdit*)game;
    edit->submenu.unk_00 = 0;

    mSM_submenu_dt(&edit->submenu);
    mSM_submenu_ovlptr_cleanup(&edit->submenu);
}
// madeup name
void cpedit_init(Game* game) {
    Game_CPEdit* edit = (Game_CPEdit*)game;

    edit->state.main = cpedit_main;
    edit->state.destroy = cpedit_cleanup;
    initView(&edit->view, edit->state.gfxCtx);
    edit->view.flag = 8;
    edit->unk208 = func_80804ADC_jp;
    SetGameFrame(1);
    mSM_submenu_ovlptr_init((struct Game_Play*)edit);
    mSc_data_bank_ct((struct Game_Play*)edit, &edit->bank);
    mSc_decide_exchange_bank(&edit->bank);
    mSM_submenu_ct(&edit->submenu);
    new_Matrix(&edit->state);
}
