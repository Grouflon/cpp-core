#include "stdafx.h"
#include "core/JsonSerializer.h"

#include <json.h>

#include "core/File.h"
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
bool JsonSerializer::beginRead(const File* file)
{
	if (!Serializer::beginRead(file)) return false;

	size_t bufferSize = file->getSize() - file->getOffset();
	char* buffer = new char[bufferSize];
	size_t sizeRead = file->read(buffer, bufferSize);
	ASSERT(sizeRead == bufferSize);

	m_root = json_parse(buffer, bufferSize);
	m_currentValue = m_root;

	delete buffer;

	return m_root != nullptr;
}

bool JsonSerializer::beginWrite(File* file)
{
	Serializer::beginWrite(file);

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
		File* file = getWriteFile();
		file->write(out, outSize - 1); // size counts \0
		free(out);

		// json value hand built
		_deleteJsonValue(m_root);
	}

	return Serializer::end();
}

bool JsonSerializer::serialize(const char* name, bool& value)
{
	if (m_currentValue->type == json_type_object)
	{
		json_object_s* currentObject = static_cast<json_object_s*>(m_currentValue->payload);

		if (isReading())
		{
			json_value_s* match = _findObjectValue(currentObject, name);
			if (match && (match->type == json_type_true || match->type == json_type_false))
			{
				value = match->type == json_type_true ? true : false;
				return true;
			}
		}
		else
		{
			json_value_s* jsonValue = new json_value_s;
			jsonValue->payload = nullptr;
			jsonValue->type = value ? json_type_true : json_type_false;

			_addValueToObject(currentObject, name, jsonValue);
			return true;
		}
	}
	return false;
}

bool JsonSerializer::serialize(const char* name, uint8& value)
{
	if (m_currentValue->type == json_type_object)
	{
		json_object_s* currentObject = static_cast<json_object_s*>(m_currentValue->payload);

		if (isReading())
		{
			json_value_s* match = _findObjectValue(currentObject, name);
			if (match && match->type == json_type_number)
			{
				value = atoi(static_cast<json_number_s*>(match->payload)->number);
				return true;
			}
		}
		else
		{
			json_value_s* jsonValue = new json_value_s;
			jsonValue->type = json_type_number;
			jsonValue->payload = _createNumber(value);
			_addValueToObject(currentObject, name, jsonValue);
			return true;
		}
	}
	return false;
}

bool JsonSerializer::serialize(const char* name, uint16& value)
{
	if (m_currentValue->type == json_type_object)
	{
		json_object_s* currentObject = static_cast<json_object_s*>(m_currentValue->payload);

		if (isReading())
		{
			json_value_s* match = _findObjectValue(currentObject, name);
			if (match && match->type == json_type_number)
			{
				value = atoi(static_cast<json_number_s*>(match->payload)->number);
				return true;
			}
		}
		else
		{
			json_value_s* jsonValue = new json_value_s;
			jsonValue->type = json_type_number;
			jsonValue->payload = _createNumber(value);
			_addValueToObject(currentObject, name, jsonValue);
			return true;
		}
	}
	return false;
}

bool JsonSerializer::serialize(const char* name, uint32& value)
{
	if (m_currentValue->type == json_type_object)
	{
		json_object_s* currentObject = static_cast<json_object_s*>(m_currentValue->payload);

		if (isReading())
		{
			json_value_s* match = _findObjectValue(currentObject, name);
			if (match && match->type == json_type_number)
			{
				value = atoi(static_cast<json_number_s*>(match->payload)->number);
				return true;
			}
		}
		else
		{
			json_value_s* jsonValue = new json_value_s;
			jsonValue->type = json_type_number;
			jsonValue->payload = _createNumber(value);
			_addValueToObject(currentObject, name, jsonValue);
			return true;
		}
	}
	return false;
}

bool JsonSerializer::serialize(const char* name, uint64& value)
{
	if (m_currentValue->type == json_type_object)
	{
		json_object_s* currentObject = static_cast<json_object_s*>(m_currentValue->payload);

		if (isReading())
		{
			json_value_s* match = _findObjectValue(currentObject, name);
			if (match && match->type == json_type_number)
			{
				value = atol(static_cast<json_number_s*>(match->payload)->number);
				return true;
			}
		}
		else
		{
			json_value_s* jsonValue = new json_value_s;
			jsonValue->type = json_type_number;
			jsonValue->payload = _createNumber(value);
			_addValueToObject(currentObject, name, jsonValue);
			return true;
		}
	}
	return false;
}

