#include "stdafx.h"
#include "core/StringTools.h"

void lowerCase(std::string& str)
{
	for (char& c : str)
	{
		if (c >= 'A' && c <= 'Z')
		{
			c -= 'A' - 'a';
		}
	}
}

void lowerCase(char* str)
{
	while (*str != '\0')
	{
		if (*str >= 'A' && *str <= 'Z')
		{
			*str -= 'A' - 'a';
		}
		++str;
	}
}

void upperCase(std::string& str)
{
	for (char& c : str)
	{
		if (c >= 'a' && c <= 'z')
		{
			c += 'A' - 'a';
		}
	}
}

void upperCase(char* str)
{
	while (*str != '\0')
	{
		if (*str >= 'a' && *str <= 'z')
		{
			*str += 'A' - 'a';
		}
		++str;
	}
}

std::string toLowerCase(const std::string& str)
{
	std::string result = str;
	lowerCase(result);
	return result;
}

std::string toUpperCase(const std::string& str)
{
	std::string result = str;
	upperCase(result);
	return result;
}