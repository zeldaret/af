#include "graph.h"
#include "global.h"

#include "audio.h"
#include "buffers.h"
#include "cfbinfo.h"
#include "fault.h"
#include "game.h"
#include "getcurrentms.h"
#include "gfx.h"
#include "idle.h"
#include "irqmgr.h"
#include "m_debug.h"
#include "m_DLF.h"
#include "speed_meter.h"
#include "sys_ucode.h"
#include "zurumode.h"
#include "6FB340.h"
#include "6FD190.h"
#include "6FD410.h"

#include "overlays/gamestates/ovl_first_game/first_game.h"
#include "overlays/gamestates/ovl_select/m_select.h"
#include "overlays/gamestates/ovl_play/m_play.h"
#include "overlays/gamestates/ovl_second_game/second_game.h"
#include "overlays/gamestates/ovl_cpedit/m_cpedit.h"
#include "overlays/gamestates/ovl_trademark/m_trademark.h"
#include "overlays/gamestates/ovl_player_select/player_select.h"
#include "overlays/gamestates/ovl_save_menu/save_menu.h"
#include "overlays/gamestates/ovl_famicom_emu/famicom_emu.h"
#include "overlays/gamestates/ovl_prenmi/m_prenmi.h"

void graph_FaultClient(void) {
    s32 i;
    void* fb;

    FaultDrawer_DrawText(30, 100, "ShowFrameBuffer PAGE 0/1/2");

    for (i = 0; i < 3; i++) {
        fb = func_800D96E8_jp(i);
        if (fb != NULL) {
            osViSwapBuffer(fb);
            osViSetMode(&gViConfigMode);
            osViSetSpecialFeatures(gViConfigFeatures);
            osViSetXScale(gViConfigXScale);
            osViSetYScale(gViConfigYScale);
            fault_WaitForInput();
        }
    }
}

void graph_setup_double_buffer(GraphicsContext* gfxCtx) {
    GfxPool* pool = &gGfxPools[gfxCtx->gfxPoolIndex % 2];

    pool->headMagic = GFXPOOL_HEAD_MAGIC;
    pool->tailMagic = GFXPOOL_TAIL_MAGIC;

    THA_GA_ct(&gfxCtx->polyOpa, pool->polyOpaBuffer, sizeof(pool->polyOpaBuffer));
    THA_GA_ct(&gfxCtx->polyXlu, pool->polyXluBuffer, sizeof(pool->polyXluBuffer));
    THA_GA_ct(&gfxCtx->overlay, pool->overlayBuffer, sizeof(pool->overlayBuffer));
    THA_GA_ct(&gfxCtx->work, pool->workBuffer, sizeof(pool->workBuffer));
    THA_GA_ct(&gfxCtx->font, pool->fontBuffer, sizeof(pool->fontBuffer));
    THA_GA_ct(&gfxCtx->shadow, pool->shadowBuffer, sizeof(pool->shadowBuffer));
    THA_GA_ct(&gfxCtx->light, pool->lightBuffer, sizeof(pool->lightBuffer));

    gfxCtx->polyOpaBuffer = pool->polyOpaBuffer;
    gfxCtx->polyXluBuffer = pool->polyXluBuffer;
    gfxCtx->overlayBuffer = pool->overlayBuffer;
    gfxCtx->workBuffer = pool->workBuffer;
    gfxCtx->fontBuffer = pool->fontBuffer;
    gfxCtx->shadowBuffer = pool->shadowBuffer;
    gfxCtx->lightBuffer = pool->lightBuffer;

    while (gfxCtx->unk_2E4 == NULL) {
        s32 temp_s1_2 = func_800D9700_jp();

        gfxCtx->unk_2E4 = func_800D96E8_jp(gfxCtx->unk_2F3);
        if (gfxCtx->unk_2E4 == B_80146084_jp) {
            gfxCtx->unk_2E4 = NULL;
        }

        gfxCtx->unk_2F3 = ((gfxCtx->unk_2F3 + 1) < temp_s1_2) ? gfxCtx->unk_2F3 + 1 : 0;
    }

    gfxCtx->unk_008 = func_800D9750_jp();
    gfxCtx->unk_20 = 0;
}

