#pragma once

class File;
class Serializable;
class ClassDesc;

class Serializer
{
public:
	Serializer();
	virtual ~Serializer();

	// TODO: string error descriptions

	virtual bool beginRead(const File* _file);
	virtual bool beginWrite(File* _file);
	virtual bool end();

	template <typename T>
	bool serialize(const char* _name, std::vector<T>& _value);

	virtual bool beginVectorSerialization(const char* _name, size_t& _size) = 0;
	virtual bool endVectorSerialization() = 0;

	virtual bool serialize(const char* _name, bool& _value) = 0;

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
	virtual bool serialize(const char* _name, char& _value) = 0;

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
	virtual bool serialize(const char* _name, char* _value, size_t _size) = 0;

	virtual bool serialize(const char* _name, std::string& _value) = 0;
	virtual bool serialize(const char* _name, std::string* _value, size_t _size) = 0;

	template <typename T>
	bool serialize(const char* _name, T** _value);

	template <typename T>
	bool serialize(const char* _name, T* _value);

	virtual bool serialize(const char* _name, void** _pointer, const ClassDesc* _classDesc) = 0;
	virtual bool serialize(const char* _name, void* _pointer, const ClassDesc* _classDesc) = 0;

	bool isReading() const;
	bool isWriting() const;

	const char* getErrorDesc();

protected:
	const File*	getReadFile() const;
	File*		getWriteFile() const;
	void		setErrorDesc(const char* _errorDesc);

private:
	const File*	m_readFile;
	File*		m_writeFile;

	std::string m_errorDesc;
};

#include "core/Serializer.inl"
