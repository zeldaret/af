/*====================================================================
 * sndpallocate.c
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

ALSndId alSndpAllocate(ALSndPlayer *sndp, ALSound *sound)
{
    ALSndId i;
    ALSoundState *sState = sndp->sndState;
    
    for (i = 0; i < sndp->maxSounds; i++) {
        if (!sState[i].sound) {
            sState[i].sound = sound;
            sState[i].priority = AL_DEFAULT_PRIORITY;
            sState[i].state = AL_STOPPED;
            sState[i].pitch = 1.0;
            sState[i].pan = AL_PAN_CENTER;
            sState[i].fxMix = AL_DEFAULT_FXMIX;
            sState[i].vol = 32767*sound->sampleVolume/AL_VOL_FULL;
	    return i;
        }
    }

    return -1;
}

