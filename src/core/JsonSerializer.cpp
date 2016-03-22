#include "stdafx.h"
#include "core/JsonSerializer.h"

#include <json.h>

#include "core/Assert.h"
#include "core/FileHandle.h"
#include "core/ClassDesc.h"
#include "core/Factory.h"
#include "core/JsonTools.h"

JsonSerializer::JsonSerializer()
	: m_root(nullptr)
	, m_currentValue(nullptr)
	, m_currentArrayElement(nullptr)
{
}

JsonSerializer::~JsonSerializer()
{
}

void JsonSerializer::beginRead(const json_value_s* _root)
{
	assert(!m_reading && !m_writing); // end() must be called before calling begin() again.

	m_root = const_cast<json_value_s*>(_root); // Seems ok but not sure
	m_currentValue = m_root;

	m_reading = true;
}

// TODO: refactor duplicated code
bool JsonSerializer::beginRead(const FileHandle* _file)
{
	if (!Serializer::beginRead(_file)) return false;

	size_t bufferSize = _file->getSize() - _file->getOffset();
	char* buffer = new char[bufferSize];
	size_t sizeRead = _file->read(buffer, bufferSize);
	ASSERT(sizeRead == bufferSize);

	m_root = json_parse(buffer, bufferSize);
	m_currentValue = m_root;

	delete buffer;

	return m_root != nullptr;
}

bool JsonSerializer::beginWrite(FileHandle* _file)
{
	Serializer::beginWrite(_file);

	m_root = new json_value_s;
	m_root->type = json_type_object;
	m_currentValue = m_root;

	json_object_s* rootObject = new json_object_s;
	rootObject->length = 0;
	rootObject->start = nullptr;
	m_root->payload = rootObject;
	return true;
}

bool JsonSerializer::end()
{
	if (isReading())
	{
		if (getReadFile()) // if we have a file, that meant we parsed our own json value
		{
			// json value built by json.h
			free(m_root);
		}
	}
	else
	{
		size_t outSize;
		void* out = json_write_pretty(m_root, "\t", "\n", &outSize);
		FileHandle* file = getWriteFile();
		file->write(out, outSize - 1); // size counts \0
		free(out);

		// json value hand built
		JsonTools::DeleteJsonValue(m_root);
	}

	return Serializer::end();
}

bool JsonSerializer::serialize(const char* _name, bool& _value)
{
	if (m_currentValue->type != json_type_object)
		return false;

	json_object_s* currentObject = static_cast<json_object_s*>(m_currentValue->payload);

	if (isReading())
	{
		json_value_s* match = JsonTools::FindObjectValue(currentObject, _name);
		if (!match || (match->type != json_type_true && match->type != json_type_false))
			return false;

		_value = match->type == json_type_true ? true : false;
	}
	else
	{
		JsonTools::AddValueToObject(currentObject, _name, JsonTools::CreateBoolValue(_value));
	}
	return true;
}

bool JsonSerializer::serialize(const char* _name, uint8& _value)
{
	if (m_currentValue->type != json_type_object)
		return false;

	json_object_s* currentObject = static_cast<json_object_s*>(m_currentValue->payload);

	if (isReading())
	{
		json_value_s* match = JsonTools::FindObjectValue(currentObject, _name, json_type_number);
		if (!match)
			return false;

		_value = atoi(static_cast<json_number_s*>(match->payload)->number);
	}
	else
	{
		JsonTools::AddValueToObject(currentObject, _name, JsonTools::CreateNumberValue(_value));
	}
	return true;
}

bool JsonSerializer::serialize(const char* _name, uint16& _value)
{
	if (m_currentValue->type != json_type_object)
		return false;

	json_object_s* currentObject = static_cast<json_object_s*>(m_currentValue->payload);

	if (isReading())
	{
		json_value_s* match = JsonTools::FindObjectValue(currentObject, _name, json_type_number);
		if (!match)
			return false;

		_value = atoi(static_cast<json_number_s*>(match->payload)->number);
	}
	else
	{
		JsonTools::AddValueToObject(currentObject, _name, JsonTools::CreateNumberValue(_value));
	}
	return true;
}

