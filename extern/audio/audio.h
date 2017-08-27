#ifndef GRU_AUDIO_H_INCLUDED
#define GRU_AUDIO_H_INCLUDED

#include <stdint.h>

#define GRU_AUDIO_LOG_ERRORS 1

#if defined(_MSC_VER)
#pragma warning(push)
#pragma warning(disable : 4200)
#endif

#ifdef __cplusplus
extern "C" {
#endif

enum audio_format_e
{
	audio_format_mono8,
	audio_format_mono16,
	audio_format_stereo8,
	audio_format_stereo16,
};

struct audio_sample_s
{
	uint32_t frequency;
	uint16_t chunk_size;
	uint16_t channel_count;
	uint32_t chunk_count;
	char data[0];
};

struct audio_sample_s* audio_read(const void* _data);

#ifdef __cplusplus
} // extern "C"
#endif

#if defined(_MSC_VER)
#pragma warning(pop)
#endif

#endif//GRU_AUDIO_H_INCLUDED
