/**
 * @file fault_drawer.c
 *
 * Implements routines for drawing text with a fixed font directly to a framebuffer, used in displaying
 * the crash screen implemented by fault.c
 */
#include "fault.h"
#include "macros.h"
#include "libc64/aprintf.h"
#include "libc/stdarg.h"
#include "libc/stdbool.h"
#include "terminal.h"

typedef struct {
    /* 0x00 */ u16* fb;
    /* 0x04 */ u16 w;
    /* 0x06 */ u16 h;
    /* 0x08 */ u16 yStart;
    /* 0x0A */ u16 yEnd;
    /* 0x0C */ u16 xStart;
    /* 0x0E */ u16 xEnd;
    /* 0x10 */ u16 foreColor;
    /* 0x12 */ u16 backColor;
    /* 0x14 */ u16 cursorX;
    /* 0x16 */ u16 cursorY;
    /* 0x18 */ const u32* fontData;
    /* 0x1C */ u8 charW;
    /* 0x1D */ u8 charH;
    /* 0x1E */ s8 charWPad;
    /* 0x1F */ s8 charHPad;
    /* 0x20 */ u16 printColors[10];
    /* 0x34 */ u8 escCode; // bool
    /* 0x35 */ u8 osSyncPrintfEnabled;
    /* 0x38 */ void (*inputCallback)(void);
} FaultDrawer; // size = 0x3C

// TODO: Extract sFaultDrawerFont
extern const u32 sFaultDrawerFont[];
#pragma GLOBAL_ASM("asm/jp/nonmatchings/boot/fault_drawer/sFaultDrawerFont.s")

#define FAULT_DRAWER_CURSOR_X 22
#define FAULT_DRAWER_CURSOR_Y 16

FaultDrawer sFaultDrawerDefault = {
    (u16*)(PHYS_TO_K0(0x400000) - sizeof(u16[SCREEN_HEIGHT][SCREEN_WIDTH])),
    SCREEN_WIDTH,
    SCREEN_HEIGHT,
    FAULT_DRAWER_CURSOR_Y,
    SCREEN_HEIGHT - FAULT_DRAWER_CURSOR_Y - 1,
    FAULT_DRAWER_CURSOR_X,
    SCREEN_WIDTH - FAULT_DRAWER_CURSOR_X - 1,
    GPACK_RGBA5551(255, 255, 255, 1),
    GPACK_RGBA5551(0, 0, 0, 0),
    FAULT_DRAWER_CURSOR_X,
    FAULT_DRAWER_CURSOR_Y,
    sFaultDrawerFont,
    8,
    8,
    0,
    0,
    {
        GPACK_RGBA5551(0, 0, 0, 1),
        GPACK_RGBA5551(255, 0, 0, 1),
        GPACK_RGBA5551(0, 255, 0, 1),
        GPACK_RGBA5551(255, 255, 0, 1),
        GPACK_RGBA5551(0, 0, 255, 1),
        GPACK_RGBA5551(255, 0, 255, 1),
        GPACK_RGBA5551(0, 255, 255, 1),
        GPACK_RGBA5551(255, 255, 255, 1),
        GPACK_RGBA5551(120, 120, 120, 1),
        GPACK_RGBA5551(176, 176, 176, 1),
    },
    false,
    false,
    NULL,
};

FaultDrawer sFaultDrawer;

void FaultDrawer_SetOsSyncPrintfEnabled(u32 enabled) {
    sFaultDrawer.osSyncPrintfEnabled = enabled;
}

void FaultDrawer_DrawRecImpl(s32 xStart, s32 yStart, s32 xEnd, s32 yEnd, u16 color) {
    u16* fb;
    s32 x;
    s32 y;
    s32 xDiff = sFaultDrawer.w - xStart;
    s32 yDiff = sFaultDrawer.h - yStart;
    s32 xSize = xEnd - xStart + 1;
    s32 ySize = yEnd - yStart + 1;

    if ((xDiff > 0) && (yDiff > 0)) {
        if (xDiff < xSize) {
            xSize = xDiff;
        }

        if (yDiff < ySize) {
            ySize = yDiff;
        }

        fb = sFaultDrawer.fb + sFaultDrawer.w * yStart + xStart;
        for (y = 0; y < ySize; y++) {
            for (x = 0; x < xSize; x++) {
                *fb++ = color;
            }
            fb += sFaultDrawer.w - xSize;
        }

        osWritebackDCacheAll();
    }
}

