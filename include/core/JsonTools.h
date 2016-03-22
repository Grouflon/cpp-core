#pragma once

#include <json.h>

namespace JsonTools {


json_value_s*	FindObjectValue(json_object_s* _object, const char* _name);
json_value_s*	FindObjectValue(json_object_s* _object, const char* _name, json_type_e _type);

json_string_s*	CreateString(const char* _str, int _size = -1);
json_number_s*	CreateNumber(double _number);
json_number_s*	CreateNumber(float _number);
json_number_s*	CreateNumber(int64 _number);
json_number_s*	CreateNumber(int _number);
json_number_s*	CreateNumber(uint64 _number);
json_number_s*	CreateNumber(unsigned int _number);
json_value_s*	CreateStringValue(const char* _str, int _size = -1);
json_value_s*	CreateNumberValue(double _number);
json_value_s*	CreateNumberValue(float _number);
json_value_s*	CreateNumberValue(int64 _number);
json_value_s*	CreateNumberValue(int _number);
json_value_s*	CreateNumberValue(uint64 _number);
json_value_s*	CreateNumberValue(unsigned int _number);
json_value_s*	CreateBoolValue(bool _value);
json_value_s*	CreateObjectValue();
void			AddValueToObject(json_object_s* _object, const char* _name, json_value_s* _value);
void			DeleteJsonValue(json_value_s* _jsonValue);

// These functions does not perform any type check. Use with caution
char*			ValueToString(json_value_s* _value);


} // namespace JsonTools
