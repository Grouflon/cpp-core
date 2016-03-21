#pragma once

#include <json.h>

json_value_s*	FindJsonValue(json_value_s* _value, const char* _name);

// These functions does not perform any type check. Use with caution
char*			JsonValueToString(json_value_s* _value);
