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

void Serializer::beginRead(const File* file)
{
	ASSERT(!m_readFile && !m_writeFile); // end() not called
	ASSERT(file);
	m_readFile = file;
}

void Serializer::beginWrite(File* file)
{
	ASSERT(!m_readFile && !m_writeFile); // end() not called
	ASSERT(file);
	m_writeFile = file;
}

void Serializer::end()
{
	m_readFile = nullptr;
	m_writeFile = nullptr;
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