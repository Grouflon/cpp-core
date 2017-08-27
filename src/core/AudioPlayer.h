#pragma once

#include <portaudio.h>
#include "core/Types.h"

class AudioSample;
typedef void PaStream;

class AudioPlayer
{
public:
	AudioPlayer();
	AudioPlayer(AudioSample* _sample);
	~AudioPlayer();

	void setSample(AudioSample* _sample);

	void play();
	void stop();

	bool isPlaying() const;

	void setLooping(bool _value);
	bool isLooping() const;

private:

	static int PaReadCallback(const void* _input, void* _output, unsigned long _frameCount, const PaStreamCallbackTimeInfo* _timeInfo, PaStreamCallbackFlags _statusFlags, void* _userData);

	bool m_looping;

	AudioSample* m_sample;
	PaStream* m_stream;

	uint32 m_playedSamples;
};