#include "stdafx.h"
#include "core/JsonTools.h"

json_value_s* FindJsonValue(json_value_s* _value, const char* _name)
{
	if (_value->type == json_type_object)
	{
		json_object_s* object = static_cast<json_object_s*>(_value->payload);
		json_object_element_s* currentElement = object->start;
		while (currentElement)
		{
			if (strcmp(static_cast<char*>(currentElement->name->string), _name) == 0)
			{
				return currentElement->value;
			}

			currentElement = currentElement->next;
		}
	}

	return nullptr;
}

char* JsonValueToString(json_value_s* _value)
{
	return static_cast<char*>(static_cast<json_string_s*>(_value->payload)->string);
}
