#pragma once

class File;
class Serializable;

class Serializer
{
public:
	enum Mode
	{
		MODE_READ,
		MODE_WRITE
	};

	Serializer(File* file, Mode mode);
	virtual ~Serializer();

	// TODO-THINK: Should this return a bool ?
	virtual void serialize(const char* name, bool& value) = 0;

	virtual void serialize(const char* name, uint8& value) = 0;
	virtual void serialize(const char* name, uint16& value) = 0;
	virtual void serialize(const char* name, uint32& value) = 0;
	virtual void serialize(const char* name, uint64& value) = 0;

	virtual void serialize(const char* name, int8& value) = 0;
	virtual void serialize(const char* name, int16& value) = 0;
	virtual void serialize(const char* name, int32& value) = 0;
	virtual void serialize(const char* name, int64& value) = 0;

	// TODO-THINK: is const char* serialization relevant ? is allocation free serialization possible ?
	virtual void serialize(const char* name, std::string& value) = 0;

	virtual void serialize(const char* name, Serializable& serializable) = 0;

	// TODO: Container types
	// TODO: float
	// TODO: pointers/size

protected:
	File* _getFile();
	Mode _getMode() const;

private:
	File*	m_file;
	Mode	m_mode;
};
