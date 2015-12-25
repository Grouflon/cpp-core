#include "core/JsonSerializer.h"

#include "core/Assert.h"
#include "core/FileHandle.h"
#include "core/ClassDesc.h"
#include "core/Factory.h"

JsonSerializer::JsonSerializer()
	: m_root(nullptr)
	, m_currentValue(nullptr)
{
}

JsonSerializer::~JsonSerializer()
{
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
		// json value built by json.h
		free(m_root);
	}
	else
	{
		size_t outSize;
		void* out = json_write_pretty(m_root, "\t", "\n", &outSize);
		FileHandle* file = getWriteFile();
		file->write(out, outSize - 1); // size counts \0
		free(out);

		// json value hand built
		deleteJsonValue(m_root);
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
		json_value_s* match = findObjectValue(currentObject, _name);
		if (!match || (match->type != json_type_true && match->type != json_type_false))
			return false;

		_value = match->type == json_type_true ? true : false;
	}
	else
	{
		addValueToObject(currentObject, _name, createBoolValue(_value));
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
		json_value_s* match = findObjectValue(currentObject, _name, json_type_number);
		if (!match)
			return false;

		_value = atoi(static_cast<json_number_s*>(match->payload)->number);
	}
	else
	{
		addValueToObject(currentObject, _name, createNumberValue(_value));
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
		json_value_s* match = findObjectValue(currentObject, _name, json_type_number);
		if (!match)
			return false;

		_value = atoi(static_cast<json_number_s*>(match->payload)->number);
	}
	else
	{
		addValueToObject(currentObject, _name, createNumberValue(_value));
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
		json_value_s* match = findObjectValue(currentObject, _name, json_type_number);
		if (!match)
			return false;

		_value = atoi(static_cast<json_number_s*>(match->payload)->number);
	}
	else
	{
		addValueToObject(currentObject, _name, createNumberValue(_value));
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
		json_value_s* match = findObjectValue(currentObject, _name, json_type_number);
		if (!match)
			return false;

		_value = atol(static_cast<json_number_s*>(match->payload)->number);
	}
	else
	{
		addValueToObject(currentObject, _name, createNumberValue(_value));
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
		json_value_s* match = findObjectValue(currentObject, _name, json_type_number);
		if (!match)
			return false;

		_value = atoi(static_cast<json_number_s*>(match->payload)->number);
	}
	else
	{
		addValueToObject(currentObject, _name, createNumberValue(_value));
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
		json_value_s* match = findObjectValue(currentObject, _name, json_type_number);
		if (!match)
			return false;

		_value = atoi(static_cast<json_number_s*>(match->payload)->number);
	}
	else
	{
		addValueToObject(currentObject, _name, createNumberValue(_value));
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
		json_value_s* match = findObjectValue(currentObject, _name, json_type_number);
		if (!match)
			return false;

		_value = atoi(static_cast<json_number_s*>(match->payload)->number);
	}
	else
	{
		addValueToObject(currentObject, _name, createNumberValue(_value));
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
		json_value_s* match = findObjectValue(currentObject, _name, json_type_number);
		if (!match)
			return false;

		_value = atoi(static_cast<json_number_s*>(match->payload)->number);
	}
	else
	{
		addValueToObject(currentObject, _name, createNumberValue(_value));
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
		json_value_s* match = findObjectValue(currentObject, _name, json_type_number);
		if (!match)
			return false;

		_value = static_cast<float>(atof(static_cast<json_number_s*>(match->payload)->number));
	}
	else
	{
		addValueToObject(currentObject, _name, createNumberValue(_value));
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
		json_value_s* match = findObjectValue(currentObject, _name, json_type_number);
		if (!match)
			return false;

		_value = atof(static_cast<json_number_s*>(match->payload)->number);
	}
	else
	{
		addValueToObject(currentObject, _name, createNumberValue(_value));
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
		json_value_s* match = findObjectValue(currentObject, _name, json_type_number);
		if (!match)
			return false;

		_value = *static_cast<char*>((static_cast<json_string_s*>(match->payload)->string));
	}
	else
	{
		addValueToObject(currentObject, _name, createStringValue(&_value, 1));
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
		_element->value = createBoolValue(_value[_index]);
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
			_element->value = createNumberValue(_value[_index]);
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
		_element->value = createNumberValue(_value[_index]);
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
		_element->value = createNumberValue(_value[_index]);
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
		_element->value = createNumberValue(_value[_index]);
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
		_element->value = createNumberValue(_value[_index]);
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
		_element->value = createNumberValue(_value[_index]);
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
		_element->value = createNumberValue(_value[_index]);
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
		_element->value = createNumberValue(_value[_index]);
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
		_element->value = createNumberValue(_value[_index]);
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
		_element->value = createNumberValue(_value[_index]);
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
		json_value_s* match = findObjectValue(currentObject, _name);
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
		jsonValue->payload = createString(_value, _size);
		addValueToObject(currentObject, _name, jsonValue);
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
			json_value_s* match = findObjectValue(currentObject, _name);
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
			jsonValue->payload = createString(_value.c_str());
			addValueToObject(currentObject, _name, jsonValue);
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
		_element->value = createStringValue(_value[_index].c_str());
		return true;
	}
	);
}

