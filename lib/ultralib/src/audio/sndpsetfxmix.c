/*====================================================================
 * sndpsetfxmix.c
 *
 * Copyright 1995, Silicon Graphics, Inc.
 * All Rights Reserved.
 *
 * This is UNPUBLISHED PROPRIETARY SOURCE CODE of Silicon Graphics,
 * Inc.; the contents of this file may not be disclosed to third
 * parties, copied or duplicated in any form, in whole or in part,
 * without the prior written permission of Silicon Graphics, Inc.
 *
 * RESTRICTED RIGHTS LEGEND:
 * Use, duplication or disclosure by the Government is subject to
 * restrictions as set forth in subdivision (c)(1)(ii) of the Rights
 * in Technical Data and Computer Software clause at DFARS
 * 252.227-7013, and/or in similar or successor clauses in the FAR,
 * DOD or NASA FAR Supplement. Unpublished - rights reserved under the
 * Copyright Laws of the United States.
 *====================================================================*/

#include "sndp.h"
#include <os_internal.h>
#include <ultraerror.h>

void alSndpSetFXMix(ALSndPlayer *sndp, u8 mix) 
{
    ALSndpEvent evt;
    ALSoundState  *sState = sndp->sndState;

#ifdef _DEBUG
    if ((sndp->target >= sndp->maxSounds) || (sndp->target < 0)){
        __osError(ERR_ALSNDPSETPAR, 2, sndp->target, sndp->maxSounds-1);
	return;
    }
#endif

    evt.fx.type = AL_SNDP_FX_EVT;
    evt.fx.state = &sState[sndp->target];
    evt.fx.mix = mix;
    alEvtqPostEvent(&sndp->evtq, (ALEvent *)&evt, 0);
}

