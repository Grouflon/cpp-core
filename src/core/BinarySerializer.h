#pragma once

#include "core/Serializer.h"

class BinarySerializer
	: public Serializer
{
public:
	BinarySerializer();
	virtual ~BinarySerializer();

	virtual bool serialize(const char* _name, bool& _value) override;

	virtual bool serialize(const char* _name, uint8& _value) override;
	virtual bool serialize(const char* _name, uint16& _value) override;
	virtual bool serialize(const char* _name, uint32& _value) override;
	virtual bool serialize(const char* _name, uint64& _value) override;
	virtual bool serialize(const char* _name, int8& _value) override;
	virtual bool serialize(const char* _name, int16& _value) override;
	virtual bool serialize(const char* _name, int32& _value) override;
	virtual bool serialize(const char* _name, int64& _value) override;
	virtual bool serialize(const char* _name, float& _value) override;
	virtual bool serialize(const char* _name, double& _value) override;

	virtual bool serialize(const char* _name, uint8* _value, size_t _size) override;
	virtual bool serialize(const char* _name, uint16* _value, size_t _size) override;
	virtual bool serialize(const char* _name, uint32* _value, size_t _size) override;
	virtual bool serialize(const char* _name, uint64* _value, size_t _size) override;
	virtual bool serialize(const char* _name, int8* _value, size_t _size) override;
	virtual bool serialize(const char* _name, int16* _value, size_t _size) override;
	virtual bool serialize(const char* _name, int32* _value, size_t _size) override;
	virtual bool serialize(const char* _name, int64* _value, size_t _size) override;
	virtual bool serialize(const char* _name, float* _value, size_t _size) override;
	virtual bool serialize(const char* _name, double* _value, size_t _size) override;


	virtual bool serialize(const char* _name, char* _value, size_t _size) override;
	virtual bool serialize(const char* _name, std::string& _value) override;
	virtual bool serialize(const char* _name, std::string* _value, size_t _size) override;

	virtual bool beginVectorSerialization(const char* _name, size_t& _size) override;
	virtual bool endVectorSerialization() override;
	virtual bool serialize(const char* _name, void** _pointer, const ClassDesc* _classDesc) override;
	virtual bool serialize(const char* _name, void* _pointer, const ClassDesc* _classDesc) override;

private:
	bool _rawSerialize(void* data, int _size);
};
