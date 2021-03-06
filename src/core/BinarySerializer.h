﻿#pragma once

#include <cstdlib>
#include <string>
#include <vector>
#include "core/Types.h"
#include "core/Serializer.h"

class BinarySerializer
	: public Serializer
{
public:
	BinarySerializer();
	virtual ~BinarySerializer();

	virtual bool serialize(const char* _name, bool& _value) override;
	virtual bool serialize(const char* _name, char& _value) override;
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

	virtual bool serialize(const char* _name, bool* _value, size_t _size) override;
	virtual bool serialize(const char* _name, char* _value, size_t _size) override;
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


	virtual bool serialize(const char* _name, std::string& _value) override;
	virtual bool serialize(const char* _name, std::string* _value, size_t _size) override;

	virtual bool serializeVectorStart(const char* _name, size_t& _size) override;
	virtual bool serializeVectorStop() override;
	virtual bool serialize(const char* _name, void** _pointer, const ClassDesc* _classDesc) override;
	virtual bool serialize(const char* _name, void* _pointer, const ClassDesc* _classDesc) override;

private:
	bool serializeClassDesc(const ClassDesc** _classDesc);
	bool serializeMembers(void* _pointer, const ClassDesc* _classDesc);
	bool rawSerialize(void* data, int _size);
};
