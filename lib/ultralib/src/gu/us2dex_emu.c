/*---------------------------------------------------------------------*
	Copyright (C) 1998, Nintendo.
	
	File		us2dex_emu.c
	Coded    by	Yoshitaka Yasumoto.	Apr  9, 1998.
	
	$Id: us2dex_emu.c,v 1.9 1999/07/08 05:02:04 yurugi Exp $
 *---------------------------------------------------------------------*/
#define		F3DEX_GBI
#include	<ultra64.h>
#include	<PR/gs2dex.h>

#define	RSP_DEBUG

static	u16	scissorX0 = 0;		/* (s13.2) */
static	u16	scissorY0 = 0;		/* (s13.2) */
static	u16	scissorX1 = 320<<2;	/* (s13.2) */
static	u16	scissorY1 = 240<<2;	/* (s13.2) */
static	u8	flagBilerp = 0;

static	u32	rdpSetTimg_w0, rdpSetTile_w0;
static  u16	tmemSliceWmax;
static  u16	imageSrcWsize;
static	s16	flagSplit;
static	u16	imagePtrX0;
static	u32	imageTop;
static  s16	tmemSrcLines;

/* Addition 99/05/31(Y) */
#if BUILD_VERSION >= VERSION_K
static s8 bgflg;
#endif

/*----------------------------------------------------------------------------*
 * Set scissoring parameters
 * *---------------------------------------------------------------------------*/
void	guS2DEmuSetScissor(u32 ulx, u32 uly, u32 lrx, u32 lry, u8 flag)
{
  scissorX0 = (u16)ulx << 2;
  scissorY0 = (u16)uly << 2;
  scissorX1 = (u16)lrx << 2;
  scissorY1 = (u16)lry << 2;
  flagBilerp = (flag) ? 1 : 0;
}

/*---------------------------------------------------------------------------*
 * Create texture load RDP commands
 *---------------------------------------------------------------------------*/
static	void	tmemLoad_B(Gfx **pkt, u32 imagePtr, s16 loadLines, s16 tmemSH)
{
  /*
   * Load 16-bit texture of tmemSH word width starting from imagePtr
   * into the loadLines amount of lines of tmem.
   */

  /* [SetTImg]  CMD=0x3d FMT=RGBA(0) SIZ=16b(2) */
  (*pkt)->words.w0 = rdpSetTimg_w0;
  (*pkt)->words.w1 = imagePtr;
  (*pkt) ++;

  /* [LoadSync] Wait for completion of preceding primitive draw */
  (*pkt)->words.w0 = (G_RDPLOADSYNC<<24);
  (*pkt) ++;

  /* [LoadTile] CMD=0x34 TILE=7 SH=TMEMW*16-1 TMEMH*4-1 */
  (*pkt)->words.w0 = (G_LOADTILE<<24)|0x000000;
/* addition 99/5/31(Y) */
#if BUILD_VERSION >= VERSION_K
  if(bgflg==3) (*pkt)->words.w1 = 0x07000000 | (tmemSH-1)<<16;
  else  (*pkt)->words.w1 = 0x07000000 | (tmemSH-1)<<16 | (loadLines<<2)-1;
#else
  (*pkt)->words.w1 = 0x07000000 | (tmemSH-1)<<16 | (loadLines<<2)-1;
#endif
  (*pkt) ++;
}

static	void	tmemLoad_A(Gfx **pkt, u32 imagePtr,
			   s16 loadLines, s16 tmemAdrs, s16 tmemSH)
{
  /*
   * Load 16-bit texture of tmemSH word width starting from imagePtr into 
   * the loadLines amount of lines of  the tmemAdrs of tmem.
   */

  /* [TileSync] Wait for completion of Tile access of preceding command */
  (*pkt)->words.w0 = 0xe8000000;
  (*pkt) ++;

  /* [SetTile] */
  (*pkt)->words.w0 = rdpSetTile_w0|tmemAdrs;
  (*pkt)->words.w1 = 0x07000000;
  (*pkt) ++;
  
  tmemLoad_B(pkt, imagePtr, loadLines, tmemSH);
}

