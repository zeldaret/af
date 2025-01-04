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

/****************************************************************************
 * NOTE: To view this file correctly, set tabstop=3
*****************************************************************************/												
#include "guint.h"
#include <stdio.h>
#include "ultra64.h"
#include "PRinternal/macros.h"

// TODO: this comes from a header
#ident "$Revision: 1.49 $"

#define TRAM_SIZE       4096    /* in bytes */
#define TRAM_WSIZE      8       /* TRAM word size in bytes */
#define TRAM_LSIZE      8       /* TRAM load word size in bytes */
#define MM_MAX_LEVEL 	7	/* number of mipmap levels 0 to MM_MAX_LEVEL */
#define MM_MIN_SIZE 	1	/* smallest mipmap tile */

struct texelSizeParams
{
	unsigned char gran;
	unsigned char shift;
	unsigned char tsize;
	unsigned char shiftr;
};	

/* texture ram tile */
struct Tile 
{
	int w;		/* width of tile in texels, padded to tram line sz */
 	int s, t;	/* size of tile in texels */
	int addr;	/* address in tram of tile */
};

/* tram mipmaps */
static struct Tile mipmap[MM_MAX_LEVEL+1] ALIGNED(0x8);
static struct texelSizeParams sizeParams[4] =
					{ 16, 3, 1, 0,
					   8, 2, 2, 1,
					   4, 1, 4, 2,
					   2, 0, 8, 3
					};


static int 		max_mipmap;
static unsigned char 	*tram;
static int		txlsize;
static int		errNo = 0;
static int		NA = 0;  /* Not applicable */
static unsigned int 	length;  /* total texels in mipmap */
static int 				level;	/* total levels in mipmap */

static void get3x3(struct Tile *tile, int *s, int *t, int *texel, int shift, int size);
static void stuffDisplayList(Gfx **glistp, Image *im, char *tbuf, unsigned char startTile, 
		unsigned char pal, unsigned char cms, unsigned char cmt, 
		unsigned char masks, unsigned char maskt, unsigned char shifts, 
		unsigned char shiftt);
static void  kernel(int i, int r1, int g1, int b1, int a1, float *r2, float *g2, 
		float *b2, float *a2);

#define unpack_ia16(c,i,a) \
	i = (c & 0xff00) >> 8, a = (c & 0xff)
#define pack_ia16(i,a) \
	(i << 8) | a

#define unpack_ia8(c,i,a) \
	i = ((c & 0xf0) >> 4), a = (c & 0xf)
#define pack_ia8(i,a) \
	(a & 0xf) | ((i & 0xf) << 4)

#define unpack_ia4(c,i,a) \
	i = ((c & 0xe) >> 1),  a = (c & 0x1)
#define pack_ia4(i,a) \
	((i & 0x7) << 1) | ((a & 0x1))

#define unpack_i4(c,i) \
	i = (c & 0xf)
#define pack_i4(i) \
	 (i)

#define unpack_i8(c,i) \
	i = (c & 0xff)
#define pack_i8(i) \
	 (i)

#define unpack_ci8(c,ci) unpack_i8(c,ci)
#define pack_ci8(ci) pack_i8(ci)

#define unpack_ci4(c,ci) unpack_i4(c,ci)
#define pack_ci4(ci) pack_i4(ci)

#define unpack_rgba(c,r,g,b,a) \
   (r = (c & 0xf800) >> 11), g = ((c & 0x07c0) >> 6), b = ((c & 0x003e) >> 1), \
   a = (c & 0x1)

#define pack_rgba( r, g, b, a)  ((r&0x1f) << 11) | (g&0x1f) << 6 | \
                ((b&0x1f) << 1) | (a)

/*************************************************************************
 * Generates all levels of a power-of-two mipmap from an input array.	 *
 * Also stuffs display list with entries for loading and rendering the	 *
 * texture. Filtering Color-Index maps makes sense only if the lookup	 *
 * is a linear ramp. Billboards and trees cutout using alpha will change *
 * shape as the level changes due to change in map resolution. Texel 	 *
 * formats with only one bit of alpha will not be filtered very well.	 *
 *************************************************************************
 * ErrNo value		error description				 *
 *-----------------------------------------------------------------------*
 * 	1		Mipmap too big to load into tmem. Not Fatal,     *
 *			will load as many levels as there is space for.  *
 * 									 *
 * 	2		Texel format not supported, Fatal error		 *
 ************************************************************************/

