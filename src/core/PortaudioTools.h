#pragma once

#include <portaudio.h>
#include "core/Log.h"
#include "core/Assert.h"
#include "core/AudioSample.h"

#define PA_ASSERT(f) if (PaError error = f != paNoError) { LOG_ERROR("Portaudio error: %s", Pa_GetErrorText(error)); ASSERT(false); }

static PaSampleFormat AudioFormatToPaSampleFormat(AudioFormat _format)
{
	switch(_format)
	{
	case AUDIOFORMAT_MONO8: return paInt8;
	case AUDIOFORMAT_MONO16: return paInt16;
	case AUDIOFORMAT_MONO24: return paInt24;
	case AUDIOFORMAT_STEREO8: return paInt8;
	case AUDIOFORMAT_STEREO16: return paInt16;
	default: return paNonInterleaved;
	}
}