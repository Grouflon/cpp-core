#pragma once

#include <al.h>

class AudioSample;

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

	bool m_playing;

	AudioSample* m_sample;
	ALuint m_alBufferId;
	ALuint m_alSourceId;
};