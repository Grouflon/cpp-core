#pragma once

#include "core/Serializer.h"

class BinarySerializer
	: public Serializer
{
public:
	BinarySerializer(File* file, Mode mode);
	virtual ~BinarySerializer();

	virtual void serialize(const char* name, bool& value) override;

	virtual void serialize(const char* name, uint8& value) override;
	virtual void serialize(const char* name, uint16& value) override;
	virtual void serialize(const char* name, uint32& value) override;
	virtual void serialize(const char* name, uint64& value) override;

	virtual void serialize(const char* name, int8& value) override;
	virtual void serialize(const char* name, int16& value) override;

	virtual void serialize(const char* name, int32& value) override;
	virtual void serialize(const char* name, int64& value) override;

	virtual void serialize(const char* name, std::string& value) override;

	virtual void serialize(const char* name, Serializable& serializable) override;

private:
	void _rawSerialize(void* data, int size);
};
