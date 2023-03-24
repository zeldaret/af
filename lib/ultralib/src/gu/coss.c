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

/* ====================================================================
 * ====================================================================
 *
 * Module: coss.c
 * $Revision: 1.3 $
 * $Date: 1998/10/09 06:11:01 $
 * $Author: has $
 * $Source: /exdisk2/cvs/N64OS/Master/cvsmdev2/PR/libultra/monegi/gu/coss.c,v $
 *
 * ====================================================================
 * ====================================================================
 */

/* coefficients for polynomial approximation of sin on +/- pi/2 */

/* ====================================================================
 *
 * FunctionName		coss
 *
 * Description		computes cosine of arg
 *
 * ====================================================================
 */

signed short
coss( unsigned short x )
{
	/* 0 <= x < 0x10000  ==>  0 <= x < 2PI */

	return sins ((unsigned short) (x + 0x4000));
}
