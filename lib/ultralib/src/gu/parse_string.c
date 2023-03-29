/**************************************************************************
 *                                                                        *
 *               Copyright (C) 1995, Silicon Graphics, Inc.               *
 *                                                                        *
 *  These coded instructions, statements, and computer programs  contain  *
 *  unpublished  proprietary  information of Silicon Graphics, Inc., and  *
 *  are protected by Federal copyright  law.  They  may not be disclosed  *
 *  to  third  parties  or copied or duplicated in any form, in whole or  *
 *  in part, without the prior written consent of Silicon Graphics, Inc.  *
 *                                                                        *
 *************************************************************************/
#include <ultra64.h>
#include <ultrahost.h>
#include <gu.h>

/* guParseString works in conjunction with dlprint which must be running on 
 * the host Indy. guParseString simply uses the hostio routines to send the
 * string to the Indy, and dlprint does all the parsing.
 */

#ifndef _FINALROM
void guParseString(char *StringPointer, u64 nbytes)
{
    guDLPrintCB    cntlBlk;

    cntlBlk.dataSize = nbytes /* /8 + ((nbytes%8) != 0) */;
    cntlBlk.dlType = GU_PARSE_STRING_TYPE;
    cntlBlk.paddr = osVirtualToPhysical((u64 *) StringPointer);

    osWriteHost(&cntlBlk,sizeof(cntlBlk));
    osWriteHost((u64 *) StringPointer,nbytes);  
        
}

#endif
