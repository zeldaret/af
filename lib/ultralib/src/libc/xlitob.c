#include "stdlib.h"
#include "string.h"
#include "xstdio.h"

// TODO: these come from headers
#ident "$Revision: 1.34 $"
#ident "$Revision: 1.5 $"
#ident "$Revision: 1.23 $"

#define BUFF_LEN 0x18

static char ldigs[] = "0123456789abcdef";
static char udigs[] = "0123456789ABCDEF";

void _Litob(_Pft *px, char code) {
    char buff[BUFF_LEN];
    const char *digs;
    int base;
    int i;
    unsigned long long ullval;

    digs = (code == 'X') ? udigs : ldigs;

    base = (code == 'o') ? 8 : ((code != 'x' && code != 'X') ? 10 : 16);
    i = BUFF_LEN;
    ullval = px->v.ll;

    if ((code == 'd' || code == 'i') && px->v.ll < 0) {
        ullval = -ullval;
    }

    if (ullval != 0 || px->prec != 0) {
        buff[--i] = digs[ullval % base];
    }

    px->v.ll = ullval / base;

    while (px->v.ll > 0 && i > 0) {
        lldiv_t qr = lldiv(px->v.ll, base);
        
        px->v.ll = qr.quot;
        buff[--i] = digs[qr.rem];
    }

    px->n1 = BUFF_LEN - i;

    memcpy(px->s, buff + i, px->n1);

    if (px->n1 < px->prec) {
        px->nz0 = px->prec - px->n1;
    }

    if (px->prec < 0 && (px->flags & (FLAGS_ZERO | FLAGS_MINUS)) == FLAGS_ZERO) {
        if ((i = px->width - px->n0 - px->nz0 - px->n1) > 0) {
            px->nz0 += i;
        }
    }
}
