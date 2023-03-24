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
 * define a positional light.
 * this function must be called anytime the light or object moves.
 *
 * pl  = (input) positional light description.
 * l   = (output) directiona light description for gSPLight or gSPSetLightsN.
 * *Ob = position of (center of) object to be lit.
 *
 */
#define THRESH1 0.01
#define THRESH2 0.1
void guPosLight(PositionalLight *pl, Light *l,
                        float xOb, float yOb, float zOb)
{
        float x,y,z,d,a;


        x = pl->pos[0]-xOb;
        y = pl->pos[1]-yOb;
        z = pl->pos[2]-zOb;
        d = sqrtf(x*x + y*y + z*z);

        a = d*pl->a1 + pl->a2;
        if (a<THRESH1)
                a=100.0;
        else
                a = 1/a;

        if (d<THRESH1) {
                l->l.dir[0] = 0;
                l->l.dir[1] = 0;
                l->l.dir[2] = -120;

                l->l.col[0] = 0;
                l->l.col[1] = 0;
                l->l.col[2] = 0;
                l->l.colc[0] = 0;
                l->l.colc[1] = 0;
                l->l.colc[2] = 0;
        } else {
                d = 1/d;
                l->l.dir[0] = 120.0*x*d;
                l->l.dir[1] = 120.0*y*d;
                l->l.dir[2] = 120.0*z*d;

                l->l.col[0] = pl->col[0]*a;
                l->l.col[1] = pl->col[1]*a;
                l->l.col[2] = pl->col[2]*a;
                l->l.colc[0] = pl->col[0]*a;
                l->l.colc[1] = pl->col[1]*a;
                l->l.colc[2] = pl->col[2]*a;
        }

}
