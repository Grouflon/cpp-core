#pragma once

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
	uint32 m_alBufferId;
	uint32 m_alSourceId;
};