bool JsonSerializer::serialize(const char* _name, uint32& _value)
{
	if (m_currentValue->type != json_type_object)
		return false;

	json_object_s* currentObject = static_cast<json_object_s*>(m_currentValue->payload);

	if (isReading())
	{
		json_value_s* match = JsonTools::FindObjectValue(currentObject, _name, json_type_number);
		if (!match)
			return false;

		_value = atoi(static_cast<json_number_s*>(match->payload)->number);
	}
	else
	{
		JsonTools::AddValueToObject(currentObject, _name, JsonTools::CreateNumberValue(_value));
	}
	return true;
}

bool JsonSerializer::serialize(const char* _name, uint64& _value)
{
	if (m_currentValue->type != json_type_object)
		return false;

	json_object_s* currentObject = static_cast<json_object_s*>(m_currentValue->payload);

	if (isReading())
	{
		json_value_s* match = JsonTools::FindObjectValue(currentObject, _name, json_type_number);
		if (!match)
			return false;

		_value = atol(static_cast<json_number_s*>(match->payload)->number);
	}
	else
	{
		JsonTools::AddValueToObject(currentObject, _name, JsonTools::CreateNumberValue(_value));
	}
	return true;
}

bool JsonSerializer::serialize(const char* _name, int8& _value)
{
	if (m_currentValue->type != json_type_object)
		return false;

	json_object_s* currentObject = static_cast<json_object_s*>(m_currentValue->payload);

	if (isReading())
	{
		json_value_s* match = JsonTools::FindObjectValue(currentObject, _name, json_type_number);
		if (!match)
			return false;

		_value = atoi(static_cast<json_number_s*>(match->payload)->number);
	}
	else
	{
		JsonTools::AddValueToObject(currentObject, _name, JsonTools::CreateNumberValue(_value));
	}
	return true;
}

bool JsonSerializer::serialize(const char* _name, int16& _value)
{
	if (m_currentValue->type != json_type_object)
		return false;

	json_object_s* currentObject = static_cast<json_object_s*>(m_currentValue->payload);

	if (isReading())
	{
		json_value_s* match = JsonTools::FindObjectValue(currentObject, _name, json_type_number);
		if (!match)
			return false;

		_value = atoi(static_cast<json_number_s*>(match->payload)->number);
	}
	else
	{
		JsonTools::AddValueToObject(currentObject, _name, JsonTools::CreateNumberValue(_value));
	}
	return true;
}

bool JsonSerializer::serialize(const char* _name, int32& _value)
{
	if (m_currentValue->type != json_type_object)
		return false;

	json_object_s* currentObject = static_cast<json_object_s*>(m_currentValue->payload);

	if (isReading())
	{
		json_value_s* match = JsonTools::FindObjectValue(currentObject, _name, json_type_number);
		if (!match)
			return false;

		_value = atoi(static_cast<json_number_s*>(match->payload)->number);
	}
	else
	{
		JsonTools::AddValueToObject(currentObject, _name, JsonTools::CreateNumberValue(_value));
	}
	return true;
}

bool JsonSerializer::serialize(const char* _name, int64& _value)
{
	if (m_currentValue->type != json_type_object)
		return false;

	json_object_s* currentObject = static_cast<json_object_s*>(m_currentValue->payload);

	if (isReading())
	{
		json_value_s* match = JsonTools::FindObjectValue(currentObject, _name, json_type_number);
		if (!match)
			return false;

		_value = atoi(static_cast<json_number_s*>(match->payload)->number);
	}
	else
	{
		JsonTools::AddValueToObject(currentObject, _name, JsonTools::CreateNumberValue(_value));
	}
	return true;
}

