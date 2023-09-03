#include "libu64/gfxprint.h"
#include "attributes.h"

#define TX_LINE(width, siz) (((((4 << (siz)) * (width)) >> 3) + 7) >> 3)

u8 __gfxprint_default_flags;

void gfxprint_setup(gfxprint* this) {
    s32 width = 16;
    s32 height = 256;
    s32 i;

    gDPPipeSync(this->gListp++);
    gDPSetOtherMode(this->gListp++,
                    G_AD_DISABLE | G_CD_DISABLE | G_CK_NONE | G_TC_FILT | G_TF_BILERP | G_TT_IA16 | G_TL_TILE |
                        G_TD_CLAMP | G_TP_NONE | G_CYC_1CYCLE | G_PM_NPRIMITIVE,
                    G_RM_XLU_SURF | G_RM_XLU_SURF2 | G_ZS_PRIM);
    gDPSetCombineMode(this->gListp++, G_CC_DECALRGBA, G_CC_DECALRGBA);

    gDPLoadTextureBlock_4b(this->gListp++, gfxprint_font, G_IM_FMT_CI, width, height, 0, G_TX_NOMIRROR | G_TX_WRAP,
                           G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);

    gDPLoadTLUT(this->gListp++, 64, 0x100 + 0 * 0x10, gfxprint_moji_tlut);

    for (i = 1; i < 4; i++) {
        gDPSetTile(this->gListp++, G_IM_FMT_CI, G_IM_SIZ_4b, TX_LINE(16, G_IM_SIZ_4b), 0, i * 2, i,
                   G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK,
                   G_TX_NOLOD);
        gDPSetTileSize(this->gListp++, i * 2, 0, 0, (16 - 1) << G_TEXTURE_IMAGE_FRAC,
                       (256 - 1) << G_TEXTURE_IMAGE_FRAC);
    }

    gDPSetColor(this->gListp++, G_SETPRIMCOLOR, this->color.rgba);

    gDPLoadMultiTile_4b(this->gListp++, gfxprint_rainbow_txtr, 0, 1, G_IM_FMT_CI, 2, 8, 0, 0, 1, 7, 4,
                        G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, 1, 3, G_TX_NOLOD, G_TX_NOLOD);

    // loads 16 texels to palette index 4
    gDPLoadTLUT(this->gListp++, 16, 0x100 + 4 * 0x10, gfxprint_rainbow_tlut);

    for (i = 1; i < 4; i++) {
        gDPSetTile(this->gListp++, G_IM_FMT_CI, G_IM_SIZ_4b, TX_LINE(16, G_IM_SIZ_4b), 0, i * 2 + 1, 4,
                   G_TX_NOMIRROR | G_TX_WRAP, 3, G_TX_NOLOD, G_TX_NOMIRROR | G_TX_WRAP, 1, G_TX_NOLOD);
        gDPSetTileSize(this->gListp++, i * 2 + 1, 0, 0, (2 - 1) << G_TEXTURE_IMAGE_FRAC,
                       (8 - 1) << G_TEXTURE_IMAGE_FRAC);
    }
}

void gfxprint_color(gfxprint* this, u32 r, u32 g, u32 b, u32 a) {
    this->color.r = r;
    this->color.g = g;
    this->color.b = b;
    this->color.a = a;

    gDPPipeSync(this->gListp++);
    gDPSetColor(this->gListp++, G_SETPRIMCOLOR, this->color.rgba);
}

void gfxprint_locate(gfxprint* this, s32 x, s32 y) {
    this->positionX = this->offsetX + x * 4;
    this->positionY = this->offsetY + y * 4;
}

void gfxprint_locate8x8(gfxprint* this, s32 x, s32 y) {
    gfxprint_locate(this, x * 8, y * 8);
}

void gfxprint_setoffset(gfxprint* this, s32 x, s32 y) {
    this->offsetX = x * 4;
    this->offsetY = y * 4;
}