bool JsonSerializer::beginVectorSerialization(const char* _name, size_t& size)
{
	// TODO
	return true;
}

bool JsonSerializer::endVectorSerialization()
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
		json_value_s* match = findObjectValue(currentObject, _name, json_type_object);
		if (!match)
			return false;

		m_currentValue = match;
	}
	else
	{
		m_currentValue = createObjectValue();
		addValueToObject(static_cast<json_object_s*>(prevValue->payload), _name, m_currentValue);
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
		json_value_s* match = findObjectValue(currentObject, _name, json_type_object);
		if (!match)
			return false;

		m_currentValue = match;
	}
	else
	{
		m_currentValue = createObjectValue();
		addValueToObject(static_cast<json_object_s*>(prevValue->payload), _name, m_currentValue);
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
		json_value_s* match = findObjectValue(currentObject, _name, json_type_array);
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

		addValueToObject(currentObject, _name, jsonValue);
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
		*_classDesc = getClassDesc(className.c_str());

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
		case ClassDesc::TYPE_BOOL: { result = result && serialize(member.name, *reinterpret_cast<bool*>(static_cast<uint8*>(_pointer) + member.address)); } break;
		case ClassDesc::TYPE_CHAR: { result = result && serialize(member.name, *reinterpret_cast<char*>(static_cast<uint8*>(_pointer) + member.address)); } break;
		case ClassDesc::TYPE_INT8: { result = result && serialize(member.name, *reinterpret_cast<int8*>(static_cast<uint8*>(_pointer) + member.address)); } break;
		case ClassDesc::TYPE_INT16: { result = result && serialize(member.name, *reinterpret_cast<int16*>(static_cast<uint8*>(_pointer) + member.address)); } break;
		case ClassDesc::TYPE_INT32: { result = result && serialize(member.name, *reinterpret_cast<int32*>(static_cast<uint8*>(_pointer) + member.address)); } break;
		case ClassDesc::TYPE_INT64: { result = result && serialize(member.name, *reinterpret_cast<int64*>(static_cast<uint8*>(_pointer) + member.address)); } break;
		case ClassDesc::TYPE_UINT8: { result = result && serialize(member.name, *reinterpret_cast<uint8*>(static_cast<uint8*>(_pointer) + member.address)); } break;
		case ClassDesc::TYPE_UINT16: { result = result && serialize(member.name, *reinterpret_cast<uint16*>(static_cast<uint8*>(_pointer) + member.address)); } break;
		case ClassDesc::TYPE_UINT32: { result = result && serialize(member.name, *reinterpret_cast<uint32*>(static_cast<uint8*>(_pointer) + member.address)); } break;
		case ClassDesc::TYPE_UINT64: { result = result && serialize(member.name, *reinterpret_cast<uint64*>(static_cast<uint8*>(_pointer) + member.address)); } break;
		case ClassDesc::TYPE_FLOAT: { result = result && serialize(member.name, *reinterpret_cast<float*>(static_cast<uint8*>(_pointer) + member.address)); } break;
		case ClassDesc::TYPE_DOUBLE: { result = result && serialize(member.name, *reinterpret_cast<double*>(static_cast<uint8*>(_pointer) + member.address)); } break;
		case ClassDesc::TYPE_STRING: { result = result && serialize(member.name, *reinterpret_cast<std::string*>(static_cast<uint8*>(_pointer) + member.address)); } break;

		case ClassDesc::TYPE_ARRAY:
			{
				switch(member.elementType)
				{
				case ClassDesc::TYPE_BOOL: { result = result && serialize(member.name, reinterpret_cast<bool*>(static_cast<uint8*>(_pointer) + member.address), member.elementCount); } break;
				case ClassDesc::TYPE_CHAR: { result = result && serialize(member.name, reinterpret_cast<char*>(static_cast<uint8*>(_pointer) + member.address), member.elementCount); } break;
				case ClassDesc::TYPE_INT8: { result = result && serialize(member.name, reinterpret_cast<int8*>(static_cast<uint8*>(_pointer) + member.address), member.elementCount); } break;
				case ClassDesc::TYPE_INT16: { result = result && serialize(member.name, reinterpret_cast<int16*>(static_cast<uint8*>(_pointer) + member.address), member.elementCount); } break;
				case ClassDesc::TYPE_INT32: { result = result && serialize(member.name, reinterpret_cast<int32*>(static_cast<uint8*>(_pointer) + member.address), member.elementCount); } break;
				case ClassDesc::TYPE_INT64: { result = result && serialize(member.name, reinterpret_cast<int64*>(static_cast<uint8*>(_pointer) + member.address), member.elementCount); } break;
				case ClassDesc::TYPE_UINT8: { result = result && serialize(member.name, reinterpret_cast<uint8*>(static_cast<uint8*>(_pointer) + member.address), member.elementCount); } break;
				case ClassDesc::TYPE_UINT16: { result = result && serialize(member.name, reinterpret_cast<uint16*>(static_cast<uint8*>(_pointer) + member.address), member.elementCount); } break;
				case ClassDesc::TYPE_UINT32: { result = result && serialize(member.name, reinterpret_cast<uint32*>(static_cast<uint8*>(_pointer) + member.address), member.elementCount); } break;
				case ClassDesc::TYPE_UINT64: { result = result && serialize(member.name, reinterpret_cast<uint64*>(static_cast<uint8*>(_pointer) + member.address), member.elementCount); } break;
				case ClassDesc::TYPE_FLOAT: { result = result && serialize(member.name, reinterpret_cast<float*>(static_cast<uint8*>(_pointer) + member.address), member.elementCount); } break;
				case ClassDesc::TYPE_DOUBLE: { result = result && serialize(member.name, reinterpret_cast<double*>(static_cast<uint8*>(_pointer) + member.address), member.elementCount); } break;
				case ClassDesc::TYPE_STRING: { result = result && serialize(member.name, reinterpret_cast<std::string*>(static_cast<uint8*>(_pointer) + member.address), member.elementCount); } break;
				default: break;
				}
			} break;

		default: break;
		}
	};

	return result;
}

