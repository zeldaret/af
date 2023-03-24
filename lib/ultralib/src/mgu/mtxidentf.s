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
 $Date: 1999/06/16 09:15:38 $
 $Revision: 1.1 $
 $Author: doseki $
************************************************************************/
#include <asm.h>
#include <regdef.h>

/*
 * guMtxIdentF( float matrix[4][4] )
 *	substitute unit matrix for floating point matrix
 *	correspond only when alignment is four byte boundary
 * Input
 *	a0 = matrix
 * Output
 *	*matrix	 unti matix
 */
	.text
	.align	5
LEAF( guMtxIdentF )
	.set reorder

	li	t0, 0x3f800000	/* t0 = 1.0 */

	sw	t0, 0(a0)
	sw	zero, 4(a0)	/* line 1 */
	sw	zero, 8(a0)
	sw	zero, 12(a0)

	sw	zero, 16(a0)	/* line 2 */
	sw	t0, 20(a0)
	sw	zero, 24(a0)
	sw	zero, 28(a0)

	sw	zero, 32(a0)	/* line 3 */
	sw	zero, 36(a0)
	sw	t0, 40(a0)
	sw	zero, 44(a0)

	sw	zero, 48(a0)	/* line 4 */
	sw	zero, 52(a0)
	sw	zero, 56(a0)
	sw	t0, 60(a0)

	j	ra

	END( guMtxIdentF )

/* End of file */