#pragma once

#include <alc.h>

class AudioManager
{
public:
	AudioManager();
	~AudioManager();

	bool init();
	void shutdown();

private:

	ALCdevice* m_alDevice;
	ALCcontext* m_alContext;
};

static AudioManager g_audioManager;
