#pragma once

struct ALCdevice_struct;
struct ALCcontext_struct;
typedef ALCdevice_struct ALCdevice;
typedef ALCcontext_struct ALCcontext;

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
