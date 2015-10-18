#include "stdafx.h"
#include "core/BinarySerializer.h"

#include "core/File.h"
#include "core/Serializer.h"
#include "core/Serializable.h"

BinarySerializer::BinarySerializer(File* file, Mode mode)
	: Serializer(file, mode)
{
}

BinarySerializer::~BinarySerializer()
{
}

void BinarySerializer::serialize(const char*, bool& value)
{
	_rawSerialize(&value, sizeof(value));
}

void BinarySerializer::serialize(const char*, uint8& value)
{
	_rawSerialize(&value, sizeof(value));
}

void BinarySerializer::serialize(const char*, uint16& value)
{
	_rawSerialize(&value, sizeof(value));
}

void BinarySerializer::serialize(const char*, uint32& value)
{
	_rawSerialize(&value, sizeof(value));
}

void BinarySerializer::serialize(const char*, uint64& value)
{
	_rawSerialize(&value, sizeof(value));
}

void BinarySerializer::serialize(const char*, int8& value)
{
	_rawSerialize(&value, sizeof(value));
}

void BinarySerializer::serialize(const char*, int16& value)
{
	_rawSerialize(&value, sizeof(value));
}

void BinarySerializer::serialize(const char*, int32& value)
{
	_rawSerialize(&value, sizeof(value));
}

void BinarySerializer::serialize(const char*, int64& value)
{
	_rawSerialize(&value, sizeof(value));
}

void BinarySerializer::serialize(const char*, std::string& value)
{
	if (_getMode() == MODE_READ)
	{
		value.clear();
		File* file = _getFile();
		char buf;
		while (true)
		{
			if (file->read(&buf, 1) == 0 || buf == '\0')
			{
				break;
			}
			value += buf;
		}
	}
	else
	{
		_getFile()->write(value.c_str(), value.size()+1);
	}
}

void BinarySerializer::serialize(const char*, Serializable& serializable)
{
	serializable.serialize(this);
}

void BinarySerializer::_rawSerialize(void* data, int size)
{
	if (_getMode() == MODE_READ)
	{
		_getFile()->read(data, size);
	}
	else
	{
		_getFile()->write(data, size);
	}
}
