/**************************************************************************
 *									  *
 *		 Copyright (C) 1995, Silicon Graphics, Inc.		  *
 *									  *
 *  These coded instructions, statements, and computer programs  contain  *
 *  unpublished  proprietary  information of Silicon Graphics, Inc., and  *
 *  are protected by Federal copyright law.  They  may  not be disclosed  *
 *  to  third  parties  or copied or duplicated in any form, in whole or  *
 *  in part, without the prior written consent of Silicon Graphics, Inc.  *
 *									  *
 **************************************************************************/

#include "guint.h"

/*
 *  Return a pseudorandom 32 bit number
 *  try the RAND macro too
 *   
 */
int guRandom(void)
{
    static unsigned int xseed = 174823885;
    unsigned int x;

    x = (xseed<<2) + 2;

    x *= (x+1);
    x = x >> 2;

    xseed = x;

    return( x );
}
