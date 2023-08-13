#ifndef LIBU64_GFX_PRINT_H
#define LIBU64_GFX_PRINT_H

#include "ultra64.h"
#include "color.h"

typedef void* (*PrintCallback)(void*, const u8*, s32);
typedef struct gfxprint {
    /* 0x00 */ PrintCallback proutFunc; /* Current print out func */
    /* 0x04 */ Gfx* gListp; /* Current display list to write text to */
    /* 0x08 */ u16 positionX; /* Display coords (sub-pixel units) */
    /* 0x0A */ u16 positionY; /* Display coords (sub-pixel units) */
    /* 0x0C */ u16 offsetX; /* Display offset */
    /* 0x0E */ u8 offsetY; /* Display offset */
    /* 0x0F */ u8 flags; /* 1: Kana mode -> 0: Katakana/1: Hiragana
                 2: Gradient displayed
                 4: Shadow displayed
                 8: Attribute changed
                 64: Low-res -> high-res conversion
                 128: Opened state */
    /* 0x10 */ Color_RGBA8 color; /* Current font color */
    /* 0x14 */ char dummy[0x1C];
} gfxprint; // size = 0x30

// void gfxprint_setup();
void gfxprint_color(gfxprint* this, u8 r, u8 g, u8 b, u8 a);
// void gfxprint_locate();
void gfxprint_locate8x8(gfxprint* this, s32 arg1, s32 arg2);
// void gfxprint_setoffset();
// void gfxprint_putc1();
// void gfxprint_putc();
// void gfxprint_write();
// void gfxprint_puts();
// void gfxprint_prout();
void gfxprint_init(gfxprint* this);
void gfxprint_cleanup(gfxprint* this);
void gfxprint_open(gfxprint* this, Gfx* gfx);
Gfx* gfxprint_close(gfxprint* this);
// void gfxprint_vprintf();
void gfxprint_printf(gfxprint* this, const char* fmt, ...);

// extern UNK_TYPE gfxprint_moji_tlut;
// extern UNK_TYPE gfxprint_rainbow_tlut;
// extern UNK_TYPE gfxprint_rainbow_txtr;
// extern UNK_TYPE gfxprint_font;

// extern UNK_TYPE __gfxprint_default_flags;

#endif
