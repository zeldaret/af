#include "PR/R4300.h"
#include "sys/asm.h"
#include "sys/regdef.h"

.text
.set noreorder
LEAF(__osDisableInt)
	la    t2, __OSGlobalIntMask
	lw    t3, (t2)
	andi  t3, 0xFF00
    mfc0  t0, C0_SR
    and   t1, t0, ~SR_IE
    mtc0  t1, C0_SR
    andi  v0, t0, SR_IE
    lw    t0, (t2)
    andi  t0, 0xFF00
    beq   t0, t3, No_Change_Global_Int
     la   t2, __osRunningThread # this is intentionally a macro in the branch delay slot
    lw    t1, 280(t2)
    andi  t2, t1, 0xFF00
    and   t2, t0
    and   t1, 0xFFFF00FF
    or    t1, t2
    and   t1, -2
    mtc0  t1, $12
	nop
	nop
No_Change_Global_Int:
    jr ra
     nop
END(__osDisableInt)
	
LEAF(__osRestoreInt)
    mfc0  t0, C0_SR
    or    t0, t0, a0
    mtc0  t0, C0_SR
    nop
    nop
    jr    ra
     nop
END(__osRestoreInt)
