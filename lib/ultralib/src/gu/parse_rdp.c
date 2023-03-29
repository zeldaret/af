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

/* guParseRdpDL works in conjunction with dlprint which must be running on 
 * the host Indy. guParseRdpDL simple uses the hostio routines to send the
 * display list to the Indy, and dlprint does all the parsing.
 */

#ifndef _FINALROM
void guParseRdpDL(u64 *rdp_dl, u64 nbytes, u8 flags)
{
    guDLPrintCB    cntlBlk;

    cntlBlk.dataSize = nbytes;
    cntlBlk.flags = flags;
    cntlBlk.dlType = GU_PARSE_RDP_TYPE;
    cntlBlk.paddr = osVirtualToPhysical(rdp_dl);

    osWriteHost(&cntlBlk,sizeof(cntlBlk));
    osWriteHost(rdp_dl,nbytes);  
        
}

#endif
