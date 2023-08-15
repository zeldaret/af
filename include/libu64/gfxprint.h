#ifndef LIBU64_GFX_PRINT_H
#define LIBU64_GFX_PRINT_H

#include "ultra64.h"
#include "color.h"

typedef struct gfxprint {
    /* 0x00 */ char unk00[0x30];
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
