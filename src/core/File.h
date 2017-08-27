#pragma once

#include <string>
#include <core/Resource.h>

class File : public Resource
{
public:
	File(const char* path);
	virtual ~File();

	const char* getPath() const;
	const char* getContent() const;
	size_t getSize() const;

protected:
	virtual void onLoad() override;
	virtual void onRelease() override;


private:
	std::string m_path;
	char*		m_buffer;
	size_t		m_size;
};