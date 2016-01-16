#pragma once

#include <string>

class AudioFile;
class AudioSample;

class EditorAudio
{
public:
	EditorAudio();
	~EditorAudio();

	void update(float _dt);

private:
	void openSample(const char* _path);
	void displaySampleGraph(AudioSample* _sample);

	bool m_openingFile;
	char m_pathBuffer[256];
	AudioFile* m_currentAudioFile;
};