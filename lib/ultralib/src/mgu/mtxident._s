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
 * void guMtxIdent( Mtx * matrix )
 *	Substitute unit matrix for matrix
 *	Correspond only when alignment is 4 byte boundary
 * Input
 *	a0 = matrix
 * Output
 *	*matrix	 unit matrix
 */

#define	SIZE_OF_MTX	64	/* sizeof( Mtx ) */
	.text
	.align	5
LEAF(guMtxIdent)
	.set reorder

	addi	t0, zero, 1	/* t0 = 0x00000001 */
	sll	t1, t0, 16	/* t1 = 0x00010000 */

	sw	t1, 0(a0)	/* Substitution of integers */
	sw	zero, 4(a0)
	sw	t0, 8(a0)
	sw	zero, 12(a0)
	sw	zero, 16(a0)
	sw	t1, 20(a0)
	sw	zero, 24(a0)
	sw	t0, 28(a0)
	
	sw	zero, 32(a0)	/* Substitution of fractions */
	sw	zero, 36(a0)
	sw	zero, 40(a0)
	sw	zero, 44(a0)
	sw	zero, 48(a0)
	sw	zero, 52(a0)
	sw	zero, 56(a0)
	sw	zero, 60(a0)
	j	ra

	END(guMtxIdent)
	
/* End of file */