GameStateOverlay* game_get_next_game_dlftbl(Game* game) {
    GameStateFunc init = game_get_next_game_init(game);

    if (init == first_game_init) {
        return &game_dlftbls[0];
    }
    if (init == select_init) {
        return &game_dlftbls[1];
    }
    if (init == play_init) {
        return &game_dlftbls[2];
    }
    if (init == second_game_init) {
        return &game_dlftbls[3];
    }
    if (init == cpedit_init) {
        return &game_dlftbls[4];
    }
    if (init == trademark_init) {
        return &game_dlftbls[5];
    }
    if (init == player_select_init) {
        return &game_dlftbls[6];
    }
    if (init == save_menu_init) {
        return &game_dlftbls[7];
    }
    if (init == famicom_emu_init) {
        return &game_dlftbls[8];
    }
    if (init == prenmi_init) {
        return &game_dlftbls[9];
    }

    return NULL;
}

uintptr_t graph_FaultAddrConv(uintptr_t address, UNUSED void* param) {
    uintptr_t addr = address;
    GameStateOverlay* gameStateOvl = &game_dlftbls[0];
    uintptr_t ramConv;
    void* ramStart;
    size_t diff;
    s32 i;

    for (i = 0; i < game_dlftbls_num; i++, gameStateOvl++) {
        diff = (uintptr_t)gameStateOvl->vramEnd - (uintptr_t)gameStateOvl->vramStart;
        ramStart = gameStateOvl->loadedRamAddr;
        ramConv = (uintptr_t)gameStateOvl->vramStart - (uintptr_t)ramStart;

        if (ramStart != NULL) {
            if ((addr >= (uintptr_t)ramStart) && (addr < (uintptr_t)ramStart + diff)) {
                return addr + ramConv;
            }
        }
    }
    return 0;
}

void graph_ct(GraphicsContext* gfxCtx) {
    bzero(gfxCtx, sizeof(GraphicsContext));
    gfxCtx->gfxPoolIndex = 0;
    gfxCtx->unk_2F3 = 0;
    gfxCtx->unk_25C = &osViModeNtscLan1;
    gfxCtx->unk_2EC = 66;
    gfxCtx->unk_2FC = 1.0f;
    gfxCtx->unk_300 = 1.0f;
    osCreateMesgQueue(&gfxCtx->queue, gfxCtx->msgBuff, ARRAY_COUNT(gfxCtx->msgBuff));
    SREG(33) &= ~2;
    SREG(33) &= ~1;
    zurumode_init();
    fault_AddClient(&sGraphFaultClient, (void*)graph_FaultClient, NULL, NULL);
    fault_AddressConverterAddClient(&sGraphFaultAddrConvClient, graph_FaultAddrConv, NULL);
    gfxCtx->unk_2F0 = 1;
}

void graph_dt(GraphicsContext* gfxCtx) {
    gfxCtx->unk_2F0 = 0x15;
    zurumode_cleanup();
    fault_RemoveClient(&sGraphFaultClient);
    fault_AddressConverterRemoveClient(&sGraphFaultAddrConvClient);
}

void func_800D3E14_jp(GraphicsContext* gfxCtx) {
    osSendMesg(&gfxCtx->queue, NULL, OS_MESG_BLOCK);
}

void func_800D3E40_jp(GraphicsContext* gfxCtx) {
    static s32 sRetryCount = 100;
    UNUSED s32 pad;
    OSTimer timer;
    OSMesg msg;

retry:
    osSetTimer(&timer, OS_USEC_TO_CYCLES(1000000), 0, &gfxCtx->queue, (OSMesg)666);
    osRecvMesg(&gfxCtx->queue, &msg, OS_MESG_BLOCK);
    osStopTimer(&timer);
    if ((ResetStatus < 2) && (msg == (OSMesg)666)) {
        if (sRetryCount >= 0) {
            if (1) {
                sRetryCount--;
                func_800D8644_jp();
            }
            goto retry;
        }
        fault_AddHungupAndCrashImpl("RCP is HUNG UP!!", "Oh! MY GOD!!");
    }
}

