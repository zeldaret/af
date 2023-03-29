/**************************************************************************
 *									  *
 *		 Copyright (C) 1995, Silicon Graphics, Inc.		  *
 *									  *
 *  These coded instructions, statements, and computer programs  contain  *
 *  unpublished  proprietary  information of Silicon Graphics, Inc., and  *
 *  are protected by Federal copyright law.  They  may  not be disclosed  *
 *  to  third  parties  or copied or duplicated in any form, in whole or  *
 *  in part, without the prior written consent of Silicon Graphics, Inc.  *
 *									  *
 **************************************************************************/

#include "guint.h"


/*
 * define 2 positional lights with highlights.
 * this function must be called anytime the viewpoint, light or object moves.
 *
 * pl1  = (input) positional light#1 description.
 * pl2  = (input) positional light#2 description.
 * l1   = (output) directional light desc. #1 for gSPLight or gSPSetLightsN.
 * l2   = (output) directional light desc. #2 for gSPLight or gSPSetLightsN.
 * *Eye = position of eye (viewpoint). (usually same as in LookAt command.)
 * *Ob  = position of (center of) object to be lit.
 * *Ob  = up vector (usually same as in LookAt command).
 * twidth  = width of texture map used for highlight.
 * theight = height of texture map used for highlight.
 *
 */
#define THRESH2 0.01
#define THRESH3 0.1
void guPosLightHilite(PositionalLight *pl1, PositionalLight *pl2,
                Light *l1, Light *l2,
                LookAt *l, Hilite *h,
                float xEye, float yEye, float zEye,
                float xOb,  float yOb,  float zOb,
                float xUp,  float yUp,  float zUp,
                int twidth, int theight)        /* hilite txtr size*/
{
        float x,y,z,d,a;
        Mtx m;


/*
 * light 1, diffuse
 */
        x = pl1->pos[0]-xOb;
        y = pl1->pos[1]-yOb;
        z = pl1->pos[2]-zOb;
        d = sqrtf(x*x + y*y + z*z);

        a=d*pl1->a1 + pl1->a2;
        if (a<THRESH2)
                a=100.0;
        else
                a = 1/a;

        if (d<THRESH2) {
                l1->l.dir[0] = 0;
                l1->l.dir[1] = 0;
                l1->l.dir[2] = -120;

                l1->l.col[0] = 0;
                l1->l.col[1] = 0;
                l1->l.col[2] = 0;
                l1->l.colc[0] = 0;
                l1->l.colc[1] = 0;
                l1->l.colc[2] = 0;
        } else {
                d = 1/d;
                l1->l.dir[0] = 120.0*x*d;
                l1->l.dir[1] = 120.0*y*d;
                l1->l.dir[2] = 120.0*z*d;

                l1->l.col[0] = pl1->col[0]*a;
                l1->l.col[1] = pl1->col[1]*a;
                l1->l.col[2] = pl1->col[2]*a;
                l1->l.colc[0] = pl1->col[0]*a;
                l1->l.colc[1] = pl1->col[1]*a;
                l1->l.colc[2] = pl1->col[2]*a;
        }


/*
 * light 2, diffuse
 */
        x = pl2->pos[0]-xOb;
        y = pl2->pos[1]-yOb;
        z = pl2->pos[2]-zOb;
        d = sqrtf(x*x + y*y + z*z);

        a = d*pl2->a1 + pl2->a2;
        if (a<THRESH2)
                a=100.0;
        else
                a = 1/a;

        if (d<THRESH2) {
                l2->l.dir[0] = 0;
                l2->l.dir[1] = 0;
                l2->l.dir[2] = -120;

                l2->l.col[0] = 0;
                l2->l.col[1] = 0;
                l2->l.col[2] = 0;
                l2->l.colc[0] = 0;
                l2->l.colc[1] = 0;
                l2->l.colc[2] = 0;
        } else {
                d = 1/d;
                l2->l.dir[0] = 120.0*x*d;
                l2->l.dir[1] = 120.0*y*d;
                l2->l.dir[2] = 120.0*z*d;

                l2->l.col[0] = pl2->col[0]*a;
                l2->l.col[1] = pl2->col[1]*a;
                l2->l.col[2] = pl2->col[2]*a;
                l2->l.colc[0] = pl2->col[0]*a;
                l2->l.colc[1] = pl2->col[1]*a;
                l2->l.colc[2] = pl2->col[2]*a;
        }


/*
 * Hilight factors
 */
        x = xOb-xEye;
        y = yOb-yEye;
        z = zOb-zEye;
        if (sqrtf(x*x + y*y + z*z)<THRESH3) {
                h->h.x1 = twidth*2;
                h->h.y1 = twidth*2;
                h->h.x2 = twidth*2;
                h->h.y2 = twidth*2;
                l->l[0].l.dir[0] = 0;
                l->l[0].l.dir[1] = 0;
                l->l[0].l.dir[2] = 0;
                l->l[1].l.dir[0] = 0;
                l->l[1].l.dir[1] = 0;
                l->l[1].l.dir[2] = 0;
                l->l[0].l.col[0] = 0x00;
                l->l[0].l.col[1] = 0x00;
                l->l[0].l.col[2] = 0x00;
                l->l[0].l.pad1 = 0x00;
                l->l[0].l.colc[0] = 0x00;
                l->l[0].l.colc[1] = 0x00;
                l->l[0].l.colc[2] = 0x00;
                l->l[0].l.pad2 = 0x00;
                l->l[1].l.col[0] = 0x00;
                l->l[1].l.col[1] = 0x80;
                l->l[1].l.col[2] = 0x00;
                l->l[1].l.pad1 = 0x00;
                l->l[1].l.colc[0] = 0x00;
                l->l[1].l.colc[1] = 0x80;
                l->l[1].l.colc[2] = 0x00;
                l->l[1].l.pad2 = 0x00;
        } else {
                guLookAtHilite(&m, l, h,
                        xEye, yEye, zEye,
                        xOb,  yOb,  zOb,
                        xUp,  yUp,  zUp,
                        l1->l.dir[0], l1->l.dir[1], l1->l.dir[2],
                        l2->l.dir[0], l2->l.dir[1], l2->l.dir[2],
                        twidth, theight);
        }
}

