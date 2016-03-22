#pragma once

class FileHandle;
class Serializable;
class ClassDesc;

class Serializer
{
public:
	Serializer();
	virtual ~Serializer();

	// TODO-THINK: Not sure FileHandle* is the good choice here. Or at least we'll need a MemFileHandle
	virtual bool beginRead(const FileHandle* _file);
	virtual bool beginWrite(FileHandle* _file);
	virtual bool end();

	virtual bool serialize(const char* _name, bool& _value) = 0;
	virtual bool serialize(const char* _name, char& _value) = 0;
	virtual bool serialize(const char* _name, uint8& _value) = 0;
	virtual bool serialize(const char* _name, uint16& _value) = 0;
	virtual bool serialize(const char* _name, uint32& _value) = 0;
	virtual bool serialize(const char* _name, uint64& _value) = 0;
	virtual bool serialize(const char* _name, int8& _value) = 0;
	virtual bool serialize(const char* _name, int16& _value) = 0;
	virtual bool serialize(const char* _name, int32& _value) = 0;
	virtual bool serialize(const char* _name, int64& _value) = 0;
	virtual bool serialize(const char* _name, float& _value) = 0;
	virtual bool serialize(const char* _name, double& _value) = 0;
	virtual bool serialize(const char* _name, std::string& _value) = 0;

	virtual bool serialize(const char* _name, bool* _value, size_t _size) = 0;
	virtual bool serialize(const char* _name, char* _value, size_t _size) = 0;
	virtual bool serialize(const char* _name, uint8* _value, size_t _size) = 0;
	virtual bool serialize(const char* _name, uint16* _value, size_t _size) = 0;
	virtual bool serialize(const char* _name, uint32* _value, size_t _size) = 0;
	virtual bool serialize(const char* _name, uint64* _value, size_t _size) = 0;
	virtual bool serialize(const char* _name, int8* _value, size_t _size) = 0;
	virtual bool serialize(const char* _name, int16* _value, size_t _size) = 0;
	virtual bool serialize(const char* _name, int32* _value, size_t _size) = 0;
	virtual bool serialize(const char* _name, int64* _value, size_t _size) = 0;
	virtual bool serialize(const char* _name, float* _value, size_t _size) = 0;
	virtual bool serialize(const char* _name, double* _value, size_t _size) = 0;
	virtual bool serialize(const char* _name, std::string* _value, size_t _size) = 0;

	virtual bool serialize(const char* _name, void** _pointer, const ClassDesc* _classDesc) = 0;
	virtual bool serialize(const char* _name, void* _pointer, const ClassDesc* _classDesc) = 0;

	virtual bool serializeVectorStart(const char* _name, size_t& _size) = 0;
	virtual bool serializeVectorStop() = 0;

	template <typename T>
	bool serialize(const char* _name, T** _value);

	template <typename T>
	bool serialize(const char* _name, T* _value);

	template <typename T>
	bool serialize(const char* _name, std::vector<T>& _value);

	bool isReading() const;
	bool isWriting() const;

	const char* getErrorDesc();

protected:
	const FileHandle*	getReadFile() const;
	FileHandle*		getWriteFile() const;
	void		setErrorDesc(const char* _errorDesc);

	bool		m_reading;
	bool		m_writing;

private:
	const FileHandle*	m_readFile;
	FileHandle*			m_writeFile;

	std::string m_errorDesc;
};

#include "core/Serializer.inl"
