
/*
 * Copyright 1995, Silicon Graphics, Inc.
 * ALL RIGHTS RESERVED
 *
 * UNPUBLISHED -- Rights reserved under the copyright laws of the United
 * States.   Use of a copyright notice is precautionary only and does not
 * imply publication or disclosure.
 *
 * U.S. GOVERNMENT RESTRICTED RIGHTS LEGEND:
 * Use, duplication or disclosure by the Government is subject to restrictions
 * as set forth in FAR 52.227.19(c)(2) or subparagraph (c)(1)(ii) of the Rights
 * in Technical Data and Computer Software clause at DFARS 252.227-7013 and/or
 * in similar or successor clauses in the FAR, or the DOD or NASA FAR
 * Supplement.  Contractor/manufacturer is Silicon Graphics, Inc.,
 * 2011 N. Shoreline Blvd. Mountain View, CA 94039-7311.
 *
 * THE CONTENT OF THIS WORK CONTAINS CONFIDENTIAL AND PROPRIETARY
 * INFORMATION OF SILICON GRAPHICS, INC. ANY DUPLICATION, MODIFICATION,
 * DISTRIBUTION, OR DISCLOSURE IN ANY FORM, IN WHOLE, OR IN PART, IS STRICTLY
 * PROHIBITED WITHOUT THE PRIOR EXPRESS WRITTEN PERMISSION OF SILICON
 * GRAPHICS, INC.
 *
 */

/*
 * File:	gt.c
 * Creator:	hsa@sgi.com
 * Create Date:	Fri Oct 13 14:23:48 PDT 1995
 *
 */


#include "gtint.h"


/*
 * Set the cached RDP othermode word in the gt state structure.
 */
void
gtStateSetOthermode(Gfx *om, gtStateOthermode_t mode, int data)
{
    int		shift, length;
    u32		mask;

    if (mode == GT_CLEAR) {	/* special case */
	om->words.w0 = (G_RDPSETOTHERMODE << 24);
	om->words.w1 = 0x0;
    }

    if (mode <= GT_RENDERMODE) {
	/* these are OTHERMODE_L */
	switch (mode) {

	  case GT_ALPHACOMPARE:
	    shift = G_MDSFT_ALPHACOMPARE;
	    length = 2;
	    break;

	  case GT_ZSRCSEL:
	    shift = G_MDSFT_ZSRCSEL;
	    length = 1;
	    break;

	  case GT_RENDERMODE:
	    shift = G_MDSFT_RENDERMODE;
	    length = 29;
	    break;

	  default:
	    break;
	}

	mask = (0x01 << length);
	mask = mask - 1;
	mask = (mask << shift);
	mask = mask ^ 0xffffffff;
	om->words.w1 &= mask;
	om->words.w1 |= data;

    } else {
	/* these are OTHERMODE_H */
	switch (mode) {
	  case GT_ALPHADITHER:
	    shift = G_MDSFT_ALPHADITHER;
	    length = 2;
	    break;

	  case GT_RGBDITHER:
	    shift = G_MDSFT_RGBDITHER;
	    length = 2;
	    break;

	  case GT_COMBKEY:
	    shift = G_MDSFT_COMBKEY;
	    length = 1;
	    break;

	  case GT_TEXTCONV:
	    shift = G_MDSFT_TEXTCONV;
	    length = 3;
	    break;

	  case GT_TEXTFILT:
	    shift = G_MDSFT_TEXTFILT;
	    length = 2;
	    break;

	  case GT_TEXTLUT:
	    shift = G_MDSFT_TEXTLUT;
	    length = 2;
	    break;

	  case GT_TEXTLOD:
	    shift = G_MDSFT_TEXTLOD;
	    length = 1;
	    break;

	  case GT_TEXTDETAIL:
	    shift = G_MDSFT_TEXTDETAIL;
	    length = 2;
	    break;

	  case GT_TEXTPERSP:
	    shift = G_MDSFT_TEXTPERSP;
	    length = 1;
	    break;

	  case GT_CYCLETYPE:
	    shift = G_MDSFT_CYCLETYPE;
	    length = 2;
	    break;

	  case GT_PIPELINE:
	    shift = G_MDSFT_PIPELINE;
	    length = 1;
	    break;

	  default:
	    break;
	}

	mask = (0x01 << length);
	mask = mask - 1;
	mask = (mask << shift);
	mask = mask ^ 0xffffffff;
	om->words.w0 &= mask;
	om->words.w0 |= data;
    }

    /* force cached othermode word to have proper command id: */
    om->words.w0 &= 0x00ffffff;
    om->words.w0 |= (G_RDPSETOTHERMODE << 24);
}