bool JsonSerializer::serialize(const char* _name, float& _value)
{
	if (m_currentValue->type != json_type_object)
		return false;

	json_object_s* currentObject = static_cast<json_object_s*>(m_currentValue->payload);

	if (isReading())
	{
		json_value_s* match = JsonTools::FindObjectValue(currentObject, _name, json_type_number);
		if (!match)
			return false;

		_value = static_cast<float>(atof(static_cast<json_number_s*>(match->payload)->number));
	}
	else
	{
		JsonTools::AddValueToObject(currentObject, _name, JsonTools::CreateNumberValue(_value));
	}
	return true;
}

bool JsonSerializer::serialize(const char* _name, double& _value)
{
	if (m_currentValue->type != json_type_object)
		return false;

	json_object_s* currentObject = static_cast<json_object_s*>(m_currentValue->payload);

	if (isReading())
	{
		json_value_s* match = JsonTools::FindObjectValue(currentObject, _name, json_type_number);
		if (!match)
			return false;

		_value = atof(static_cast<json_number_s*>(match->payload)->number);
	}
	else
	{
		JsonTools::AddValueToObject(currentObject, _name, JsonTools::CreateNumberValue(_value));
	}
	return true;
}

bool JsonSerializer::serialize(const char* _name, char& _value)
{
	if (m_currentValue->type != json_type_object)
		return false;

	json_object_s* currentObject = static_cast<json_object_s*>(m_currentValue->payload);

	if (isReading())
	{
		json_value_s* match = JsonTools::FindObjectValue(currentObject, _name, json_type_number);
		if (!match)
			return false;

		_value = *static_cast<char*>((static_cast<json_string_s*>(match->payload)->string));
	}
	else
	{
		JsonTools::AddValueToObject(currentObject, _name, JsonTools::CreateStringValue(&_value, 1));
	}
	return true;
}

bool JsonSerializer::serialize(const char* _name, bool* _value, size_t _size)
{
	return serializeArray(
		_name,
		_size,

		// READ
		[_value](const json_array_element_s* _element, int _index) -> bool
	{
		if (_element->value->type != json_type_true && _element->value->type != json_type_false)
			return false;

		_value[_index] = _element->value->type == json_type_true ? true : false;
		return true;
	},

		// WRITE
		[_value](json_array_element_s* _element, int _index) -> bool
	{
		_element->value = JsonTools::CreateBoolValue(_value[_index]);
		return true;
	}
	);
}

bool JsonSerializer::serialize(const char* _name, uint8* _value, size_t _size)
{
	return serializeArray(
		_name,
		_size,

		// READ
		[_value](const json_array_element_s* _element, int _index) -> bool
		{
			if (_element->value->type != json_type_number)
				return false;

			_value[_index] = atoi(static_cast<json_number_s*>(_element->value->payload)->number);
			return true;
		},

		// WRITE
		[_value](json_array_element_s* _element, int _index) -> bool
		{
			_element->value = JsonTools::CreateNumberValue(_value[_index]);
			return true;
		}
	);
}

bool JsonSerializer::serialize(const char* _name, uint16* _value, size_t _size)
{
	return serializeArray(
		_name,
		_size,

		// READ
		[_value](const json_array_element_s* _element, int _index) -> bool
		{
			if (_element->value->type != json_type_number)
				return false;

			_value[_index] = atoi(static_cast<json_number_s*>(_element->value->payload)->number);
			return true;
		},

		// WRITE
		[_value](json_array_element_s* _element, int _index) -> bool
	{
		_element->value = JsonTools::CreateNumberValue(_value[_index]);
		return true;
	}
	);
}

bool JsonSerializer::serialize(const char* _name, uint32* _value, size_t _size)
{
	return serializeArray(
		_name,
		_size,

		// READ
		[_value](const json_array_element_s* _element, int _index) -> bool
		{
			if (_element->value->type != json_type_number)
				return false;

			_value[_index] = atoi(static_cast<json_number_s*>(_element->value->payload)->number);
			return true;
		},

		// WRITE
		[_value](json_array_element_s* _element, int _index) -> bool
	{
		_element->value = JsonTools::CreateNumberValue(_value[_index]);
		return true;
	}
	);
}

