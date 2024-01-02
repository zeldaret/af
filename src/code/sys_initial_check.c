/**
 * @file sys_initial_check.c
 * Functions for checking the TV type (PAL/NTSC/MPAL), and printing an error message to the screen if it's not NTSC
 */

#include "color.h"
#include "macros.h"
#include "m_std_dma.h"
#include "segment_symbols.h"
#include "fault.h"

void Check_WriteRGBA16Pixel(u16* buffer, u32 x, u32 y, u32 value) {
    if (value & RGBA16_PIXEL_OPAQUE) {
        (&buffer[x])[y * SCREEN_WIDTH] = value;
    }
}

void Check_WriteI4Pixel(u16* buffer, u32 x, u32 y, u32 value) {
    Check_WriteRGBA16Pixel(buffer, x, y, value * GPACK_RGBA5551(16, 16, 16, 0) + GPACK_RGBA5551(12, 12, 12, 1));
}

void Check_DrawI4Texture(u16* buffer, s32 x, s32 y, s32 width, s32 height, u8* texture) {
    s32 v;
    s32 u;
    u8 pixelPair;
    u8* pixelPairPointer = texture;

    for (v = 0; v < height; v++) {
        for (u = 0; u < width; u += 2, pixelPairPointer++) {
            pixelPair = *pixelPairPointer;
            Check_WriteI4Pixel(buffer, x + u, y + v, pixelPair >> 4);
            pixelPair = *pixelPairPointer;
            Check_WriteI4Pixel(buffer, x + u + 1, y + v, pixelPair & 0xF);
        }
    }
}

void Check_ClearRGBA16(u16* buffer) {
    u32 x;
    u32 y;

    for (y = 0; y < SCREEN_HEIGHT; y++) {
        for (x = 0; x < SCREEN_WIDTH; x++) {
            Check_WriteRGBA16Pixel(buffer, x, y, 1);
        }
    }
}

#define ERROR_TEXTURE_WIDTH 208
#define ERROR_TEXTURE_HEIGHT 16
#define ERROR_TEXTURE_SIZE (ERROR_TEXTURE_WIDTH * ERROR_TEXTURE_HEIGHT / 2)
#define ERROR_TEXTURE_VRAM (u8*)((uintptr_t)FAULT_FB_ADDRESS - ERROR_TEXTURE_SIZE)
u8 Check_ErrorTextureYCoords[] = { 112, 0 };

void Check_DrawRegionLockErrorMessage(void) {
    s32 i;

    DmaMgr_RequestSyncDebug(ERROR_TEXTURE_VRAM, SEGMENT_ROM_START(locerrmsg), SEGMENT_VRAM_SIZE(locerrmsg),
                            "../sys_initial_check.c", 130);
    Check_ClearRGBA16(FAULT_FB_ADDRESS);
    for (i = 0; i < 1; i++) {
        Check_DrawI4Texture(FAULT_FB_ADDRESS, 56, Check_ErrorTextureYCoords[i], ERROR_TEXTURE_WIDTH,
                            ERROR_TEXTURE_HEIGHT, ERROR_TEXTURE_VRAM + i * ERROR_TEXTURE_SIZE);
    }
    osWritebackDCacheAll();
    osViSwapBuffer(FAULT_FB_ADDRESS);
    osViBlack(false);
}

void Check_RegionIsSupported(void) {
    s32 regionSupported = false;

    if (osTvType == OS_TV_NTSC) {
        regionSupported = true;
    }

    if (!regionSupported) {
        Check_DrawRegionLockErrorMessage();
        osDestroyThread(NULL);
        while (true) {};
    }
}
