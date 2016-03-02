#pragma once

#include "core/Resource.h"

enum AudioFormat
{
	AUDIOFORMAT_MONO8,
	AUDIOFORMAT_MONO16,
	AUDIOFORMAT_MONO24,
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

	void setSampleCount(uint32 _value);
	uint32 getSampleCount() const;
	void setFormat(AudioFormat _value);
	AudioFormat getFormat() const;
	void setFrequency(uint32 _value);
	uint32 getFrequency() const;

	void* getBuffer();
	const void* getBuffer() const;

	static uint32 GetFormatSampleSize(AudioFormat _format);
	static uint8 GetFormatChannelCount(AudioFormat _format);

private:
	uint32	m_frequency;
	uint32	m_samplesCount;
	AudioFormat	m_format;
	void*	m_buffer;
};