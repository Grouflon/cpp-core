#include "stdafx.h"
#include "core/BinarySerializer.h"

#include "core/FileHandle.h"
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
	return rawSerialize(&_value, sizeof(_value));
}

bool BinarySerializer::serialize(const char*, uint8& _value)
{
	return rawSerialize(&_value, sizeof(_value));
}

bool BinarySerializer::serialize(const char*, uint16& _value)
{
	return rawSerialize(&_value, sizeof(_value));
}

bool BinarySerializer::serialize(const char*, uint32& _value)
{
	return rawSerialize(&_value, sizeof(_value));
}

bool BinarySerializer::serialize(const char*, uint64& _value)
{
	return rawSerialize(&_value, sizeof(_value));
}

bool BinarySerializer::serialize(const char*, int8& _value)
{
	return rawSerialize(&_value, sizeof(_value));
}

bool BinarySerializer::serialize(const char*, int16& _value)
{
	return rawSerialize(&_value, sizeof(_value));
}

bool BinarySerializer::serialize(const char*, int32& _value)
{
	return rawSerialize(&_value, sizeof(_value));
}

bool BinarySerializer::serialize(const char*, int64& _value)
{
	return rawSerialize(&_value, sizeof(_value));
}

bool BinarySerializer::serialize(const char*, float& _value)
{
	return rawSerialize(&_value, sizeof(_value));
}

bool BinarySerializer::serialize(const char*, double& _value)
{
	return rawSerialize(&_value, sizeof(_value));
}

bool BinarySerializer::serialize(const char*, char& _value)
{
	return rawSerialize(&_value, sizeof(_value));
}

bool BinarySerializer::serialize(const char*, bool* _value, size_t _size)
{
	return rawSerialize(_value, _size * sizeof(*_value));
}

bool BinarySerializer::serialize(const char*, uint8* _value, size_t _size)
{
	return rawSerialize(_value, _size * sizeof(*_value));
}

bool BinarySerializer::serialize(const char*, uint16* _value, size_t _size)
{
	return rawSerialize(_value, _size * sizeof(*_value));
}

bool BinarySerializer::serialize(const char*, uint32* _value, size_t _size)
{
	return rawSerialize(_value, _size * sizeof(*_value));
}

bool BinarySerializer::serialize(const char*, uint64* _value, size_t _size)
{
	return rawSerialize(_value, _size * sizeof(*_value));
}

bool BinarySerializer::serialize(const char*, int8* _value, size_t _size)
{
	return rawSerialize(_value, _size * sizeof(*_value));
}

bool BinarySerializer::serialize(const char*, int16* _value, size_t _size)
{
	return rawSerialize(_value, _size * sizeof(*_value));
}

bool BinarySerializer::serialize(const char*, int32* _value, size_t _size)
{
	return rawSerialize(_value, _size * sizeof(*_value));
}

bool BinarySerializer::serialize(const char*, int64* _value, size_t _size)
{
	return rawSerialize(_value, _size * sizeof(*_value));
}

bool BinarySerializer::serialize(const char*, float* _value, size_t _size)
{
	return rawSerialize(_value, _size * sizeof(*_value));
}

bool BinarySerializer::serialize(const char*, double* _value, size_t _size)
{
	return rawSerialize(_value, _size * sizeof(*_value));
}

bool BinarySerializer::serialize(const char*, char* _value, size_t _size)
{
	return rawSerialize(_value, (_size) * sizeof(*_value));
}

