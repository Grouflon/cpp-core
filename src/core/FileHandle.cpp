#include "stdafx.h"
#include "core/FileHandle.h"

#include "core/Log.h"

FileHandle::FileHandle(const char* path)
	: m_file(nullptr)
{
	m_path = path;
}

FileHandle::~FileHandle()
{
	close();
}

bool FileHandle::open(OpenMode mode)
{
	if (m_file && mode != m_openMode)
	{
		close();
	}

	m_openMode = mode;
	char modeStr[8] = "";
	switch (m_openMode)
	{
	case OPENMODE_READ:
		{
			sprintf(modeStr, "rb");
		} break;

	case OPENMODE_WRITE:
		{
			sprintf(modeStr, "wb");
		} break;

	case OPENMODE_APPEND:
		{
			sprintf(modeStr, "ab");
		} break;

	default:
		break;
	}

	m_file = fopen(m_path.c_str(), modeStr);

	if (!m_file)
	{
		LOG_ERROR("Failed to open file \"%s\". %s", m_path.c_str(), strerror(errno));
		return false;
	}

	return true;
}

void FileHandle::close()
{
	if (m_file)
	{
		fclose(m_file);
		m_file = nullptr;
	}
}

bool FileHandle::write(const void* buffer, size_t size)
{
	if (m_file)
	{
		return size == 0 || fwrite(buffer, size, 1, m_file) != 0;
	}
	return false;
}

size_t FileHandle::read(void* buffer, size_t size) const
{
	if (m_file)
	{
		return fread(buffer, 1, size, m_file);
	}
	return 0;
}

bool FileHandle::isOpen() const
{
	return m_file != nullptr;
}

long FileHandle::getSize() const
{
	if (m_file)
	{
		long offset = ftell(m_file);
		fseek(m_file, 0, SEEK_END);
		long size = ftell(m_file);
		fseek(m_file, offset, SEEK_SET);
		return size;
	}
	return 0;
}

long FileHandle::getOffset() const
{
	if (m_file)
	{
		return ftell(m_file);
	}
	return 0;
}

void FileHandle::setOffset(long offset)
{
	if (m_file)
	{
		fseek(m_file, offset, SEEK_SET);
	}
}

const char* FileHandle::getPath() const
{
	return m_path.c_str();
}