void FaultDrawer_DrawChar(char c) {
    FaultDrawer* faultDrawer = &sFaultDrawer;
    s32 x;
    s32 y;
    u32 data;
    s32 cursorX = sFaultDrawer.cursorX;
    s32 cursorY = sFaultDrawer.cursorY;
    s32 shift = c % 4;
    const u32* dataPtr = &faultDrawer->fontData[((c / 8) * 16) + ((c & 4) >> 2)];
    u16* fb = sFaultDrawer.fb + (sFaultDrawer.w * cursorY) + cursorX;

    if ((sFaultDrawer.xStart <= cursorX) && ((sFaultDrawer.charW + cursorX - 1) <= sFaultDrawer.xEnd) &&
        (sFaultDrawer.yStart <= cursorY) && ((sFaultDrawer.charH + cursorY - 1) <= sFaultDrawer.yEnd)) {
        for (y = 0; y < sFaultDrawer.charH; y++) {
            u32 mask = 0x10000000 << shift;

            data = *dataPtr;
            for (x = 0; x < sFaultDrawer.charW; x++) {
                if (mask & data) {
                    fb[x] = sFaultDrawer.foreColor;
                } else if (sFaultDrawer.backColor & 1) {
                    fb[x] = sFaultDrawer.backColor;
                }
                mask >>= 4;
            }
            fb += sFaultDrawer.w;
            dataPtr += 2;
        }
    }
}

s32 FaultDrawer_ColorToPrintColor(u16 color) {
    s32 i;

    for (i = 0; i < ARRAY_COUNT(sFaultDrawer.printColors); i++) {
        if (color == sFaultDrawer.printColors[i]) {
            return i;
        }
    }
    return -1;
}

void FaultDrawer_UpdatePrintColor(void) {
    s32 idx;

    if (sFaultDrawer.osSyncPrintfEnabled) {
        osSyncPrintf(VT_RST);

        idx = FaultDrawer_ColorToPrintColor(sFaultDrawer.foreColor);
        if (idx >= 0 && idx < ARRAY_COUNT(sFaultDrawer.printColors) - 2) {
            osSyncPrintf(VT_SGR("3%d"), idx);
        }

        idx = FaultDrawer_ColorToPrintColor(sFaultDrawer.backColor);
        if (idx >= 0 && idx < ARRAY_COUNT(sFaultDrawer.printColors) - 2) {
            osSyncPrintf(VT_SGR("4%d"), idx);
        }
    }
}

void FaultDrawer_SetForeColor(u16 color) {
    sFaultDrawer.foreColor = color;
    FaultDrawer_UpdatePrintColor();
}

void FaultDrawer_SetBackColor(u16 color) {
    sFaultDrawer.backColor = color;
    FaultDrawer_UpdatePrintColor();
}

void FaultDrawer_SetFontColor(u16 color) {
    FaultDrawer_SetForeColor(color | 1); // force alpha to be set
}

void FaultDrawer_SetCharPad(s8 padW, s8 padH) {
    sFaultDrawer.charWPad = padW;
    sFaultDrawer.charHPad = padH;
}

void FaultDrawer_SetCursor(s32 x, s32 y) {
    if (sFaultDrawer.osSyncPrintfEnabled) {
        osSyncPrintf(VT_CUP("%d", "%d"), (y - sFaultDrawer.yStart) / (sFaultDrawer.charH + sFaultDrawer.charHPad),
                     (x - sFaultDrawer.xStart) / (sFaultDrawer.charW + sFaultDrawer.charWPad));
    }
    sFaultDrawer.cursorX = x;
    sFaultDrawer.cursorY = y;
}

