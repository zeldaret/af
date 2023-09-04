#include "global.h"

#include "sys_ucode.h"

s64* poly_tbl[] = { gspF3DZEX2_NoN_PosLight_fifoTextStart, gspF3DZEX2_NoN_PosLight_fifoDataStart };

s64* sprite_tbl[] = { gspS2DEX2_fifoTextStart, gspS2DEX2_fifoDataStart };

s64* ucode_GetRspBootTextStart() {
    return rspbootTextStart;
}

size_t ucode_GetRspBootTextSize() {
    return ((uintptr_t)rspbootTextEnd - (uintptr_t)rspbootTextStart);
}

s64* ucode_GetPolyTextStart() {
    return poly_tbl[0];
}

s64* ucode_GetPolyDataStart() {
    return poly_tbl[1];
}

s64* ucode_GetSpriteTextStart() {
    return sprite_tbl[0];
}

s64* ucode_GetSpriteDataStart() {
    return sprite_tbl[1];
}