void graph_task_set00(GraphicsContext* gfxCtx) {
    UNUSED s32 pad;
    OSTask* task = &gfxCtx->task.list;
    OSScTask* scTask = &gfxCtx->task;
    uintptr_t temp_a1;
    uintptr_t temp_a0;
    uintptr_t temp_a2;

    gfxCtx->unk_2F0 = 0xD;

    func_800D3E40_jp(gfxCtx);
    gfxCtx->unk_2F0 = 0xE;

    if (ResetStatus < 2) {
        gfxCtx->unk_304 = gfxCtx->workBuffer;
        if (gfxCtx->callback != NULL) {
            gfxCtx->callback(gfxCtx, gfxCtx->callbackArg);
        }
        if (SREG(33) & 2) {
            SREG(33) &= ~2;
            task->t.type = 0;
        } else {
            task->t.type = M_GFXTASK;
            task->t.flags = OS_SC_DRAM_DLIST;

            OPEN_DISPS(gfxCtx);

            task->t.ucode_boot = ucode_GetRspBootTextStart();
            task->t.ucode_boot_size = ucode_GetRspBootTextSize();
            task->t.ucode = ucode_GetPolyTextStart();
            task->t.ucode_data = ucode_GetPolyDataStart();
            task->t.ucode_size = SP_UCODE_SIZE;
            task->t.ucode_data_size = SP_UCODE_DATA_SIZE;
            task->t.dram_stack = D_80153CC0_jp;
            task->t.dram_stack_size = sizeof(D_80153CC0_jp);

            temp_a1 = (uintptr_t)POLY_OPA_DISP;
            temp_a0 = ALIGN16(temp_a1);
            temp_a2 = ALIGN16(THA_GA_getFreeBytes(&gfxCtx->polyOpa) - temp_a0 + temp_a1 - 0xF);

            if (((uintptr_t)(D_801524C0_jp + ARRAY_COUNT(D_801524C0_jp)) - (uintptr_t)D_801524C0_jp) < temp_a2) {
                task->t.output_buff = (u64*)temp_a0;
                task->t.output_buff_size = (u64*)(temp_a0 + temp_a2);
            } else {
                task->t.output_buff = D_801524C0_jp;
                task->t.output_buff_size = D_801524C0_jp + ARRAY_COUNT(D_801524C0_jp);
            }
            CLOSE_DISPS(gfxCtx);

            task->t.data_ptr = (u64*)gfxCtx->workBuffer;

            OPEN_DISPS(gfxCtx);
            task->t.data_size = (uintptr_t)WORK_DISP - (uintptr_t)gfxCtx->workBuffer;
            CLOSE_DISPS(gfxCtx);

            task->t.yield_data_ptr = D_801530C0_jp;
            task->t.yield_data_size = sizeof(D_801530C0_jp);
        }
        scTask->next = NULL;

        if (SREG(33) & 1) {
            scTask->flags = OS_SC_NEEDS_RSP | OS_SC_NEEDS_RDP | OS_SC_LAST_TASK;
        } else {
            scTask->flags = OS_SC_NEEDS_RSP | OS_SC_NEEDS_RDP | OS_SC_SWAPBUFFER | OS_SC_LAST_TASK;
        }
        scTask->msgQ = &gfxCtx->queue;
        scTask->msg = NULL;

        {
            CfbInfo* cfb = func_800D2C10_jp();

            cfb->unk_00 = gfxCtx->unk_2E4;
            cfb->swapBuffer = NULL;
            cfb->unk_09 = game_GameFrame;
            cfb->viMode = NULL;
            if (scTask->flags & OS_SC_SWAPBUFFER) {
                cfb->swapBuffer = gfxCtx->unk_2E4;
                if (gfxCtx->unk_2F2 != 0) {
                    gfxCtx->unk_2F2 = 0;
                    cfb->viMode = gfxCtx->unk_25C;
                    cfb->viFeatures = gfxCtx->unk_2EC;
                    cfb->xScale = gfxCtx->unk_2FC;
                    cfb->yScale = gfxCtx->unk_300;
                }
                if (B_80146080_jp == 1) {
                    B_80146084_jp = cfb->swapBuffer;
                    cfb->unk_0B = 1;
                    B_80146080_jp = 2;
                }
            }

            scTask->framebuffer = cfb;
        }

        while (gfxCtx->queue.validCount != 0) {
            osRecvMesg(&gfxCtx->queue, NULL, OS_MESG_NOBLOCK);
        }

        if (ResetStatus < 2) {
            gfxCtx->unk_064 = &B_80145DB8_jp;
            osSendMesg(&B_80145DB8_jp, (OSMesg)scTask, OS_MESG_BLOCK);
            func_800D85EC_jp();
        }
    }
}

