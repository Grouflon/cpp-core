#pragma once

class File;
class Serializable;

class Serializer
{
public:
	Serializer();
	virtual ~Serializer();

	void beginRead(const File* file);
	void beginWrite(File* file);
	void end();

	// TODO-THINK: all serialize methods could be const so far. do I want that ?
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

	// TODO-THINK: is const char* serialization relevant ? is allocation free serialization possible ?
	virtual bool serialize(const char* name, std::string& value) = 0;

	virtual bool serialize(const char* name, Serializable& serializable) = 0;
	virtual bool serialize(const char* name, Serializable* serializable, size_t size) = 0;

	// TODO: Container types
	// TODO: float
	// TODO: pointers/size

	bool isReading() const;

protected:
	// TODO: Think of something more elegant
	const File*	_getReadFile() const;
	File*		_getWriteFile() const;

private:
	const File*	m_readFile;
	File*		m_writeFile;
};