int guLoadTextureBlockMipMap(Gfx **glistp, unsigned char *tbuf, Image *im,
 unsigned char startTile, unsigned char pal, unsigned char cms, unsigned char cmt, 
 unsigned char masks, unsigned char maskt, unsigned char shifts, unsigned char shiftt, 
 unsigned char cfs, unsigned char cft)
{
  
	unsigned char	*iaddr, *taddr;
	int		im_bytes, tr_bytes;
	int		h, b;
	int		flip;
	char		startUnAligned;
	char		endUnAligned;

	txlsize = sizeParams[im->siz].tsize; /* texel size in nibbles */
						 /* to next line size */

	/*
 	 * Do top level map, swizzle bytes on odd t's							 *
 	 */
	/* base char address of tile to be loaded */
	iaddr = ((im->t * im->lsize)+((im->s * txlsize) >> 1) + im->base);

	/*check tile line starting and ending alignments along 4bit bndries */
	startUnAligned = ((im->s & 0x1)  && (im->siz == G_IM_SIZ_4b));
	endUnAligned = (((im->s + im->w) & 0x1) && (im->siz == G_IM_SIZ_4b));

	im_bytes = ((im->w * txlsize + 1) >> 1); /* siz of 1 tile line in bytes */
	tr_bytes = im_bytes / TRAM_LSIZE; /* no of tram lines per tile line */
	tr_bytes = tr_bytes * TRAM_LSIZE; /* tile line size in bytes */
	if (im_bytes > tr_bytes) tr_bytes += TRAM_LSIZE;
        
	taddr = &tbuf[im->addr]; /* why ? make this zero?*/

	if (startUnAligned)
	{
	  for (h=0; h<im->h; h++)
     	  {
	  	flip = (h & 1) << 2; /*shift does not depend on txlsize*/
	 	for (b=0; b<im_bytes; b++) 
 	 	{
	   	*(taddr+(b^flip)) = ((*(iaddr+b) & 0x0f) << 4) 
		   | ((*(iaddr+b+1) & 0xf0) >> 4);
	 	}
	 	/* add last aligned nibble */
	 	if (!endUnAligned) *(taddr+((b-1)^flip)) &= (0xf0);
	  	/* pickup trailing bytes */
	  	for (b=im_bytes; b<tr_bytes; b++) *(taddr+(b^flip)) = 0;
	  	iaddr += im->lsize;
	  	taddr += tr_bytes;
     		}
	} 
	else  /* if start aligned */
	{
		for (h=0; h<im->h; h++) 
		{
			flip = (h & 1) << 2; /*shift does not depend on txlsize*/
			for (b=0; b<im_bytes; b++)
			*(taddr+(b^flip)) = *(iaddr+b);

			/* zero out last extra nibble */
			if (endUnAligned) *(taddr+((b-1)^flip)) &= (0xf0);
			/* pad trailing bytes with zeroes */
			for (b=im_bytes; b<tr_bytes; b++) *(taddr+(b^flip)) = 0;

			iaddr += im->lsize;
			taddr += tr_bytes;
	   	}
	}

	tram = tbuf;

	/* save tile attributes in top mipmap */
	mipmap[0].s = im->w; /* tile width  */
	mipmap[0].t = im->h; /* tile height */
        /*  guaranteed no remainder ? */
	mipmap[0].w = ((tr_bytes / txlsize) << 1); /* tile line width in texels*/
	mipmap[0].addr = im->addr;
	max_mipmap = MM_MAX_LEVEL;
	length = mipmap[0].w*mipmap[0].t; /* total texels in level 0 */
/**
        rmonPrintf("level0 w,t,l = %d %d %d\n",mipmap[0].w, mipmap[0].t,length);
***/

/******************************************************************************
	Generate other levels of mipmap using a box filter
******************************************************************************/

{/* generate mip map for this tile */
 	unsigned char *taddr, *saddr;
 	int shift = (int) sizeParams[im->siz].shift;
 	int s, t, si, ti, sii, tii;
 	int s4[9];
 	int t4[9];
 	int tex4[9];
 	int r0, g0, b0, a0, r1, g1, b1, a1;
	float r2 ,g2, b2, a2;
	float dummy;
 	int i0, ci0, ia0, i1, ci1, ia1;
	float i2, ci2, ia2;
 	int texel;
 	int i,trip;
 	unsigned int tempaddr;
 	int ntexels = ((TRAM_LSIZE/txlsize) << 1); /* texels per line */
 
	level = 0;  /* need to check for memory overflow */
	while ((mipmap[level].s > 1) || (mipmap[level].t > 1))
	{
		level++;
 		/* 
		 * set new mipmap level address in bytes
		 */
 		mipmap[level].addr = mipmap[level-1].addr +
 		(mipmap[level-1].w * txlsize * mipmap[level-1].t  >> 1);

 		/* 
		 * grab location in tram pointing to the current level address 
		 */
 		taddr = &(tram[ mipmap[level].addr ]);

 		/* 
		 * downfilter by 2X, bump odd size 
	   	 * compute parameters for new mipmap level 
		 */
 		mipmap[level].s = (mipmap[0].s) >> level;
 		mipmap[level].t = (mipmap[0].t) >> level;

		if (mipmap[level].s == 0) mipmap[level].s = 1;
		if (mipmap[level].t == 0) mipmap[level].t = 1;

 		/* 
		 * width must be a multiple of 8 bytes (padding for tram line size)
		 */
		mipmap[level].w = 
		((mipmap[level].s + (ntexels -1)) >> (shift +1) << (shift +1));

		/*
		 * compute total no of texels to be loaded
		 */
	 	length += mipmap[level].w*mipmap[level].t; 
/**
                rmonPrintf("level, w,t,l = %d %d %d %d\n", level, mipmap[level].w, mipmap[level].t,length);
**/
	   	if ((length*txlsize >> 1) >= TRAM_SIZE)
      		{
		  errNo = 1;
	 	  length -= mipmap[level].w*mipmap[level].t; 
	     	  break;
	   	}

 		/* 
		 * for each scanline 
		 */
 		for (t=0; t<mipmap[level-1].t; t+=2) 
		{
 		   flip = 0;
		   trip =  (t & 2) << 1;	/* invert bit 4 on odd line */
 		   ti = t + 1;
	           tii = t - 1;

		  /*
	 	   * check filtering clamp/wrap flag and do accordingly
  		   */
		   if ( cft) {
			if (ti >= mipmap[level-1].t) ti = t;
            		if (tii < 0) tii = t;
		   } else {
 			if (ti >= mipmap[level-1].t) ti = 0;
	      	   	if (tii < 0) tii = mipmap[level-1].t - 1;
		   }

		   tempaddr = 0;

 	    	   for (s=0; s<mipmap[level-1].s; s+=2) 
		   {
 			si  = s + 1;
			sii = s - 1;
		  	/*
	 	 	 * duplicate last texel for odd sizes for filtering
  			 */
			if (cfs) {
			   if (si >= mipmap[level-1].s) si = s;
               		   if (sii < 0) sii = s;
			} else {
 			   if (si >= mipmap[level-1].s) si = 0;
			   if (sii < 0) sii = mipmap[level-1].s - 1;
			}

/***
			if (level == 6) 
			rmonPrintf("sts = %d %d %d %d %d %d\n",
			s, si, sii, t, ti, tii);
***/

			/*
			 * grab the nine neighbours to apply kernel function
			 */
 			s4[0] = s;   t4[0] = tii;
 			s4[1] = si;  t4[1] = tii;
 			s4[2] = si;  t4[2] = t;
 			s4[3] = si;  t4[3] = ti;
 			s4[4] = s;   t4[4] = ti;
 			s4[5] = sii; t4[5] = ti;
 			s4[6] = sii; t4[6] = t;
 			s4[7] = sii; t4[7] = tii;
 			s4[8] = s;   t4[8] = t;

 			get3x3( &mipmap[level-1], s4, t4, tex4, shift, im->siz);

			saddr = taddr + ((tempaddr >> 1)^trip);
 			r1 = g1 = b1 = a1 = ci1 = i1 = 0;
 			r2 = g2 = b2 = a2 = ci2 = i2 = 0;
		
			/*
			 * Extract R,G and B components of the 9 texels and 
			 * apply the filter kernel
			 */
			switch (im->fmt)
			{
			   case (G_IM_FMT_RGBA):
		  	   	if (im->siz == G_IM_SIZ_16b)
				{
 		           	   for (i=0; i< 9; i++) 
				   {
 			  	      unpack_rgba(tex4[i], r0, g0, b0, a0);
				      kernel(i, r0, g0, b0, a0, &r2, &g2, &b2, &a2);
/***
				      if (level == 6) 
				      rmonPrintf("r0, g0, b0, a0 = %d %d %d %d\n",
					r0, g0, b0, a0);
**/
			  	   }
				   r1 = (int)(r2/16.0 + 0.5);
				   g1 = (int)(g2/16.0 + 0.5);
				   b1 = (int)(b2/16.0 + 0.5);
				   a1 = (int)(a2/16.0 + 0.5);
				} 
				else 
				{ 
				   /*
				    * RGBA32 is not supported
				    */
				   errNo = 2;
				   return errNo;
				}
			  	break;

			   case (G_IM_FMT_YUV):
				errNo = 2;
				return errNo;
			  	break;

			   case (G_IM_FMT_CI):	
			  	if (im->siz == G_IM_SIZ_4b)
				{
 		      		  for (i=0; i<9; i++) 
				  {
			     	     unpack_ci4(tex4[i],ci0);
				     kernel(i, ci0, 0, 0, 0, &ci2, &dummy, &dummy, 
					    &dummy);
			     	   }
				   ci1 = (int)(ci2/16.0 + 0.5);
		      		}
			  	else 
				if (im->siz == G_IM_SIZ_8b)
				{
				   for (i=0; i<9; i++)
				   {
			       	      unpack_ci8(tex4[i],ci0);
				      kernel(i, ci0, 0, 0, 0, &ci2, &dummy, 
					     &dummy, &dummy);
			      	    }
				    ci1 = (int)(ci2/16.0 + 0.5);
			  	}
				else
				{
				    errNo=2;
				    return errNo;
				}
			  	break;		

			   case (G_IM_FMT_IA):
			  	if (im->siz == G_IM_SIZ_4b)
				{
	            		   for (i=0; i<9; i++) 
				   {
                   		      unpack_ia4(tex4[i],i0,a0);
				      kernel(i, i0, a0, 0, 0, &i2, &a2, &dummy, 
					     &dummy); 
                  		    }  
				    i1 = (int)(i2/16.0 +0.5);
				    a1 = (int)(a2/16.0 +0.5);
               			}
               			else if (im->siz == G_IM_SIZ_8b)
				{
               		           for (i=0; i<9; i++) 
				   {
                  		      unpack_ia8(tex4[i],i0,a0);
				      kernel(i, i0, a0, 0, 0, &i2, &a2, &dummy, 
					     &dummy);
				   }
				   i1 = (int)(i2/16.0 +0.5);
				   a1 = (int)(a2/16.0 +0.5);
                		}
	     		  	else 
				if (im->siz == G_IM_SIZ_16b)
				{
                 		   for (i=0; i<9; i++) 
				   {
                   		      unpack_ia16(tex4[i],i0,a0);
				      kernel(i, i0, a0, 0, 0, &i2, &a2, &dummy, 
					     &dummy);
                  		    }
				    i1 = (int)(i2/16.0 +0.5);
				    a1 = (int)(a2/16.0 +0.5);
               			} 
				else
				{
				    errNo = 2;
				    return errNo;
				}
			  	break;

			   case (G_IM_FMT_I):
				if (im->siz == G_IM_SIZ_4b)
				{
		 		   for (i=0; i<9; i++) 
				   {
                			unpack_i4(tex4[i],i0);
					kernel(i, i0, 0, 0, 0, &i2, &dummy, &dummy,
					       &dummy);
           			    }  
				    i1 = (int)(i2/16.0 + 0.5);
              			}
              			else 
				if (im->siz == G_IM_SIZ_8b)
				{
              			   for (i=0; i<9; i++)
				   {
              				unpack_i8(tex4[i],i0);
					kernel(i, i0, 0, 0, 0, &i2, &dummy, &dummy,
					       &dummy);
              			   }
				   i1 = (int)(i2/16.0 +0.5);
               			}
				else
				{ 
				   errNo = 2;
				   return errNo;
				}
					
			   default:
			   break;
 			}

			/*
		 	 * Pack fields into destination texel
		         */
			switch (im->fmt)
			{

			   case (G_IM_FMT_RGBA):
			  	texel = pack_rgba(r1,g1,b1,a1); 
			     	*(short *)((int)saddr^flip) = texel;
				break;

			   case (G_IM_FMT_YUV):
				break;

			   case (G_IM_FMT_CI):	

			  	if (im->siz == G_IM_SIZ_4b)
				{
			     		texel = pack_ci4(ci1);
			     		*(char *)((int)saddr^flip) |= (s & 0x2)? 
					(texel): (texel << 4);
			 	}
				else
				if (im->siz == G_IM_SIZ_8b)
				{
			     		texel = pack_ci8(ci1);
			     		*(char *)((int)saddr^flip) = texel;
			  	}
		  		break;	

			   case (G_IM_FMT_IA):
			  	if (im->siz == G_IM_SIZ_4b)
				{
                  			texel = pack_ia4(i1,a1);  
			     		*(char *)((int)saddr^flip) |= (s & 0x2)?
			     		(texel): (texel << 4);
			  	}
                  		else 
				if (im->siz == G_IM_SIZ_8b)
				{
                  			texel = pack_ia8(i1,a1); 
			     		*(char *)((int)saddr^flip) = texel;
			  	}
                  		else 
				if (im->siz == G_IM_SIZ_16b)
				{
					texel = pack_ia16(i1,a1); 
			    		*(short *)((int)saddr^flip) = texel;
                  		}
				break;

			   case (G_IM_FMT_I):
			  	if (im->siz == G_IM_SIZ_4b)
				{
                  			texel = pack_i4(i1);
			     		*(char *)((int)saddr^flip) |= (s & 0x2)?
			     		(texel): (texel << 4);
			    	}
                 		else
				if (im->siz == G_IM_SIZ_8b)
				{
                  			texel = pack_i8(i1); 
			     		*(char *)((int)saddr^flip) = texel;
                  		}
				break;
 			}

			tempaddr += txlsize;

 		   } /* end s */

 		   taddr += ((mipmap[level].w * txlsize) >> 1);

		} /* end t */

 		if (mipmap[level].s <= MM_MIN_SIZE && 
		    mipmap[level].t <= MM_MIN_SIZE) 
		{
 		  max_mipmap = level;
 		  break;
 		}
 	} /* end level */

}/* end generate mipmap */
/* 
 * Add entries for texture loading and rendering in DL 
 */
stuffDisplayList(glistp, im, tbuf, startTile, pal, cms, cmt, masks, maskt, shifts, shiftt);

return errNo;
} /* end guLoadTextureBlockMipMap */