u32 graph_draw_finish(GraphicsContext* gfxCtx) {
    u32 err;
    UNUSED s32 pad[2];

    OPEN_DISPS(gfxCtx);

    gSPBranchList(WORK_DISP++, gfxCtx->polyOpaBuffer);
    gSPBranchList(POLY_OPA_DISP++, gfxCtx->shadowBuffer);
    gSPBranchList(SHADOW_DISP++, gfxCtx->polyXluBuffer);
    gSPBranchList(POLY_XLU_DISP++, gfxCtx->lightBuffer);
    gSPBranchList(LIGHT_DISP++, gfxCtx->fontBuffer);
    gSPBranchList(FONT_DISP++, gfxCtx->overlayBuffer);

    gDPPipeSync(OVERLAY_DISP++);
    gDPFullSync(OVERLAY_DISP++);
    gSPEndDisplayList(OVERLAY_DISP++);

    CLOSE_DISPS(gfxCtx);

    err = false;
    {
        GfxPool* pool = &gGfxPools[gfxCtx->gfxPoolIndex & 1];

        if (pool->headMagic != GFXPOOL_HEAD_MAGIC) {
            fault_AddHungupAndCrash("../graph.c", 606);
        }
        if (pool->tailMagic != GFXPOOL_TAIL_MAGIC) {
            err = true;
            fault_AddHungupAndCrash("../graph.c", 614);
        }
    }

    if (THA_GA_isCrash(&gfxCtx->polyOpa)) {
        err = true;
    }
    if (THA_GA_isCrash(&gfxCtx->polyXlu)) {
        err = true;
    }
    if (THA_GA_isCrash(&gfxCtx->overlay)) {
        err = true;
    }
    if (THA_GA_isCrash(&gfxCtx->font)) {
        err = true;
    }
    if (THA_GA_isCrash(&gfxCtx->shadow)) {
        err = true;
    }
    if (THA_GA_isCrash(&gfxCtx->light)) {
        err = true;
    }

    return err;
}

void graph_main(GraphicsContext* gfxCtx, Game* game) {
    game->unk_A4 = false;
    graph_setup_double_buffer(gfxCtx);
    game_get_controller(game);
    game->unk_9E = false;
    gfxCtx->unk_2F0 = 4;

    game_main(game);

    gfxCtx->unk_2F0 = 0xB;

    if ((ResetStatus < 2) && !game->unk_9E && !graph_draw_finish(gfxCtx)) {
        gfxCtx->unk_2F0 = 0xC;

        graph_task_set00(gfxCtx);
        gfxCtx->unk_2F0 = 0xF;

        gfxCtx->gfxPoolIndex++;
        if (SREG(33) & 1) {
            SREG(33) &= ~1;
        } else {
            gfxCtx->unk_2E4 = NULL;
        }
    }
    if (SREG(20) < 2) {
        gfxCtx->unk_2F0 = 0x10;

        sAdo_GameFrame();
        gfxCtx->unk_2F0 = 0x11;
    }

    func_800D93F4_jp();

    if ((ResetStatus == 1) && !game->unk_A4) {
        STOP_GAMESTATE(game);
        SET_NEXT_GAMESTATE(game, prenmi_init, sizeof(Game_Prenmi));
    }
}

void graph_proc(UNUSED void* arg) {
    s32 state;
    GameStateOverlay* nextOvl = &game_dlftbls[0];
    GameStateOverlay* ovl;
    size_t size;
    Game* game;
    char msg[80];

    graph_ct(&graph_class);

    while (nextOvl != NULL) {
        ovl = nextOvl;

        Overlay_LoadGameState(ovl);

        state = 2;
        size = ovl->instanceSize;
        game = malloc(size);
        game_class_p = game;
        if (game == NULL) {
            sprintf(msg, "CLASS SIZE= %d bytes", size);
            fault_AddHungupAndCrashImpl("GAME CLASS MALLOC FAILED", msg);
        }
        bzero(game, size);
        graph_class.unk_2F0 = state;

        state = 3;
        game_ct(game, ovl->init, &graph_class);
        graph_class.unk_2F0 = state;

        state = 0x12;
        while (game_is_doing(game)) {
            graph_main(&graph_class, game);
            B_80145FF8_jp = GetCurrentMilliseconds();
        }
        nextOvl = game_get_next_game_dlftbl(game);
        graph_class.unk_2F0 = state;

        state = 0x13;
        func_800D79F4_jp();
        graph_class.unk_2F0 = state;

        state = 0x14;
        game_dt(game);
        graph_class.unk_2F0 = state;

        free(game);
        game_class_p = NULL;
        Overlay_FreeGameState(ovl);
    }

    graph_dt(&graph_class);
}
