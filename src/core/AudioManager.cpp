#include "stdafx.h"
#include "core/AudioManager.h"

#include <portaudio.h>

#include "core/Log.h"

AudioManager::AudioManager()
{

}

AudioManager::~AudioManager()
{

}

bool AudioManager::init()
{
	// PORTAUDIO
	if (PaError error = Pa_Initialize() != paNoError)
	{
		LOG_ERROR("Failed to initialize portaudio: %s", Pa_GetErrorText(error));
		return false;
	}

	return true;
}

void AudioManager::shutdown()
{
	// PORTAUDIO
	if (PaError error = Pa_Terminate() != paNoError)
	{
		LOG_ERROR("Failed to terminate portaudio: %s", Pa_GetErrorText(error));
	}
}