/******************************************************************************
 * 
 * Apply Kernel :
 *			1  2  1
 * 			2  4  1
 * 			1  2  1
 ******************************************************************************/
static void kernel(int i, int r0, int g0, int b0, int a0, float *r2, float *g2, float *b2, float *a2)
{
		if (i == 8)
		{
			*r2 += r0*4; *g2 += g0*4; *b2 += b0*4; *a2 += a0*4;
		} else 
 		if (i%2 == 0)
		{
 	   		*r2 += r0*2; 
			*g2 += g0*2; 
			*b2 += b0*2; 
			*a2 += a0*2;
		} else
		{
 	   		*r2 += r0; 
			*g2 += g0; 
			*b2 += b0; 
			*a2 += a0;
		}
}

/********************************************************************
 Add entries for loading and rendering textures into the display list
*********************************************************************/
static void stuffDisplayList(Gfx **glistp, Image *im, char *tbuf, unsigned char startTile,
		unsigned char pal, unsigned char cms, unsigned char cmt, 
		unsigned char masks, unsigned char maskt, unsigned char shifts, 
		unsigned char shiftt)
{ 
	int tile;	
	int Smask, Tmask;
	int Sshift, Tshift;

	/* 
	 * set LOADTILE for loading texture 
    	 * 4-bit textures are loaded in 8-bit chunks
	 */
	if (im->siz == G_IM_SIZ_4b) {
	   gDPSetTextureImage((*glistp)++, im->fmt, G_IM_SIZ_8b, 1, 
      	   osVirtualToPhysical((unsigned short *)tbuf));
	   gDPSetTile((*glistp)++, im->fmt, G_IM_SIZ_8b, NA, 0, G_TX_LOADTILE, NA,
		NA, NA, NA, NA, NA, NA);
	   /* Wait until all primitives are done */
	   gDPLoadSync((*glistp)++);
	   gDPLoadBlock((*glistp)++, G_TX_LOADTILE, 0, 0, length/2, 0x0);
	} else {
	   gDPSetTextureImage((*glistp)++, im->fmt, im->siz, 1, 
           osVirtualToPhysical((unsigned short *)tbuf));
	   gDPSetTile((*glistp)++, im->fmt, im->siz, NA, 0, G_TX_LOADTILE, NA,
      	   NA, NA, NA, NA, NA, NA);
	   /* Wait until all primitives are done */
	   gDPLoadSync((*glistp)++);
	   gDPLoadBlock((*glistp)++, G_TX_LOADTILE, 0, 0, length, 0x0);
	}
			
	for (tile = 0; tile <= level; tile ++)
	{
 	    Tmask = maskt-tile;
	    if (Tmask < 0){ 
		Tmask = 0;
	    } else {
		Tshift = tile;
	    }
		
 	    Smask = masks-tile;
	    if (Smask < 0){ 
		Smask = 0;
	    } else {
		Sshift = tile;
	    }

/***
	    rmonPrintf("tile, Tmask, Tshift, Smask, Sshift %d %d %d %d %d\n",
	    tile, Tmask, Tshift, Smask, Sshift);
	    rmonPrintf("%d\n",startTile);
***/

	
	    gDPSetTile((*glistp)++,im->fmt, im->siz, (mipmap[tile].w*txlsize >> 4), 
	    (mipmap[tile].addr >>  3), tile+startTile, pal, cmt, Tmask, Tshift, cms, 
	    Smask, Sshift);

	    gDPSetTileSize((*glistp)++,tile+startTile, (0 <<G_TEXTURE_IMAGE_FRAC), 
	    (0 <<G_TEXTURE_IMAGE_FRAC), (mipmap[tile].s-1) <<G_TEXTURE_IMAGE_FRAC, 
   	    (mipmap[tile].t-1) << G_TEXTURE_IMAGE_FRAC);
	}
}