bool JsonSerializer::serialize(const char* _name, uint64* _value, size_t _size)
{
	return serializeArray(
		_name,
		_size,

		// READ
		[_value](const json_array_element_s* _element, int _index) -> bool
		{
			if (_element->value->type != json_type_number)
				return false;

			_value[_index] = atol(static_cast<json_number_s*>(_element->value->payload)->number);
			return true;
		},

		// WRITE
		[_value](json_array_element_s* _element, int _index) -> bool
	{
		_element->value = JsonTools::CreateNumberValue(_value[_index]);
		return true;
	}
	);
}

bool JsonSerializer::serialize(const char* _name, int8* _value, size_t _size)
{
	return serializeArray(
		_name,
		_size,

		// READ
		[_value](const json_array_element_s* _element, int _index) -> bool
		{
			if (_element->value->type != json_type_number)
				return false;

			_value[_index] = atoi(static_cast<json_number_s*>(_element->value->payload)->number);
			return true;
		},

		// WRITE
		[_value](json_array_element_s* _element, int _index) -> bool
	{
		_element->value = JsonTools::CreateNumberValue(_value[_index]);
		return true;
	}
	);
}

bool JsonSerializer::serialize(const char* _name, int16* _value, size_t _size)
{
	return serializeArray(
		_name,
		_size,

		// READ
		[_value](const json_array_element_s* _element, int _index) -> bool
		{
			if (_element->value->type != json_type_number)
				return false;

			_value[_index] = atoi(static_cast<json_number_s*>(_element->value->payload)->number);
			return true;
		},

		// WRITE
		[_value](json_array_element_s* _element, int _index) -> bool
	{
		_element->value = JsonTools::CreateNumberValue(_value[_index]);
		return true;
	}
	);
}

bool JsonSerializer::serialize(const char* _name, int32* _value, size_t _size)
{
	return serializeArray(
		_name,
		_size,

		// READ
		[_value](const json_array_element_s* _element, int _index) -> bool
		{
			if (_element->value->type != json_type_number)
				return false;

			_value[_index] = atoi(static_cast<json_number_s*>(_element->value->payload)->number);
			return true;
		},

		// WRITE
		[_value](json_array_element_s* _element, int _index) -> bool
	{
		_element->value = JsonTools::CreateNumberValue(_value[_index]);
		return true;
	}
	);
}

bool JsonSerializer::serialize(const char* _name, int64* _value, size_t _size)
{
	return serializeArray(
		_name,
		_size,

		// READ
		[_value](const json_array_element_s* _element, int _index) -> bool
		{
			if (_element->value->type != json_type_number)
				return false;

			_value[_index] = atol(static_cast<json_number_s*>(_element->value->payload)->number);
			return true;
		},

		// WRITE
		[_value](json_array_element_s* _element, int _index) -> bool
	{
		_element->value = JsonTools::CreateNumberValue(_value[_index]);
		return true;
	}
	);
}

bool JsonSerializer::serialize(const char* _name, float* _value, size_t _size)
{
	return serializeArray(
		_name,
		_size,

		// READ
		[_value](const json_array_element_s* _element, int _index) -> bool
		{
			if (_element->value->type != json_type_number)
				return false;

			_value[_index] = static_cast<float>(atof(static_cast<json_number_s*>(_element->value->payload)->number));
			return true;
		},

		// WRITE
		[_value](json_array_element_s* _element, int _index) -> bool
	{
		_element->value = JsonTools::CreateNumberValue(_value[_index]);
		return true;
	}
	);
}