void FaultDrawer_FillScreen(void) {
    if (sFaultDrawer.osSyncPrintfEnabled) {
        osSyncPrintf(VT_CLS);
    }

    FaultDrawer_DrawRecImpl(sFaultDrawer.xStart, sFaultDrawer.yStart, sFaultDrawer.xEnd, sFaultDrawer.yEnd,
                            sFaultDrawer.backColor | 1);
    FaultDrawer_SetCursor(sFaultDrawer.xStart, sFaultDrawer.yStart);
}

char* FaultDrawer_PrintCallback(char* arg, const char* str, size_t count) {
    for (; count != 0; count--, str++) {
        s32 curXStart;
        s32 curXEnd;

        if (sFaultDrawer.escCode) {
            sFaultDrawer.escCode = false;
            if (*str > '0' && *str <= '9') {
                FaultDrawer_SetForeColor(sFaultDrawer.printColors[*str - '0']);
            }

            curXStart = sFaultDrawer.cursorX;
            curXEnd = sFaultDrawer.xEnd - sFaultDrawer.charW;
        } else {
            switch (*str) {
                case '\n':
                    if (sFaultDrawer.osSyncPrintfEnabled) {
                        osSyncPrintf("\n");
                    }

                    sFaultDrawer.cursorX = sFaultDrawer.w;
                    curXStart = sFaultDrawer.cursorX;
                    curXEnd = sFaultDrawer.xEnd - sFaultDrawer.charW;
                    break;

                case FAULT_ESC:
                    sFaultDrawer.escCode = true;
                    curXStart = sFaultDrawer.cursorX;
                    curXEnd = sFaultDrawer.xEnd - sFaultDrawer.charW;
                    break;

                default:
                    if (sFaultDrawer.osSyncPrintfEnabled) {
                        osSyncPrintf("%c", *str);
                    }

                    FaultDrawer_DrawChar(*str);
                    sFaultDrawer.cursorX += sFaultDrawer.charW + sFaultDrawer.charWPad;

                    curXStart = sFaultDrawer.cursorX;
                    curXEnd = sFaultDrawer.xEnd - sFaultDrawer.charW;
                    break;
            }
        }

        if (curXEnd <= curXStart) {
            sFaultDrawer.cursorX = sFaultDrawer.xStart;
            sFaultDrawer.cursorY += sFaultDrawer.charH + sFaultDrawer.charHPad;
            if (sFaultDrawer.yEnd - sFaultDrawer.charH <= sFaultDrawer.cursorY) {
                if (sFaultDrawer.inputCallback) {
                    sFaultDrawer.inputCallback();
                    FaultDrawer_FillScreen();
                }
                sFaultDrawer.cursorY = sFaultDrawer.yStart;
            }
        }
    }
    osWritebackDCacheAll();

    return arg;
}

const char D_8003E280[] = "(null)";

s32 FaultDrawer_VPrintf(const char* fmt, va_list args) {
    return _Printf(FaultDrawer_PrintCallback, (void*)&sFaultDrawer, fmt, args);
}

s32 FaultDrawer_Printf(const char* fmt, ...) {
    s32 ret;
    va_list args;
    va_start(args, fmt);

    ret = FaultDrawer_VPrintf(fmt, args);

    va_end(args);
    return ret;
}

void FaultDrawer_DrawText(s32 x, s32 y, const char* fmt, ...) {
    va_list args;
    va_start(args, fmt);

    FaultDrawer_SetCursor(x, y);
    FaultDrawer_VPrintf(fmt, args);

    va_end(args);
}

void FaultDrawer_SetDrawerFB(void* fb, u16 w, u16 h) {
    sFaultDrawer.fb = fb;
    sFaultDrawer.w = w;
    sFaultDrawer.h = h;
}

void FaultDrawer_SetInputCallback(void (*callback)(void)) {
    sFaultDrawer.inputCallback = callback;
}

void FaultDrawer_WritebackFBDCache(void) {
    osWritebackDCache(sFaultDrawer.fb, sFaultDrawer.w * sFaultDrawer.h * sizeof(u16));
}

void FaultDrawer_Init(void) {
    bcopy(&sFaultDrawerDefault, &sFaultDrawer, sizeof(FaultDrawer));
    sFaultDrawer.fb = (u16*)(PHYS_TO_K0(osMemSize) - sizeof(u16[SCREEN_HEIGHT][SCREEN_WIDTH]));
}
