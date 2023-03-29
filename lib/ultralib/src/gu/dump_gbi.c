
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
 * Interpret Task with GBI display list and dump it for debugging.
 */


/**************************************************
 *
 *          guDumpGbiDL no longer supported        
 *   applications should use guParseGbiDL with the 
 *   GU_PARSEGBI_DUMPONLY  flag set.               
 *
 **************************************************/


#if 0


#include "ultra64.h"
#include "bstring.h"

#undef  PRINTF
#define PRINTF      osSyncPrintf

#define DL_STACKSIZE	11
static u32            *Gp[DL_STACKSIZE];

#define TX_MAX		100
static u32	textures[TX_MAX];
static u32	numtextures;

static u32      segment_base[16];
static u32      dotextures = TRUE;
static int      dl_depth = 0;


/*
 * dump a DMA-type display list command.
 */
static void
dump_dma(u32 *bufp)
{
    u32             addr,
	           *data;
    u8              seg_id;
    u16             len;
    char            op,
	            b0;

    op = ((*bufp & 0xff000000) >> 24);

    /*
     * DMA op addressing is all the same: 
     */
    seg_id = (u8) ((bufp[1] & 0x0f000000) >> 24);
    addr = segment_base[seg_id] + (bufp[1] & 0x00ffffff);


    addr = (u32) osPhysicalToVirtual(addr);

    len = (u16) (bufp[0] & 0x0000ffff);

    PRINTF(">%08x\n-%08x\n", bufp[0], bufp[1]);
    if (op == (char) G_DL) {
	b0 = (char) ((bufp[0] & 0x00ff0000) >> 16);
	++dl_depth;
	if (dl_depth > (DL_STACKSIZE - 1)) {
	    PRINTF("***** Error, max levels of display lists exceeded\n");
	    return;
	}
	Gp[dl_depth] = (u32 *) addr;
	PRINTF("@ %08x\n",(int)Gp[dl_depth]&0x7fffffff);
    } else {
	PRINTF("& %08x\n", (int)addr&0x7fffffff);
	data = (u32 *) addr;
	while(len>0) {
	    PRINTF("+%08x\n", *data);
	    data++;
	    len -= 4;
	}
	PRINTF("@ %08x\n",(int)(Gp[dl_depth] + (sizeof(Gfx) >> 2))&0x7fffffff);
    }
}

/*
 * dump a IMM-type display list command.
 */
static void
dump_imm(u32 *bufp)
{
	char            op,
		b0;

    op = ((*bufp & 0xff000000) >> 24);

    PRINTF(">%08x\n-%08x\n", bufp[0], bufp[1]);
    if (op == (char) G_ENDDL) {
		dl_depth--;
		if (dl_depth >= 0) {
			PRINTF("@ %08x\n",(int)(Gp[dl_depth] + (sizeof(Gfx) >> 2))&0x7fffffff);
		}
    }
    if (op == (char) G_MOVEWORD) {
		if (((bufp[0] ) & 0xff) == G_MW_SEGMENT) {
			b0 = (char) ((bufp[0] & 0xff00)>>10);
			segment_base[b0] = bufp[1] & 0x00ffffff;
		}
    }
}

/*
 * dump a RDP-type display list command.
 */
static void
dump_rdp(u32 *bufp)
{
	u8              seg_id;
	u32             addr;
	int             i0,
	                i1;
	char            op;

    op = ((*bufp & 0xff000000) >> 24);

    PRINTF(">%08x\n-%08x\n", bufp[0], bufp[1]);
    if (op == (char) G_SETTIMG && dotextures) {
		if (numtextures>=TX_MAX) {
			PRINTF("GBI DUMP ERROR: too many textures (max=%d)\n",TX_MAX);
			return;
		}
		seg_id = (u8) ((bufp[1] & 0x0f000000) >> 24);
		addr = segment_base[seg_id] + (bufp[1] & 0x00ffffff);
		addr = (u32) osPhysicalToVirtual(addr);
		i1=1;
		for (i0=0;i0<numtextures;i0++)
			if (textures[i0] == addr) i1=0;
		if (i1) textures[numtextures++]=addr;
    }
}

/*
 * Takes a pointer in DRAM, and a length in bytes. Dumps
 * the display list, until a G_ENDDL command is found.
 */
static void
guDumpGbi(u32 *gfxp)
{
	u8              op;
	u32             readBuf[4];

	Gp[dl_depth] = gfxp;
	numtextures=0;

	PRINTF("@ %08x\n",(int)Gp[dl_depth]&0x7fffffff);

	while ((dl_depth >= 0) && (dl_depth < (DL_STACKSIZE - 1))) {

		op = (u8) ((*Gp[dl_depth] & 0xff000000) >> 24);
		bcopy((char *) Gp[dl_depth], (char *) &(readBuf[0]), sizeof(Gfx));

		switch (op & 0xc0) {

			case (u8) 0x00:
				dump_dma(readBuf);
				break;

			case (u8) 0x80:
				dump_imm(readBuf);
				break;

			case (u8) 0xc0:
				dump_rdp(readBuf);
				break;

			default:
				PRINTF("ERROR : display list is lost, op = %02x\n", op);
				break;

		}

		if (op != (u8) G_DL) {
			Gp[dl_depth] += (sizeof(Gfx) >> 2);
		}
	}
        if (dotextures) {
                u32 i,j;
                for (i=0; i<numtextures; i++) {
                        PRINTF("%% %08x\n",textures[i]&0x7fffffff);
                        for (j=textures[i]; j<textures[i]+0x400; j+=4) {
                                PRINTF("*%08x\n",(int) *((u32 *) j));
                        }
                }
        }
}

#define UCODE_SIZE_MAX (4096*3)
void
guDumpGbiDL(OSTask *tp,u8 flags)
{
	int i;

	if (flags & GU_PARSEGBI_NOTEXTURES) dotextures=0;

	PRINTF("\nGBI_DUMP_START:\n");
	PRINTF("$ %08x\n",(int) tp & 0x7fffffff);

	for (i=(int)tp; i<(int)tp+sizeof(OSTask); i+=4) {
		PRINTF("<%08x\n",(int) *((u32 *) i));
	}

	PRINTF("? %08x\n",(int) tp->t.ucode_boot & 0x7fffffff);
	for (i=(int)tp->t.ucode_boot; i<(int)tp->t.ucode_boot+tp->t.ucode_boot_size; i+=4) {
		PRINTF("|%08x\n",(int) *((u32 *) i));
	}
	
	PRINTF("? %08x\n",(int) tp->t.ucode& 0x7fffffff);
	for (i=(int)tp->t.ucode; i<(int)tp->t.ucode+UCODE_SIZE_MAX; i+=4) {
		PRINTF("|%08x\n",(int) *((u32 *) i));
	}
	
	PRINTF("? %08x\n",(int) tp->t.ucode_data & 0x7fffffff);
	for (i=(int)tp->t.ucode_data; i<(int)tp->t.ucode_data+tp->t.ucode_data_size; i+=4) {
		PRINTF("|%08x\n",(int) *((u32 *) i));
	}
	

	guDumpGbi((u32 *) tp->t.data_ptr);


        PRINTF("^\nGBI_DUMP_END:\n");

	if (flags & GU_PARSEGBI_HANGAFTER) {
	    int i;
	    for (i=0; i<1000;i++) 
	    PRINTF("=============================================================\n");
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

#endif
