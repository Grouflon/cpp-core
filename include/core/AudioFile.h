#pragma once

#include "core/AudioSample.h"

class AudioFile : public AudioSample
{
public:
	AudioFile(const char* _path);
	virtual ~AudioFile();

	virtual void onLoad() override;
	virtual void onRelease() override;

	const char* getPath() const;

private:
	std::string m_path;
};