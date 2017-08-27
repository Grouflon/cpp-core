#pragma once

#include <stack>
#include <string>
#include <vector>
#include <algorithm>
#include <json.h>
#include "core/Types.h"
#include "core/Serializer.h"

struct json_value_s;
struct json_object_s;
struct json_string_s;
struct json_number_s;
struct json_array_element_s;

class JsonSerializer
	: public Serializer
{
public:

	JsonSerializer();
	virtual ~JsonSerializer();

	void beginRead(const json_value_s* _root);

	virtual bool beginRead(const FileHandle* file) override;
	virtual bool beginWrite(FileHandle* file) override;
	virtual bool end() override;

	// TODO : handle value write / read into array currentValue (will be used for vectors)
	virtual bool serialize(const char* name, bool& value) override;
	virtual bool serialize(const char* name, char& value) override;
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
	virtual bool serialize(const char* name, bool* value, size_t size) override;
	virtual bool serialize(const char* name, char* value, size_t size) override;
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
	virtual bool serialize(const char* name, std::string& value) override;
	virtual bool serialize(const char* name, std::string* value, size_t size) override;

	virtual bool serializeVectorStart(const char* _name, size_t& size) override;
	virtual bool serializeVectorStop() override;

	template <typename T>
	bool serialize(const char* _name, T** _value) { return Serializer::serialize(_name, _value); }

	template <typename T>
	bool serialize(const char* _name, T* _value)  { return Serializer::serialize(_name, _value); }

	template <typename T>
	bool serialize(const char* _name, std::vector<T>& _value) { return Serializer::serialize(_name, _value); }

	virtual bool serialize(const char* _name, void** _pointer, const ClassDesc* _classDesc) override;
	virtual bool serialize(const char* _name, void* _pointer, const ClassDesc* _classDesc) override;

private:
	bool	serializeArray(const char* _name, size_t _size, std::function<bool(const json_array_element_s*, int)> _readCallback, std::function<bool(json_array_element_s*, int)> _writeCallback);
	bool	serializeClassDesc(const ClassDesc** _classDesc);
	bool	serializeMembers(void* _pointer, const ClassDesc* _classDesc);
	bool	serializeValue(const char* _name, json_type_e _type, void* _value, void(*_readFunc)(json_value_s*, void*), json_value_s*(*_writeFunc)(void*));

	json_value_s*						m_root;
	json_value_s*						m_currentValue;
	
	std::stack<json_value_s*>			m_currentArrayParent;
	std::stack<json_array_element_s*>	m_currentArrayElement;
};
