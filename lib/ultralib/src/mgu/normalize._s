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
 $Date: 1999/06/16 09:15:39 $
 $Revision: 1.1 $
 $Author: doseki $
************************************************************************/
#include <asm.h>
#include <regdef.h>

/*
 * void guNormalize(float *x, float *y, float *z)
 */
	.text
	.align	5
LEAF( guNormalize )
	.set noreorder

	l.s	ft0, 0(a0)	/* ft0 = x */
	l.s	ft1, 0(a1)	/* ft1 = y */
	l.s	ft2, 0(a2)	/* ft2 = z */

	mul.s	ft3, ft0, ft0	/* ft3 = x*x */
	lui	t0, 0x3f80	/* t0 = 1.0f */
	mul.s	ft4, ft1, ft1	/* ft4 = y*y */
	add.s	ft5, ft3, ft4
	mul.s	ft4, ft2, ft2	/* ft4 = z*z */
	
	add.s	ft3, ft4, ft5	/* ft3 = x*x + y*y + z*z */
	mtc1	t0, ft5
	sqrt.s	ft4, ft3	/* ft4 = sqrt(x*x + y*y + z*z) */

	div.s	ft3, ft5, ft4	/* ft3 = 1/sqrt(x*x + y*y + z*z) */

	mul.s	ft4, ft0, ft3	/* ft4 = x * 1/sqrt(x*x + y*y + z*z) */
	nop
	mul.s	ft5, ft1, ft3	/* ft5 = y * 1/sqrt(x*x + y*y + z*z) */
	nop
	mul.s	ft0, ft2, ft3	/* ft0 = z * 1/sqrt(x*x + y*y + z*z) */

	s.s	ft4, 0(a0)	/* x = ft4 */
	s.s	ft5, 0(a1)	/* y = ft5 */
	j	ra
	s.s	ft0, 0(a2)	/* z = ft0 */	/* Use delayed slot */

	END( guNormalize )
/* end of file */