bool JsonSerializer::serialize(const char* name, int8& value)
{
	if (m_currentValue->type == json_type_object)
	{
		json_object_s* currentObject = static_cast<json_object_s*>(m_currentValue->payload);

		if (isReading())
		{
			json_value_s* match = _findObjectValue(currentObject, name);
			if (match && match->type == json_type_number)
			{
				value = atoi(static_cast<json_number_s*>(match->payload)->number);
				return true;
			}
		}
		else
		{
			json_value_s* jsonValue = new json_value_s;
			jsonValue->type = json_type_number;
			jsonValue->payload = _createNumber(value);
			_addValueToObject(currentObject, name, jsonValue);
			return true;
		}
	}
	return false;
}

bool JsonSerializer::serialize(const char* name, int16& value)
{
	if (m_currentValue->type == json_type_object)
	{
		json_object_s* currentObject = static_cast<json_object_s*>(m_currentValue->payload);

		if (isReading())
		{
			json_value_s* match = _findObjectValue(currentObject, name);
			if (match && match->type == json_type_number)
			{
				value = atoi(static_cast<json_number_s*>(match->payload)->number);
				return true;
			}
		}
		else
		{
			json_value_s* jsonValue = new json_value_s;
			jsonValue->type = json_type_number;
			jsonValue->payload = _createNumber(value);
			_addValueToObject(currentObject, name, jsonValue);
			return true;
		}
	}
	return false;
}

bool JsonSerializer::serialize(const char* name, int32& value)
{
	if (m_currentValue->type == json_type_object)
	{
		json_object_s* currentObject = static_cast<json_object_s*>(m_currentValue->payload);

		if (isReading())
		{
			json_value_s* match = _findObjectValue(currentObject, name);
			if (match && match->type == json_type_number)
			{
				value = atoi(static_cast<json_number_s*>(match->payload)->number);
				return true;
			}
		}
		else
		{
			json_value_s* jsonValue = new json_value_s;
			jsonValue->type = json_type_number;
			jsonValue->payload = _createNumber(value);
			_addValueToObject(currentObject, name, jsonValue);
			return true;
		}
	}
	return false;
}

bool JsonSerializer::serialize(const char* name, int64& value)
{
	if (m_currentValue->type == json_type_object)
	{
		json_object_s* currentObject = static_cast<json_object_s*>(m_currentValue->payload);

		if (isReading())
		{
			json_value_s* match = _findObjectValue(currentObject, name);
			if (match && match->type == json_type_number)
			{
				value = atol(static_cast<json_number_s*>(match->payload)->number);
				return true;
			}
		}
		else
		{
			json_value_s* jsonValue = new json_value_s;
			jsonValue->type = json_type_number;
			jsonValue->payload = _createNumber(value);
			_addValueToObject(currentObject, name, jsonValue);
			return true;
		}
	}
	return false;
}

bool JsonSerializer::serialize(const char* name, float& value)
{
	if (m_currentValue->type == json_type_object)
	{
		json_object_s* currentObject = static_cast<json_object_s*>(m_currentValue->payload);

		if (isReading())
		{
			json_value_s* match = _findObjectValue(currentObject, name);
			if (match && match->type == json_type_number)
			{
				value = static_cast<float>(atof(static_cast<json_number_s*>(match->payload)->number));
				return true;
			}
		}
		else
		{
			json_value_s* jsonValue = new json_value_s;
			jsonValue->type = json_type_number;
			jsonValue->payload = _createNumber(value);
			_addValueToObject(currentObject, name, jsonValue);
			return true;
		}
	}
	return false;
}

bool JsonSerializer::serialize(const char* name, double& value)
{
	if (m_currentValue->type == json_type_object)
	{
		json_object_s* currentObject = static_cast<json_object_s*>(m_currentValue->payload);

		if (isReading())
		{
			json_value_s* match = _findObjectValue(currentObject, name);
			if (match && match->type == json_type_number)
			{
				value = atof(static_cast<json_number_s*>(match->payload)->number);
				return true;
			}
		}
		else
		{
			json_value_s* jsonValue = new json_value_s;
			jsonValue->type = json_type_number;
			jsonValue->payload = _createNumber(value);
			_addValueToObject(currentObject, name, jsonValue);
			return true;
		}
	}
	return false;
}

bool JsonSerializer::serialize(const char* name, uint8* value, size_t size)
{
	if (m_currentValue->type == json_type_object)
	{
		json_object_s* currentObject = static_cast<json_object_s*>(m_currentValue->payload);

		if (isReading())
		{
			json_value_s* match = _findObjectValue(currentObject, name);
			if (match && match->type == json_type_array)
			{
				json_array_s* array = static_cast<json_array_s*>(match->payload);
				if (size <= array->length)
				{
					json_array_element_s* currentElement = array->start;
					int i = 0;
					while (currentElement)
					{
						if (currentElement->value->type != json_type_number)
							return false;

						value[i] = atoi(static_cast<json_number_s*>(currentElement->value->payload)->number);
						++i;
						currentElement = currentElement->next;
					}
					return true;
				}
			}
		}
		else
		{
			json_value_s* jsonValue = new json_value_s;
			jsonValue->type = json_type_array;
			json_array_s* array = new json_array_s;
			jsonValue->payload = array;

			array->length = size;

			json_array_element_s** elementPtr = &array->start;
			for (size_t i = 0; i < size; i++)
			{
				json_array_element_s* element = new json_array_element_s;
				element->value = new json_value_s;
				element->value->type = json_type_number;
				element->value->payload = _createNumber(value[i]);
				
				*elementPtr = element;
				elementPtr = &element->next;
			}

			_addValueToObject(currentObject, name, jsonValue);
			return true;
		}
	}
	return false;
}

