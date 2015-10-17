#pragma once

#include <string>

#include "core/Types.h"

class File;
class Serializable;

class Serializer
{
public:
	enum Mode
	{
		MODE_READ,
		MODE_WRITE
	};

	Serializer(File* file, Mode mode);
	virtual ~Serializer();

	virtual void serialize(const char* name, bool& value) = 0;

	virtual void serialize(const char* name, uint8& value) = 0;
	virtual void serialize(const char* name, uint16& value) = 0;
	virtual void serialize(const char* name, uint32& value) = 0;
	virtual void serialize(const char* name, uint64& value) = 0;

	virtual void serialize(const char* name, int8& value) = 0;
	virtual void serialize(const char* name, int16& value) = 0;
	virtual void serialize(const char* name, int32& value) = 0;
	virtual void serialize(const char* name, int64& value) = 0;

	virtual void serialize(const char* name, std::string& value) = 0;

	virtual void serialize(const char* name, Serializable& serializable) = 0;

	// TODO: Container types

private:
	File*	m_file;
	Mode	m_mode;
};
