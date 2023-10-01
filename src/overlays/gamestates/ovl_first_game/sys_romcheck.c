#include "first_game.h"
#include "carthandle.h"
#include "m_nmi_buf.h"
#include "attributes.h"

void sys_romcheck(void) {
    u32 sp24;
    u8 version;
    UNUSED s32 pad;

    // Read the last 4 bytes from the ROM header
    osEPiReadIo(carthandle, 0x3C, &sp24);

    version = sp24;
    sp24 = 0x23;
    // Check if the version byte is equal to 0x23
    if (version == sp24) {
        APPNMI_ZURUMODE2_SET();
    }
}