/******************************************************************************
	Extract quad of texels for filtering.  Compute bank and row addresses.
******************************************************************************/
static void get3x3(struct Tile *tile, int *s, int *t, int *texel, int shift, int size)
{
	int		i;
	int		bank, row;
	unsigned int	addr;
	int		overlap;
	unsigned char	r, g, b, a;
	unsigned long	tex;
	struct Image *im;
	unsigned int ss,tt;

	for (i=0; i< 9; i++) 
	{
		ss = s[i];
		tt = t[i];
		/* bank and row indexing */
		bank = (((ss & (0x3 << (shift-1))) >> (shift-1)) ^ ((tt & 0x1) << 1)) << 1;
		row = (((tt * tile->w + ss) * txlsize) >> 1) / TRAM_LSIZE;
		addr = tile->addr + row * TRAM_WSIZE + bank;

		overlap = (i == 0) ? bank : overlap ^ bank;

		switch  (size)
		{
			case G_IM_SIZ_4b:
				texel[i] = (tram[addr + ((ss & 0x2) >> 1)]
				& (0xf0 >> ((ss & 0x1) << 2)));
				if (!(ss & 0x1)) texel[i] = texel[i] >> 4;
				break;

			case G_IM_SIZ_8b:
				texel[i] = tram[addr + (ss & 0x1)];
				break;

			case G_IM_SIZ_16b:
	  			texel[i] = (tram[addr] << 8) | tram[addr+1];
	  			break;

			case G_IM_SIZ_32b:
				errNo = 2; /* Format not supported */
				break;

			default: 
	  			break;
		}

	}
}
