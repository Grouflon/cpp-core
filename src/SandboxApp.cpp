#include "stdafx.h"
#include "SandboxApp.h"

#include <al.h>
#include <alc.h>

SandboxApp::SandboxApp()
{
}

SandboxApp::~SandboxApp()
{
}


class AudioSample
{
public:
	enum Format
	{
		FORMAT_MONO8,
		FORMAT_MONO16,
		FORMAT_STEREO8,
		FORMAT_STEREO16,
	};
	AudioSample(uint32 frequency, uint32 samplesCount, Format format)
		: m_frequency(frequency)
		, m_samplesCount(samplesCount)
		, m_format(format)
		, m_buffer(nullptr)
	{
		m_buffer = new char[getBufferSize()];
	}
	~AudioSample()
	{
		delete m_buffer;
	}

	void* getBuffer()
	{
		return m_buffer;
	}
	const void* getBuffer() const
	{
		return m_buffer;
	}
	uint32 getBufferSize() const
	{
		return m_samplesCount * getFormatSampleSize(m_format);
	}
	uint32 getSamplesCount() const
	{
		return m_samplesCount;
	}
	uint32 getFrequency() const
	{
		return m_frequency;
	}

	static uint32 getFormatSampleSize(Format format)
	{
		switch(format)
		{
		case FORMAT_MONO8: return 1;
		case FORMAT_MONO16: return 2;
		case FORMAT_STEREO8: return 2;
		case FORMAT_STEREO16: return 4;
		default: return 0;
		}
	}

private:
	uint32	m_frequency;
	uint32	m_samplesCount;
	Format	m_format;
	void*	m_buffer;
};

static ALCdevice* ALDevice;
static ALCcontext* ALContext;
static ALuint buffer;
static ALuint source;
static bool isPlaying;

int32 amplitude = 1000;
uint32 frequency = 48000;
uint32 tone = 260; // C
uint32 waveLength = frequency / tone;
static AudioSample sample(frequency, waveLength, AudioSample::FORMAT_STEREO16);
static AudioSample sample2(frequency, waveLength, AudioSample::FORMAT_STEREO16);

#define ALC_ASSERT(cond) cond; { ALCenum error = alcGetError(); ASSERT(error == ALC_NO_ERROR); }
#define AL_ASSERT(cond) cond; { ALCenum error = alGetError(); ASSERT(error == AL_NO_ERROR); }

void SandboxApp::started()
{
	ALDevice = alcOpenDevice(nullptr);

	if (ALDevice)
	{
		ALContext = alcCreateContext(ALDevice, nullptr);
		alcMakeContextCurrent(ALContext);
		alcGetError(ALDevice);

		uint32 halfWaveLength = sample.getSamplesCount() / 2;
		int16* bufferCursor = (int16*)sample.getBuffer();

		for (uint32 i = 0; i < waveLength; ++i)
		{
			*bufferCursor++ = (i / halfWaveLength) % 2 ? amplitude : -amplitude; // LEFT
			*bufferCursor++ = (i / halfWaveLength) % 2 ? amplitude : -amplitude; // RIGHT
		}

		bufferCursor = (int16*)sample2.getBuffer();
		for (uint32 i = 0; i < waveLength; ++i)
		{
			*bufferCursor++ = (int16)(sinf((float)i / float(waveLength) * MATH_PI * 2.f) * amplitude); // LEFT
			*bufferCursor++ = (int16)(sinf((float)i / float(waveLength) * MATH_PI * 2.f) * amplitude); // RIGHT
		}

		AL_ASSERT(alGenBuffers(1, &buffer));
		AL_ASSERT(alBufferData(buffer, AL_FORMAT_STEREO16, sample2.getBuffer(), sample2.getBufferSize(), sample2.getFrequency()));

		AL_ASSERT(alGenSources(1, &source));
		AL_ASSERT(alSourcei(source, AL_BUFFER, buffer));

		ALfloat listenerPos[]={0.0,0.0,0.0};
		ALfloat listenerVel[]={0.0,0.0,0.0};
		ALfloat listenerOri[]={0.0,0.0,-1.0, 0.0,1.0,0.0};
		AL_ASSERT(alListenerfv(AL_POSITION,listenerPos));
		AL_ASSERT(alListenerfv(AL_VELOCITY,listenerVel));
		AL_ASSERT(alListenerfv(AL_ORIENTATION,listenerOri));

		alSourcei(source, AL_LOOPING, AL_TRUE);
	}
	else
	{
		std::cerr << "SandboxApp -> Error creating ALDevice." << std::endl;
	}
}

void SandboxApp::update(float dt)
{
	if (isPlaying)
	{
		if (ImGui::Button("STOP"))
		{
			isPlaying = false;
			alSourceStop(source);
		}
	}
	else
	{
		if (ImGui::Button("PLAY"))
		{
			isPlaying = true;
			alSourcePlay(source);
		}
	}

	ImGui::PlotLines(
		"sampleL",
		[](void* data, int idx) -> float
		{
			return ((int16*)data)[idx*2];
		},
		sample.getBuffer(),
		sample.getSamplesCount()
		);

	ImGui::PlotLines(
		"sampleR",
		[](void* data, int idx) -> float
		{
			return ((int16*)data)[idx*2+1];
		},
		sample.getBuffer(),
		sample.getSamplesCount()
		);

	ImGui::PlotLines(
		"sampleL",
		[](void* data, int idx) -> float
		{
			return ((int16*)data)[idx*2];
		},
		sample2.getBuffer(),
		sample2.getSamplesCount()
		);

	ImGui::PlotHistogram(
		"sampleR",
		[](void* data, int idx) -> float
		{
			return ((int16*)data)[idx*2+1];
		},
		sample2.getBuffer(),
		sample2.getSamplesCount()
		);
}

void SandboxApp::render()
{
}

void SandboxApp::stopped()
{
	alDeleteBuffers(1, &buffer);
	alcDestroyContext(ALContext); 
	alcCloseDevice(ALDevice);
}