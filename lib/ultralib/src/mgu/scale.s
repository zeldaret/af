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
 * FTOFIX32 (float to fix32)
 * a:	input
 * t:	output
 * ft0 : (float)0x00010000
 * ft1, ft2, ft3, t0 :	work reg 				 		
 */
#define FTOFIX32(a, t)	\
	mtc1		a, ft1		;	\
	mul.s		ft2, ft1, ft0	;	\
	trunc.w.s	ft3, ft2, t0	;	\
	mfc1		t, ft3		; 

/* 
   void guScale(Mtx *m, float x, float y, float z)
	m:	a0
	x:	a1
	y:	a2
	z	a3		
 */
#define	SIZE_OF_MTX	64	/* sizeof( Mtx ) */
#define FLOAT_0x10000	6.5536e+04	/* (float)0x00010000) */

	.text
	.align	5
LEAF( guScale )
	.set reorder

	li.s	ft0, FLOAT_0x10000	/* (float)0x00010000 */

	FTOFIX32(a1, t1)		/* t1 = FTOFIX32(x) */
	srl	t2, t1, 16
	sll	t0, t2, 16
	sw	t0, 0(a0)		/* t0 = x integral part */
	sll	t2, t1, 16
	sw	t2, 32(a0)		/* t2 = x decimal part */
	
	FTOFIX32(a2, t1)		/* t1 = FTOFIX32(y) */
	srl	t0, t1, 16
	sw	t0, 8(a0)		/* t0 = y integral part */
	andi	t2, t1, 0xffff
	sw	t2, 40(a0)		/* t2 = y decimal part */

	FTOFIX32(a3, t1)		/* t1 = FTOFIX32(z) */
	srl	t2, t1, 16
	sll	t0, t2, 16
	sw	t0, 20(a0)		/* t0 = z integral part */
	sll	t2, t1, 16
	sw	t2, 52(a0)		/* t2 = z decimal part */

	li	t0, 1			/* t0 = 1.0 integral part  */
	sw	t0, 28(a0)

	sw	zero, 4(a0)
	sw	zero, 12(a0)
	sw	zero, 16(a0)
	sw	zero, 24(a0)
	sw	zero, 36(a0)
	sw	zero, 44(a0)
	sw	zero, 48(a0)
	sw	zero, 56(a0)
	sw	zero, 60(a0)
	j	ra
	
	END( guScale )
/* end of file */
