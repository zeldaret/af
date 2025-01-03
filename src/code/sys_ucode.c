#include "global.h"

#include "sys_ucode.h"

u64* poly_tbl[] = { gspF3DZEX2_NoN_PosLight_fifoTextStart, gspF3DZEX2_NoN_PosLight_fifoDataStart };

u64* sprite_tbl[] = { gspS2DEX2_fifoTextStart, gspS2DEX2_fifoDataStart };

u64* ucode_GetRspBootTextStart() {
    return (u64*)rspbootTextStart;
}

size_t ucode_GetRspBootTextSize() {
    return ((uintptr_t)rspbootTextEnd - (uintptr_t)rspbootTextStart);
}

u64* ucode_GetPolyTextStart() {
    return poly_tbl[0];
}

u64* ucode_GetPolyDataStart() {
    return poly_tbl[1];
}

u64* ucode_GetSpriteTextStart() {
    return sprite_tbl[0];
}

u64* ucode_GetSpriteDataStart() {
    return sprite_tbl[1];
}
