#include "main.h"
#include "zurumode.h"
#include "fault.h"
#include "code_variables.h"
#include "macros.h"
#include "game.h"
#include "audioMgr.h"
#include "graph.h"
#include "m_debug.h"
#include "getcurrentms.h"

void func_800D64E0_jp(void) {
    u32 baseTime;
    u32 graphTime;
    u32 audioTime;
    u32 graphReg;
    u32 audioReg;
    u8 unk9C;
    u8 unk9D;

    if ((zurumode_flag != 0) && (fault_class.msgId == 0) && (D_8010F3E8_jp != 0)) {

        baseTime = GetCurrentMilliseconds();

        graphTime = (B_80145FF8_jp != 0) ? (baseTime - B_80145FF8_jp) : 0;
        audioTime = (B_80145FFC_jp != 0) ? (baseTime - B_80145FFC_jp) : 0;

        if (SREG(31) != 0) {
            graphReg = SREG(31) < graphTime;
            audioReg = SREG(31) < audioTime;
        } else {
            graphReg = (graphTime >= 3001);
            audioReg = (audioTime >= 3001);
        }

        if ((graphReg != 0) || (audioReg != 0)) {
            FaultDrawer_SetDrawerFB(osViGetCurrentFramebuffer(), SCREEN_WIDTH, SCREEN_HEIGHT);
            FaultDrawer_SetForeColor(65535);
            FaultDrawer_SetBackColor(32769);
            FaultDrawer_SetCharPad(0, 0);
            if (graphReg != 0) {
                unk9D = (game_class_p != NULL) ? game_class_p->unk_9D : 0;

                unk9C = (game_class_p != NULL) ? game_class_p->unk_9C : 0;

                FaultDrawer_DrawText(24, 16, "GRAPH INF.LOOP %2d %3d %3d %6lu", B_80145370_jp, unk9D, unk9C, graphTime);
                fault_DrawStackTrace(&graphThread, 0x20, 0x1A, 0xA);
            }
            if (audioReg != 0) {
                FaultDrawer_DrawText(24, 126, "AUDIO INF.LOOP %2d %3d     %6lu", audiomgr_class.unk_28A, D_80113854_jp,
                                     audioTime);
                fault_DrawStackTrace(&audiomgr_class.thread, 0x20, 0x88, 0xA);
            }
            FaultDrawer_WritebackFBDCache();
        }
    }
}

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/main/func_800D66D0_jp.s")
