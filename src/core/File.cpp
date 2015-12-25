#include "core/File.h"

#include "core/Assert.h"
#include "core/FileHandle.h"

File::File(const char* path)
{
	m_path = path;
	m_buffer = nullptr;
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

	size_t size = file.getSize();
	m_buffer = new char[size];
	file.read(m_buffer, size);
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