bool JsonSerializer::serialize(const char* name, uint16* value, size_t size)
{
	if (m_currentValue->type == json_type_object)
	{
		json_object_s* currentObject = static_cast<json_object_s*>(m_currentValue->payload);

		if (isReading())
		{
			json_value_s* match = _findObjectValue(currentObject, name);
			if (match && match->type == json_type_array)
			{
				json_array_s* array = static_cast<json_array_s*>(match->payload);
				if (size <= array->length)
				{
					json_array_element_s* currentElement = array->start;
					int i = 0;
					while (currentElement)
					{
						if (currentElement->value->type != json_type_number)
							return false;

						value[i] = atoi(static_cast<json_number_s*>(currentElement->value->payload)->number);
						++i;
						currentElement = currentElement->next;
					}
					return true;
				}
			}
		}
		else
		{
			json_value_s* jsonValue = new json_value_s;
			jsonValue->type = json_type_array;
			json_array_s* array = new json_array_s;
			jsonValue->payload = array;

			array->length = size;

			json_array_element_s** elementPtr = &array->start;
			for (size_t i = 0; i < size; i++)
			{
				json_array_element_s* element = new json_array_element_s;
				element->value = new json_value_s;
				element->value->type = json_type_number;
				element->value->payload = _createNumber(value[i]);

				*elementPtr = element;
				elementPtr = &element->next;
			}

			_addValueToObject(currentObject, name, jsonValue);
			return true;
		}
	}
	return false;
}

bool JsonSerializer::serialize(const char* name, uint32* value, size_t size)
{
	if (m_currentValue->type == json_type_object)
	{
		json_object_s* currentObject = static_cast<json_object_s*>(m_currentValue->payload);

		if (isReading())
		{
			json_value_s* match = _findObjectValue(currentObject, name);
			if (match && match->type == json_type_array)
			{
				json_array_s* array = static_cast<json_array_s*>(match->payload);
				if (size <= array->length)
				{
					json_array_element_s* currentElement = array->start;
					int i = 0;
					while (currentElement)
					{
						if (currentElement->value->type != json_type_number)
							return false;

						value[i] = atoi(static_cast<json_number_s*>(currentElement->value->payload)->number);
						++i;
						currentElement = currentElement->next;
					}
					return true;
				}
			}
		}
		else
		{
			json_value_s* jsonValue = new json_value_s;
			jsonValue->type = json_type_array;
			json_array_s* array = new json_array_s;
			jsonValue->payload = array;

			array->length = size;

			json_array_element_s** elementPtr = &array->start;
			for (size_t i = 0; i < size; i++)
			{
				json_array_element_s* element = new json_array_element_s;
				element->value = new json_value_s;
				element->value->type = json_type_number;
				element->value->payload = _createNumber(value[i]);

				*elementPtr = element;
				elementPtr = &element->next;
			}

			_addValueToObject(currentObject, name, jsonValue);
			return true;
		}
	}
	return false;
}

bool JsonSerializer::serialize(const char* name, uint64* value, size_t size)
{
	if (m_currentValue->type == json_type_object)
	{
		json_object_s* currentObject = static_cast<json_object_s*>(m_currentValue->payload);

		if (isReading())
		{
			json_value_s* match = _findObjectValue(currentObject, name);
			if (match && match->type == json_type_array)
			{
				json_array_s* array = static_cast<json_array_s*>(match->payload);
				if (size <= array->length)
				{
					json_array_element_s* currentElement = array->start;
					int i = 0;
					while (currentElement)
					{
						if (currentElement->value->type != json_type_number)
							return false;

						value[i] = atol(static_cast<json_number_s*>(currentElement->value->payload)->number);
						++i;
						currentElement = currentElement->next;
					}
					return true;
				}
			}
		}
		else
		{
			json_value_s* jsonValue = new json_value_s;
			jsonValue->type = json_type_array;
			json_array_s* array = new json_array_s;
			jsonValue->payload = array;

			array->length = size;

			json_array_element_s** elementPtr = &array->start;
			for (size_t i = 0; i < size; i++)
			{
				json_array_element_s* element = new json_array_element_s;
				element->value = new json_value_s;
				element->value->type = json_type_number;
				element->value->payload = _createNumber(value[i]);

				*elementPtr = element;
				elementPtr = &element->next;
			}

			_addValueToObject(currentObject, name, jsonValue);
			return true;
		}
	}
	return false;
}