bool JsonSerializer::serialize(const char* _name, double* _value, size_t _size)
{
	return serializeArray(
		_name,
		_size,

		// READ
		[_value](const json_array_element_s* _element, int _index) -> bool
		{
			if (_element->value->type != json_type_number)
				return false;

			_value[_index] = atof(static_cast<json_number_s*>(_element->value->payload)->number);
			return true;
		},

		// WRITE
		[_value](json_array_element_s* _element, int _index) -> bool
	{
		_element->value = JsonTools::CreateNumberValue(_value[_index]);
		return true;
	}
	);
}

bool JsonSerializer::serialize(const char* _name, char* _value, size_t _size)
{
	if (m_currentValue->type != json_type_object && m_currentValue->type != json_type_array)
		return false;

	json_object_s* currentObject = static_cast<json_object_s*>(m_currentValue->payload);

	if (isReading())
	{
		json_value_s* match = JsonTools::FindObjectValue(currentObject, _name);
		if (!match || match->type != json_type_string)
			return false;

		json_string_s* string = static_cast<json_string_s*>(match->payload);

		if ((_size) != string->string_size)
			return false;

		strncpy(_value, static_cast<char*>(string->string), _size);
	}
	else
	{
		json_value_s* jsonValue = new json_value_s;
		jsonValue->type = json_type_string;
		jsonValue->payload = JsonTools::CreateString(_value, _size);
		JsonTools::AddValueToObject(currentObject, _name, jsonValue);
	}
	return true;
}

bool JsonSerializer::serialize(const char* _name, std::string& _value)
{
	if (m_currentValue->type == json_type_object)
	{
		json_object_s* currentObject = static_cast<json_object_s*>(m_currentValue->payload);

		if (isReading())
		{
			json_value_s* match = JsonTools::FindObjectValue(currentObject, _name);
			if (match && match->type == json_type_string)
			{
				_value = static_cast<char*>(static_cast<json_string_s*>(match->payload)->string);
				return true;
			}
		}
		else
		{
			json_value_s* jsonValue = new json_value_s;
			jsonValue->type = json_type_string;
			jsonValue->payload = JsonTools::CreateString(_value.c_str());
			JsonTools::AddValueToObject(currentObject, _name, jsonValue);
			return true;
		}
	}
	return false;
}

bool JsonSerializer::serialize(const char* _name, std::string* _value, size_t _size)
{
	return serializeArray(
		_name,
		_size,

		// READ
		[_value](const json_array_element_s* _element, int _index) -> bool
		{
			if (_element->value->type != json_type_string)
				return false;

			_value[_index] = static_cast<char*>(static_cast<json_string_s*>(_element->value->payload)->string);
			return true;
		},

		// WRITE
		[_value](json_array_element_s* _element, int _index) -> bool
	{
		_element->value = JsonTools::CreateStringValue(_value[_index].c_str());
		return true;
	}
	);
}

bool JsonSerializer::serializeVectorStart(const char* _name, size_t& size)
{
	// TODO
	return true;
}

bool JsonSerializer::serializeVectorStop()
{
	// TODO
	return true;
}

bool JsonSerializer::serialize(const char* _name, void** _pointer, const ClassDesc* _classDesc)
{
	if (m_currentValue->type != json_type_object)
		return false;

	json_object_s* currentObject = static_cast<json_object_s*>(m_currentValue->payload);

	json_value_s* prevValue = m_currentValue;
	if (isReading())
	{
		json_value_s* match = JsonTools::FindObjectValue(currentObject, _name, json_type_object);
		if (!match)
			return false;

		m_currentValue = match;
	}
	else
	{
		m_currentValue = JsonTools::CreateObjectValue();
		JsonTools::AddValueToObject(static_cast<json_object_s*>(prevValue->payload), _name, m_currentValue);
	}

	bool result = serializeClassDesc(&_classDesc);

	if (result && isReading())
	{
		*_pointer = Factory::create(_classDesc->getName());
	}

	result = result && serializeMembers(*_pointer, _classDesc);

	m_currentValue = prevValue;
	return result;
}

