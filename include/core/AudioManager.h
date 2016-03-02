#pragma once

class AudioManager
{
public:
	AudioManager();
	~AudioManager();

	bool init();
	void shutdown();
};

static AudioManager g_audioManager;
