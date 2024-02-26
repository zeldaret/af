/*====================================================================
 * Sndplayer.c
 *
 * Copyright 1993, Silicon Graphics, Inc.
 * All Rights Reserved.
 * This is UNPUBLISHED PROPRIETARY SOURCE CODE of Silicon Graphics,
 * Inc.; the contents of this file may not be disclosed to third
 * parties, copied or duplicated in any form, in whole or in part,
 * without the prior written permission of Silicon Graphics, Inc.
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
#include <assert.h>

// TODO: this comes from a header
#ident "$Revision: 1.17 $"

void alSndpNew(ALSndPlayer *sndp, ALSndpConfig *c) 
{    
    u8            *ptr;
    ALEvent       evt;
    ALSoundState  *sState;
    u32           i;

    /*
     * Init member variables
     */
    sndp->maxSounds = c->maxSounds;
    sndp->target = -1;
    sndp->frameTime = AL_USEC_PER_FRAME;        /* time between API events */
    sState = (ALSoundState*)alHeapAlloc(c->heap, 1,
                                        c->maxSounds * sizeof(ALSoundState));
    sndp->sndState = sState;

    for(i = 0; i < c->maxSounds; i++)
	sState[i].sound = 0;

    /*
     * init the event queue
     */
    ptr = alHeapAlloc(c->heap, 1, c->maxEvents * sizeof(ALEventListItem));
    alEvtqNew(&sndp->evtq, (ALEventListItem *)ptr, c->maxEvents);
    
    /*
     * add ourselves to the driver
     */
    sndp->drvr = &alGlobals->drvr;
    sndp->node.next = NULL;
    sndp->node.handler = _sndpVoiceHandler;
    sndp->node.clientData = sndp;
    alSynAddPlayer(sndp->drvr, &sndp->node);

    /*
     * Start responding to API events
     */
    evt.type = AL_SNDP_API_EVT;
    alEvtqPostEvent(&sndp->evtq, (ALEvent *)&evt, sndp->frameTime);
    sndp->nextDelta = alEvtqNextEvent(&sndp->evtq, &sndp->nextEvent);

}

/*************************************************************
 * Sound Player private routines
 *************************************************************/
ALMicroTime _sndpVoiceHandler(void *node)
{
    ALSndPlayer *sndp = (ALSndPlayer *) node;
    ALSndpEvent evt;

    do {
        switch (sndp->nextEvent.type) {
            case (AL_SNDP_API_EVT):
                evt.common.type = AL_SNDP_API_EVT;
#if BUILD_VERSION >= VERSION_K
		        evt.common.state = (ALSoundState*)-1;
#endif
                alEvtqPostEvent(&sndp->evtq, (ALEvent *)&evt, sndp->frameTime);
                break;

            default:
                _handleEvent(sndp, (ALSndpEvent *)&sndp->nextEvent);
                break;
        }
        sndp->nextDelta = alEvtqNextEvent(&sndp->evtq, &sndp->nextEvent);
        
    } while (sndp->nextDelta == 0);
    sndp->curTime += sndp->nextDelta;
    return sndp->nextDelta;
}

