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

bool BinarySerializer::serialize(const char*, bool& _value)
{
	return _rawSerialize(&_value, sizeof(_value));
}

bool BinarySerializer::serialize(const char*, uint8& _value)
{
	return _rawSerialize(&_value, sizeof(_value));
}

bool BinarySerializer::serialize(const char*, uint16& _value)
{
	return _rawSerialize(&_value, sizeof(_value));
}

bool BinarySerializer::serialize(const char*, uint32& _value)
{
	return _rawSerialize(&_value, sizeof(_value));
}

bool BinarySerializer::serialize(const char*, uint64& _value)
{
	return _rawSerialize(&_value, sizeof(_value));
}

bool BinarySerializer::serialize(const char*, int8& _value)
{
	return _rawSerialize(&_value, sizeof(_value));
}

bool BinarySerializer::serialize(const char*, int16& _value)
{
	return _rawSerialize(&_value, sizeof(_value));
}

bool BinarySerializer::serialize(const char*, int32& _value)
{
	return _rawSerialize(&_value, sizeof(_value));
}

bool BinarySerializer::serialize(const char*, int64& _value)
{
	return _rawSerialize(&_value, sizeof(_value));
}

bool BinarySerializer::serialize(const char*, float& _value)
{
	return _rawSerialize(&_value, sizeof(_value));
}

bool BinarySerializer::serialize(const char*, double& _value)
{
	return _rawSerialize(&_value, sizeof(_value));
}

bool BinarySerializer::serialize(const char*, uint8* _value, size_t _size)
{
	return _rawSerialize(_value, _size * sizeof(*_value));
}

bool BinarySerializer::serialize(const char*, uint16* _value, size_t _size)
{
	return _rawSerialize(_value, _size * sizeof(*_value));
}

bool BinarySerializer::serialize(const char*, uint32* _value, size_t _size)
{
	return _rawSerialize(_value, _size * sizeof(*_value));
}

bool BinarySerializer::serialize(const char*, uint64* _value, size_t _size)
{
	return _rawSerialize(_value, _size * sizeof(*_value));
}

bool BinarySerializer::serialize(const char*, int8* _value, size_t _size)
{
	return _rawSerialize(_value, _size * sizeof(*_value));
}

bool BinarySerializer::serialize(const char*, int16* _value, size_t _size)
{
	return _rawSerialize(_value, _size * sizeof(*_value));
}

bool BinarySerializer::serialize(const char*, int32* _value, size_t _size)
{
	return _rawSerialize(_value, _size * sizeof(*_value));
}

bool BinarySerializer::serialize(const char*, int64* _value, size_t _size)
{
	return _rawSerialize(_value, _size * sizeof(*_value));
}

bool BinarySerializer::serialize(const char*, float* _value, size_t _size)
{
	return _rawSerialize(_value, _size * sizeof(*_value));
}

bool BinarySerializer::serialize(const char*, double* _value, size_t _size)
{
	return _rawSerialize(_value, _size * sizeof(*_value));
}

bool BinarySerializer::serialize(const char*, char* _value, size_t _size)
{
	return _rawSerialize(_value, (_size + 1) * sizeof(*_value));
}

bool BinarySerializer::serialize(const char*, std::string& _value)
{
	if (isReading())
	{
		_value.clear();
		const File* file = getReadFile();
		char buf;
		while (true)
		{
			if (file->read(&buf, 1) == 0 || buf == '\0')
			{
				break;
			}
			_value += buf;
		}
		return true;
	}
	else
	{
		return getWriteFile()->write(_value.c_str(), _value.size()+1);
	}
}

bool BinarySerializer::serialize(const char* _name, std::string* _value, size_t _size)
{
	for (size_t i = 0; i < _size; ++i)
	{
		if (!serialize(_name, _value[i]))
			return false;
	}
	return true;
}

bool BinarySerializer::beginVectorSerialization(const char*, size_t& _size)
{
	return serialize(nullptr, _size);
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
				result = result && serialize(nullptr, *reinterpret_cast<int*>((*(uint8**)_pointer) + member.address));
			}
			break;

		case ClassDesc::TYPE_FLOAT:
			{
				result = result && serialize(nullptr, *reinterpret_cast<int*>((*(uint8**)_pointer) + member.address));
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
				result = result && serialize(nullptr, *(reinterpret_cast<int*>((uint8*)_pointer + member.address)));
			}
			break;

		case ClassDesc::TYPE_FLOAT:
			{
				result = result && serialize(nullptr, *(reinterpret_cast<float*>((uint8*)_pointer + member.address)));
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

bool BinarySerializer::_rawSerialize(void* _data, int _size)
{
	if (isReading())
	{
		return getReadFile()->read(_data, _size) == _size;
	}
	else
	{
		return getWriteFile()->write(_data, _size);
	}
}
