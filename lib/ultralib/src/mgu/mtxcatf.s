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
 $Date: 1999/06/16 09:15:37 $
 $Revision: 1.1 $
 $Author: doseki $
************************************************************************/

#include <asm.h>
#include <regdef.h>

/*
 * void guMtxCatF(float mf[4][4], float nf[4][4], float res[4][4])
 *	res = mf * nf
 */	
#define	FRAME_SIZE	64
	.text
	.align	5
	.globl	guMtxCatF
	.ent	guMtxCatF, 0
guMtxCatF:
	.set reorder	
	subu	sp, FRAME_SIZE
	.frame	sp, FRAME_SIZE, ra

	addu	v0, a0, 64
	addu	v1, a1, 16
	move	t2, sp
label_loop_i:
	move	a3, a1
label_loop_j:
	l.s	ft0, 0(a0)	/* mf[i][0] * nf[0][j] */
	l.s	ft1, 0(a3)
	mul.s	ft2, ft0, ft1
	l.s	ft3, 4(a0)	/* + mf[i][1] * nf[1][j] */
	l.s	ft4, 16(a3)
	mul.s	ft5, ft3, ft4
	add.s	ft2, ft2, ft5
	l.s	ft0, 8(a0)	/* + mf[i][2] * nf[2][j] */
	l.s	ft1, 32(a3)
	mul.s	ft5, ft0, ft1
	add.s	ft2, ft2, ft5
	l.s	ft3, 12(a0)	/* + mf[i][3] * nf[3][j] */
	l.s	ft4, 48(a3)
	mul.s	ft5, ft3, ft4
	add.s	ft2, ft2, ft5

	s.s	ft2, 0(t2)
	addu	a3, a3, 4
	addu	t2, t2, 4
	bne	a3, v1, label_loop_j
/* loop_j_end */
	addu	a0, a0, 16
	bne	a0, v0, label_loop_i
/* loop_i_end */
	s.s	ft2, 60(a2)
	lw	t0, 0(sp)
	lw	t1, 4(sp)
	lw	t2, 8(sp)
	lw	t3, 12(sp)
	lw	ta0, 16(sp)
	lw	ta1, 20(sp)
	lw	ta2, 24(sp)
	lw	ta3, 28(sp)
	lw	t8, 32(sp)
	lw	t9, 36(sp)
	lw	v0, 40(sp)
	lw	v1, 44(sp)
	lw	a0, 48(sp)
	lw	a1, 52(sp)
	lw	a3, 56(sp)

	sw	t0, 0(a2)
	sw	t1, 4(a2)
	sw	t2, 8(a2)
	sw	t3, 12(a2)
	sw	ta0, 16(a2)
	sw	ta1, 20(a2)
	sw	ta2, 24(a2)
	sw	ta3, 28(a2)
	sw	t8, 32(a2)
	sw	t9, 36(a2)
	sw	v0, 40(a2)
	sw	v1, 44(a2)
	sw	a0, 48(a2)
	sw	a1, 52(a2)
	sw	a3, 56(a2)

	addu	sp , FRAME_SIZE
	j	ra

	.end	guMtxCatF

/* end of file */
