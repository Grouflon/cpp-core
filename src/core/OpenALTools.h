#pragma once

#include <al.h>
#include <alc.h>
#include "core/Assert.h"
#include "core/AudioSample.h"

#define ALC_ASSERT(cond, device) cond; { ALCenum error = alcGetError(device); ASSERT(error == ALC_NO_ERROR); }
#define AL_ASSERT(cond) cond; { ALCenum error = alGetError(); ASSERT(error == AL_NO_ERROR); }

static ALenum AudioFormatToALFormat(AudioFormat _format)
{
	switch(_format)
	{
		case AUDIOFORMAT_MONO8: return AL_FORMAT_MONO8;
		case AUDIOFORMAT_MONO16: return AL_FORMAT_MONO16;
		case AUDIOFORMAT_STEREO8: return AL_FORMAT_STEREO8;
		case AUDIOFORMAT_STEREO16: return AL_FORMAT_STEREO16;
		default: return AL_INVALID;
	}
}