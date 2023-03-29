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

#include	<asm.h>
#include	<regdef.h>

/*
 * void guMtxF2L(float mf[4][4], Mtx *m)
 *
 * Input
 *	float mf[4][4]
 * Output
 *	Mtx *m
 */

#define	HALF_SIZE_MTX	32
#define	MASK_LOW	0x0000FFFF
#define	MASK_HIGH	0xFFFF0000
#define	MAGNIFICANT	1.5258789062500000e-05	/* ~ 1 / 0x10000 */

#define	ptr_fl	a0	/* argument */
#define	ptr_mtx	a1	/* argument */
#define	end_mtx	t8
#define	mask_hi t9
#define	magni	fv0

	.text	
	.align	5
LEAF( guMtxL2F )
	.set reorder
	li.s	magni, MAGNIFICANT
	li	mask_hi, MASK_HIGH
	addu	end_mtx, ptr_mtx, HALF_SIZE_MTX
label_loop:
	lw	t0, 0(ptr_mtx)
	lw	t1, 32(ptr_mtx)
	
	and	t2, t0, mask_hi
	srl	t3, t1, 16
	or	ta0, t2, t3

	sll	ta1, t0, 16
	and	ta2, t1, MASK_LOW
	or	ta3, ta1, ta2

	mtc1	ta0, ft0	/* FIX32TOF( ) */
	cvt.s.w	ft1, ft0
	mul.s	ft2, ft1, magni

	mtc1	ta3, ft3	/* FIX32TOF( ) */
	cvt.s.w	ft4, ft3
	mul.s	ft5, ft4, magni

	s.s	ft2, 0(ptr_fl)
	s.s	ft5, 4(ptr_fl)

	addu	ptr_mtx, ptr_mtx, 4
	addu	ptr_fl, ptr_fl, 8

	bne	ptr_mtx, end_mtx, label_loop
/* loop-end */

	j	ra
	END( guMtxL2F )

/* End of file */
