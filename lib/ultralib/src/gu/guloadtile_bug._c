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

#include "ultra64.h"

/*
 *  Inidicates how many words will be added to display list
 *  by guDPLoadTextureTile function.
 */
int
guGetDPLoadTextureTileSz(int ult, int lrt)
{
	return (((lrt - ult + 1) / 2) * 4 + 3);
}

/*
 *  Workaround for load_tile bug on tapeout one hardware.  Uses
 *  load blocks for each line.  ~25% more dma traffic + memory for
 *  extra commands.
 */
void
guDPLoadTextureTile(Gfx * temp, void *timg,
					int texl_fmt, int texl_size,
					int img_width, int img_height,
					int uls, int ult, int lrs, int lrt,
					int palette,
					int cms, int cmt,
					int masks, int maskt,
					int shifts, int shiftt)
{
	int             line;
	int             tile_width,
	                tile_height;	/*

									 * in texels 
									 */
	int             dxt;
	int             sizeb;
	int             lineb;
	int             line_size;	/*

								 * in 64-bit words 
								 */
	int             texel_num_pad;	/*

									 * in texels, pad to 64-bit word size 
									 */
	int             count;
	int             tmem;
	int             tile;
	int             s,
	                t;

	tile_width = lrs - uls + 1;
	tile_height = lrt - ult + 1;

	switch (texl_size) {
		case G_IM_SIZ_8b:
			sizeb = G_IM_SIZ_8b_BYTES;
			lineb = G_IM_SIZ_8b_LINE_BYTES;
			break;
		case G_IM_SIZ_16b:
			sizeb = G_IM_SIZ_16b_BYTES;
			lineb = G_IM_SIZ_16b_LINE_BYTES;
			break;
		case G_IM_SIZ_32b:
			sizeb = G_IM_SIZ_32b_BYTES;
			lineb = G_IM_SIZ_32b_LINE_BYTES;
			break;
	}

	dxt = CALC_DXT(tile_width, sizeb);
	line_size = ((tile_width * lineb) + 7) >> 3;
	/*
	 * pad line to word boundary 
	 */
	texel_num_pad = ((((tile_width * sizeb) + 7) >> 3) * 8) / sizeb;

	gDPSetTextureImage(temp++, texl_fmt, texl_size, img_width, timg);

	for (line = 0; line < tile_height; line += 2) {
		t = (ult + line) & ~1;	/*
								 * load from even line 
								 */
		tmem = line * line_size;

		/*
		 * set for both loads, avoid sync by alternating tiles 
		 */
		tile = (line % 4) ? 1 : 0;

		gDPSetTile(temp++, texl_fmt, texl_size, 0, tmem, G_TX_LOADTILE - tile, 0,
				   cmt, maskt, shiftt,
				   cms, masks, shifts);

		/*
		 * do odd line first 
		 */
		s = uls + img_width - texel_num_pad;
		count = (texel_num_pad * 2) - 1;

		gDPLoadBlock(temp++, G_TX_LOADTILE - tile, s, t, s + count, dxt);

		/*
		 * do even line 
		 */
		s = uls;
		count = tile_width - 1;

		gDPLoadSync(temp++);
		gDPLoadBlock(temp++, G_TX_LOADTILE - tile, s, t, s + count, dxt);

	}

	/*
	 * set final tile 
	 */
	gDPSetTile(temp++, texl_fmt, texl_size, line_size, 0, G_TX_RENDERTILE, 0,
			   cmt, maskt, shiftt,
			   cms, masks, shifts);

	gDPSetTileSize(temp++, G_TX_RENDERTILE,
				   (uls) << G_TEXTURE_IMAGE_FRAC,
				   (ult) << G_TEXTURE_IMAGE_FRAC,
				   (lrs) << G_TEXTURE_IMAGE_FRAC,
				   (lrt) << G_TEXTURE_IMAGE_FRAC);
}

/*
 *  4-BIT VERSION 
 */

/*
 *  Inidicates how many words will be added to display list
 *  by guDPLoadTextureTile function.
 */
int
guGetDPLoadTextureTile_4bSz(int ult, int lrt)
{
	return (((lrt - ult + 1) / 2) * 4 + 3);
}

/*
 *  Workaround for load_tile bug on version 1.0 hardware.  Uses
 *  load blocks for each line.  ~25% more dma traffic + memory for
 *  extra commands.
 */
void
guDPLoadTextureTile_4b(Gfx * temp, void *timg,
					   int texl_fmt,
					   int img_width, int img_height,
					   int uls, int ult, int lrs, int lrt,
					   int palette,
					   int cms, int cmt,
					   int masks, int maskt,
					   int shifts, int shiftt)
{
	int             line;
	int             tile_width,
	                tile_height;
	int             dxt;
	int             sizeb;
	int             lineb;
	int             line_size;
	int             count;
	int             tmem;
	int             tile;
	int             s,
	                t;

	tile_width = (lrs - uls + 1) >> 1;
	tile_height = lrt - ult + 1;
	sizeb = G_IM_SIZ_8b_BYTES;
	lineb = G_IM_SIZ_8b_LINE_BYTES;
	line_size = ((tile_width * lineb) + 7) >> 3;
	dxt = CALC_DXT_4b(tile_width);

	gDPSetTextureImage(temp++, texl_fmt, G_IM_SIZ_8b, ((img_width) >> 1), timg);

	for (line = 0; line < tile_height; line += 2) {
		t = (ult + line) & ~1;	/*
								 * load from even line 
								 */
		tmem = line * line_size;

		/*
		 * set for both loads, avoid sync by alternating tiles 
		 */
		tile = (line % 4) ? 1 : 0;

		gDPSetTile(temp++, texl_fmt, G_IM_SIZ_8b, 0, tmem, G_TX_LOADTILE - tile, 0,
				   cmt, maskt, shiftt,
				   cms, masks, shifts);

		/*
		 * do odd line first 
		 */
		s = uls + img_width - line_size * 8;
		count = (line_size * 8 * 2) - 1;

		gDPLoadBlock(temp++, G_TX_LOADTILE - tile, s, t, s + count, dxt);

		/*
		 * do even line 
		 */
		s = uls;
		count = tile_width - 1;

		gDPLoadSync(temp++);
		gDPLoadBlock(temp++, G_TX_LOADTILE - tile, s, t, s + count, dxt);

	}

	/*
	 * set final tile 
	 */
	gDPSetTile(temp++, texl_fmt, G_IM_SIZ_4b, line_size, 0, G_TX_RENDERTILE, 0,
			   cmt, maskt, shiftt,
			   cms, masks, shifts);

	gDPSetTileSize(temp++, G_TX_RENDERTILE,
				   (uls) << G_TEXTURE_IMAGE_FRAC,
				   (ult) << G_TEXTURE_IMAGE_FRAC,
				   (lrs) << G_TEXTURE_IMAGE_FRAC,
				   (lrt) << G_TEXTURE_IMAGE_FRAC);
}
