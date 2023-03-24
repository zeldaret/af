/************************************************************************
 Copyright (C) 1998,1999 NINTENDO CO,Ltd,
 Copyright (C) 1998,1999 MONEGI CORPORATION,
	All Rights Reserved
This program is a trade secret of NINTENDO CO,Ltd and MONEGI Corp. 
and it is not to be reproduced, published, disclosed to others, copied,
adapted, distributed, or displayed without the prior authorization of 
NINTENDO CO,Ltd. and MONEGI Corp. Licensee agrees to attach or embed 
this Notice on all copies of the program, including partial copies or 
modified versions thereof.
*************************************************************************/
/************************************************************************
 $Date: 1999/06/16 09:15:40 $
 $Revision: 1.1 $
 $Author: doseki $
************************************************************************/
#include <asm.h>
#include <regdef.h>

/* 
 * void guScaleF(float m[4][4], float x, float y, float z)
 * m:	a0
 * x:	a1
 * y:	a2
 * z:	a3		
 */
	.text
	.align	5
LEAF( guScaleF )
	.set reorder

	sw	a1, 0(a0)
	sw	zero, 4(a0)	/* line 1 */
	sw	zero, 8(a0)
	sw	zero, 12(a0)

	sw	zero, 16(a0)	/* line 2 */
	sw	a2, 20(a0)
	sw	zero, 24(a0)
	sw	zero, 28(a0)

	sw	zero, 32(a0)	/* line 3 */
	sw	zero, 36(a0)
	sw	a3, 40(a0)
	sw	zero, 44(a0)

	li	t0, 0x3f800000	/* t0 = 1.0 */
	sw	zero, 48(a0)	/* line 4 */
	sw	zero, 52(a0)
	sw	zero, 56(a0)
	sw	t0, 60(a0)

	j	ra

	END( guScaleF )

/* End of file */
