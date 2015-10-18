#include "stdafx.h"
#include "core/Serializer.h"

#include "core/File.h"

Serializer::Serializer(File* file, Mode mode)
{
	ASSERT(file && file->isOpen()) // File should be given opened
	// TODO: test if the file is opened in the right mode

	m_file = file;
	m_mode = mode;
}

Serializer::~Serializer()
{
}

File* Serializer::_getFile()
{
	return m_file;
}

Serializer::Mode Serializer::_getMode() const
{
	return m_mode;
}