#pragma once

#include <cstdio>
#include <string>

class FileHandle
{
public:
	enum OpenMode
	{
		OPENMODE_READ,
		OPENMODE_WRITE,
		OPENMODE_APPEND
	};

	FileHandle(const char* path);
	~FileHandle();

	bool open(OpenMode mode);
	void close();

	bool write(const void* buffer, size_t size);
	size_t read(void* buffer, size_t size) const;

	bool isOpen() const;
	long getSize() const;
	long getOffset() const;
	void setOffset(long offset);
	const char* getPath() const;

private:
	std::string	m_path;
	OpenMode	m_openMode;
	std::FILE*	m_file;
};
