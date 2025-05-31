#include "cfbinfo.h"

#include "libc/stdbool.h"
#include "libc64/sleep.h"
#include "libu64/debug.h"

#include "idle.h"
#include "irqmgr.h"
#include "macros.h"
#include "viconfig.h"
#include "6FD410.h"

CfbInfo sCfbInfos[3];

CfbInfo* func_800D2C10_jp(void) {
    s32 i;
    CfbInfo* cfb;
    s32 attempts = 0;

retry:
    i = 0;
    while (true) {
        cfb = &sCfbInfos[i];
        if (cfb->state == 0) {
            break;
        }

        i++;
        if (i == ARRAY_COUNT(sCfbInfos)) {
            if (attempts++ > 10000) {
                _dbg_hungup("../cfbinfo.c", 0x27);
            }
            usleep(100);
            (void)"";
            goto retry;
        }
    }
    bzero(cfb, sizeof(CfbInfo));
    cfb->state = 1;

    // (reservation)
    (void)"(予約)";
    return cfb;
}

void func_800D2CB4_jp(CfbInfo* cfb) {
    if (cfb->unk_0B != 0) {
        cfb->unk_0B = 0;
        B_80146080_jp = 3;
    }
    cfb->state = 0;
}

void func_800D2CDC_jp(CfbInfo* cfb) {
    if ((ResetStatus < 2) && (cfb->swapBuffer != NULL)) {
        osViSwapBuffer(cfb->swapBuffer);
        cfb->unk_0A = cfb->unk_09;
        cfb->state = 4;
        if (cfb->viMode != NULL) {
            gViConfigMode = *cfb->viMode;
            gViConfigFeatures = cfb->viFeatures;
            gViConfigXScale = cfb->xScale;
            gViConfigYScale = cfb->yScale;
            if (!gViConfigBlack) {
                osViSetMode(cfb->viMode);
                osViSetSpecialFeatures(cfb->viFeatures);
                osViSetXScale(cfb->xScale);
                osViSetYScale(cfb->yScale);
            }
            if (!gViConfigBlack) {}
        }
    } else {
        func_800D2CB4_jp(cfb);
    }
}