bool JsonSerializer::serialize(const char* name, int8* value, size_t size)
{
	if (m_currentValue->type == json_type_object)
	{
		json_object_s* currentObject = static_cast<json_object_s*>(m_currentValue->payload);

		if (isReading())
		{
			json_value_s* match = _findObjectValue(currentObject, name);
			if (match && match->type == json_type_array)
			{
				json_array_s* array = static_cast<json_array_s*>(match->payload);
				if (size <= array->length)
				{
					json_array_element_s* currentElement = array->start;
					int i = 0;
					while (currentElement)
					{
						if (currentElement->value->type != json_type_number)
							return false;

						value[i] = atoi(static_cast<json_number_s*>(currentElement->value->payload)->number);
						++i;
						currentElement = currentElement->next;
					}
					return true;
				}
			}
		}
		else
		{
			json_value_s* jsonValue = new json_value_s;
			jsonValue->type = json_type_array;
			json_array_s* array = new json_array_s;
			jsonValue->payload = array;

			array->length = size;

			json_array_element_s** elementPtr = &array->start;
			for (size_t i = 0; i < size; i++)
			{
				json_array_element_s* element = new json_array_element_s;
				element->value = new json_value_s;
				element->value->type = json_type_number;
				element->value->payload = _createNumber(value[i]);

				*elementPtr = element;
				elementPtr = &element->next;
			}

			_addValueToObject(currentObject, name, jsonValue);
			return true;
		}
	}
	return false;
}

bool JsonSerializer::serialize(const char* name, int16* value, size_t size)
{
	if (m_currentValue->type == json_type_object)
	{
		json_object_s* currentObject = static_cast<json_object_s*>(m_currentValue->payload);

		if (isReading())
		{
			json_value_s* match = _findObjectValue(currentObject, name);
			if (match && match->type == json_type_array)
			{
				json_array_s* array = static_cast<json_array_s*>(match->payload);
				if (size <= array->length)
				{
					json_array_element_s* currentElement = array->start;
					int i = 0;
					while (currentElement)
					{
						if (currentElement->value->type != json_type_number)
							return false;

						value[i] = atoi(static_cast<json_number_s*>(currentElement->value->payload)->number);
						++i;
						currentElement = currentElement->next;
					}
					return true;
				}
			}
		}
		else
		{
			json_value_s* jsonValue = new json_value_s;
			jsonValue->type = json_type_array;
			json_array_s* array = new json_array_s;
			jsonValue->payload = array;

			array->length = size;

			json_array_element_s** elementPtr = &array->start;
			for (size_t i = 0; i < size; i++)
			{
				json_array_element_s* element = new json_array_element_s;
				element->value = new json_value_s;
				element->value->type = json_type_number;
				element->value->payload = _createNumber(value[i]);

				*elementPtr = element;
				elementPtr = &element->next;
			}

			_addValueToObject(currentObject, name, jsonValue);
			return true;
		}
	}
	return false;
}

bool JsonSerializer::serialize(const char* name, int32* value, size_t size)
{
	if (m_currentValue->type == json_type_object)
	{
		json_object_s* currentObject = static_cast<json_object_s*>(m_currentValue->payload);

		if (isReading())
		{
			json_value_s* match = _findObjectValue(currentObject, name);
			if (match && match->type == json_type_array)
			{
				json_array_s* array = static_cast<json_array_s*>(match->payload);
				if (size <= array->length)
				{
					json_array_element_s* currentElement = array->start;
					int i = 0;
					while (currentElement)
					{
						if (currentElement->value->type != json_type_number)
							return false;

						value[i] = atoi(static_cast<json_number_s*>(currentElement->value->payload)->number);
						++i;
						currentElement = currentElement->next;
					}
					return true;
				}
			}
		}
		else
		{
			json_value_s* jsonValue = new json_value_s;
			jsonValue->type = json_type_array;
			json_array_s* array = new json_array_s;
			jsonValue->payload = array;

			array->length = size;

			json_array_element_s** elementPtr = &array->start;
			for (size_t i = 0; i < size; i++)
			{
				json_array_element_s* element = new json_array_element_s;
				element->value = new json_value_s;
				element->value->type = json_type_number;
				element->value->payload = _createNumber(value[i]);

				*elementPtr = element;
				elementPtr = &element->next;
			}

			_addValueToObject(currentObject, name, jsonValue);
			return true;
		}
	}
	return false;
}

