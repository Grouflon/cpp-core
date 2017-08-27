#include "core/JsonSerializer.h"

#include <cstring>
#include "core/Assert.h"
#include "core/FileHandle.h"
#include "core/ClassDesc.h"
#include "core/Factory.h"
#include "core/JsonTools.h"

JsonSerializer::JsonSerializer()
	: m_root(nullptr)
	, m_currentValue(nullptr)
{
}

JsonSerializer::~JsonSerializer()
{
}

void JsonSerializer::beginRead(const json_value_s* _root)
{
	ASSERT(!m_reading && !m_writing); // end() must be called before calling begin() again.

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
	return serializeValue(_name, json_type_true, &_value,

		// READ
		[](json_value_s* _jsonValue, void* _readValue) -> void
		{
			*static_cast<bool*>(_readValue) = _jsonValue->type == json_type_true ? true : false;
		},
		
		// WRITE
		[](void* _writeValue) -> json_value_s*
		{
			return JsonTools::CreateBoolValue(*static_cast<bool*>(_writeValue));
		}
	);
}

bool JsonSerializer::serialize(const char* _name, uint8& _value)
{
	return serializeValue(_name, json_type_number, &_value,

		// READ
		[](json_value_s* _jsonValue, void* _readValue) -> void
		{
			*static_cast<uint8*>(_readValue) = atoi(static_cast<json_number_s*>(_jsonValue->payload)->number);
		},

		// WRITE
		[](void* _writeValue) -> json_value_s*
		{
			return JsonTools::CreateNumberValue(*static_cast<uint8*>(_writeValue));
		}
	);
}

bool JsonSerializer::serialize(const char* _name, uint16& _value)
{
	return serializeValue(_name, json_type_number, &_value,

		// READ
		[](json_value_s* _jsonValue, void* _readValue) -> void
		{
			*static_cast<uint16*>(_readValue) = atoi(static_cast<json_number_s*>(_jsonValue->payload)->number);
		},

		// WRITE
		[](void* _writeValue) -> json_value_s*
		{
			return JsonTools::CreateNumberValue(*static_cast<uint16*>(_writeValue));
		}
	);
}

bool JsonSerializer::serialize(const char* _name, uint32& _value)
{
	return serializeValue(_name, json_type_number, &_value,

		// READ
		[](json_value_s* _jsonValue, void* _readValue) -> void
		{
			*static_cast<uint32*>(_readValue) = atoi(static_cast<json_number_s*>(_jsonValue->payload)->number);
		},

		// WRITE
		[](void* _writeValue) -> json_value_s*
		{
			return JsonTools::CreateNumberValue(*static_cast<uint32*>(_writeValue));
		}
	);
}

bool JsonSerializer::serialize(const char* _name, uint64& _value)
{
	return serializeValue(_name, json_type_number, &_value,

		// READ
		[](json_value_s* _jsonValue, void* _readValue) -> void
		{
			*static_cast<uint64*>(_readValue) = atol(static_cast<json_number_s*>(_jsonValue->payload)->number);
		},

		// WRITE
		[](void* _writeValue) -> json_value_s*
		{
			return JsonTools::CreateNumberValue(*static_cast<uint64*>(_writeValue));
		}
	);
}

bool JsonSerializer::serialize(const char* _name, int8& _value)
{
	return serializeValue(_name, json_type_number, &_value,

		// READ
		[](json_value_s* _jsonValue, void* _readValue) -> void
		{
			*static_cast<int8*>(_readValue) = atoi(static_cast<json_number_s*>(_jsonValue->payload)->number);
		},

		// WRITE
		[](void* _writeValue) -> json_value_s*
		{
			return JsonTools::CreateNumberValue(*static_cast<int8*>(_writeValue));
		}
	);
}

