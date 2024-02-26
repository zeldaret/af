
/**************************************************************************
 *                                                                        *
 *               Copyright (C) 1994, Silicon Graphics, Inc.               *
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

#ifndef _FINALROM

/*
 * guParseGbiDL works in conjunction with the dlprint tool. dlprint must be
 * running on the host Indy. guParseGbiDL, sends a bunch of blocks of data,
 * with a minimum of one display list, but typically, the principle display
 * list with a bunch of branched or nested display lists, as well as all the
 * vertex and matrix data that will be used. After all the blocks of data 
 * are sent, a GU_PARSE_READY command is sent, and dlprint parses out the
 * data printing it to stdout.
 *
 * In order to know what data to send, guParseGbiDL must step through the 
 * display list, find all the gSPDisplayList and gSPBranchList calls, go
 * to those lists, and also find and send info for all the matrix and vertex
 * calls.
 */
void guParseGbiDL(u64 *gbi_dl, u32 nbytes, u8 flags)
{
    guDLPrintCB    cntlBlk;
    Gfx*           dlStk[11];
    s32            dlcount = 0;
    Gfx            *curGfx,*dlPtr,*vaddr;
    s8             op;
    u32            *word0;
    u32            *word1;
    u32            segments[16];
    u32            param, seg;
    u32            paddr,len;


    cntlBlk.dataSize = nbytes;
    cntlBlk.flags = flags;
    cntlBlk.dlType = GU_PARSE_GBI_TYPE;
    cntlBlk.paddr = osVirtualToPhysical(gbi_dl);

    osWriteHost(&cntlBlk,sizeof(cntlBlk));
    osWriteHost(gbi_dl,nbytes);  
        
    dlStk[0] = (Gfx*)gbi_dl;
    while((dlcount >= 0) && (dlcount <= 10))
    {
        curGfx = dlStk[dlcount];    /* get the current graphics display list */
        op = *((s8*)curGfx);        /* get the first byte */
        dlStk[dlcount]++;           /* increment to next gfx command */
        switch(op)
        {
	    case G_MOVEWORD:
                word0 = (u32*)curGfx;       /* get ptr to first word */
                if(((*word0) & 0x000000ff) == G_MW_SEGMENT)
                {
                    u32  seg;
                    seg = (((*word0) & 0x00ffff00) >> 8) >> 2;
                    word1 = word0 + 1;
                    segments[seg] = *word1;
                }
                break;
            case G_ENDDL:   
                dlcount--;
                break;
            case G_DL:
                word0 = (u32*)curGfx;       /* get ptr to first word */
                param = ((*word0) & 0x00ff0000) >> 16; /* get param */
                word1 = word0 + 1;          /* get pointer to second word */
#if BUILD_VERSION >= VERSION_J
                seg = ((*word1) & 0x0f000000) >> 24; /* get the segment */
#else
                seg = ((*word1) & 0xff000000) >> 24; /* get the segment */
#endif
                paddr = segments[seg] + ((*word1) & 0x00ffffff);
                vaddr = (Gfx*)osPhysicalToVirtual(paddr);
                len = 1;
                dlPtr = vaddr;
                while((*(s8*)dlPtr) != G_ENDDL)
                {
                    len++;
                    dlPtr++;
                }
                len *= sizeof(Gfx);
                        
                cntlBlk.dataSize = len;
                cntlBlk.dlType = GU_PARSE_GBI_TYPE;
                cntlBlk.paddr = paddr;
                        
                osWriteHost(&cntlBlk,sizeof(cntlBlk));
                osWriteHost((u8*)vaddr,len); 
                if(param == G_DL_PUSH)
                {
                    if(dlcount < 10)
                        dlcount++;
                    else
                        osSyncPrintf("Display lists nested too deep!!!\n");
                }
                dlStk[dlcount] = (Gfx*)vaddr;
                break;
            case G_VTX:
            case G_MOVEMEM:
            case G_MTX:
                word0 = (u32*)curGfx;       /* get ptr to first word */
                word1 = word0 + 1;          /* get pointer to second word */
#if BUILD_VERSION >= VERSION_J
                seg = ((*word1) & 0x0f000000) >> 24; /* get the segment */
#else
                seg = ((*word1) & 0xff000000) >> 24; /* get the segment */
#endif
                paddr = segments[seg] + ((*word1) & 0x00ffffff);
                vaddr = (Gfx*)osPhysicalToVirtual(paddr);
                len = (*word0) & 0x0000ffff;
                cntlBlk.dataSize = len;  /* always send 32 bytes, the most used */
                cntlBlk.dlType = GU_PARSE_MEM_BLOCK;
                cntlBlk.paddr = paddr;
                osWriteHost(&cntlBlk,sizeof(cntlBlk));
                osWriteHost((u8*)vaddr,len);
                break;
                
        }
    }

    cntlBlk.dlType = GU_PARSE_READY;
    osWriteHost(&cntlBlk,sizeof(cntlBlk)); 
}

#endif

