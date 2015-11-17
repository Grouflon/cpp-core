#pragma once

class File;
class Serializable;
class ClassDesc;

class Serializer
{
public:
	Serializer();
	virtual ~Serializer();

	// TODO: string error description

	virtual bool beginRead(const File* file);
	virtual bool beginWrite(File* file);
	virtual bool end();

	template <typename T>
	bool serialize(const char* _name, std::vector<T>& _value);

	virtual bool beginVectorSerialization(const char* _name, size_t& size) = 0;
	virtual bool endVectorSerialization() = 0;

	virtual bool serialize(const char* name, bool& value) = 0;

	virtual bool serialize(const char* name, uint8& value) = 0;
	virtual bool serialize(const char* name, uint16& value) = 0;
	virtual bool serialize(const char* name, uint32& value) = 0;
	virtual bool serialize(const char* name, uint64& value) = 0;
	virtual bool serialize(const char* name, int8& value) = 0;
	virtual bool serialize(const char* name, int16& value) = 0;
	virtual bool serialize(const char* name, int32& value) = 0;
	virtual bool serialize(const char* name, int64& value) = 0;
	virtual bool serialize(const char* name, float& value) = 0;
	virtual bool serialize(const char* name, double& value) = 0;

	virtual bool serialize(const char* name, uint8* value, size_t size) = 0;
	virtual bool serialize(const char* name, uint16* value, size_t size) = 0;
	virtual bool serialize(const char* name, uint32* value, size_t size) = 0;
	virtual bool serialize(const char* name, uint64* value, size_t size) = 0;
	virtual bool serialize(const char* name, int8* value, size_t size) = 0;
	virtual bool serialize(const char* name, int16* value, size_t size) = 0;
	virtual bool serialize(const char* name, int32* value, size_t size) = 0;
	virtual bool serialize(const char* name, int64* value, size_t size) = 0;
	virtual bool serialize(const char* name, float* value, size_t size) = 0;
	virtual bool serialize(const char* name, double* value, size_t size) = 0;
	virtual bool serialize(const char* name, char* value, size_t size) = 0;

	virtual bool serialize(const char* name, std::string& value) = 0;
	virtual bool serialize(const char* name, std::string* value, size_t size) = 0;

	template <typename T>
	bool serialize(const char* _name, T** _value);

	template <typename T>
	bool serialize(const char* _name, T* _value);

	virtual bool serialize(const char* _name, void** _pointer, const ClassDesc* _classDesc) = 0;
	virtual bool serialize(const char* _name, void* _pointer, const ClassDesc* _classDesc) = 0;

	bool isReading() const;

protected:
	// TODO: Think of something more elegant
	const File*	_getReadFile() const;
	File*		_getWriteFile() const;

private:
	const File*	m_readFile;
	File*		m_writeFile;
};

#include "core/Serializer.inl"
