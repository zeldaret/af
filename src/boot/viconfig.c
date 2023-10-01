#include "viconfig.h"
#include "idle.h"
#include "irqmgr.h"

u8 gViConfigBlackNext;
u8 gViConfigBlack;

void ViConfig_UpdateVi(u32 black) {
    if ((black || (ResetStatus == 0)) && ((black != gViConfigBlack) || (black != gViConfigBlackNext))) {
        if (black) {
            if (osTvType == OS_TV_PAL) {
                osViSetMode(&osViModePalLan1);
            } else {
                osViSetMode(&osViModeNtscLan1);
            }

            if (gViConfigYScale == 1.0f) {
                osViBlack(1);
            } else {
                osViSetYScale(1.0f);
            }
        } else {
            osViSetMode(&gViConfigMode);

            if (gViConfigFeatures != 0) {
                osViSetSpecialFeatures(gViConfigFeatures);
            }

            if (gViConfigXScale != 1.0f) {
                osViSetXScale(gViConfigXScale);
            }

            if (gViConfigYScale != 1.0f) {
                osViSetYScale(gViConfigYScale);
            }
        }
        gViConfigBlackNext = black;
    }
}

void ViConfig_UpdateBlack(void) {
    if (gViConfigBlackNext != gViConfigBlack) {
        osViBlack(gViConfigBlackNext);
        gViConfigBlack = gViConfigBlackNext;
    }
}