void JsonSerializer::addValueToObject(json_object_s* _object, const char* _name, json_value_s* _value)
{
	json_object_element_s* nextElement = new json_object_element_s;
	nextElement->value = _value;
	nextElement->name = createString(_name);
	nextElement->next = nullptr;

	json_object_element_s* currentElement = _object->start;
	if (!currentElement)
	{
		_object->start = nextElement;
	}
	else
	{
		while (currentElement->next)
		{
			currentElement = currentElement->next;
		}
		currentElement->next = nextElement;
	}
	++_object->length;
}

json_value_s* JsonSerializer::findObjectValue(json_object_s* _object, const char* _name)
{
	json_object_element_s* currentElement = _object->start;
	while (currentElement)
	{
		if (strcmp(_name, static_cast<char*>(currentElement->name->string)) == 0)
		{
			return currentElement->value;
		}
		currentElement = currentElement->next;
	}
	return nullptr;
}

json_value_s* JsonSerializer::findObjectValue(json_object_s* _object, const char* _name, json_type_e _type)
{
	json_value_s* ret = findObjectValue(_object, _name);
	if (!ret || ret->type != _type)
	{
		ret = nullptr;
	}
	return ret;
}

json_string_s* JsonSerializer::createString(const char* _str, int _size)
{
	json_string_s* result = new json_string_s;
	result->string_size = _size < 0 ? strlen(_str) : _size;
	char* strBuffer = new char[result->string_size + 1];
	memcpy(strBuffer, _str, result->string_size);
	strBuffer[result->string_size] = '\0';
	result->string = strBuffer;
	return result;
}

json_number_s* JsonSerializer::createNumber(double _number)
{
	json_number_s* result = new json_number_s;
	result->number = new char[32]; 
	sprintf(result->number, "%f\0", _number);
	result->number_size = strlen(result->number);
	return result;
}

