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
  void guTranslate(Mtx *m, float x, float y, float z)
	m:	a0
	x:	a1
	y:	a2
	z	a3		
 */

#define	SIZE_OF_MTX	64	/* sizeof( Mtx ) */
#define FLOAT_0x10000	6.5536e+04	/* (float)0x00010000) */

	.text
	.align	5
LEAF( guTranslate )
	.set reorder

	li.s	ft0, FLOAT_0x10000	/* (float)0x00010000 */

	mtc1		a1, ft1
	mul.s		ft2, ft1, ft0
	trunc.w.s	ft3, ft2
	mfc1		t1, ft3		/* t1 = FTOFIX32(x) */

	mtc1		a2, ft1
	mul.s		ft2, ft1, ft0
	trunc.w.s	ft3, ft2
	mfc1		t3, ft3		/* t3 = FTOFIX32(y) */

		/* Save t1 and t3 values until fraction process is finished! */

	srl	t2, t1, 16		/* x integeral part for t0 interger */
	sll	t0, t2, 16
	srl	t2, t3, 16		/* y integral part for t2 fraction */
	or	t0, t0, t2		/* Compose in t0 */
	sw	t0, 24(a0)

	sll	t0,t1,16		/* x fraction part for t0 interger */
	sll	t2,t3,16
	srl	t2,t2,16		/* y fraction part for t2 fraction */
	or	t0,t0,t2		/* Compose in t0 */
	sw	t0,24+32(a0)

	
	mtc1		a3, ft1
	mul.s		ft2, ft1, ft0
	trunc.w.s	ft3, ft2
	mfc1		t1, ft3		/* t1 = FTOFIX32(z) */

	srl	t2,t1,16
	sll	t0,t2,16		/* z integral part for t0 integer */
	addiu	t0,t0,1			/* enter 0x0001 in t0 fraction */
	sw	t0,28(a0)

	sll	t2,t1,16		/* z fraction part for t2 integer */
	sw	t2,28+32(a0)

	sw	zero, 0(a0)
	sw	zero, 4(a0)
	sw	zero, 8(a0)
	sw	zero, 12(a0)
	sw	zero, 16(a0)
	sw	zero, 20(a0)
	sw	zero, 0+32(a0)
	sw	zero, 4+32(a0)
	sw	zero, 8+32(a0)
	sw	zero, 12+32(a0)
	sw	zero, 16+32(a0)
	sw	zero, 20+32(a0)

	lui	t0,0x0001
	ori	t0,0x0000
	sw	t0,0(a0)
	sw	t0,20(a0)
	
	lui	t0,0x0000
	ori	t0,0x0001
	sw	t0,8(a0)
	
	j	ra
	
	END( guTranslate )
/* end of file */