bool JsonSerializer::serialize(const char* _name, void* _pointer, const ClassDesc* _classDesc)
{
	if (m_currentValue->type != json_type_object)
		return false;

	json_object_s* currentObject = static_cast<json_object_s*>(m_currentValue->payload);

	json_value_s* prevValue = m_currentValue;
	if (isReading())
	{
		json_value_s* match = JsonTools::FindObjectValue(currentObject, _name, json_type_object);
		if (!match)
			return false;

		m_currentValue = match;
	}
	else
	{
		m_currentValue = JsonTools::CreateObjectValue();
		JsonTools::AddValueToObject(static_cast<json_object_s*>(prevValue->payload), _name, m_currentValue);
	}

	bool result = serializeClassDesc(&_classDesc);
	result = result && serializeMembers(_pointer, _classDesc);

	m_currentValue = prevValue;
	return result;
}

bool JsonSerializer::serializeArray(const char* _name, size_t _size, std::function<bool(const json_array_element_s*, int)> _readCallback, std::function<bool(json_array_element_s*, int)> _writeCallback)
{
	if (m_currentValue->type != json_type_object)
		return false;

	json_object_s* currentObject = static_cast<json_object_s*>(m_currentValue->payload);

	if (isReading())
	{
		json_value_s* match = JsonTools::FindObjectValue(currentObject, _name, json_type_array);
		if (!match)
			return false;

		json_array_s* array = static_cast<json_array_s*>(match->payload);
		if (_size > array->length)
			return false;

		json_array_element_s* currentElement = array->start;
		int i = 0;
		while (currentElement)
		{
			if (!_readCallback(currentElement, i))
				return false;

			++i;
			currentElement = currentElement->next;
		}
	}
	else
	{
		json_value_s* jsonValue = new json_value_s;
		jsonValue->type = json_type_array;
		json_array_s* array = new json_array_s;
		jsonValue->payload = array;
		array->length = _size;

		json_array_element_s** elementPtr = &array->start;
		for (size_t i = 0; i < _size; i++)
		{
			json_array_element_s* element = new json_array_element_s;

			if (!_writeCallback(element, i))
				return false;

			*elementPtr = element;
			elementPtr = &element->next;
		}
		*elementPtr = nullptr;

		JsonTools::AddValueToObject(currentObject, _name, jsonValue);
	}
	return true;
}

bool JsonSerializer::serializeClassDesc(const ClassDesc** _classDesc)
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

