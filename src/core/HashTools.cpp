#include "core/HashTools.h"

#include <cstring>

#define OFFSET_BASIS	2166136261
#define FNV_PRIME		16777619

uint32 hash32(const void* data, size_t size)
{
	if (size == 0)
	{
		return 0;
	}

	// FNV-1a algorithm
	// http://isthe.com/chongo/tech/comp/fnv/
	uint32 hash = OFFSET_BASIS;
	const uint8* buf = static_cast<const uint8*>(data);
	for (uint32 i = 0u; i < size; i++)
	{
		hash = hash * FNV_PRIME;
		hash = hash ^ *buf;
		++buf;
	}
	return hash;
}

uint32 hashString(const char* str)
{
	return hash32(str, strlen(str));
}