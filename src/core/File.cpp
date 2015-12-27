#include "core/File.h"

#include "core/Assert.h"
#include "core/FileHandle.h"

File::File(const char* path)
{
	m_path = path;
	m_buffer = nullptr;
	m_size = 0;
}

File::~File() {}

void File::onLoad()
{
	FileHandle file(m_path.c_str());
	if (!file.open(FileHandle::MODE_READ))
	{
		setError(RESOURCE_LOADERROR, "Could not open file.");
		return;
	}

	m_size = file.getSize();
	m_buffer = new char[m_size];
	file.read(m_buffer, m_size);
}

void File::onRelease()
{
	delete[] m_buffer;
}

const char* File::getPath() const
{
	return m_path.c_str();
}

const char* File::getContent() const
{
	ASSERT(isLoaded());
	return m_buffer;
}

size_t File::getSize() const
{
	return m_size;
}