bool JsonSerializer::serializeMembers(void* _pointer, const ClassDesc* _classDesc)
{
	bool result = true;

	for (const auto& member : _classDesc->getMembers())
	{
		switch (member.type)
		{
		case ClassDesc::TYPE_BOOL: { result = serialize(member.name, *reinterpret_cast<bool*>(static_cast<uint8*>(_pointer) + member.address)) && result; } break;
		case ClassDesc::TYPE_CHAR: { result = serialize(member.name, *reinterpret_cast<char*>(static_cast<uint8*>(_pointer) + member.address)) && result; } break;
		case ClassDesc::TYPE_INT8: { result = serialize(member.name, *reinterpret_cast<int8*>(static_cast<uint8*>(_pointer) + member.address)) && result; } break;
		case ClassDesc::TYPE_INT16: { result = serialize(member.name, *reinterpret_cast<int16*>(static_cast<uint8*>(_pointer) + member.address)) && result; } break;
		case ClassDesc::TYPE_INT32: { result = serialize(member.name, *reinterpret_cast<int32*>(static_cast<uint8*>(_pointer) + member.address)) && result; } break;
		case ClassDesc::TYPE_INT64: { result = serialize(member.name, *reinterpret_cast<int64*>(static_cast<uint8*>(_pointer) + member.address)) && result; } break;
		case ClassDesc::TYPE_UINT8: { result = serialize(member.name, *reinterpret_cast<uint8*>(static_cast<uint8*>(_pointer) + member.address)) && result; } break;
		case ClassDesc::TYPE_UINT16: { result = serialize(member.name, *reinterpret_cast<uint16*>(static_cast<uint8*>(_pointer) + member.address)) && result; } break;
		case ClassDesc::TYPE_UINT32: { result = serialize(member.name, *reinterpret_cast<uint32*>(static_cast<uint8*>(_pointer) + member.address)) && result; } break;
		case ClassDesc::TYPE_UINT64: { result = serialize(member.name, *reinterpret_cast<uint64*>(static_cast<uint8*>(_pointer) + member.address)) && result; } break;
		case ClassDesc::TYPE_FLOAT: { result = serialize(member.name, *reinterpret_cast<float*>(static_cast<uint8*>(_pointer) + member.address)) && result; } break;
		case ClassDesc::TYPE_DOUBLE: { result = serialize(member.name, *reinterpret_cast<double*>(static_cast<uint8*>(_pointer) + member.address)) && result; } break;
		case ClassDesc::TYPE_STRING: { result = serialize(member.name, *reinterpret_cast<std::string*>(static_cast<uint8*>(_pointer) + member.address)) && result; } break;

		case ClassDesc::TYPE_ARRAY:
			{
				switch(member.elementType)
				{
				case ClassDesc::TYPE_BOOL: { result = serialize(member.name, reinterpret_cast<bool*>(static_cast<uint8*>(_pointer) + member.address), member.elementCount) && result; } break;
				case ClassDesc::TYPE_CHAR: { result = serialize(member.name, reinterpret_cast<char*>(static_cast<uint8*>(_pointer) + member.address), member.elementCount) && result; } break;
				case ClassDesc::TYPE_INT8: { result = serialize(member.name, reinterpret_cast<int8*>(static_cast<uint8*>(_pointer) + member.address), member.elementCount) && result; } break;
				case ClassDesc::TYPE_INT16: { result = serialize(member.name, reinterpret_cast<int16*>(static_cast<uint8*>(_pointer) + member.address), member.elementCount) && result; } break;
				case ClassDesc::TYPE_INT32: { result = serialize(member.name, reinterpret_cast<int32*>(static_cast<uint8*>(_pointer) + member.address), member.elementCount) && result; } break;
				case ClassDesc::TYPE_INT64: { result = serialize(member.name, reinterpret_cast<int64*>(static_cast<uint8*>(_pointer) + member.address), member.elementCount) && result; } break;
				case ClassDesc::TYPE_UINT8: { result = serialize(member.name, reinterpret_cast<uint8*>(static_cast<uint8*>(_pointer) + member.address), member.elementCount) && result; } break;
				case ClassDesc::TYPE_UINT16: { result = serialize(member.name, reinterpret_cast<uint16*>(static_cast<uint8*>(_pointer) + member.address), member.elementCount) && result; } break;
				case ClassDesc::TYPE_UINT32: { result = serialize(member.name, reinterpret_cast<uint32*>(static_cast<uint8*>(_pointer) + member.address), member.elementCount) && result; } break;
				case ClassDesc::TYPE_UINT64: { result = serialize(member.name, reinterpret_cast<uint64*>(static_cast<uint8*>(_pointer) + member.address), member.elementCount) && result; } break;
				case ClassDesc::TYPE_FLOAT: { result = serialize(member.name, reinterpret_cast<float*>(static_cast<uint8*>(_pointer) + member.address), member.elementCount) && result; } break;
				case ClassDesc::TYPE_DOUBLE: { result = serialize(member.name, reinterpret_cast<double*>(static_cast<uint8*>(_pointer) + member.address), member.elementCount) && result; } break;
				case ClassDesc::TYPE_STRING: { result = serialize(member.name, reinterpret_cast<std::string*>(static_cast<uint8*>(_pointer) + member.address), member.elementCount) && result; } break;
				default: break;
				}
			} break;

		default: break;
		}
	};

	return result;
}
