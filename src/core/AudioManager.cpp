#include "stdafx.h"
#include "core/AudioManager.h"

#include <alc.h>
#include <portaudio.h>

#include "core/OpenALTools.h"
#include "core/Log.h"

AudioManager::AudioManager()
	: m_alDevice(nullptr)
	, m_alContext(nullptr)
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

	// OPEN DEVICE
	m_alDevice = alcOpenDevice(nullptr);
	if (!m_alDevice)
	{
		LOG_ERROR("Failed to open ALCdevice.");
		return false;
	}

	// CREATE CONTEXT
	m_alContext = alcCreateContext(m_alDevice, nullptr);
	if (!m_alContext)
	{
		LOG_ERROR("Failed to create ALCcontext.");
		return false;
	}
	ALC_ASSERT(alcMakeContextCurrent(m_alContext), m_alDevice);

	// POSITION LISTENER
	ALfloat listenerPos[]={0.0,0.0,0.0};
	ALfloat listenerVel[]={0.0,0.0,0.0};
	ALfloat listenerOri[]={0.0,0.0,-1.0, 0.0,1.0,0.0};
	AL_ASSERT(alListenerfv(AL_POSITION,listenerPos));
	AL_ASSERT(alListenerfv(AL_VELOCITY,listenerVel));
	AL_ASSERT(alListenerfv(AL_ORIENTATION,listenerOri));

	return true;
}

void AudioManager::shutdown()
{
	alcDestroyContext(m_alContext); 
	alcCloseDevice(m_alDevice);

	// PORTAUDIO
	if (PaError error = Pa_Terminate() != paNoError)
	{
		LOG_ERROR("Failed to terminate portaudio: %s", Pa_GetErrorText(error));
	}
}