bool BinarySerializer::serialize(const char*, std::string& _value)
{
	if (isReading())
	{
		_value.clear();
		const FileHandle* file = getReadFile();
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

bool BinarySerializer::serializeVectorStart(const char*, size_t& _size)
{
	return serialize(nullptr, _size);
}

bool BinarySerializer::serializeVectorStop()
{
	return true;
}

bool BinarySerializer::serialize(const char*, void** _pointer, const ClassDesc* _classDesc)
{
	bool result = serializeClassDesc(&_classDesc);

	if (isReading())
	{
		*_pointer = static_cast<void*>(Factory::create(_classDesc->getName()));
	}

	result = result && serializeMembers(*_pointer, _classDesc);
	return result;
}

bool BinarySerializer::serialize(const char*, void* _pointer, const ClassDesc* _classDesc)
{
	bool result = serializeClassDesc(&_classDesc);
	result = result && serializeMembers(_pointer, _classDesc);
	return result;
}

bool BinarySerializer::serializeClassDesc(const ClassDesc** _classDesc)
{
	std::string className;
	if (isWriting())
	{
		className = (*_classDesc)->getName();
	}

	bool result = serialize("className", className);

	if (isReading())
	{
		*_classDesc = GetClassDesc(className.c_str());

		if (!*_classDesc)
			result = false;
	}
	return result;
}

bool BinarySerializer::serializeMembers(void* _pointer, const ClassDesc* _classDesc)
{
	bool result = true;

	for (const auto& member : _classDesc->getMembers())
	{
		switch (member.type)
		{
		case ClassDesc::TYPE_BOOL: { result = result && serialize(nullptr, *reinterpret_cast<bool*>(static_cast<uint8*>(_pointer) + member.address)); } break;
		case ClassDesc::TYPE_CHAR: { result = result && serialize(nullptr, *reinterpret_cast<char*>(static_cast<uint8*>(_pointer) + member.address)); } break;
		case ClassDesc::TYPE_INT8: { result = result && serialize(nullptr, *reinterpret_cast<int8*>(static_cast<uint8*>(_pointer) + member.address)); } break;
		case ClassDesc::TYPE_INT16: { result = result && serialize(nullptr, *reinterpret_cast<int16*>(static_cast<uint8*>(_pointer) + member.address)); } break;
		case ClassDesc::TYPE_INT32: { result = result && serialize(nullptr, *reinterpret_cast<int32*>(static_cast<uint8*>(_pointer) + member.address)); } break;
		case ClassDesc::TYPE_INT64: { result = result && serialize(nullptr, *reinterpret_cast<int64*>(static_cast<uint8*>(_pointer) + member.address)); } break;
		case ClassDesc::TYPE_UINT8: { result = result && serialize(nullptr, *reinterpret_cast<uint8*>(static_cast<uint8*>(_pointer) + member.address)); } break;
		case ClassDesc::TYPE_UINT16: { result = result && serialize(nullptr, *reinterpret_cast<uint16*>(static_cast<uint8*>(_pointer) + member.address)); } break;
		case ClassDesc::TYPE_UINT32: { result = result && serialize(nullptr, *reinterpret_cast<uint32*>(static_cast<uint8*>(_pointer) + member.address)); } break;
		case ClassDesc::TYPE_UINT64: { result = result && serialize(nullptr, *reinterpret_cast<uint64*>(static_cast<uint8*>(_pointer) + member.address)); } break;
		case ClassDesc::TYPE_FLOAT: { result = result && serialize(nullptr, *reinterpret_cast<float*>(static_cast<uint8*>(_pointer) + member.address)); } break;
		case ClassDesc::TYPE_DOUBLE: { result = result && serialize(nullptr, *reinterpret_cast<double*>(static_cast<uint8*>(_pointer) + member.address)); } break;
		case ClassDesc::TYPE_STRING: { result = result && serialize(nullptr, *reinterpret_cast<std::string*>(static_cast<uint8*>(_pointer) + member.address)); } break;

		case ClassDesc::TYPE_ARRAY:
			{
				switch(member.elementType)
				{
				case ClassDesc::TYPE_BOOL: { result = result && serialize(nullptr, reinterpret_cast<bool*>(static_cast<uint8*>(_pointer) + member.address), member.elementCount); } break;
				case ClassDesc::TYPE_CHAR: { result = result && serialize(nullptr, reinterpret_cast<char*>(static_cast<uint8*>(_pointer) + member.address), member.elementCount); } break;
				case ClassDesc::TYPE_INT8: { result = result && serialize(nullptr, reinterpret_cast<int8*>(static_cast<uint8*>(_pointer) + member.address), member.elementCount); } break;
				case ClassDesc::TYPE_INT16: { result = result && serialize(nullptr, reinterpret_cast<int16*>(static_cast<uint8*>(_pointer) + member.address), member.elementCount); } break;
				case ClassDesc::TYPE_INT32: { result = result && serialize(nullptr, reinterpret_cast<int32*>(static_cast<uint8*>(_pointer) + member.address), member.elementCount); } break;
				case ClassDesc::TYPE_INT64: { result = result && serialize(nullptr, reinterpret_cast<int64*>(static_cast<uint8*>(_pointer) + member.address), member.elementCount); } break;
				case ClassDesc::TYPE_UINT8: { result = result && serialize(nullptr, reinterpret_cast<uint8*>(static_cast<uint8*>(_pointer) + member.address), member.elementCount); } break;
				case ClassDesc::TYPE_UINT16: { result = result && serialize(nullptr, reinterpret_cast<uint16*>(static_cast<uint8*>(_pointer) + member.address), member.elementCount); } break;
				case ClassDesc::TYPE_UINT32: { result = result && serialize(nullptr, reinterpret_cast<uint32*>(static_cast<uint8*>(_pointer) + member.address), member.elementCount); } break;
				case ClassDesc::TYPE_UINT64: { result = result && serialize(nullptr, reinterpret_cast<uint64*>(static_cast<uint8*>(_pointer) + member.address), member.elementCount); } break;
				case ClassDesc::TYPE_FLOAT: { result = result && serialize(nullptr, reinterpret_cast<float*>(static_cast<uint8*>(_pointer) + member.address), member.elementCount); } break;
				case ClassDesc::TYPE_DOUBLE: { result = result && serialize(nullptr, reinterpret_cast<double*>(static_cast<uint8*>(_pointer) + member.address), member.elementCount); } break;
				case ClassDesc::TYPE_STRING: { result = result && serialize(nullptr, reinterpret_cast<std::string*>(static_cast<uint8*>(_pointer) + member.address), member.elementCount); } break;
				default: break;
				}
			} break;

		default: break;
		}
	};

	return result;
}

bool BinarySerializer::rawSerialize(void* _data, int _size)
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
