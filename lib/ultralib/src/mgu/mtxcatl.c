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

#include <ultra64.h>
#include "../gu/guint.h"
#include "gu.h"

void guMtxCatL(Mtx *m, Mtx *n, Mtx *res)
{
	float	mf[4][4], nf[4][4], resf[4][4];

	guMtxL2F(mf, m);
	guMtxL2F(nf, n);

	guMtxCatF(mf, nf, resf);

	guMtxF2L(resf, res);
}

#if BUILD_VERSION < VERSION_K
void guMtxXFML(Mtx *m, float x, float y, float z, float *ox, float *oy, float *oz)
{
	float	mf[4][4];

	guMtxL2F(mf, m);

	guMtxXFMF(mf, x, y, z, ox, oy, oz);
}
#endif
/* End of file */