json_number_s* JsonSerializer::createNumber(float _number)
{
	json_number_s* result = new json_number_s;
	result->number = new char[32]; 
	sprintf(result->number, "%f\0", _number);
	result->number_size = strlen(result->number);
	return result;
}

json_number_s* JsonSerializer::createNumber(int64 _number)
{
	json_number_s* result = new json_number_s;
	result->number = new char[32]; 
	sprintf(result->number, "%lld\0", _number);
	result->number_size = strlen(result->number);
	return result;
}

json_number_s* JsonSerializer::createNumber(int _number)
{
	json_number_s* result = new json_number_s;
	result->number = new char[32]; 
	sprintf(result->number, "%d\0", _number);
	result->number_size = strlen(result->number);
	return result;
}

json_number_s* JsonSerializer::createNumber(uint64 _number)
{
	json_number_s* result = new json_number_s;
	result->number = new char[32]; 
	sprintf(result->number, "%lld\0", _number);
	result->number_size = strlen(result->number);
	return result;
}

json_number_s* JsonSerializer::createNumber(unsigned int _number)
{
	json_number_s* result = new json_number_s;
	result->number = new char[32]; 
	sprintf(result->number, "%d\0", _number);
	result->number_size = strlen(result->number);
	return result;
}

json_value_s* JsonSerializer::createStringValue(const char* _str, int _size)
{
	json_value_s* ret = new json_value_s;
	ret->type = json_type_string;
	ret->payload = createString(_str, _size);
	return ret;
}

json_value_s* JsonSerializer::createNumberValue(double _number)
{
	json_value_s* ret = new json_value_s;
	ret->type = json_type_number;
	ret->payload = createNumber(_number);
	return ret;
}

json_value_s* JsonSerializer::createNumberValue(float _number)
{
	json_value_s* ret = new json_value_s;
	ret->type = json_type_number;
	ret->payload = createNumber(_number);
	return ret;
}

json_value_s* JsonSerializer::createNumberValue(int64 _number)
{
	json_value_s* ret = new json_value_s;
	ret->type = json_type_number;
	ret->payload = createNumber(_number);
	return ret;
}

json_value_s* JsonSerializer::createNumberValue(int _number)
{
	json_value_s* ret = new json_value_s;
	ret->type = json_type_number;
	ret->payload = createNumber(_number);
	return ret;
}

json_value_s* JsonSerializer::createNumberValue(uint64 _number)
{
	json_value_s* ret = new json_value_s;
	ret->type = json_type_number;
	ret->payload = createNumber(_number);
	return ret;
}

json_value_s* JsonSerializer::createNumberValue(unsigned _number)
{
	json_value_s* ret = new json_value_s;
	ret->type = json_type_number;
	ret->payload = createNumber(_number);
	return ret;
}

json_value_s* JsonSerializer::createBoolValue(bool _value)
{
	json_value_s* ret = new json_value_s;
	ret->type = _value ? json_type_true : json_type_false;
	ret->payload = nullptr;
	return ret;
}

json_value_s* JsonSerializer::createObjectValue()
{
	json_value_s* ret = new json_value_s;
	ret->type = json_type_object;
	json_object_s* object = new json_object_s;
	ret->payload = object;
	object->length = 0;
	object->start = nullptr;
	return ret;
}

void JsonSerializer::deleteJsonValue(json_value_s* _jsonValue)
{
	switch (_jsonValue->type)
	{
	case json_type_number:
		{
			json_number_s* payload = static_cast<json_number_s*>(_jsonValue->payload);
			delete payload->number;
		}
		break;

	case json_type_string:
		{
			json_string_s* payload = static_cast<json_string_s*>(_jsonValue->payload);
			delete payload->string;
		}
		break;

	case json_type_array:
		{
			json_array_s* payload = static_cast<json_array_s*>(_jsonValue->payload);
			json_array_element_s* nextElement = payload->start;
			while (nextElement)
			{
				json_array_element_s* element = nextElement;
				nextElement = element->next;

				deleteJsonValue(element->value);
				delete element;
			}
		}
		break;

	case json_type_object:
		{
			json_object_s* payload = static_cast<json_object_s*>(_jsonValue->payload);
			json_object_element_s* nextElement = payload->start;
			while (nextElement)
			{
				json_object_element_s* element = nextElement;
				nextElement = element->next;

				delete element->name->string;
				delete element->name;
				deleteJsonValue(element->value);
				delete element;
			}
		}
		break;

	default:
		break;
	}

	delete _jsonValue->payload;
	delete _jsonValue;
}