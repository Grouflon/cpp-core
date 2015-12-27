#ifndef GRU_AUDIO_H_INCLUDED
#define GRU_AUDIO_H_INCLUDED

#include <stdint.h>

#define GRU_AUDIO_LOG_ERRORS 1

#ifdef __cplusplus
extern "C" {
#endif

struct audio_sample_s;
enum audio_format_e;


struct audio_sample_s* audio_read(const void* _data);



struct audio_sample_s
{
	uint32_t frequency;
	uint16_t bytes_per_chunk;
	uint16_t channel_count;
	uint32_t chunk_count;
	char data[0];
};


enum audio_format_e
{
	audio_format_mono8,
	audio_format_mono16,
	audio_format_stereo8,
	audio_format_stereo16,
};

#ifdef __cplusplus
} // extern "C"
#endif

#endif//GRU_AUDIO_H_INCLUDED