bool JsonSerializer::serialize(const char* _name, int16& _value)
{
	return serializeValue(_name, json_type_number, &_value,

		// READ
		[](json_value_s* _jsonValue, void* _readValue) -> void
		{
			*static_cast<int16*>(_readValue) = atoi(static_cast<json_number_s*>(_jsonValue->payload)->number);
		},

		// WRITE
		[](void* _writeValue) -> json_value_s*
		{
			return JsonTools::CreateNumberValue(*static_cast<int16*>(_writeValue));
		}
	);
}

bool JsonSerializer::serialize(const char* _name, int32& _value)
{
	return serializeValue(_name, json_type_number, &_value,

		// READ
		[](json_value_s* _jsonValue, void* _readValue) -> void
		{
			*static_cast<int32*>(_readValue) = atoi(static_cast<json_number_s*>(_jsonValue->payload)->number);
		},

		// WRITE
		[](void* _writeValue) -> json_value_s*
		{
			return JsonTools::CreateNumberValue(*static_cast<int32*>(_writeValue));
		}
	);
}

bool JsonSerializer::serialize(const char* _name, int64& _value)
{
	return serializeValue(_name, json_type_number, &_value,

		// READ
		[](json_value_s* _jsonValue, void* _readValue) -> void
		{
			*static_cast<int64*>(_readValue) = atol(static_cast<json_number_s*>(_jsonValue->payload)->number);
		},

		// WRITE
		[](void* _writeValue) -> json_value_s*
		{
			return JsonTools::CreateNumberValue(*static_cast<int64*>(_writeValue));
		}
	);
}

bool JsonSerializer::serialize(const char* _name, float& _value)
{
	return serializeValue(_name, json_type_number, &_value,

		// READ
		[](json_value_s* _jsonValue, void* _readValue) -> void
		{
			*static_cast<float*>(_readValue) = static_cast<float>(atof(static_cast<json_number_s*>(_jsonValue->payload)->number));
		},

		// WRITE
		[](void* _writeValue) -> json_value_s*
		{
			return JsonTools::CreateNumberValue(*static_cast<float*>(_writeValue));
		}
	);
}

bool JsonSerializer::serialize(const char* _name, double& _value)
{
	return serializeValue(_name, json_type_number, &_value,

		// READ
		[](json_value_s* _jsonValue, void* _readValue) -> void
		{
			*static_cast<double*>(_readValue) = atof(static_cast<json_number_s*>(_jsonValue->payload)->number);
		},

		// WRITE
		[](void* _writeValue) -> json_value_s*
		{
			return JsonTools::CreateNumberValue(*static_cast<double*>(_writeValue));
		}
	);
}

bool JsonSerializer::serialize(const char* _name, char& _value)
{
	return serializeValue(_name, json_type_string, &_value,

		// READ
		[](json_value_s* _jsonValue, void* _readValue) -> void
		{
			*static_cast<char*>(_readValue) = *static_cast<char*>((static_cast<json_string_s*>(_jsonValue->payload)->string));
		},

		// WRITE
		[](void* _writeValue) -> json_value_s*
		{
			return JsonTools::CreateStringValue(static_cast<char*>(_writeValue), 1);
		}
	);
}

bool JsonSerializer::serialize(const char* _name, std::string& _value)
{
	return serializeValue(_name, json_type_string, &_value,

		// READ
		[](json_value_s* _jsonValue, void* _readValue) -> void
		{
			*static_cast<std::string*>(_readValue) = static_cast<char*>((static_cast<json_string_s*>(_jsonValue->payload)->string));
		},

		// WRITE
		[](void* _writeValue) -> json_value_s*
		{
			std::string* _str = static_cast<std::string*>(_writeValue);
			return JsonTools::CreateStringValue(_str->c_str(), _str->size());
		}
	);
}

