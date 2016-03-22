#include "stdafx.h"
#include "core/JsonTools.h"

namespace JsonTools {
	

json_value_s* FindObjectValue(json_object_s* _object, const char* _name)
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

json_value_s* FindObjectValue(json_object_s* _object, const char* _name, json_type_e _type)
{
	json_value_s* ret = FindObjectValue(_object, _name);
	if (!ret || ret->type != _type)
	{
		ret = nullptr;
	}
	return ret;
}

json_string_s* CreateString(const char* _str, int _size)
{
	json_string_s* result = new json_string_s;
	result->string_size = _size < 0 ? strlen(_str) : _size;
	char* strBuffer = new char[result->string_size + 1];
	memcpy(strBuffer, _str, result->string_size);
	strBuffer[result->string_size] = '\0';
	result->string = strBuffer;
	return result;
}

json_number_s* CreateNumber(double _number)
{
	json_number_s* result = new json_number_s;
	result->number = new char[32];
	sprintf(result->number, "%f\0", _number);
	result->number_size = strlen(result->number);
	return result;
}

json_number_s* CreateNumber(float _number)
{
	json_number_s* result = new json_number_s;
	result->number = new char[32];
	sprintf(result->number, "%f\0", _number);
	result->number_size = strlen(result->number);
	return result;
}

json_number_s* CreateNumber(int64 _number)
{
	json_number_s* result = new json_number_s;
	result->number = new char[32];
	sprintf(result->number, "%lld\0", _number);
	result->number_size = strlen(result->number);
	return result;
}

json_number_s* CreateNumber(int _number)
{
	json_number_s* result = new json_number_s;
	result->number = new char[32];
	sprintf(result->number, "%d\0", _number);
	result->number_size = strlen(result->number);
	return result;
}

json_number_s* CreateNumber(uint64 _number)
{
	json_number_s* result = new json_number_s;
	result->number = new char[32];
	sprintf(result->number, "%lld\0", _number);
	result->number_size = strlen(result->number);
	return result;
}

json_number_s* CreateNumber(unsigned int _number)
{
	json_number_s* result = new json_number_s;
	result->number = new char[32];
	sprintf(result->number, "%d\0", _number);
	result->number_size = strlen(result->number);
	return result;
}

json_value_s* CreateStringValue(const char* _str, int _size)
{
	json_value_s* ret = new json_value_s;
	ret->type = json_type_string;
	ret->payload = CreateString(_str, _size);
	return ret;
}

json_value_s* CreateNumberValue(double _number)
{
	json_value_s* ret = new json_value_s;
	ret->type = json_type_number;
	ret->payload = CreateNumber(_number);
	return ret;
}

json_value_s* CreateNumberValue(float _number)
{
	json_value_s* ret = new json_value_s;
	ret->type = json_type_number;
	ret->payload = CreateNumber(_number);
	return ret;
}

json_value_s* CreateNumberValue(int64 _number)
{
	json_value_s* ret = new json_value_s;
	ret->type = json_type_number;
	ret->payload = CreateNumber(_number);
	return ret;
}

json_value_s* CreateNumberValue(int _number)
{
	json_value_s* ret = new json_value_s;
	ret->type = json_type_number;
	ret->payload = CreateNumber(_number);
	return ret;
}

json_value_s* CreateNumberValue(uint64 _number)
{
	json_value_s* ret = new json_value_s;
	ret->type = json_type_number;
	ret->payload = CreateNumber(_number);
	return ret;
}

json_value_s* CreateNumberValue(unsigned int _number)
{
	json_value_s* ret = new json_value_s;
	ret->type = json_type_number;
	ret->payload = CreateNumber(_number);
	return ret;
}

json_value_s* CreateBoolValue(bool _value)
{
	json_value_s* ret = new json_value_s;
	ret->type = _value ? json_type_true : json_type_false;
	ret->payload = nullptr;
	return ret;
}

json_value_s* CreateObjectValue()
{
	json_value_s* ret = new json_value_s;
	ret->type = json_type_object;
	json_object_s* object = new json_object_s;
	ret->payload = object;
	object->length = 0;
	object->start = nullptr;
	return ret;
}

void AddValueToObject(json_object_s* _object, const char* _name, json_value_s* _value)
{
	json_object_element_s* nextElement = new json_object_element_s;
	nextElement->value = _value;
	nextElement->name = CreateString(_name);
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

json_value_s* CreateArrayValue()
{
	json_value_s* ret = new json_value_s;
	ret->type = json_type_array;
	json_array_s* array = new json_array_s;
	ret->payload = array;
	array->length = 0;
	array->start = nullptr;
	return ret;
}

void PushBackValueToArray(json_array_s* _array, json_value_s* _value)
{
	json_array_element_s* nextElement = new json_array_element_s;
	nextElement->value = _value;
	nextElement->next = nullptr;

	json_array_element_s* currentElement = _array->start;
	if (!currentElement)
	{
		_array->start = nextElement;
	}
	else
	{
		while (currentElement->next)
		{
			currentElement = currentElement->next;
		}
		currentElement->next = nextElement;
	}
	++_array->length;
}

void DeleteJsonValue(json_value_s* _jsonValue)
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

			DeleteJsonValue(element->value);
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
			DeleteJsonValue(element->value);
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

char* ValueToString(json_value_s* _value)
{
	return static_cast<char*>(static_cast<json_string_s*>(_value->payload)->string);
}


} // namespace JsonTools
