#pragma once

#include <string>

class AudioFile;

class EditorAudio
{
public:
	EditorAudio();
	~EditorAudio();

	void update(float _dt);
	void setRootPath(const char* _value);

private:
	char buf[256];
	std::string m_rootPath;
	AudioFile* m_currentAudioFile;
};