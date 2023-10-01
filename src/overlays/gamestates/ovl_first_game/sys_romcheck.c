#include "first_game.h"
#include "carthandle.h"
#include "m_nmi_buf.h"

void sys_romcheck(void) {
    u32 sp24;
    u8 temp;
    s32 pad;

    osEPiReadIo(carthandle, 0x3C, &sp24);

    temp = sp24;
    sp24 = 0x23;
    if (temp == sp24) {
        APPNMI_ZURUMODE2_SET();
    }
}
