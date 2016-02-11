#pragma once

#include <string>
#include "core/AudioPlayer.h"

class AudioFile;
class AudioSample;

class EditorAudio
{
public:
	EditorAudio();
	~EditorAudio();

	void update(float _dt);
	void openSample(const char* _path);

private:
	void displaySampleGraph(AudioSample* _sample);

	bool m_openingFile;
	char m_pathBuffer[256];
	AudioFile* m_currentAudioFile;
	AudioPlayer m_player;
};