bool JsonSerializer::serialize(const char* _name, void** _pointer, const ClassDesc* _classDesc)
{
	if (m_currentValue->type != json_type_object && m_currentValue->type != json_type_array)
		return false;

	json_value_s* prevValue = m_currentValue;

	if (m_currentValue->type == json_type_object)
	{
		json_object_s* currentObject = static_cast<json_object_s*>(m_currentValue->payload);

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
			JsonTools::AddValueToObject(currentObject, _name, m_currentValue);
		}
	}
	else if (m_currentValue->type == json_type_array)
	{
		json_array_s* currentArray = static_cast<json_array_s*>(m_currentValue->payload);

		if (isReading())
		{
			json_array_element_s* currentElement = m_currentArrayElement.top();
			if (!currentElement || currentElement->value->type != json_type_object)
				return false;

			m_currentValue = currentElement->value;
			m_currentArrayElement.top() = currentElement->next;
		}
		else
		{
			m_currentValue = JsonTools::CreateObjectValue();
			JsonTools::PushBackValueToArray(currentArray, m_currentValue);
		}
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
	if (m_currentValue->type != json_type_object && m_currentValue->type != json_type_array)
		return false;

	json_value_s* prevValue = m_currentValue;

	if (m_currentValue->type == json_type_object)
	{
		json_object_s* currentObject = static_cast<json_object_s*>(m_currentValue->payload);

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
			JsonTools::AddValueToObject(currentObject, _name, m_currentValue);
		}
	}
	else if (m_currentValue->type == json_type_array)
	{
		json_array_s* currentArray = static_cast<json_array_s*>(m_currentValue->payload);

		if (isReading())
		{
			json_array_element_s* currentElement = m_currentArrayElement.top();
			if (!currentElement || currentElement->value->type != json_type_object)
				return false;

			m_currentValue = currentElement->value;
			m_currentArrayElement.top() = currentElement->next;
		}
		else
		{
			m_currentValue = JsonTools::CreateObjectValue();
			JsonTools::PushBackValueToArray(currentArray, m_currentValue);
		}
	}

	bool result = serializeClassDesc(&_classDesc);
	result = result && serializeMembers(_pointer, _classDesc);

	m_currentValue = prevValue;
	return result;
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

bool JsonSerializer::serializeVectorStart(const char* _name, size_t& _size)
{
	if (m_currentValue->type != json_type_object && m_currentValue->type != json_type_array)
		return false;

	m_currentArrayParent.push(m_currentValue);

	if (m_currentValue->type == json_type_object)
	{
		json_object_s* currentObject = static_cast<json_object_s*>(m_currentValue->payload);

		if (isReading())
		{
			json_value_s* match = JsonTools::FindObjectValue(currentObject, _name, json_type_array);
			if (!match)
			{
				m_currentArrayParent.pop();
				return false;
			}
			m_currentValue = match;
		}
		else
		{
			m_currentValue = JsonTools::CreateArrayValue();
			JsonTools::AddValueToObject(currentObject, _name, m_currentValue);
		}
	}
	else if (m_currentValue->type == json_type_array)
	{
		json_array_s* currentArray = static_cast<json_array_s*>(m_currentValue->payload);

		if (isReading())
		{
			json_array_element_s* currentElement = m_currentArrayElement.top();
			if (!currentElement || (currentElement->value->type != json_type_array))
			{
				m_currentArrayParent.pop();
				return false;
			}

			m_currentValue = currentElement->value;
		}
		else
		{
			m_currentValue = JsonTools::CreateArrayValue();
			JsonTools::PushBackValueToArray(currentArray, m_currentValue);
		}
	}

	json_array_s* array = static_cast<json_array_s*>(m_currentValue->payload);
	_size = array->length;
	m_currentArrayElement.push(array->start);
	return true;
}

