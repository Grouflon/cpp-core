#include "audio.h"

#include <string.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#if GRU_AUDIO_LOG_ERRORS
#define GRU_LOG_ERROR(...) { fprintf(stderr, "[ERROR]"); fprintf(stderr, __VA_ARGS__); fprintf(stderr, "\n"); }
#else
#define GRU_LOG_ERROR(...)
#endif

static uint16_t read2(const char** _cursor)
{
	uint16_t ret = **(const uint16_t**)_cursor;
	*_cursor += 2;
	return ret;
}

static uint32_t read4(const char** _cursor)
{
	uint32_t ret = **(const uint32_t**)_cursor;
	*_cursor += 4;
	return ret;
}

static struct audio_sample_s* audio_read_wav(const void* _data)
{
	struct audio_sample_s* sample = NULL;
	const char* cursor = (const char*)_data;
	uint32_t file_size = 0;
	uint32_t description_header_size = 0;
	uint16_t compression = 0;
	uint16_t channel_count = 0;
	uint32_t frequency = 0;
	uint32_t bytes_per_second = 0;
	uint16_t bytes_per_chunk = 0;
	uint16_t bits_per_sample = 0;
	uint32_t data_size = 0;
	
	// HEADER
	if (memcmp(cursor, "RIFF", 4) != 0) return NULL;	cursor += 4;
	file_size = read4(&cursor);
	if (memcmp(cursor, "WAVE", 4) != 0) return NULL;	cursor += 4;
	if (memcmp(cursor, "fmt ", 4) != 0) return NULL;	cursor += 4;
	
	// DESCRIPTION
	description_header_size = read4(&cursor);
	if (description_header_size != 16)
	{
		GRU_LOG_ERROR("audio_read_wav: Unsupported format.");
		return NULL;
	}
	compression = read2(&cursor);
	if (compression != 1)
	{
		GRU_LOG_ERROR("audio_read_wav: Unsupported compression type.");
		return NULL;
	}
	channel_count = read2(&cursor);
	frequency = read4(&cursor);
	bytes_per_second = read4(&cursor);
	bytes_per_chunk = read2(&cursor);
	bits_per_sample = read2(&cursor);

	// DATA
	while (memcmp(cursor, "data", 4) != 0 && (cursor != (const char*)_data + file_size))
	{
		++cursor;
	}

	if (*cursor == '\0')
	{
		GRU_LOG_ERROR("audio_read_wav: Malformed wav file.");
		return NULL;
	}
	else
	{
		cursor += 4;
	}

	data_size = read4(&cursor);

	sample = (struct audio_sample_s*) malloc(sizeof(*sample) + data_size);
	sample->frequency = frequency;
	sample->chunk_size = bytes_per_chunk;
	sample->channel_count = channel_count;
	sample->chunk_count = data_size / bytes_per_chunk;
	memcpy(sample->data, cursor, data_size);

	return sample;
}

struct audio_sample_s* audio_read(const void* _data)
{
	struct audio_sample_s* sample = audio_read_wav(_data);
	if (!sample)
	{
		GRU_LOG_ERROR("audio_read: Unknown audio format.");
	}
	return sample;
}

#undef GRU_LOG_ERROR
