#include "core/AudioSample.h"

#include "core/Assert.h"

AudioSample::AudioSample()
	: m_frequency(0)
	, m_samplesCount(0)
	, m_format(AUDIOFORMAT_MONO8)
	, m_buffer(nullptr)
{

}

AudioSample::AudioSample(uint32 frequency, uint32 samplesCount, AudioFormat format)
	: m_frequency(frequency)
	, m_samplesCount(samplesCount)
	, m_format(format)
	, m_buffer(nullptr)
{
}

AudioSample::~AudioSample()
{
	
}

void AudioSample::onLoad()
{
	m_buffer = new char[m_samplesCount* getFormatSampleSize(m_format)];
}

void AudioSample::onRelease()
{
	delete[] m_buffer;
}

void AudioSample::setSampleCount(uint32 _value)
{
	ASSERT(!isLoaded());
	m_samplesCount = _value;
}

void* AudioSample::getBuffer()
{
	return m_buffer;
}

const void* AudioSample::getBuffer() const
{
	return m_buffer;
}

uint32 AudioSample::getSampleCount() const
{
	return m_samplesCount;
}

void AudioSample::setFormat(AudioFormat _value)
{
	ASSERT(!isLoaded());
	m_format = _value;
}

AudioFormat AudioSample::getFormat() const
{
	return m_format;
}

void AudioSample::setFrequency(uint32 _value)
{
	ASSERT(!isLoaded());
	m_frequency = _value;
}

uint32 AudioSample::getFrequency() const
{
	return m_frequency;
}

uint32 AudioSample::getFormatSampleSize(AudioFormat format)
{
	switch(format)
	{
	case AUDIOFORMAT_MONO8: return 1;
	case AUDIOFORMAT_MONO16: return 2;
	case AUDIOFORMAT_MONO24: return 3;
	case AUDIOFORMAT_STEREO8: return 2;
	case AUDIOFORMAT_STEREO16: return 4;
	default: return 0;
	}
}

uint8 AudioSample::getFormatChannelCount(AudioFormat _format)
{
	switch(_format)
	{
	case AUDIOFORMAT_MONO8: return 1;
	case AUDIOFORMAT_MONO16: return 1;
	case AUDIOFORMAT_MONO24: return 1;
	case AUDIOFORMAT_STEREO8: return 2;
	case AUDIOFORMAT_STEREO16: return 2;
	default: return 0;
	}
}