bool JsonSerializer::serialize(const char* name, int64* value, size_t size)
{
	if (m_currentValue->type == json_type_object)
	{
		json_object_s* currentObject = static_cast<json_object_s*>(m_currentValue->payload);

		if (isReading())
		{
			json_value_s* match = _findObjectValue(currentObject, name);
			if (match && match->type == json_type_array)
			{
				json_array_s* array = static_cast<json_array_s*>(match->payload);
				if (size <= array->length)
				{
					json_array_element_s* currentElement = array->start;
					int i = 0;
					while (currentElement)
					{
						if (currentElement->value->type != json_type_number)
							return false;

						value[i] = atol(static_cast<json_number_s*>(currentElement->value->payload)->number);
						++i;
						currentElement = currentElement->next;
					}
					return true;
				}
			}
		}
		else
		{
			json_value_s* jsonValue = new json_value_s;
			jsonValue->type = json_type_array;
			json_array_s* array = new json_array_s;
			jsonValue->payload = array;

			array->length = size;

			json_array_element_s** elementPtr = &array->start;
			for (size_t i = 0; i < size; i++)
			{
				json_array_element_s* element = new json_array_element_s;
				element->value = new json_value_s;
				element->value->type = json_type_number;
				element->value->payload = _createNumber(value[i]);

				*elementPtr = element;
				elementPtr = &element->next;
			}

			_addValueToObject(currentObject, name, jsonValue);
			return true;
		}
	}
	return false;
}

bool JsonSerializer::serialize(const char* name, float* value, size_t size)
{
	if (m_currentValue->type == json_type_object)
	{
		json_object_s* currentObject = static_cast<json_object_s*>(m_currentValue->payload);

		if (isReading())
		{
			json_value_s* match = _findObjectValue(currentObject, name);
			if (match && match->type == json_type_array)
			{
				json_array_s* array = static_cast<json_array_s*>(match->payload);
				if (size <= array->length)
				{
					json_array_element_s* currentElement = array->start;
					int i = 0;
					while (currentElement)
					{
						if (currentElement->value->type != json_type_number)
							return false;

						value[i] = static_cast<float>(atof(static_cast<json_number_s*>(currentElement->value->payload)->number));
						++i;
						currentElement = currentElement->next;
					}
					return true;
				}
			}
		}
		else
		{
			json_value_s* jsonValue = new json_value_s;
			jsonValue->type = json_type_array;
			json_array_s* array = new json_array_s;
			jsonValue->payload = array;

			array->length = size;

			json_array_element_s** elementPtr = &array->start;
			for (size_t i = 0; i < size; i++)
			{
				json_array_element_s* element = new json_array_element_s;
				element->value = new json_value_s;
				element->value->type = json_type_number;
				element->value->payload = _createNumber(value[i]);

				*elementPtr = element;
				elementPtr = &element->next;
			}

			_addValueToObject(currentObject, name, jsonValue);
			return true;
		}
	}
	return false;
}

bool JsonSerializer::serialize(const char* name, double* value, size_t size)
{
	if (m_currentValue->type == json_type_object)
	{
		json_object_s* currentObject = static_cast<json_object_s*>(m_currentValue->payload);

		if (isReading())
		{
			json_value_s* match = _findObjectValue(currentObject, name);
			if (match && match->type == json_type_array)
			{
				json_array_s* array = static_cast<json_array_s*>(match->payload);
				if (size <= array->length)
				{
					json_array_element_s* currentElement = array->start;
					int i = 0;
					while (currentElement)
					{
						if (currentElement->value->type != json_type_number)
							return false;

						value[i] = atof(static_cast<json_number_s*>(currentElement->value->payload)->number);
						++i;
						currentElement = currentElement->next;
					}
					return true;
				}
			}
		}
		else
		{
			json_value_s* jsonValue = new json_value_s;
			jsonValue->type = json_type_array;
			json_array_s* array = new json_array_s;
			jsonValue->payload = array;

			array->length = size;

			json_array_element_s** elementPtr = &array->start;
			for (size_t i = 0; i < size; i++)
			{
				json_array_element_s* element = new json_array_element_s;
				element->value = new json_value_s;
				element->value->type = json_type_number;
				element->value->payload = _createNumber(value[i]);

				*elementPtr = element;
				elementPtr = &element->next;
			}

			_addValueToObject(currentObject, name, jsonValue);
			return true;
		}
	}
	return false;
}

bool JsonSerializer::serialize(const char* name, char* value, size_t size)
{
	if (m_currentValue->type != json_type_object && m_currentValue->type != json_type_array)
		return false;

	json_object_s* currentObject = static_cast<json_object_s*>(m_currentValue->payload);

	if (isReading())
	{
		json_value_s* match = _findObjectValue(currentObject, name);
		if (!match || match->type != json_type_string)
			return false;

		json_string_s* string = static_cast<json_string_s*>(match->payload);

		if ((size - 1) != string->string_size)
			return false;

		strcpy(value, static_cast<char*>(string->string));
	}
	else
	{
		json_value_s* jsonValue = new json_value_s;
		jsonValue->type = json_type_string;
		jsonValue->payload = _createString(value, size);
		_addValueToObject(currentObject, name, jsonValue);
	}
	return true;
}