bool JsonSerializer::serializeVectorStop()
{
	m_currentValue = m_currentArrayParent.top();
	m_currentArrayElement.pop();
	m_currentArrayParent.pop();
	return true;
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

		case ClassDesc::TYPE_VECTOR:
			{
				switch (member.elementType)
				{
				case ClassDesc::TYPE_BOOL: { result = serialize(member.name, *reinterpret_cast<std::vector<bool>*>(static_cast<uint8*>(_pointer) + member.address)) && result; } break;
				case ClassDesc::TYPE_CHAR: { result = serialize(member.name, *reinterpret_cast<std::vector<char>*>(static_cast<uint8*>(_pointer) + member.address)) && result; } break;
				case ClassDesc::TYPE_INT8: { result = serialize(member.name, *reinterpret_cast<std::vector<int8>*>(static_cast<uint8*>(_pointer) + member.address)) && result; } break;
				case ClassDesc::TYPE_INT16: { result = serialize(member.name, *reinterpret_cast<std::vector<int16>*>(static_cast<uint8*>(_pointer) + member.address)) && result; } break;
				case ClassDesc::TYPE_INT32: { result = serialize(member.name, *reinterpret_cast<std::vector<int32>*>(static_cast<uint8*>(_pointer) + member.address)) && result; } break;
				case ClassDesc::TYPE_INT64: { result = serialize(member.name, *reinterpret_cast<std::vector<int64>*>(static_cast<uint8*>(_pointer) + member.address)) && result; } break;
				case ClassDesc::TYPE_UINT8: { result = serialize(member.name, *reinterpret_cast<std::vector<uint8>*>(static_cast<uint8*>(_pointer) + member.address)) && result; } break;
				case ClassDesc::TYPE_UINT16: { result = serialize(member.name, *reinterpret_cast<std::vector<uint16>*>(static_cast<uint8*>(_pointer) + member.address)) && result; } break;
				case ClassDesc::TYPE_UINT32: { result = serialize(member.name, *reinterpret_cast<std::vector<uint32>*>(static_cast<uint8*>(_pointer) + member.address)) && result; } break;
				case ClassDesc::TYPE_UINT64: { result = serialize(member.name, *reinterpret_cast<std::vector<uint64>*>(static_cast<uint8*>(_pointer) + member.address)) && result; } break;
				case ClassDesc::TYPE_FLOAT: { result = serialize(member.name, *reinterpret_cast<std::vector<float>*>(static_cast<uint8*>(_pointer) + member.address)) && result; } break;
				case ClassDesc::TYPE_DOUBLE: { result = serialize(member.name, *reinterpret_cast<std::vector<double>*>(static_cast<uint8*>(_pointer) + member.address)) && result; } break;
				case ClassDesc::TYPE_STRING: { result = serialize(member.name, *reinterpret_cast<std::vector<std::string>*>(static_cast<uint8*>(_pointer) + member.address)) && result; } break;
				default: break;
				}
			} break;

		default: break;
		}
	};

	return result;
}

bool JsonSerializer::serializeValue(const char* _name, json_type_e _type, void* _value, void(*_readFunc)(json_value_s*, void*), json_value_s*(*_writeFunc)(void*))
{
	if (m_currentValue->type == json_type_object)
	{
		json_object_s* currentObject = static_cast<json_object_s*>(m_currentValue->payload);

		if (isReading())
		{
			json_value_s* match = JsonTools::FindObjectValue(currentObject, _name);
			if (!match || (match->type != _type))
			{
				if (_type != json_type_true || (_type == json_type_true && match->type != json_type_false)) // special case for bool
					return false;
			}

			_readFunc(match, _value);
		}
		else
		{
			JsonTools::AddValueToObject(currentObject, _name, _writeFunc(_value));
		}
		return true;
	}
	else if (m_currentValue->type == json_type_array)
	{
		json_array_s* currentArray = static_cast<json_array_s*>(m_currentValue->payload);

		if (isReading())
		{
			json_array_element_s* currentElement = m_currentArrayElement.top();
			if (!currentElement || (currentElement->value->type != _type))
			{
				if (_type != json_type_true || (_type == json_type_true && currentElement->value->type != json_type_false)) // special case for bool
					return false;
			}

			_readFunc(currentElement->value, _value);
			m_currentArrayElement.top() = currentElement->next;
		}
		else
		{
			JsonTools::PushBackValueToArray(currentArray, _writeFunc(_value));
		}
		return true;
	}
	return false;
}
