#include "core/AudioPlayer.h"

#include "core/PortaudioTools.h"
#include "core/AudioSample.h"

AudioPlayer::AudioPlayer()
	: m_looping(false)
	, m_sample(nullptr)
	, m_stream(nullptr)
	, m_playedSamples(0u)
{
}

AudioPlayer::AudioPlayer(AudioSample* _sample)
	: AudioPlayer()
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

		PA_ASSERT(Pa_StopStream(m_stream))
		PA_ASSERT(Pa_CloseStream(m_stream));
		m_stream = nullptr;
	}

	if (_sample)
	{
		m_sample = _sample;
		m_sample->loadUse();

		AudioFormat format = m_sample->getFormat();

		PaStreamParameters outputParameters = {};
		outputParameters.device = Pa_GetDefaultOutputDevice();
		outputParameters.channelCount = AudioSample::GetFormatChannelCount(format);
		outputParameters.suggestedLatency = Pa_GetDeviceInfo(outputParameters.device)->defaultLowOutputLatency;
		outputParameters.sampleFormat = AudioFormatToPaSampleFormat(format);

		PA_ASSERT(Pa_OpenStream(&m_stream, nullptr, &outputParameters, static_cast<double>(m_sample->getFrequency()), 0, paNoFlag, PaReadCallback, this));
	}
}

void AudioPlayer::play()
{
	if (!m_sample) return;

	stop(); // Stream does not seem to stop automatically when paComplete is returned by the callback

	PaError error = Pa_StartStream(m_stream);
	if (error != paNoError)
	{
		LOG_ERROR("Portaudio error: %s", Pa_GetErrorText(error));
		ASSERT(false);
	}
}

bool AudioPlayer::isPlaying() const
{
	PaError active = Pa_IsStreamActive(m_stream);
	if (active < 0)
	{
		LOG_ERROR("Portaudio error: %s", Pa_GetErrorText(active));
		ASSERT(false);
	}
	return active == 1;
}

void AudioPlayer::setLooping(bool _value)
{
	m_looping = _value;
}

bool AudioPlayer::isLooping() const
{
	return m_looping;
}

void AudioPlayer::stop()
{
	if (!m_sample) return;

	m_playedSamples = 0;

	PaError error = Pa_StopStream(m_stream);
	if (error != paNoError)
	{
		LOG_ERROR("Portaudio error: %s", Pa_GetErrorText(error));
		ASSERT(false);
	}
}

int AudioPlayer::PaReadCallback(const void*, void* _output, unsigned long _frameCount, const PaStreamCallbackTimeInfo*, PaStreamCallbackFlags _statusFlags, void* _userData)
{
	AudioPlayer* player = reinterpret_cast<AudioPlayer*>(_userData);
	AudioSample* sample = player->m_sample;
	uint16 sampleSize = AudioSample::GetFormatSampleSize(sample->getFormat());
	uint32 sampleCount = player->m_sample->getSampleCount();

	uint8* out = static_cast<uint8*>(_output);
	uint8* buffer = static_cast<uint8*>(sample->getBuffer()) + (player->m_playedSamples * sampleSize);

	if (player->m_playedSamples + _frameCount > sampleCount)
	{
		uint32 remainingSamples = sampleCount - player->m_playedSamples;
		uint32 remainingSize = remainingSamples * sampleSize;
		memcpy(out, buffer, remainingSize);

		if (player->isLooping())
		{
			out += remainingSize;
			buffer = static_cast<uint8*>(sample->getBuffer());
			uint32 overflowSamples = _frameCount - remainingSamples;
			memcpy(out, buffer, overflowSamples * sampleSize);
			player->m_playedSamples = overflowSamples;
			return paContinue;
		}
		else
		{
			player->m_playedSamples = 0;
			return paComplete;
		}
	}
	else
	{
		memcpy(out, buffer, _frameCount * sampleSize);
		player->m_playedSamples += _frameCount;
		return paContinue;
	}
}