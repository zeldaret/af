#ifndef LIBU64_GFX_PRINT_H
#define LIBU64_GFX_PRINT_H

#include "ultra64.h"
#include "color.h"
#include "libc64/aprintf.h"

typedef struct gfxprint  {
    /* 0x00 */ PrintCallback proutFunc; /* Current print out func */
    /* 0x04 */ Gfx* gListp; /* Current display list to write text to */
    /* 0x08 */ u16 positionX; /* Display coords (sub-pixel units) */
    /* 0x0A */ u16 positionY; /* Display coords (sub-pixel units) */
    /* 0x0C */ u16 offsetX; /* Display offset */
    /* 0x0E */ u8 offsetY; /* Display offset */
    /* 0x0F */ u8 flags;
    /* 0x10 */ Color_RGBA8_u32 color; /* Current font color */
    /* 0x14 */ u8 dummy[0x16];
} gfxprint;

#define GFXPRINT_NUM_SUBPIXELS 4
#define GFXPRINT_PIXELS_PER_BLOCK 8
#define GFXPRINT_PAD GFXPRINT_PIXELS_PER_BLOCK * GFXPRINT_NUM_SUBPIXELS

#define GFXPRINT_FLAG_KANA_MODE (1 << 0) /* Japanese characters displayed as hiragana or katakana */
#define GFXPRINT_FLAG_GRADIENT (1 << 1) /* Gradient state */
#define GFXPRINT_FLAG_SHADOW (1 << 2) /* Shadow state */
#define GFXPRINT_FLAG_CHANGED (1 << 3) /* Text changed */
#define GFXPRINT_FLAG_HIGHRES (1 << 6) /* Highres text */
#define GFXPRINT_FLAG_OPENED (1 << 7) /* Open state */

#define GFXPRINT_KANA_MODE_KATAKANA 0
#define GFXPRINT_KANA_MODE_HIRAGANA 1

#define GFXPRINT_CLEAR_GRADIENT_CHAR '\x8A'
#define GFXPRINT_ENABLE_GRADIENT_CHAR '\x8B'

#define GFXPRINT_KATAKANA_MODE_CHAR '\x8C'
#define GFXPRINT_HIRAGANA_MODE_CHAR '\x8D'

#define GFXPRINT_UNUSED_CHAR '\x8E'

#define GFXPRINT_CLEAR_GRADIENT "\x8A"
#define GFXPRINT_ENABLE_GRADIENT "\x8B"

#define GFXPRINT_KATAKANA_MODE "\x8C"
#define GFXPRINT_HIRAGANA_MODE "\x8D"

#define GFXPRINT_UNUSED "\x8E"

/* Macros for quickly checking state of gfxprint struct */
#define gfxprint_isFlagOn(this, flag) ((this->flags & flag) != 0)
#define gfxprint_setFlag(this, flag) (this->flags |= flag)
#define gfxprint_clrFlag(this, flag) (this->flags &= ~flag)

#define gfxprint_isOpened(this) (gfxprint_isFlagOn(this, GFXPRINT_FLAG_OPENED))
#define gfxprint_setOpened(this) (gfxprint_setFlag(this, GFXPRINT_FLAG_OPENED))
#define gfxprint_clrOpened(this) (gfxprint_clrFlag(this, GFXPRINT_FLAG_OPENED))

#define gfxprint_isHighres(this) (gfxprint_isFlagOn(this, GFXPRINT_FLAG_HIGHRES))
#define gfxprint_setHighres(this) (gfxprint_setFlag(this, GFXPRINT_FLAG_HIGHRES))
#define gfxprint_clrHighres(this) (gfxprint_clrFlag(this, GFXPRINT_FLAG_HIGHRES))

#define gfxprint_isHiragana(this) ((this->flags & GFXPRINT_FLAG_KANA_MODE) != GFXPRINT_KANA_MODE_KATAKANA)
#define gfxprint_isKatakana(this) ((this->flags & GFXPRINT_FLAG_KANA_MODE) == GFXPRINT_KANA_MODE_KATAKANA)
#define gfxprint_setHiragana(this) (this->flags |= GFXPRINT_FLAG_KANA_MODE)
#define gfxprint_setKatakana(this) (this->flags &= ~GFXPRINT_FLAG_KANA_MODE)

#define gfxprint_isGradient(this) (gfxprint_isFlagOn(this, GFXPRINT_FLAG_GRADIENT))
#define gfxprint_setGradient(this) (gfxprint_setFlag(this, GFXPRINT_FLAG_GRADIENT))
#define gfxprint_clrGradient(this) (gfxprint_clrFlag(this, GFXPRINT_FLAG_GRADIENT))

#define gfxprint_isShadow(this) (gfxprint_isFlagOn(this, GFXPRINT_FLAG_SHADOW))
#define gfxprint_setShadow(this) (gfxprint_setFlag(this, GFXPRINT_FLAG_SHADOW))
#define gfxprint_clrShadow(this) (gfxprint_clrFlag(this, GFXPRINT_FLAG_SHADOW))

#define gfxprint_isChanged(this) (gfxprint_isFlagOn(this, GFXPRINT_FLAG_CHANGED))
#define gfxprint_setChanged(this) (gfxprint_setFlag(this, GFXPRINT_FLAG_CHANGED))
#define gfxprint_clrChanged(this) (gfxprint_clrFlag(this, GFXPRINT_FLAG_CHANGED))

//TODO: migrate data and add these when we can extract assets

extern u16 gfxprint_moji_tlut[];
extern u16 gfxprint_rainbow_tlut[];

extern u8 gfxprint_font[];
extern u8 gfxprint_rainbow_txtr[];


extern u8 __gfxprint_default_flags;


void gfxprint_setup(gfxprint* this);
void gfxprint_color(gfxprint* this, u32 r, u32 g, u32 b, u32 a);
void gfxprint_locate(gfxprint* this, s32 x, s32 y);
void gfxprint_locate8x8(gfxprint* this, s32 x, s32 y);
void gfxprint_setoffset(gfxprint* this, s32 x, s32 y);
void gfxprint_putc1(gfxprint* this, char c);
void gfxprint_putc(gfxprint* this, char c);
void gfxprint_write(gfxprint* this, const void* buffer, s32 size, s32 n);
void gfxprint_puts(gfxprint* this, const char* buffer);
void* gfxprint_prout(void* this, const char* buffer, s32 n);
void gfxprint_init(gfxprint* this);
void gfxprint_cleanup(gfxprint* this);
void gfxprint_open(gfxprint* this, Gfx* gListp);
Gfx* gfxprint_close(gfxprint* this);
s32 gfxprint_vprintf(gfxprint* this, const char* fmt, va_list ap);
s32 gfxprint_printf(gfxprint* this, const char* fmt, ...);


#endif
