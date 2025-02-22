
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

/*
 * Interpret & dump a turbo display list for RSPSIM debugging
 *
 */

#include <ultra64.h>
#include <gt.h>
#include "PRinternal/macros.h"

#if BUILD_VERSION < VERSION_J
#ident "$Revision: 1.4 $"
#endif

#undef  PRINTF
#define PRINTF      rmonPrintf


#define TX_MAX		100
static u32	textures[TX_MAX] ALIGNED(0x8);
static u32	numtextures;

#define UNSEG_ADDR(sa)	((u32 *) (((globp)?				   \
			(((int)(sa) & 0x00ffffff) + 			   \
					globp->sp.segBases[(int)(sa)>>24]) \
			: (int)(sa)) | 0x80000000))
#define PHYS(a)		((int) ((int)(a) & 0x7fffffff))
#define UNPHYS(a)	((u32 *) ((int)(a) | 0x80000000))

#define DOPRINT(a,r)	\
rmonPrintf("UNSEG: %x ->(seg%x = %06x)-> %08x\n",(int)(a),(int)(a)>>24,((globp)?(globp->sp.segBases[(int)(a)>>24]):0), (int)(r))



#define UCODE_SIZE_MAX (4096*1)
void
gtDumpTurbo(OSTask *tp,u8 flags)
{
	int 		i;
	gtGfx 		*gtlistp;
	gtGlobState 	*globp=0;
	gtState		*statep;
	u32   		dat,*datp,*addr;


	PRINTF("\nGBI_DUMP_START:\n");
	PRINTF("$ %08x\n",PHYS(tp));

	for (i=(int)tp; i<(int)tp+sizeof(OSTask); i+=4) {
		PRINTF("<%08x\n",(int) *((u32 *) i));
	}

#if 1
	PRINTF("? %08x\n",PHYS(tp->t.ucode_boot));
	for (i=(int)tp->t.ucode_boot; 
			i<(int)tp->t.ucode_boot+tp->t.ucode_boot_size; i+=4) {
		PRINTF("|%08x\n",(int) *((u32 *) i));
	}
	
	PRINTF("? %08x\n",PHYS(tp->t.ucode));
	for (i=(int)tp->t.ucode; i<(int)tp->t.ucode+UCODE_SIZE_MAX; i+=4) {
		PRINTF("|%08x\n",(int) *((u32 *) i));
	}
	
	PRINTF("? %08x\n",PHYS(tp->t.ucode_data));
	for (i=(int)tp->t.ucode_data; 
			i<(int)tp->t.ucode_data+tp->t.ucode_data_size; i+=4) {
		PRINTF("|%08x\n",(int) *((u32 *) i));
	}
	
#endif 



	gtlistp = (gtGfx *) tp->t.data_ptr;
	PRINTF("@ %08x\n",PHYS(gtlistp));

/*
 * Dump turbo display list
 */
	while (gtlistp->obj.statep) {
		PRINTF(">%08x\n",(int) gtlistp->obj.gstatep);
		PRINTF("-%08x\n",(int) gtlistp->obj.statep);
		PRINTF("-%08x\n",(int) gtlistp->obj.vtxp);
		PRINTF("-%08x\n",(int) gtlistp->obj.trip);
		gtlistp++;
	}
	PRINTF(">%08x\n",(int) gtlistp->obj.gstatep);
	PRINTF("-%08x\n",(int) gtlistp->obj.statep);
	PRINTF("-%08x\n",(int) gtlistp->obj.vtxp);
	PRINTF("-%08x\n",(int) gtlistp->obj.trip);

/*
 * Dump infor pointed to by DL
 */
	gtlistp = (gtGfx *) tp->t.data_ptr;
	while (gtlistp->obj.statep) {
/*rmonPrintf("=============== DUMP A DL ENTRY (%x)\n",(int)gtlistp);*/

/*
 * Dump global state
 */
	    if (gtlistp->obj.gstatep) {
	    	addr = UNSEG_ADDR(gtlistp->obj.gstatep);
		globp = (gtGlobState *) addr;
/*rmonPrintf("======= DUMP GlobalState (%x)\n",(int)addr);*/
		PRINTF("& %08x\n",PHYS(addr));
		for (datp = addr;
			(u8 *) datp < (u8 *) addr + sizeof(gtGlobState);
			datp++) {
		    PRINTF("+%08x\n",*datp);
		}
		if (globp->sp.rdpCmds) {
	    	    addr = UNSEG_ADDR(globp->sp.rdpCmds);
/*rmonPrintf("GlobalState RDP cmds (%x)\n",(int)addr);*/
		    PRINTF("& %08x\n",PHYS(addr));
		    for (datp = addr;
				*datp || *(datp+1);
				datp+=2) {
		        PRINTF("+%08x\n",*datp);
		        PRINTF("+%08x\n",*(datp+1));
		    }
		    PRINTF("+%08x\n",*datp);
		    PRINTF("+%08x\n",*(datp+1));
		}
	    }

/*
 * Dump state
 */
	    addr = UNSEG_ADDR(gtlistp->obj.statep);
	    statep = (gtState *) addr;
/*rmonPrintf("======= DUMP State (%x)\n",(int)addr);*/
	    PRINTF("& %08x\n",PHYS(addr));
	    for (datp = addr;
		    (u8 *) datp < (u8 *) addr + sizeof(gtState);
		    datp++) {
	        PRINTF("+%08x\n",*datp);
	    }
	    if (statep->sp.rdpCmds) {
	  	addr = UNSEG_ADDR(statep->sp.rdpCmds);
/*rmonPrintf("DUMP State RDP cmds (%x)\n",(int)addr);*/
		PRINTF("& %08x\n",PHYS(addr));
		for (datp = addr;
			*datp || *(datp+1);
			datp+=2) {
		    PRINTF("+%08x\n",*datp);
		    PRINTF("+%08x\n",*(datp+1));
		}
		PRINTF("+%08x\n",*datp);
		PRINTF("+%08x\n",*(datp+1));
	    }

/*
 * Dump vertices
 */
	    if (gtlistp->obj.vtxp) {
		addr = UNSEG_ADDR(gtlistp->obj.vtxp);
/*rmonPrintf("======= DUMP VTX (%x)\n",(int)addr);*/
		PRINTF("& %08x\n",PHYS(addr));
		for (datp = (u32 *) addr;
			(u8 *) datp < (u8 *) addr +
			    (statep->sp.vtxCount * sizeof(Vtx));
			datp++) {
		    PRINTF("+%08x\n",*datp);
		}
	    }

/*
 * Dump triangles
 */
	    if (gtlistp->obj.trip) {
		addr = UNSEG_ADDR(gtlistp->obj.trip);
/*rmonPrintf("======= DUMP TRI (%x)\n",(int)addr);*/
		PRINTF("& %08x\n",PHYS(addr));
		for (datp = (u32 *) addr;
			(u8 *) datp < (u8 *) addr +
			    (statep->sp.triCount * sizeof(gtTriN));
			datp++) {
		    PRINTF("+%08x\n",*datp);
		}
	    }


		
	    gtlistp++;
	}


/*
 * Dump Last global state
 */
	    if (gtlistp->obj.gstatep) {
	    	addr = UNSEG_ADDR(gtlistp->obj.gstatep);
		globp = (gtGlobState *) addr;
/*rmonPrintf("======= DUMP GlobalState (%x)\n",(int)addr);*/
		PRINTF("& %08x\n",PHYS(addr));
		for (datp = addr;
			(u8 *) datp < (u8 *) addr + sizeof(gtGlobState);
			datp++) {
		    PRINTF("+%08x\n",*datp);
		}
		if (globp->sp.rdpCmds) {
	    	    addr = UNSEG_ADDR(globp->sp.rdpCmds);
/*rmonPrintf("GlobalState RDP cmds (%x)\n",(int)addr);*/
		    PRINTF("& %08x\n",PHYS(addr));
		    for (datp = addr;
				*datp || *(datp+1);
				datp+=2) {
		        PRINTF("+%08x\n",*datp);
		        PRINTF("+%08x\n",*(datp+1));
		    }
		    PRINTF("+%08x\n",*datp);
		    PRINTF("+%08x\n",*(datp+1));
		}
	    }

	PRINTF("^\nGBI_DUMP_END:\n");
	
	
	if (flags & GT_DUMPTURBO_HANGAFTER) {
		for (i=0; i<1000;i++) 
			rmonPrintf("=======================================\n");
		while(1);
	}
		

/*
 *   Dumps stuff
 *   each line is either an address for data to follow or data itself
 *   1st char on line indicates what it is:
 *
 *   $  task header address
 *   @  display list address
 *   &  dma data address
 *   %  texture address
 *   ?  code/code data address
 *
 *   <  task header data
 *   >  1st half of display list command
 *   -  2nd half of display list command
 *   +  dma data
 *   *  texture data
 *   |  code/code data
 *
 */
	
}
