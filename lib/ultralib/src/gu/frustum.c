/**************************************************************************
 *									  *
 *		 Copyright (C) 1994, Silicon Graphics, Inc.		  *
 *									  *
 *  These coded instructions, statements, and computer programs  contain  *
 *  unpublished  proprietary  information of Silicon Graphics, Inc., and  *
 *  are protected by Federal copyright law.  They  may  not be disclosed  *
 *  to  third  parties  or copied or duplicated in any form, in whole or  *
 *  in part, without the prior written consent of Silicon Graphics, Inc.  *
 *									  *
 **************************************************************************/

#include "guint.h"

void guFrustumF(float mf[4][4], float l, float r, float b, float t, float n, float f, float scale)
{
	int	i, j;

	guMtxIdentF(mf);

	mf[0][0] = 2*n/(r-l);
	mf[1][1] = 2*n/(t-b);
	mf[2][0] = (r+l)/(r-l);
	mf[2][1] = (t+b)/(t-b);
	mf[2][2] = -(f+n)/(f-n);
	mf[2][3] = -1;
	mf[3][2] = -2*f*n/(f-n);
	mf[3][3] = 0;

	for (i=0; i<4; i++)
	    for (j=0; j<4; j++)
		mf[i][j] *= scale;
}

void guFrustum(Mtx *m, float l, float r, float b, float t, float n, float f, float scale)
{
	Matrix	mf;

	guFrustumF(mf, l, r, b, t, n, f, scale);

	guMtxF2L(mf, m);
}