static	void	tmemLoad(Gfx **pkt, u32 *imagePtr,
		 s16 *imageRemain, s16 drawLines, s16 flagBilerp)
{
  s16	loadLines = drawLines + flagBilerp;
  s16	iLoadable = (*imageRemain) - flagSplit;
  
  if (iLoadable >= loadLines){		/* If load can be done all at once */
    tmemLoad_B(pkt, *imagePtr, loadLines, tmemSliceWmax);    
    (*imagePtr)    += imageSrcWsize * drawLines;
    (*imageRemain) -= drawLines;
    
  } else {				/* If load is to be partitioned */
    s16  SubSliceL2, SubSliceD2, SubSliceY2;
    u32	 imageTopSeg = imageTop & 0xff000000; 
    
    SubSliceY2 = *imageRemain;
    SubSliceL2 = loadLines - SubSliceY2;
    SubSliceD2 = drawLines - SubSliceY2;
    
    if (SubSliceL2 > 0){
      u32  imagePtr2;
      
      imagePtr2 = imageTop + imagePtrX0;
      if (SubSliceY2 & 1){
	imagePtr2 -= imageSrcWsize;
	imagePtr2  = imageTopSeg | (imagePtr2 & 0x00ffffff); /*Segment counterm */
	SubSliceY2 --;
	SubSliceL2 ++;
      }
      tmemLoad_A(pkt, imagePtr2,
		 SubSliceL2, SubSliceY2 * tmemSliceWmax, tmemSliceWmax);
    }
    if (flagSplit){
      u32    imagePtr1A, imagePtr1B;
      s16    SubSliceY1, SubSliceL1;
      s16    tmemSH_A, tmemSH_B;
      
      imagePtr1A = (*imagePtr) + iLoadable * imageSrcWsize;
      imagePtr1B = imageTop;
      SubSliceY1 = iLoadable;
      if (SubSliceL1 = iLoadable & 1){
	imagePtr1A -= imageSrcWsize;
	imagePtr1B -= imageSrcWsize;
	imagePtr1B  = imageTopSeg | (imagePtr1B & 0x00ffffff); /*Segment countermeasure */
	SubSliceY1 --;
      }
      SubSliceL1 ++;
      tmemSH_A = (imageSrcWsize - imagePtrX0) >> 3;
      tmemSH_B =  tmemSliceWmax - tmemSH_A;
      tmemLoad_A(pkt, imagePtr1B,
		 SubSliceL1, SubSliceY1 * tmemSliceWmax + tmemSH_A, tmemSH_B);
      tmemLoad_A(pkt, imagePtr1A,
		 SubSliceL1, SubSliceY1 * tmemSliceWmax, tmemSH_A);      
    }
    if (iLoadable > 0){

      tmemLoad_A(pkt, *imagePtr, iLoadable, 0, tmemSliceWmax);
            
    } else {
      
      /* [SetTile] */
      (*pkt)->words.w0 = rdpSetTile_w0;
      (*pkt)->words.w1 = 0x07000000;
      (*pkt) ++;
    }
    
    (*imageRemain) -= drawLines;
    if ((*imageRemain) > 0){
      (*imagePtr) += imageSrcWsize * drawLines;
    } else {
      (*imageRemain) = tmemSrcLines - SubSliceD2;
      (*imagePtr) = imageTop + SubSliceD2 * imageSrcWsize + imagePtrX0;
    }
    
  }
}

/*---------------------------------------------------------------------------*
 * Scalable BG serface draw process
 *---------------------------------------------------------------------------*/
