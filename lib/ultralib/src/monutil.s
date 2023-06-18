#ifndef _FINALROM
#include "asm.h"
#include "sgidefs.h"
#include "regdef.h"
#include "sgidefs.h"
#include "PR/R4300.h"










































#define EXC(code) (EXC_##code >> CAUSE_EXCSHIFT)

.text

LEAF(__isExpJP); .set noreorder
    j       __isExp
     nop
    sw      k0, -0x10(sp)
    la      k0, __isExp
    jr      k0
     nop
.set reorder
END(__isExpJP)

LEAF(__isExp); .set noreorder
    sw      k0, -0x10(sp)
    sw      k1, -8(sp)

    mfc0    k0, C0_CAUSE
    nop
    andi    k0, k0, CAUSE_EXCMASK
    bnez    k0, non_stop

     nop
    mfc0    k0, C0_CAUSE
    nop
    andi    k0, k0, CAUSE_IP7
    beqz    k0, throw_os_exception
     nop
    j       go_monitor
     nop
non_stop:
    sra     k0, k0, CAUSE_EXCSHIFT
    li      k1, EXC(BREAK)
    bne     k0, k1, non_bp
     nop
    j       go_monitor
     nop

non_bp:
    li      k1, EXC(RADE)
    bne     k0, k1, non_adrs_store_exp
     nop
    j       go_monitor
     nop
non_adrs_store_exp:
    li      k1, EXC(WADE)
    bne     k0, k1, non_adrs_load_exp
     nop
    j       go_monitor
     nop
non_adrs_load_exp:
    li      k1, EXC(IBE)
    bne     k0, k1, non_bus_code_exp
     nop
    j       go_monitor
     nop
non_bus_code_exp:
    li      k1, EXC(DBE)
    bne     k0, k1, non_bus_data_exp
     nop
    j       go_monitor
     nop
non_bus_data_exp:
    li      k1, EXC(MOD)
    bne     k0, k1, non_tlb_mod
     nop
    j       go_monitor
     nop
non_tlb_mod:
    li      k1, EXC(RMISS)
    bne     k0, k1, non_tlb_load
     nop
    j       go_monitor
     nop
non_tlb_load:
    li      k1, EXC(WMISS)
    bne     k0, k1, non_tlb_store
     nop
    j       go_monitor
     nop
non_tlb_store:
    li      k1, EXC(II)
    bne     k0, k1, non_resv
     nop
    j       go_monitor
     nop

non_resv:
    lw      k1, -8(sp)

throw_os_exception:
    j       ramOldVector
     nop









go_monitor:
    move    k0, sp
    addiu   sp, sp, -0x200
    sw      k0, 0x78(sp)
    lw      k1, -8(k0)
    sw      k1, 0x70(sp)
    lw      k1, -0x10(k0)
    sw      k1, 0x6c(sp)
    nop
w:
    lui     k0, (0xA4600010 >> 16)
    lw      k0, (0xA4600010 & 0xFFFF)(k0)   /* PI_STATUS_REG */
    nop
    andi    k0, k0, 3           /* (PI_STATUS_DMA_BUSY | PI_STATUS_IO_BUSY) */
    bnez    k0, w
     nop
    la      k0, 0xBFF00050
    jr      k0
     nop
.set reorder
END(__isExp)


LEAF(MonitorInitBreak); .set noreorder
    nop
    nop
INIT_BREAK_POSITION:
    break   4
    nop
    nop
    nop
    jr      ra
     nop
.set reorder
END(MonitorInitBreak)

#endif
