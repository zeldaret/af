#include "cfbinfo.h"
#include "global.h"

#include "idle.h"
#include "irqmgr.h"
#include "viconfig.h"

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/cfbinfo/func_800D2C10_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/cfbinfo/func_800D2CB4_jp.s")

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
