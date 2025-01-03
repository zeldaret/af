#include "cfbinfo.h"
#include "global.h"

#include "libc64/sleep.h"
#include "libu64/debug.h"

#include "idle.h"
#include "irqmgr.h"
#include "viconfig.h"
#include "6FD410.h"

cfbStruct B_80144FC0_jp[3];

cfbStruct* func_800D2C10_jp(void) {
    s32 i;
    cfbStruct* cfb;
    s32 attempts = 0;

retry:
    i = 0;
    while(true) {
        cfb = &B_80144FC0_jp[i];
        if (cfb->unk_08 == 0) {
            break;
        }

        i++;
        if (i == ARRAY_COUNT(B_80144FC0_jp)) {
            if (attempts++ > 10000) {
                _dbg_hungup("../cfbinfo.c", 0x27);
            }
            usleep(100);
            (void)"";
            goto retry;
        }
    }
    bzero(cfb, sizeof(cfbStruct));
    cfb->unk_08 = 1;

    (void)"(予約)";
    return cfb;
}

void func_800D2CB4_jp(cfbStruct* cfb) {
    if (cfb->unk_0B != 0) {
        cfb->unk_0B = 0;
        B_80146080_jp = 3;
    }
    cfb->unk_08 = 0;
}

void func_800D2CDC_jp(cfbStruct* cfb) {
    if ((ResetStatus < 2) && (cfb->unk_04 != NULL)) {
        osViSwapBuffer(cfb->unk_04);
        cfb->unk_0A = cfb->unk_09;
        cfb->unk_08 = 4;
        if (cfb->unk_0C != NULL) {
            gViConfigMode = *cfb->unk_0C;
            gViConfigFeatures = cfb->unk_10;
            gViConfigXScale = cfb->unk_14;
            gViConfigYScale = cfb->unk_18;
            if (gViConfigBlack == 0) {
                osViSetMode(cfb->unk_0C);
                osViSetSpecialFeatures(cfb->unk_10);
                osViSetXScale(cfb->unk_14);
                osViSetYScale(cfb->unk_18);
            }
            if (gViConfigBlack == 0) {}
        }
    } else {
        func_800D2CB4_jp(cfb);
    }
}