bool JsonSerializer::serialize(const char* name, std::string& value)
{
	if (m_currentValue->type == json_type_object)
	{
		json_object_s* currentObject = static_cast<json_object_s*>(m_currentValue->payload);

		if (isReading())
		{
			json_value_s* match = _findObjectValue(currentObject, name);
			if (match && match->type == json_type_string)
			{
				value = static_cast<char*>(static_cast<json_string_s*>(match->payload)->string);
				return true;
			}
		}
		else
		{
			json_value_s* jsonValue = new json_value_s;
			jsonValue->type = json_type_string;
			jsonValue->payload = _createString(value.c_str());
			_addValueToObject(currentObject, name, jsonValue);
			return true;
		}
	}
	return false;
}

bool JsonSerializer::serialize(const char* name, std::string* value, size_t size)
{
	if (m_currentValue->type == json_type_object)
	{
		json_object_s* currentObject = static_cast<json_object_s*>(m_currentValue->payload);

		if (isReading())
		{
			json_value_s* match = _findObjectValue(currentObject, name);
			if (match && match->type == json_type_array)
			{
				json_array_s* array = static_cast<json_array_s*>(match->payload);
				if (size <= array->length)
				{
					json_array_element_s* currentElement = array->start;
					int i = 0;
					while (currentElement)
					{
						if (currentElement->value->type != json_type_string)
							return false;

						value[i] = static_cast<char*>(static_cast<json_string_s*>(currentElement->value->payload)->string);
						++i;
						currentElement = currentElement->next;
					}
					return true;
				}
			}
		}
		else
		{
			json_value_s* jsonValue = new json_value_s;
			jsonValue->type = json_type_array;
			json_array_s* array = new json_array_s;
			jsonValue->payload = array;

			array->length = size;

			json_array_element_s** elementPtr = &array->start;
			for (size_t i = 0; i < size; i++)
			{
				json_array_element_s* element = new json_array_element_s;
				element->value = new json_value_s;
				element->value->type = json_type_string;
				element->value->payload = _createString(value[i].c_str());

				*elementPtr = element;
				elementPtr = &element->next;
			}

			_addValueToObject(currentObject, name, jsonValue);
			return true;
		}
	}
	return false;
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

	if (isReading())
	{
		json_value_s* match = _findObjectValue(currentObject, _name);
		if (!match || match->type != json_type_object)
			return false;

		json_value_s* current_value = m_currentValue;
		m_currentValue = match;

		currentObject = static_cast<json_object_s*>(m_currentValue->payload);

		match = _findObjectValue(currentObject, "className");
		if (!match || match->type != json_type_string)
		{
			m_currentValue = current_value;
			return false;
		}

		json_string_s* className = static_cast<json_string_s*>(match->payload);
		_classDesc = getClassDesc(static_cast<char*>(className->string));

		if (!_classDesc)
			return false;

		*_pointer = Factory::create(_classDesc->getName());

		bool result = true;

		for (const auto& member : _classDesc->getMembers())
		{
			switch(member.type)
			{
			case ClassDesc::TYPE_INT:
				{
					result = result && serialize(member.name, *reinterpret_cast<int*>((*(uint8**)_pointer) + member.address));
				} break;

			case ClassDesc::TYPE_FLOAT:
				{
					result = result && serialize(member.name, *reinterpret_cast<float*>((*(uint8**)_pointer) + member.address));
				} break;

			default: break;
			}
		}

		return result;
	}
	else
	{
		json_value_s* jsonValue = new json_value_s;
		jsonValue->type = json_type_object;
		json_object_s* object = new json_object_s;
		jsonValue->payload = object;
		object->length = 0;
		object->start = nullptr;

		json_value_s* currentValue = m_currentValue;
		m_currentValue = jsonValue;

		// const_cast is ok since I know the char wont be stored nor modified.
		bool result = serialize("className", const_cast<char*>(_classDesc->getName()), strlen(_classDesc->getName()));
		
		for (const auto& member : _classDesc->getMembers())
		{
			switch(member.type)
			{
			case ClassDesc::TYPE_INT:
				{
					result = result && serialize(member.name, *reinterpret_cast<int*>((*(uint8**)_pointer) + member.address));
				} break;

			case ClassDesc::TYPE_FLOAT:
				{
					result = result && serialize(member.name, *reinterpret_cast<float*>((*(uint8**)_pointer) + member.address));
				} break;

			default: break;
			}
		}

		m_currentValue = currentValue;

		if (result)
		{
			_addValueToObject(currentObject, _name, jsonValue);
		}

		return result;
	}
}

