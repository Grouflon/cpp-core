#include "stdafx.h"
#include "core/BinarySerializer.h"

#include "core/File.h"
#include "core/Serializer.h"
#include "core/ClassDesc.h"
#include "core/Factory.h"

BinarySerializer::BinarySerializer()
{
}

BinarySerializer::~BinarySerializer()
{
}

bool BinarySerializer::serialize(const char*, bool& value)
{
	return _rawSerialize(&value, sizeof(value));
}

bool BinarySerializer::serialize(const char*, uint8& value)
{
	return _rawSerialize(&value, sizeof(value));
}

bool BinarySerializer::serialize(const char*, uint16& value)
{
	return _rawSerialize(&value, sizeof(value));
}

bool BinarySerializer::serialize(const char*, uint32& value)
{
	return _rawSerialize(&value, sizeof(value));
}

bool BinarySerializer::serialize(const char*, uint64& value)
{
	return _rawSerialize(&value, sizeof(value));
}

bool BinarySerializer::serialize(const char*, int8& value)
{
	return _rawSerialize(&value, sizeof(value));
}

bool BinarySerializer::serialize(const char*, int16& value)
{
	return _rawSerialize(&value, sizeof(value));
}

bool BinarySerializer::serialize(const char*, int32& value)
{
	return _rawSerialize(&value, sizeof(value));
}

bool BinarySerializer::serialize(const char*, int64& value)
{
	return _rawSerialize(&value, sizeof(value));
}

bool BinarySerializer::serialize(const char*, float& value)
{
	return _rawSerialize(&value, sizeof(value));
}

bool BinarySerializer::serialize(const char*, double& value)
{
	return _rawSerialize(&value, sizeof(value));
}

bool BinarySerializer::serialize(const char* name, uint8* value, size_t size)
{
	return _rawSerialize(value, size * sizeof(value));
}

bool BinarySerializer::serialize(const char* name, uint16* value, size_t size)
{
	return _rawSerialize(value, size * sizeof(value));
}

bool BinarySerializer::serialize(const char* name, uint32* value, size_t size)
{
	return _rawSerialize(value, size * sizeof(value));
}

bool BinarySerializer::serialize(const char* name, uint64* value, size_t size)
{
	return _rawSerialize(value, size * sizeof(value));
}

bool BinarySerializer::serialize(const char* name, int8* value, size_t size)
{
	return _rawSerialize(value, size * sizeof(value));
}

bool BinarySerializer::serialize(const char* name, int16* value, size_t size)
{
	return _rawSerialize(value, size * sizeof(value));
}

bool BinarySerializer::serialize(const char* name, int32* value, size_t size)
{
	return _rawSerialize(value, size * sizeof(value));
}

bool BinarySerializer::serialize(const char* name, int64* value, size_t size)
{
	return _rawSerialize(value, size * sizeof(value));
}

bool BinarySerializer::serialize(const char* name, float* value, size_t size)
{
	return _rawSerialize(value, size * sizeof(value));
}

bool BinarySerializer::serialize(const char* name, double* value, size_t size)
{
	return _rawSerialize(value, size * sizeof(value));
}

bool BinarySerializer::serialize(const char*, std::string& value)
{
	if (isReading())
	{
		value.clear();
		const File* file = _getReadFile();
		char buf;
		while (true)
		{
			if (file->read(&buf, 1) == 0 || buf == '\0')
			{
				break;
			}
			value += buf;
		}
		return true;
	}
	else
	{
		return _getWriteFile()->write(value.c_str(), value.size()+1);
	}
}

bool BinarySerializer::serialize(const char* name, std::string* value, size_t size)
{
	for (size_t i = 0; i < size; ++i)
	{
		if (!serialize(name, value[i]))
			return false;
	}
	return true;
}

bool BinarySerializer::beginVectorSerialization(const char* _name, size_t& size)
{
	return serialize(nullptr, size);
}

bool BinarySerializer::endVectorSerialization()
{
	return true;
}


// TODO: refactor duplicated code
bool BinarySerializer::serialize(const char*, void** _pointer, const ClassDesc* _classDesc)
{
	std::string	className;

	if (!isReading())
	{
		className = _classDesc->getName();
	}

	bool result = serialize("className", className);

	if (isReading())
	{
		_classDesc = getClassDesc(className.c_str());

		if (!_classDesc)
			return false;

		*_pointer = static_cast<void*>(Factory::create(className.c_str()));
	}

	for (const auto& member : _classDesc->getMembers())
	{
		switch (member.type)
		{
		case ClassDesc::TYPE_INT:
			{
				result = result && serialize(nullptr, *(*(reinterpret_cast<int**>(_pointer) + member.address)));
			}
			break;

		case ClassDesc::TYPE_REFLECTIVE:
			{

			}
			break;

		default: break;
		}
	};

	return result;
}

bool BinarySerializer::serialize(const char*, void* _pointer, const ClassDesc* _classDesc)
{
	std::string	className;

	if (!isReading())
	{
		className = _classDesc->getName();
	}

	bool result = serialize("className", className);

	if (isReading())
	{
		_classDesc = getClassDesc(className.c_str());

		if (!_classDesc)
			return false;
	}

	for (const auto& member : _classDesc->getMembers())
	{
		switch (member.type)
		{
		case ClassDesc::TYPE_INT:
			{
				result = result && serialize(nullptr, *(reinterpret_cast<int*>(_pointer) + member.address));
			}
			break;

		case ClassDesc::TYPE_REFLECTIVE:
			{

			}
			break;

		default: break;
		}
	};

	return result;
}

bool BinarySerializer::_rawSerialize(void* data, int size)
{
	if (isReading())
	{
		return _getReadFile()->read(data, size) == size;
	}
	else
	{
		return _getWriteFile()->write(data, size);
	}
}