void _handleEvent(ALSndPlayer *sndp, ALSndpEvent *event) 
{
    ALVoiceConfig       vc;
    ALSound             *snd;
    ALVoice             *voice;
    ALPan               pan;
    f32                 pitch;
    ALSndpEvent         evt;
    ALMicroTime         delta;

    s16                 vol;
    s16                 tmp;
    s32                 vtmp;
    ALSoundState        *state;

    state = event->common.state;
    snd   = state->sound;
            

    switch (event->msg.type) {
        case (AL_SNDP_PLAY_EVT):
            if (state->state != AL_STOPPED || !snd)
                return;
            
            vc.fxBus      = 0;            /* effect buss 0 */
            vc.priority   = state->priority;
	    vc.unityPitch = 0;

            voice = &state->voice;
            alSynAllocVoice(sndp->drvr, voice, &vc);

            vol   = (s16) ((s32) snd->envelope->attackVolume*state->vol/AL_VOL_FULL);
            tmp   = state->pan - AL_PAN_CENTER + snd->samplePan;
            tmp   = MAX(tmp, AL_PAN_LEFT);
            pan   = (ALPan) MIN(tmp, AL_PAN_RIGHT);
            pitch = state->pitch;
            delta   = snd->envelope->attackTime;
            
            alSynStartVoice(sndp->drvr, voice, snd->wavetable);
            state->state = AL_PLAYING;
            
            alSynSetPan(sndp->drvr, voice, pan);
            alSynSetVol(sndp->drvr, voice, vol, delta);
            alSynSetPitch(sndp->drvr, voice, pitch);
            alSynSetFXMix(sndp->drvr, voice, state->fxMix);
            
            evt.common.type     = AL_SNDP_DECAY_EVT;
            evt.common.state    = state;
	    delta = (ALMicroTime) _DivS32ByF32 (snd->envelope->attackTime, state->pitch);
            alEvtqPostEvent(&sndp->evtq, (ALEvent *)&evt, delta);
            break;
                
        case (AL_SNDP_STOP_EVT):
            if (state->state != AL_PLAYING || !snd)
                return;

	    delta = (ALMicroTime) _DivS32ByF32 (snd->envelope->releaseTime, state->pitch);
            alSynSetVol(sndp->drvr, &state->voice, 0, delta);

            if (delta) {
                evt.common.type  = AL_SNDP_END_EVT;
                evt.common.state = state;
                alEvtqPostEvent(&sndp->evtq, (ALEvent *)&evt, delta);
                state->state = AL_STOPPING;
            } else {
                /* note: this code is repeated in AL_SNDP_END_EVT */
                alSynStopVoice(sndp->drvr, &state->voice);
                alSynFreeVoice(sndp->drvr, &state->voice);
                _removeEvents(&sndp->evtq, state);
                state->state = AL_STOPPED;
            }            
            break;

        case (AL_SNDP_PAN_EVT):
            state->pan = event->pan.pan;
            if (state->state == AL_PLAYING && snd){
                tmp   = state->pan - AL_PAN_CENTER + snd->samplePan;
                tmp   = MAX(tmp, AL_PAN_LEFT);
                pan   = (ALPan) MIN(tmp, AL_PAN_RIGHT);
                alSynSetPan(sndp->drvr, &state->voice, pan);
            }
            break;

        case (AL_SNDP_PITCH_EVT):
	    /* Limit the pitch to a practical value even though we only need */
	    /* to limit it to a non-zero number to avoid divide by zero. */
            if ((state->pitch = event->pitch.pitch) < MIN_RATIO)
		state->pitch = MIN_RATIO;
	    
            if (state->state == AL_PLAYING){
                alSynSetPitch(sndp->drvr, &state->voice, state->pitch);
            }
            break;
            
        case (AL_SNDP_FX_EVT):
            state->fxMix = event->fx.mix;
            if (state->state == AL_PLAYING)
                alSynSetFXMix(sndp->drvr, &state->voice, state->fxMix);
            break;

        case (AL_SNDP_VOL_EVT):
            state->vol = event->vol.vol;
            if (state->state == AL_PLAYING && snd){
                vtmp  = snd->envelope->decayVolume * state->vol/AL_VOL_FULL;            
                alSynSetVol(sndp->drvr, &state->voice, (s16) vtmp, 1000);
            }
            break;

        case (AL_SNDP_DECAY_EVT):
            /*
             * The voice has theoretically reached its attack velocity,
             * set up callback for release envelope - except for a looped sound
             */
            if (snd->envelope->decayTime != -1){
                vtmp   = snd->envelope->decayVolume * state->vol/AL_VOL_FULL;            
		delta = (ALMicroTime) _DivS32ByF32 (snd->envelope->decayTime, state->pitch);
                alSynSetVol(sndp->drvr, &state->voice, (s16) vtmp, delta);
                evt.common.type        = AL_SNDP_STOP_EVT;
                evt.common.state       = state;
                alEvtqPostEvent(&sndp->evtq, (ALEvent *)&evt, delta);
            }
            break;

        case (AL_SNDP_END_EVT):
            /* note: this code is repeated in AL_SNDP_STOP_EVT */
            alSynStopVoice(sndp->drvr, &state->voice);
            alSynFreeVoice(sndp->drvr, &state->voice);
            _removeEvents(&sndp->evtq, state);
            state->state = AL_STOPPED;
            break;

        default:
            break;
    }
}
static void _removeEvents(ALEventQueue *evtq, ALSoundState *state)
{
    ALLink              *thisNode;
    ALLink              *nextNode;
    ALEventListItem     *thisItem;
    ALEventListItem     *nextItem;
    ALSndpEvent         *thisEvent;
    OSIntMask           mask;

    mask = osSetIntMask(OS_IM_NONE);

    thisNode = evtq->allocList.next;
    while( thisNode != 0 ) {
	nextNode = thisNode->next;
        thisItem = (ALEventListItem *)thisNode;
        nextItem = (ALEventListItem *)nextNode;
        thisEvent = (ALSndpEvent *) &thisItem->evt;
        if (thisEvent->common.state == state){
            if( nextItem )
                nextItem->delta += thisItem->delta;
            alUnlink(thisNode);
            alLink(thisNode, &evtq->freeList);
        }
	thisNode = nextNode;
    }
    
    osSetIntMask(mask);
}
/*
  This routine safely divides a signed 32-bit integer
  by a floating point value.  It avoids overflow by using
  a double to store the result and then before truncating
  to an integer it compares the result to the limit and
  limits it on overflow.  Underflow is handled automatically
  by the CPU which limits the value to zero.

  Presently this routine is  used to divide a time in usecs
  by a pitch ratio. Since the time could be a very large number,
  very small pitch ratios can cause the reult to overflow,
  causing a floating point exception.
*/
#if BUILD_VERSION == VERSION_J // Adjust line numbers to match assert
#line 277
#elif BUILD_VERSION < VERSION_J
#line 278
#endif
static s32 _DivS32ByF32 (s32 i, f32 f)
{
    #define INT_MAX         2147483647      /* Should be in a limits.h file. */
    f64	rd;
    int	ri;

    assert(f!=0);	/* Caller must make sure we do not divide by zero! */

    rd = i/f;		/* Store result as a double to avoid overflow. */
    
    if (rd > INT_MAX)	/* Limit the value if necessary. */
	ri = INT_MAX;
    else
	ri = rd;

    return ri;
}