bool JsonSerializer::serialize(const char* _name, void* _pointer, const ClassDesc* _classDesc)
{
	if (m_currentValue->type != json_type_object)
		return false;

	json_object_s* currentObject = static_cast<json_object_s*>(m_currentValue->payload);

	if (isReading())
	{
		json_value_s* match = _findObjectValue(currentObject, _name);
		if (!match || match->type != json_type_object)
			return false;

		json_value_s* current_value = m_currentValue;
		m_currentValue = match;

		currentObject = static_cast<json_object_s*>(m_currentValue->payload);

		match = _findObjectValue(currentObject, "className");
		if (!match || match->type != json_type_string)
		{
			m_currentValue = current_value;
			return false;
		}

		json_string_s* className = static_cast<json_string_s*>(match->payload);
		_classDesc = getClassDesc(static_cast<char*>(className->string));

		if (!_classDesc)
		{
			m_currentValue = current_value;
			return false;
		}

		bool result = true;

		for (const auto& member : _classDesc->getMembers())
		{
			switch(member.type)
			{
			case ClassDesc::TYPE_INT:
				{
					result = result && serialize(member.name, *(reinterpret_cast<int*>((uint8*)_pointer + member.address)));
				} break;

			case ClassDesc::TYPE_FLOAT:
				{
					result = result && serialize(member.name, *(reinterpret_cast<float*>((uint8*)_pointer + member.address)));
				} break;

			default: break;
			}
		}

		m_currentValue = current_value;
		return result;
	}
	else
	{
		json_value_s* jsonValue = new json_value_s;
		jsonValue->type = json_type_object;
		json_object_s* object = new json_object_s;
		jsonValue->payload = object;
		object->start = nullptr;
		object->length = 0;

		json_value_s* currentValue = m_currentValue;
		m_currentValue = jsonValue;

		// const_cast is ok since I know the char wont be stored nor modified.
		bool result = serialize("className", const_cast<char*>(_classDesc->getName()), strlen(_classDesc->getName()));

		for (const auto& member : _classDesc->getMembers())
		{
			switch(member.type)
			{
			case ClassDesc::TYPE_INT:
				{
					result = result && serialize(member.name, *(reinterpret_cast<int*>((uint8*)_pointer + member.address)));
				} break;

			case ClassDesc::TYPE_FLOAT:
				{
					result = result && serialize(member.name, *(reinterpret_cast<float*>((uint8*)_pointer + member.address)));
				} break;

			default: break;
			}
		}

		m_currentValue = currentValue;

		if (result)
		{
			_addValueToObject(currentObject, _name, jsonValue);
		}

		return result;
	}
}

/*bool JsonSerializer::serialize(const char* name, Serializable& serializable)
{
	if (m_currentValue->type == json_type_object)
	{
		json_object_s* currentObject = static_cast<json_object_s*>(m_currentValue->payload);

		if (isReading())
		{
			json_value_s* match = _findObjectValue(currentObject, name);
			if (match && match->type == json_type_object)
			{
				json_value_s* currentValue = m_currentValue;
				m_currentValue = match;
				bool result = serializable.serialize(this);
				m_currentValue = currentValue;
				return result;
			}
		}
		else
		{
			json_value_s* jsonValue = new json_value_s;
			jsonValue->type = json_type_object;
			json_object_s* object = new json_object_s;
			jsonValue->payload = object;

			json_value_s* currentValue = m_currentValue;
			m_currentValue = jsonValue;
			bool result = serializable.serialize(this);
			m_currentValue = currentValue;

			if (result)
			{
				_addValueToObject(currentObject, name, jsonValue);
				return result;
			}
		}
	}
	return false;
}

bool JsonSerializer::serialize(const char* name, Serializable* serializable, size_t size)
{
	if (m_currentValue->type == json_type_object)
	{
		json_object_s* currentObject = static_cast<json_object_s*>(m_currentValue->payload);

		if (isReading())
		{
			json_value_s* match = _findObjectValue(currentObject, name);
			if (match && match->type == json_type_array)
			{
				json_array_s* array = static_cast<json_array_s*>(match->payload);
				if (size <= array->length)
				{
					json_array_element_s* currentElement = array->start;
					int i = 0;
					while (currentElement)
					{
						if (currentElement->value->type != json_type_object)
							return false;

						json_value_s* currentValue = m_currentValue;
						m_currentValue = currentElement->value;
						bool result = serializable[i].serialize(this);
						m_currentValue = currentValue;

						if (!result)
							return false;

						++i;
						currentElement = currentElement->next;
					}
					return true;
				}
			}
		}
		else
		{
			json_value_s* jsonValue = new json_value_s;
			jsonValue->type = json_type_array;
			json_array_s* array = new json_array_s;
			jsonValue->payload = array;

			array->length = size;

			json_array_element_s** elementPtr = &array->start;
			for (size_t i = 0; i < size; i++)
			{
				json_array_element_s* element = new json_array_element_s;
				element->value = new json_value_s;
				element->value->type = json_type_object;
				json_object_s* object = new json_object_s;
				element->value->payload = object;

				json_value_s* currentValue = m_currentValue;
				m_currentValue = element->value;
				bool result = serializable[i].serialize(this);
				m_currentValue = currentValue;

				if (!result)
					return false;

				*elementPtr = element;
				elementPtr = &element->next;
			}

			_addValueToObject(currentObject, name, jsonValue);
			return true;
		}
	}
	return false;
}*/

