
/*====================================================================
 * os_system.h
 *
 * Copyright 1995, Silicon Graphics, Inc.
 * All Rights Reserved.
 *
 * This is UNPUBLISHED PROPRIETARY SOURCE CODE of Silicon Graphics,
 * Inc.; the contents of this file may not be disclosed to third
 * parties, copied or duplicated in any form, in whole or in part,
 * without the prior written permission of Silicon Graphics, Inc.
 *
 * RESTRICTED RIGHTS LEGEND:
 * Use, duplication or disclosure by the Government is subject to
 * restrictions as set forth in subdivision (c)(1)(ii) of the Rights
 * in Technical Data and Computer Software clause at DFARS
 * 252.227-7013, and/or in similar or successor clauses in the FAR,
 * DOD or NASA FAR Supplement. Unpublished - rights reserved under the
 * Copyright Laws of the United States.
 *====================================================================*/

/*---------------------------------------------------------------------*
        Copyright (C) 1998 Nintendo. (Originated by SGI)
        
        $RCSfile: os_system.h,v $
        $Revision: 1.1 $
        $Date: 1998/10/09 08:01:18 $
 *---------------------------------------------------------------------*/

#ifndef _OS_SYSTEM_H_
#define _OS_SYSTEM_H_

#ifdef _LANGUAGE_C_PLUS_PLUS
extern "C" {
#endif

#include "ultratypes.h"
#include "os_exception.h"

/*
 * Values for osTvType 
 */
#define OS_TV_PAL   0
#define OS_TV_NTSC  1
#define OS_TV_MPAL  2

/*
 * Size of buffer the retains contents after NMI
 */
#define OS_APP_NMI_BUFSIZE  64

#if defined(_LANGUAGE_C) || defined(_LANGUAGE_C_PLUS_PLUS)

extern s32   osRomType;     /* Bulk or cartridge ROM. 0=cartridge 1=bulk */
extern void *osRomBase;     /* Rom base address of the game image */
extern s32   osTvType;      /* 0 = PAL, 1 = NTSC, 2 = MPAL */
extern s32   osResetType;   /* 0 = cold reset, 1 = NMI */
extern s32   osCicId;
extern s32   osVersion;
extern u32   osMemSize;     /* Memory Size */
extern s32   osAppNMIBuffer[OS_APP_NMI_BUFSIZE/sizeof(s32)];

/*
 * CPU counter increments at 3/4 of bus clock rate:
 *
 * Bus Clock	Proc Clock	Counter (1/2 Proc Clock)
 * ---------	----------	------------------------
 * 62.5 Mhz	93.75 Mhz	46.875 Mhz
 */
extern u64 osClockRate;

extern OSIntMask __OSGlobalIntMask; /* global interrupt mask */

extern void     osExit(void);
extern u32      osGetMemSize(void);

/* pre-NMI */
extern s32      osAfterPreNMI(void);

#endif  /* defined(_LANGUAGE_C) || defined(_LANGUAGE_C_PLUS_PLUS) */

#ifdef _LANGUAGE_C_PLUS_PLUS
}
#endif

#endif /* !_OS_SYSTEM_H_ */
