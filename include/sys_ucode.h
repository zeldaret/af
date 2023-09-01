#ifndef SYS_UCODE_H
#define SYS_UCODE_H

#include "ultra64.h"

extern s64 gspF3DZEX2_NoN_PosLight_fifoTextStart[];
extern s64 gspF3DZEX2_NoN_PosLight_fifoDataStart[];

extern s64 gspS2DEX2_fifoTextStart[];
extern s64 gspS2DEX2_fifoDataStart[];



s64* ucode_GetRspBootTextStart(void);
size_t ucode_GetRspBootTextSize(void);
s64* ucode_GetPolyTextStart(void);
s64* ucode_GetPolyDataStart(void);
s64* ucode_GetSpriteTextStart(void);
s64* ucode_GetSpireDataStart(void);

#endif
