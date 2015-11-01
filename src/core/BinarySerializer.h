#pragma once

#include "core/Serializer.h"

class BinarySerializer
	: public Serializer
{
public:
	BinarySerializer();
	virtual ~BinarySerializer();

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

	virtual bool serialize(const char* name, std::string& value) override;

	virtual bool serialize(const char* name, Serializable& serializable) override;
	virtual bool serialize(const char* name, Serializable* serializable, size_t size) override;

private:
	bool _rawSerialize(void* data, int size);
};
