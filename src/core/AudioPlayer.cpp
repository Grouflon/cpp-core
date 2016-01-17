#include "core/AudioPlayer.h"

#include "core/OpenALTools.h"
#include "core/AudioSample.h"

AudioPlayer::AudioPlayer()
	: m_playing(false)
	, m_sample(nullptr)
	, m_alBufferId(AL_INVALID)
	, m_alSourceId(AL_INVALID)
{
}

AudioPlayer::AudioPlayer(AudioSample* _sample)
	: m_sample(nullptr)
	, m_alBufferId(AL_INVALID)
	, m_alSourceId(AL_INVALID)
{
	setSample(_sample);
}

AudioPlayer::~AudioPlayer()
{
	setSample(nullptr);
}

void AudioPlayer::setSample(AudioSample* _sample)
{
	if (m_sample)
	{
		m_sample->releaseUnuse();
		m_sample = nullptr;

		alDeleteBuffers(1, &m_alBufferId);
		alDeleteSources(1, &m_alSourceId);

		m_alBufferId = AL_INVALID;
		m_alSourceId = AL_INVALID;
	}

	if (_sample)
	{
		m_sample = _sample;
		m_sample->loadUse();

		AudioFormat format = m_sample->getFormat();

		AL_ASSERT(alGenBuffers(1, &m_alBufferId));
		AL_ASSERT(alBufferData(
			m_alBufferId,
			AudioFormatToALFormat(format),
			m_sample->getBuffer(),
			m_sample->getSampleCount() * AudioSample::getFormatSampleSize(format),
			m_sample->getFrequency()
		));

		AL_ASSERT(alGenSources(1, &m_alSourceId));
		AL_ASSERT(alSourcei(m_alSourceId, AL_BUFFER, m_alBufferId));
	}
}

void AudioPlayer::play()
{
	if (!m_sample) return;
	
	AL_ASSERT(alSourcePlay(m_alSourceId);)		
}

bool AudioPlayer::isPlaying() const
{
	ALenum state;
	AL_ASSERT(alGetSourcei(m_alSourceId, AL_SOURCE_STATE, &state));
	return state == AL_PLAYING;
}

void AudioPlayer::setLooping(bool _value)
{
	AL_ASSERT(alSourcei(m_alSourceId, AL_LOOPING, _value));
}

bool AudioPlayer::isLooping() const
{
	if (!m_sample) return false;

	int looping = 0;
	AL_ASSERT(alGetSourcei(m_alSourceId, AL_LOOPING, &looping));
	return looping != 0;
}

void AudioPlayer::stop()
{
	if (!m_sample) return;

	AL_ASSERT(alSourceStop(m_alSourceId);)
}