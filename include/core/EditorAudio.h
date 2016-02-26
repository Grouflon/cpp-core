#pragma once

#include <portaudio.h>

#include "core/AudioPlayer.h"

class AudioFile;
class AudioSample;

class EditorAudio
{
public:
	struct RecordData
	{
		uint32 currentFrame;
		uint32 maxFrame;
		int16* data;
	};

	EditorAudio();
	~EditorAudio();

	void update(float _dt);
	void openFile(const char* _path);
	void setSample(AudioSample* _sample);

private:
	void record();
	void stopRecord();
	void displaySampleGraph(AudioSample* _sample);

	bool m_openingFile;
	char m_pathBuffer[256];
	AudioSample* m_currentAudioSample;
	AudioPlayer m_player;
	PaStream* m_recording;
	RecordData m_recordingData;
};