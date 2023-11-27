#include "color.h"
#include "macros.h"
#include "z_std_dma.h"

// #pragma GLOBAL_ASM("asm/jp/nonmatchings/code/sys_initial_check/func_800D9890_jp.s")
//Check_WriteRGBA16Pixel
void func_800D9890_jp(u16* buffer, u32 x, u32 y, u32 value)
{
    if (value & RGBA16_PIXEL_OPAQUE)
    {
        (&buffer[x])[y * SCREEN_WIDTH] = value;
    }
}

// #pragma GLOBAL_ASM("asm/jp/nonmatchings/code/sys_initial_check/func_800D98C0_jp.s")
//Check_WriteI4Pixel
void func_800D98C0_jp(u16* arg0, u32 arg1, u32 arg2, u32 arg3)
{
    //todo this uses macros
    func_800D9890_jp(arg0, arg1, arg2, (arg3 * 0x1084) + 0x843);
}

// #pragma GLOBAL_ASM("asm/jp/nonmatchings/code/sys_initial_check/func_800D9900_jp.s")
//Check_DrawI4Texture
void func_800D9900_jp(u16* buffer, s32 x, s32 y, s32 width, s32 height, u8* texture)
{
    s32 v;
    s32 u;
    u8 pixelPair;
    u8* pixelPairPointer = texture;

    for (v = 0; v < height; v++)
    {
        for (u = 0; u < width; u += 2, pixelPairPointer++)
        {
            pixelPair = *pixelPairPointer;
            func_800D98C0_jp(buffer, x + u, y + v, pixelPair >> 4);
            pixelPair = *pixelPairPointer;
            func_800D98C0_jp(buffer, x + u + 1, y + v, pixelPair & 0xF);
        } 
    }
}

// #pragma GLOBAL_ASM("asm/jp/nonmatchings/code/sys_initial_check/func_800D99F0_jp.s")
//Check_ClearRGBA16
void func_800D99F0_jp(u16* buffer)
{
    u32 x;
    u32 y;

    for (y = 0; y < SCREEN_HEIGHT; y++)
    {
        for (x = 0; x < SCREEN_WIDTH; x++)
        {
            func_800D9890_jp(buffer, x, y, 1);
        }
    }
}

// #pragma GLOBAL_ASM("asm/jp/nonmatchings/code/sys_initial_check/func_800D9A6C_jp.s")
#define FAULT_FB_ADDRESS (void*)((PHYS_TO_K0(0x400000) - SCREEN_HEIGHT * SCREEN_WIDTH * sizeof(u16)))

#define ERROR_TEX_WIDTH 208
#define ERROR_TEX_HEIGHT 16
#define ERROR_TEX_SIZE (ERROR_TEX_WIDTH * ERROR_TEX_HEIGHT / 2)
#define ERROR_TEX_VRAM (u8*)((uintptr_t)FAULT_FB_ADDRESS - ERROR_TEX_SIZE)


// #pragma GLOBAL_ASM("asm/jp/nonmatchings/code/sys_initial_check/func_800D9A6C_jp.s")
extern u8 D_1000680[];
extern u8 D_8010F450_jp[1];
extern u64 D_A21000[]; // error texture
extern u8 D_01000000[];

//Check_DrawRegionLockErrorMessage
void func_800D9A6C_jp(void)
{
    s32 i;

    DmaMgr_RequestSyncDebug(ERROR_TEX_VRAM, D_A21000, D_1000680 - D_01000000, "../sys_initial_check.c", 130);
    func_800D99F0_jp(FAULT_FB_ADDRESS);
    for (i = 0; i < 1; i++)
    {
        func_800D9900_jp(FAULT_FB_ADDRESS, 56, D_8010F450_jp[i], ERROR_TEX_WIDTH, ERROR_TEX_HEIGHT, ERROR_TEX_VRAM + i * ERROR_TEX_SIZE);
    }
    osWritebackDCacheAll();
    osViSwapBuffer(FAULT_FB_ADDRESS);
    osViBlack(false);
}


// #pragma GLOBAL_ASM("asm/jp/nonmatchings/code/sys_initial_check/func_800D9B44_jp.s")
//Check_RegionIsSupported
void func_800D9A6C_jp(void);

void func_800D9B44_jp(void)
{
    s32 regionSupported = false;

    if (osTvType == OS_TV_NTSC)
    {
        regionSupported = true;
    }

    if (!regionSupported)
    {
        func_800D9A6C_jp();
        osDestroyThread(NULL);
        while (true) {};
    }
}

