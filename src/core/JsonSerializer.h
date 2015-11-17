#pragma once

#include "core/Serializer.h"

struct json_value_s;
struct json_object_s;
struct json_string_s;
struct json_number_s;

class JsonSerializer
	: public Serializer
{
public:

	JsonSerializer();
	virtual ~JsonSerializer();

	virtual bool beginRead(const File* file) override;
	virtual bool beginWrite(File* file) override;
	virtual bool end() override;

	// TODO : handle value write / read into array currentValue;
	virtual bool serialize(const char* name, bool& value) override;
	virtual bool serialize(const char* name, uint8& value) override;
	virtual bool serialize(const char* name, uint16& value) override;
	virtual bool serialize(const char* name, uint32& value) override;
	virtual bool serialize(const char* name, uint64& value) override;
	virtual bool serialize(const char* name, int8& value) override;
	virtual bool serialize(const char* name, int16& value) override;
	virtual bool serialize(const char* name, int32& value) override;
	virtual bool serialize(const char* name, int64& value) override;
	virtual bool serialize(const char* name, float& value) override;
	virtual bool serialize(const char* name, double& value) override;
	virtual bool serialize(const char* name, uint8* value, size_t size) override;
	virtual bool serialize(const char* name, uint16* value, size_t size) override;
	virtual bool serialize(const char* name, uint32* value, size_t size) override;
	virtual bool serialize(const char* name, uint64* value, size_t size) override;
	virtual bool serialize(const char* name, int8* value, size_t size) override;
	virtual bool serialize(const char* name, int16* value, size_t size) override;
	virtual bool serialize(const char* name, int32* value, size_t size) override;
	virtual bool serialize(const char* name, int64* value, size_t size) override;
	virtual bool serialize(const char* name, float* value, size_t size) override;
	virtual bool serialize(const char* name, double* value, size_t size) override;
	virtual bool serialize(const char* name, char* value, size_t size) override;
	virtual bool serialize(const char* name, std::string& value) override;
	virtual bool serialize(const char* name, std::string* value, size_t size) override;
	virtual bool beginVectorSerialization(const char* _name, size_t& size) override;
	virtual bool endVectorSerialization() override;

	template <typename T>
	bool serialize(const char* _name, T** _value) { return Serializer::serialize(_name, _value); }

	template <typename T>
	bool serialize(const char* _name, T* _value)  { return Serializer::serialize(_name, _value); }

	virtual bool serialize(const char* _name, void** _pointer, const ClassDesc* _classDesc) override;
	virtual bool serialize(const char* _name, void* _pointer, const ClassDesc* _classDesc) override;

private:
	void			_addValueToObject(json_object_s* object, const char* name, json_value_s* value);
	json_value_s*	_findObjectValue(json_object_s* object, const char* name);
	json_string_s*	_createString(const char* str, int size = -1);
	json_number_s*	_createNumber(double number);
	json_number_s*	_createNumber(float number);
	json_number_s*	_createNumber(int64 number);
	json_number_s*	_createNumber(int number);
	json_number_s*	_createNumber(uint64 number);
	json_number_s*	_createNumber(unsigned int number);
	void			_deleteJsonValue(json_value_s* jsonValue);

	json_value_s*	m_root;
	json_value_s*	m_currentValue;
};
