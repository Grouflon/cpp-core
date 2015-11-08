#include "stdafx.h"
#include "core/Serializer.h"

#include "core/File.h"

Serializer::Serializer()
	: m_readFile(nullptr)
	, m_writeFile(nullptr)
{
}

Serializer::~Serializer()
{
}

bool Serializer::beginRead(const File* file)
{
	if (m_readFile || m_writeFile) return false; // end() not called
	if (!file || !file->isOpen()) return false;

	m_readFile = file;
	return true;
}

bool Serializer::beginWrite(File* file)
{
	if (m_readFile || m_writeFile) return false; // end() not called
	if (!file || !file->isOpen()) return false;

	m_writeFile = file;
	return true;
}

bool Serializer::end()
{
	m_readFile = nullptr;
	m_writeFile = nullptr;
	return true;
}

bool Serializer::isReading() const
{
	ASSERT(m_readFile || m_writeFile); // This result has no sense if not between startRead/Write() and end().
	return m_readFile != nullptr;
}

const File* Serializer::_getReadFile() const
{
	return m_readFile;
}

File* Serializer::_getWriteFile() const
{
	return m_writeFile;
}