void	guS2DEmuBgRect1Cyc(Gfx **pkt, uObjBg *bg)
{
  s16	frameX0, frameX1, framePtrY0, frameRemain;
  s16	imageX0, imageY0, imageSliceW, imageW;
  s32	imageYorig;
  s16	scaleW,  scaleH;

  s16	imageSrcW, imageSrcH;
  s16	tmemSliceLines, imageSliceLines;
  s32	frameSliceLines, frameSliceCount;
  u16	imageS, imageT;
  u32	imagePtr;

  s16	imageISliceL0, imageIY0;
  s32	frameLSliceL0;
  
  scaleW = bg->s.scaleW;
  scaleH = bg->s.scaleH;  

/* addition 99/05/31(Y) */
#if BUILD_VERSION >= VERSION_K
  bgflg=bg->s.imageSiz;
  if(scaleW==0) scaleW=1;
  if(scaleH==0) scaleH=1;
#endif

    
{
  /*-------------------------------------------------*
    Scissoring process
   *-------------------------------------------------*/  
  /*
  /  frameX0, frameX1, framePtrY0, frameRemain
  /  imageX0, imageY0, tmemSliceW
  /  imageSrcW, imageSrcH
  */
  s16	pixX0, pixY0, pixX1, pixY1;			/* (s13.2) */
  s16	frameY0, frameW, frameH;
  s32	frameWmax, frameHmax;
  
  /* Determine maximum frame size from image and  enlargement ratio */
  frameWmax = ((((s32)bg->s.imageW << 10) / scaleW)-1) & ~3;
  frameHmax = ((((s32)bg->s.imageH << 10) / scaleH)-1) & ~3;
  
  /* Clamp the frame size */
  frameW  = bg->s.frameW;
  frameH  = bg->s.frameH;
  frameX0 = bg->s.frameX;
  frameY0 = bg->s.frameY;
  if ((frameWmax = bg->s.frameW - frameWmax) < 0) frameWmax = 0;
  if ((frameHmax = bg->s.frameH - frameHmax) < 0) frameHmax = 0;
  frameW -= frameWmax;
  frameH -= frameHmax;
  if (bg->s.imageFlip & G_BG_FLAG_FLIPS){
    frameX0 += frameWmax;
  }
  
  /* Caluculate amount of projection from screen */
  pixX0 = scissorX0 - frameX0;				/* (s13.2) */
  pixY0 = scissorY0 - frameY0;				/* (s13.2) */
  pixX1 = frameW - scissorX1 + frameX0;			/* (s13.2) */
  pixY1 = frameH - scissorY1 + frameY0;			/* (s13.2) */
  
  /* Clamp if no projection */
  if (pixX0 < 0) pixX0 = 0;
  if (pixY0 < 0) pixY0 = 0;
  if (pixX1 < 0) pixX1 = 0;
  if (pixY1 < 0) pixY1 = 0;
  
  /* Cut the part that is projecting */
  frameW  = frameW - (pixX0 + pixX1);			/* (s13.2) */
  frameH  = frameH - (pixY0 + pixY1);			/* (s13.2) */
  frameX0 = frameX0 + pixX0;				/* (s13.2) */
  frameY0 = frameY0 + pixY0;				/* (s13.2) */

  /* Terminate if no draw range remains */
  if (frameW <= 0 || frameH <= 0) return;

  /* Caluculate frame */
  frameX1     = frameX0 + frameW;			/* (s13.2) */
  framePtrY0  = frameY0 >> 2;				/* (s15.0) */
  frameRemain = frameH  >> 2; 				/* (s15.0) */
  
  /* Join image columns */
  imageSrcW = bg->s.imageW << 3;		/* (u11.5) */
  imageSrcH = bg->s.imageH << 3;		/* (u11.5) */
  
  /* Get image range (u14.2)*(u6.10)=(u20.12)->(u11.5) */
  imageSliceW = (imageW = frameW * scaleW >> 7) + flagBilerp * 32;
  if (bg->s.imageFlip & G_BG_FLAG_FLIPS){
    imageX0 = bg->s.imageX + (pixX1 * scaleW >> 7);		  /* (s10.5) */
  } else {
    imageX0 = bg->s.imageX + (pixX0 * scaleW >> 7);		  /* (s10.5) */
  }
  imageY0     = bg->s.imageY + (pixY0 * scaleH >> 7);		  /* (s10.5) */
  imageYorig  = bg->s.imageYorig;
  
  /* Loop one step down when left end of image area is greater than right end of                 image source  */
  while (imageX0 >= imageSrcW){
    imageX0     -= imageSrcW;
    imageY0     += 32;
    imageYorig  += 32;			/* Add 1 to carrier */
  }
  
  /* Loop when top end of image area is greater than bottom end of image source  */
  while (imageY0 >= imageSrcH){
    imageY0     -= imageSrcH;
    imageYorig  -= imageSrcH;
  }
}

{
  /*-------------------------------------------------*
    Check process connecting top and bottom of image
   *-------------------------------------------------*/
  /*
  // flagSplit
  // tmemSrcLines
  // imageSrcLines
  */  
  /* Top/bottom connection process necessary when image range straddles right 
end */
  flagSplit = (imageX0 + imageSliceW >= imageSrcW);
  
  /* Number of image lines that can be loaded at once */
  tmemSrcLines = imageSrcH >> 5;
}

{
  /*-------------------------------------------------*
    Get load data for TMEM
   *-------------------------------------------------*/
  /*
  //Calculate number of lines that can be loaded into TMEM.	
  //	If the slice width changes due to scissoring and  the linked 
  //	load line number is changed, then the frame division line will
  //	change and the result will be the generation of unnatural wrinkles.
  //	To prevent this, the division region is set such that scissoring
  //  does not occur.
  // 
  */
  s16	tmemSize, tmemMask, tmemShift;
  s32	imageNumSlice;
  s32	imageSliceWmax;
  s32	imageLYoffset, frameLYoffset;
  s32	imageLHidden,  frameLHidden;
  s32	frameLYslice;
  
  static s16	TMEMSIZE[]  = {   512,   512,   256,   512,  512 };
  static s16	TMEMMASK[]  = { 0x1ff,  0xff,  0x7f,  0x3f };
  static s16	TMEMSHIFT[] = { 0x200, 0x100,  0x80,  0x40 };   
  tmemSize  = TMEMSIZE[bg->s.imageFmt];		/* (s15.0) */
  tmemMask  = TMEMMASK[bg->s.imageSiz];		/* (s10.5) */
  tmemShift = TMEMSHIFT[bg->s.imageSiz];	/* (s10.5)->(s15.0) */

  /* Calculate tmem width to accommodate the slice image width */
  /* 	o Extra is needed at Bilerp time.
  //	o Clamp slice image width based on image source width.
  //	o Cut image width end number at TMEM Word boundary. 
  //	o tmem width + 1 when start position not in agreement with Word boundary */
/* addition 99/05/31(Y) */
#if BUILD_VERSION >= VERSION_K
  if(bgflg==3){
     tmemSize=480;
     imageSliceWmax = 0x2800;
  }
  else{
     imageSliceWmax = (((s32)bg->s.frameW * (s32)scaleW)>>7) + (flagBilerp<<5);
     if (imageSliceWmax > imageSrcW) imageSliceWmax = imageSrcW;  
  }
#else
  imageSliceWmax = (((s32)bg->s.frameW * (s32)scaleW)>>7) + (flagBilerp<<5);
  if (imageSliceWmax > imageSrcW) imageSliceWmax = imageSrcW;  
#endif

  tmemSliceWmax  = (imageSliceWmax + tmemMask) / tmemShift + 1;
  
  /* Get TMEM/image/frame line number that can be loaded at once */
   tmemSliceLines = tmemSize / tmemSliceWmax;		/* (s15.0) */
  imageSliceLines = tmemSliceLines - flagBilerp;	/* (s15.0) */
  frameSliceLines = (imageSliceLines << 20) / scaleH;	/* (s21.10) */

  /* Line up image Y coordinate offset value with frame image */
  imageLYoffset = ((s32)imageY0 - imageYorig) << 5;
  if (imageLYoffset < 0) imageLYoffset -= (scaleH - 1);
  frameLYoffset = imageLYoffset / scaleH;
  frameLYoffset <<= 10;
  
  /* Get slice number corresponding to image Y */
  if (frameLYoffset >= 0){
    imageNumSlice = frameLYoffset / frameSliceLines;
  } else {
    imageNumSlice = (frameLYoffset - frameSliceLines + 1) / frameSliceLines;
  }
  
  /* Calculate extent to which first draw slice is hidden at top of frame */
  frameLYslice = (frameLSliceL0 = frameSliceLines * imageNumSlice) & ~1023;
  frameLHidden = frameLYoffset - frameLYslice;
  imageLHidden = (frameLHidden >> 10) * scaleH;
  
  /* Calculate fram size of first draw slice */
  frameLSliceL0 = (frameLSliceL0 & 1023) + frameSliceLines - frameLHidden;  
  
  /* Calculate image parameters for draw in midst of slice */
  imageT        = (imageLHidden >> 5) & 31;
  imageLHidden  >>= 10;
  imageISliceL0 = imageSliceLines - imageLHidden;
  imageIY0      =
    imageSliceLines * imageNumSlice + (imageYorig & ~31) / 32 + imageLHidden;
  if (imageIY0 < 0)                    imageIY0 += (bg->s.imageH >> 2);
  if (imageIY0 >= (bg->s.imageH >> 2)) imageIY0 -= (bg->s.imageH >> 2);
  imageTop      = (u32)bg->s.imagePtr;			/* (u32.0) */
  imageSrcWsize = (imageSrcW / tmemShift) << 3;		/* (u16.0) */
  imagePtrX0    = (imageX0   / tmemShift) << 3;		/* (u16.0) */
  imagePtr      = imageTop + imageSrcWsize * imageIY0 + imagePtrX0;

  /* S invert process */
  imageS = imageX0 & tmemMask;		/* (u10.5) */
  if (bg->s.imageFlip & G_BG_FLAG_FLIPS){
    imageS = - (imageS + imageW);
  }
}

{
  /*-------------------------------------------------*
    Creating RDP command constant values
   *-------------------------------------------------*/
  /*	u32	rdpSetTimg_w0; 
  	u32	rdpSetTile_w0; */
/* Addition 99/05/31(Y) */
#if BUILD_VERSION >= VERSION_K
  if(bgflg==3){
    rdpSetTimg_w0 = (G_SETTIMG<<24)+0x180000+(imageSrcWsize>>1)-1;
    rdpSetTile_w0 = (G_SETTILE<<24)+0x180000+(tmemSliceWmax<<9);
  }
  else{
    rdpSetTimg_w0 = (G_SETTIMG<<24)+0x100000+(imageSrcWsize>>1)-1;
    rdpSetTile_w0 = (G_SETTILE<<24)+0x100000+(tmemSliceWmax<<9);
  }
#else
  rdpSetTimg_w0 = (G_SETTIMG<<24)+0x100000+(imageSrcWsize>>1)-1;
  rdpSetTile_w0 = (G_SETTILE<<24)+0x100000+(tmemSliceWmax<<9);
#endif
  /* [SetTile:7] */
  (*pkt)->words.w0 = rdpSetTile_w0;
  (*pkt)->words.w1 = 0x07000000;
  (*pkt)++;
  /* [SetTile:0] */
  (*pkt)->words.w0 = rdpSetTile_w0;
  ((u8 *)&((*pkt)->words.w0))[1] = (bg->s.imageFmt<<5)|(bg->s.imageSiz<<3);
  (*pkt)->words.w1 = 0x0007c1f0 | (bg->s.imagePal<<20);
  (*pkt)++;
  /* [SetTileSize:7] */
  (*pkt)->words.w0 = (G_SETTILESIZE<<24)|0x000000;
  (*pkt)->words.w1 = 0x00000000;
  (*pkt)++;
}
  
{
  s16	imageRemain;
  s16	imageSliceH, frameSliceH;
  
  imageRemain     = tmemSrcLines - imageIY0;  
  imageSliceH     = imageISliceL0;
  frameSliceCount = frameLSliceL0;

  while(1){

    /* Calculate draw line number and determine whether to perform a draw */
    frameSliceH = frameSliceCount >> 10;
    if (frameSliceH <= 0){
      /* If no draw to be performed */
      imageRemain -= imageSliceH;
      if (imageRemain > 0){
	imagePtr += imageSrcWsize * imageSliceH;
      } else {
	imagePtr = imageTop - (imageRemain * imageSrcWsize) + imagePtrX0;
	imageRemain += tmemSrcLines;
      }
      
    } else {
      /* If draw to be performed */
      s16	framePtrY1;
      
      frameSliceCount &= 1023;
      if ((frameRemain -= frameSliceH) < 0){
	/* Determine final slice */
	frameSliceH += frameRemain;
	imageSliceH += ((frameRemain * scaleH) >> 10) + 1;
	if (imageSliceH > imageSliceLines) imageSliceH = imageSliceLines;
      }
      tmemLoad(pkt, &imagePtr, &imageRemain, imageSliceH, flagBilerp);
      
      /* Get draw frame range */
      framePtrY1 = framePtrY0 + frameSliceH;		/* (s15.0) */
      
      /* [PipeSync] Wait for end of preceding LOADTILE command */
      (*pkt)->words.w0 = (G_RDPPIPESYNC<<24);
      (*pkt) ++;

      /* Rectangle draw */
      /* Here an RSP command is created.  With ucode an RDP command is created */
#if 1
      {
	/* [TextureRectangle] */
	(*pkt)->words.w0 = (G_TEXRECT<<24)|(frameX1<<12)|(framePtrY1<<2);
	(*pkt)->words.w1 =                 (frameX0<<12)|(framePtrY0<<2);
	(*pkt) ++;
#else
      /* Code for checking slice division line */
      if (frameSliceH > 1){
	(*pkt)->words.w0 = (G_TEXRECT<<24)|(frameX1<<12)|(framePtrY1<<2)-4;
	(*pkt)->words.w1 =                 (frameX0<<12)|(framePtrY0<<2);
	(*pkt) ++;
#endif
	
#if 0	/* At RDP command creation time */
	(*pkt)->words.w0 = (imageS<<16) | imageT;
	(*pkt)->words.w1 = (scaleW<<16) | scaleH;
#else	/* At RSP command creation time */
	(*pkt)->words.w0 = (G_RDPHALF_1<<24);
	(*pkt)->words.w1 = (imageS<<16) | imageT;
	(*pkt) ++;      
	(*pkt)->words.w0 = (G_RDPHALF_2<<24);
	(*pkt)->words.w1 = (scaleW<<16) | scaleH;
#endif
	(*pkt) ++;
      }

      /* Update region */
      framePtrY0 = framePtrY1;

      /* End if no more undrawn line numbers for frame */
      if (frameRemain <= 0){
	return;
      }
    }
    frameSliceCount += frameSliceLines;
    imageSliceH      = imageSliceLines;
    imageT           = 0;
  }
}
}

/*======== End of us2dex_emu.c ========*/
