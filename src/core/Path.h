#pragma once

#include <string>

class Path
{
public:
	static size_t GetDirectoriesLength(const char* _path);
	static void Sanitize(char* _path);
};