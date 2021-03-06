#include "core/AudioFile.h"

#include <cstdlib>
#include <cstring>
#include <audio.h>

#include "core/File.h"


AudioFile::AudioFile(const char* _path)
{
	m_path = _path;
}

AudioFile::~AudioFile()
{
}

void AudioFile::onLoad()
{
	File file(m_path.c_str());
	file.load();

	if (file.getError() != ERROR_NONE)
	{
		setError(file.getError(), file.getErrorDescription());
		return;
	}

	audio_sample_s* sample = audio_read(file.getContent());
	file.release();

	if (!sample)
	{
		setError(ERROR_LOAD, "Unable to read audio format.");
		return;
	}

	bool error = false;
	if (sample->channel_count == 1)
	{
		if (sample->chunk_size == 1) setFormat(AUDIOFORMAT_MONO8);
		else if (sample->chunk_size == 2) setFormat(AUDIOFORMAT_MONO16);
		else if (sample->chunk_size == 3) setFormat(AUDIOFORMAT_MONO24);
		else error = true;
	}
	else if (sample->channel_count == 2)
	{
		if (sample->chunk_size == 2) setFormat(AUDIOFORMAT_STEREO8);
		else if (sample->chunk_size == 4) setFormat(AUDIOFORMAT_STEREO16);
		else error = true;
	}
	else error = true;

	if (error)
	{
		setError(ERROR_LOAD, "Unable to read audio format.");
		return;
	}

	setFrequency(sample->frequency);
	setSampleCount(sample->chunk_count);
	AudioSample::onLoad();
	memcpy(getBuffer(), sample->data, sample->chunk_count * sample->chunk_size);
	free(sample);
}

void AudioFile::onRelease()
{
	AudioSample::onRelease();
}

const char* AudioFile::getPath() const
{
	return m_path.c_str();
}