void gfxprint_putc1(gfxprint* this, char c) {
    u32 tile = (c & 0xFF) * 2;
    u16 x0 = (c & 4);
    u16 x1 = (c >> 3);

    if (gfxprint_isChanged(this)) {
        gfxprint_clrChanged(this);
        gDPPipeSync(this->gListp++);

        if (gfxprint_isGradient(this)) {
            gDPSetTextureLUT(this->gListp++, G_TT_RGBA16);
            gDPSetCycleType(this->gListp++, G_CYC_2CYCLE);
            gDPSetRenderMode(this->gListp++, G_RM_PASS, G_RM_XLU_SURF2);
            gDPSetCombineMode(this->gListp++, G_CC_INTERFERENCE, G_CC_PASS2);
        } else {
            gDPSetTextureLUT(this->gListp++, G_TT_IA16);
            gDPSetCycleType(this->gListp++, G_CYC_1CYCLE);
            gDPSetRenderMode(this->gListp++, G_RM_XLU_SURF, G_RM_XLU_SURF2);
            gDPSetCombineMode(this->gListp++, G_CC_MODULATEIDECALA_PRIM, G_CC_MODULATEIDECALA_PRIM);
        }
    }

    if (gfxprint_isShadow(this)) {

        gDPSetColor(this->gListp++, G_SETPRIMCOLOR, 0);

        if (gfxprint_isHighres(this)) {
            gSPTextureRectangle(this->gListp++, (this->positionX + 4) << 1, (this->positionY + 4) << 1,
                                (this->positionX + 4 + 32) << 1, (this->positionY + 4 + 32) << 1, tile, x0 << 6,
                                x1 << 8, 512, 512);
        } else {
            gSPTextureRectangle(this->gListp++, this->positionX + 4, this->positionY + 4, this->positionX + 4 + 32,
                                this->positionY + 4 + 32, tile, x0 << 6, x1 << 8, 1024, 1024);
        }
        gDPSetColor(this->gListp++, G_SETPRIMCOLOR, this->color.rgba);
    }

    if (gfxprint_isHighres(this)) {
        gSPTextureRectangle(this->gListp++, this->positionX << 1, this->positionY << 1, (this->positionX + 32) << 1,
                            (this->positionY + 32) << 1, tile, x0 << 6, x1 << 8, 512, 512);
    } else {
        gSPTextureRectangle(this->gListp++, this->positionX, this->positionY, this->positionX + 32,
                            this->positionY + 32, tile, x0 << 6, x1 << 8, 1024, 1024);
    }

    this->positionX += 32;
}

void gfxprint_putc(gfxprint* this, char c) {
    char param = c;

    if (c == ' ') {
        this->positionX += 32;
    } else if (param > ' ' && param <= 0x7E) {
        gfxprint_putc1(this, param);
    } else if (param >= 0xA0 && param <= 0xDF) {
        if (gfxprint_isHiragana(this)) {
            if (param <= 0xBF) {
                param -= 0x20;
            } else {
                param += 0x20;
            }
        }
        gfxprint_putc1(this, param);
    } else {
        switch (param) {
            case '\0':
                break;

            case '\n':
                this->positionY += 32;

            case '\r':
                this->positionX = this->offsetX;

                break;

            case '\t':
                do {
                    gfxprint_putc1(this, ' ');
                } while ((this->positionX - this->offsetX) % 256);

                break;

            case GFXPRINT_HIRAGANA_MODE_CHAR:
                gfxprint_setHiragana(this);

                break;

            case GFXPRINT_KATAKANA_MODE_CHAR:
                gfxprint_setKatakana(this);

                break;

            case GFXPRINT_ENABLE_GRADIENT_CHAR:
                gfxprint_setGradient(this);
                gfxprint_setChanged(this);

                break;

            case GFXPRINT_CLEAR_GRADIENT_CHAR:
                gfxprint_clrGradient(this);
                gfxprint_setChanged(this);

                break;

            case GFXPRINT_UNUSED_CHAR:
                break;

            default:
                break;
        }
    }
}

void gfxprint_write(gfxprint* this, const void* buffer, s32 size, s32 n) {
    const char* buf = (const char*)buffer;
    s32 i;

    for (i = size * n; i != 0; i--) {
        gfxprint_putc(this, *buf++);
    }
}

void gfxprint_puts(gfxprint* this, const char* buffer) {
    while (*buffer != '\0') {
        gfxprint_putc(this, *buffer++);
    }
}

void* gfxprint_prout(void* this, const char* buffer, s32 n) {
    gfxprint_write(this, buffer, sizeof(char), n);
    return this;
}

void gfxprint_init(gfxprint* this) {
    gfxprint_clrOpened(this);
    this->proutFunc = (PrintCallback)gfxprint_prout;
    this->gListp = NULL;
    this->positionX = 0;
    this->positionY = 0;
    this->offsetX = 0;
    this->offsetY = 0;
    this->color.rgba = 0;
    gfxprint_setKatakana(this);
    gfxprint_clrGradient(this);
    gfxprint_setShadow(this);
    gfxprint_setChanged(this);

    if ((__gfxprint_default_flags & GFXPRINT_FLAG_HIGHRES) != 0) {
        gfxprint_setHighres(this);
    } else {
        gfxprint_clrHighres(this);
    }
}

void gfxprint_cleanup(UNUSED gfxprint* this) {
}

void gfxprint_open(gfxprint* this, Gfx* gListp) {
    if (!gfxprint_isOpened(this)) {
        gfxprint_setOpened(this);
        this->gListp = gListp;
        gfxprint_setup(this);
    }
}

Gfx* gfxprint_close(gfxprint* this) {
    Gfx* list;

    gfxprint_clrOpened(this);
    gDPPipeSync(this->gListp++);
    list = this->gListp;
    this->gListp = NULL;
    return list;
}

s32 gfxprint_vprintf(gfxprint* this, const char* fmt, va_list ap) {
    return vaprintf(&this->proutFunc, fmt, ap);
}

s32 gfxprint_printf(gfxprint* this, const char* fmt, ...) {
    s32 res;
    va_list ap;
    va_start(ap, fmt);
    res = gfxprint_vprintf(this, fmt, ap);
    va_end(ap);

    return res;
}