void JsonSerializer::_addValueToObject(json_object_s* object, const char* name, json_value_s* value)
{
	json_object_element_s* nextElement = new json_object_element_s;
	nextElement->value = value;
	nextElement->name = _createString(name);
	nextElement->next = nullptr;

	json_object_element_s* currentElement = object->start;
	if (!currentElement)
	{
		object->start = nextElement;
	}
	else
	{
		while (currentElement->next)
		{
			currentElement = currentElement->next;
		}
		currentElement->next = nextElement;
	}
	++object->length;
}

json_value_s* JsonSerializer::_findObjectValue(json_object_s* object, const char* name)
{
	json_object_element_s* currentElement = object->start;
	while (currentElement)
	{
		if (strcmp(name, static_cast<char*>(currentElement->name->string)) == 0)
		{
			return currentElement->value;
		}
		currentElement = currentElement->next;
	}
	return nullptr;
}

json_string_s* JsonSerializer::_createString(const char* str, int size)
{
	json_string_s* result = new json_string_s;
	result->string_size = size < 0 ? strlen(str) : size;
	char* strBuffer = new char[result->string_size + 1];
	memcpy(strBuffer, str, result->string_size);
	strBuffer[result->string_size] = '\0';
	result->string = strBuffer;
	return result;
}

json_number_s* JsonSerializer::_createNumber(double number)
{
	json_number_s* result = new json_number_s;
	result->number = new char[32]; 
	sprintf(result->number, "%f\0", number);
	result->number_size = strlen(result->number);
	return result;
}

json_number_s* JsonSerializer::_createNumber(float number)
{
	json_number_s* result = new json_number_s;
	result->number = new char[32]; 
	sprintf(result->number, "%f\0", number);
	result->number_size = strlen(result->number);
	return result;
}

json_number_s* JsonSerializer::_createNumber(int64 number)
{
	json_number_s* result = new json_number_s;
	result->number = new char[32]; 
	sprintf(result->number, "%lld\0", number);
	result->number_size = strlen(result->number);
	return result;
}

json_number_s* JsonSerializer::_createNumber(int number)
{
	json_number_s* result = new json_number_s;
	result->number = new char[32]; 
	sprintf(result->number, "%d\0", number);
	result->number_size = strlen(result->number);
	return result;
}

json_number_s* JsonSerializer::_createNumber(uint64 number)
{
	json_number_s* result = new json_number_s;
	result->number = new char[32]; 
	sprintf(result->number, "%lld\0", number);
	result->number_size = strlen(result->number);
	return result;
}

json_number_s* JsonSerializer::_createNumber(unsigned int number)
{
	json_number_s* result = new json_number_s;
	result->number = new char[32]; 
	sprintf(result->number, "%d\0", number);
	result->number_size = strlen(result->number);
	return result;
}

void JsonSerializer::_deleteJsonValue(json_value_s* jsonValue)
{
	switch (jsonValue->type)
	{
	case json_type_number:
		{
			json_number_s* payload = static_cast<json_number_s*>(jsonValue->payload);
			delete payload->number;
		}
		break;

	case json_type_string:
		{
			json_string_s* payload = static_cast<json_string_s*>(jsonValue->payload);
			delete payload->string;
		}
		break;

	case json_type_array:
		{
			json_array_s* payload = static_cast<json_array_s*>(jsonValue->payload);
			json_array_element_s* nextElement = payload->start;
			while (nextElement)
			{
				json_array_element_s* element = nextElement;
				nextElement = element->next;

				_deleteJsonValue(element->value);
				delete element;
			}
		}
		break;

	case json_type_object:
		{
			json_object_s* payload = static_cast<json_object_s*>(jsonValue->payload);
			json_object_element_s* nextElement = payload->start;
			while (nextElement)
			{
				json_object_element_s* element = nextElement;
				nextElement = element->next;

				delete element->name->string;
				delete element->name;
				_deleteJsonValue(element->value);
				delete element;
			}
		}
		break;

	default:
		break;
	}

	delete jsonValue->payload;
	delete jsonValue;
}