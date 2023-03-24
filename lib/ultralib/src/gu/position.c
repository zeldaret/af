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
 *  Return position matrix given roll, pitch, and yaw in degrees
 *  plus scale and position.
 *   
 * r = roll  (degrees)
 * p = pitch (degrees)
 * h = yaw   (degrees)
 * s = scale
 * x,y,z = position (world coordinates)
 *   
 */

void guPositionF(float mf[4][4], float r, float p, float h, float s,
		 float x, float y, float z)
{
        static float    dtor = 3.1415926 / 180.0;
        float   sinr, sinp, sinh;
        float   cosr, cosp, cosh;

        r *= dtor;
        p *= dtor;
        h *= dtor;
        sinr = sinf(r);
        cosr = cosf(r);
        sinp = sinf(p);
        cosp = cosf(p);
        sinh = sinf(h);
        cosh = cosf(h);

        mf[0][0] = (cosp*cosh) * s;
        mf[0][1] = (cosp*sinh) * s;
        mf[0][2] = (-sinp) * s;
        mf[0][3] = 0.0;

        mf[1][0] = (sinr*sinp*cosh - cosr*sinh) * s;
        mf[1][1] = (sinr*sinp*sinh + cosr*cosh) * s;
        mf[1][2] = (sinr*cosp) * s;
        mf[1][3] = 0.0;

        mf[2][0] = (cosr*sinp*cosh + sinr*sinh) * s;
        mf[2][1] = (cosr*sinp*sinh - sinr*cosh) * s;
        mf[2][2] = (cosr*cosp) * s;
        mf[2][3] = 0.0;

        mf[3][0] = x;
        mf[3][1] = y;
        mf[3][2] = z;
        mf[3][3] = 1.0;
}

void guPosition(Mtx *m, float r, float p, float h, float s,
                                float x, float y, float z)
{
    float mf[4][4];

    guPositionF(mf, r, p, h, s, x, y, z);

    guMtxF2L(mf, m);
}
