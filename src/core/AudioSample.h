#pragma once

#include "core/Resource.h"

enum AudioFormat
{
	AUDIOFORMAT_MONO8,
	AUDIOFORMAT_MONO16,
	AUDIOFORMAT_STEREO8,
	AUDIOFORMAT_STEREO16,
};

class AudioSample : public Resource
{
public:
	AudioSample();
	AudioSample(uint32 _frequency, uint32 _samplesCount, AudioFormat _format);
	virtual ~AudioSample();

	virtual void onLoad() override;
	virtual void onRelease() override;

	void setSamplesCount(uint32 _value);
	uint32 getSamplesCount() const;
	void setFormat(AudioFormat _value);
	AudioFormat getFormat() const;
	void setFrequency(uint32 _value);
	uint32 getFrequency() const;

	void* getBuffer();
	const void* getBuffer() const;

	static uint32 getFormatSampleSize(AudioFormat _format);

private:
	uint32	m_frequency;
	uint32	m_samplesCount;
	AudioFormat	m_format;
	void*	m_buffer;
};