#include "stdafx.h"
#include "core/File.h"

File::File(const char* path)
	: m_file(nullptr)
{
	m_path = path;
}

File::~File()
{
	close();
}

bool File::open(OpenMode mode)
{
	if (m_file && mode != m_openMode)
	{
		close();
	}

	m_openMode = mode;
	char modeStr[8] = "";
	switch (m_openMode)
	{
	case MODE_READ:
		{
			sprintf(modeStr, "rb");
		} break;

	case MODE_WRITE:
		{
			sprintf(modeStr, "wb");
		} break;

	case MODE_APPEND:
		{
			sprintf(modeStr, "ab");
		} break;

	default:
		break;
	}

	m_file = fopen(m_path.c_str(), modeStr);
	return m_file != nullptr;
}

void File::close()
{
	if (m_file)
	{
		fclose(m_file);
		m_file = nullptr;
	}
}

bool File::write(const void* buffer, size_t size)
{
	if (m_file)
	{
		return fwrite(buffer, size, 1, m_file);
	}
	return 0;
}

size_t File::read(void* buffer, size_t size)
{
	if (m_file)
	{
		return fread(buffer, 1, size, m_file);
	}
	return 0;
}

bool File::isOpen() const
{
	return m_file != nullptr;
}

long File::getSize() const
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

long File::getOffset() const
{
	if (m_file)
	{
		return ftell(m_file);
	}
	return 0;
}

void File::setOffset(long offset)
{
	if (m_file)
	{
		fseek(m_file, offset, SEEK_SET);
	}
}

const char* File::getPath() const
{
	return m_path.c_str();
}