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

bool Serializer::beginRead(const File* _file)
{
	if (m_readFile || m_writeFile)
	{
		setErrorDesc("end() must be called before calling begin() again.");
		return false; // end() not called
	}
	if (!_file || !_file->isOpen())
	{
		setErrorDesc("_file parameter must be given already opened.");
		return false;
	}

	m_readFile = _file;
	return true;
}

bool Serializer::beginWrite(File* _file)
{
	if (m_readFile || m_writeFile)
	{
		setErrorDesc("end() must be called before calling begin() again.");
		return false;
	}
	if (!_file || !_file->isOpen())
	{
		setErrorDesc("_file parameter must be given already opened.");
		return false;
	}

	m_writeFile = _file;
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

bool Serializer::isWriting() const
{
	ASSERT(m_readFile || m_writeFile); // This result has no sense if not between startRead/Write() and end().
	return m_writeFile != nullptr;
}

const char* Serializer::getErrorDesc()
{
	const char* errorDesc = m_errorDesc.c_str();
	m_errorDesc.resize(0);
	return errorDesc;
}

const File* Serializer::getReadFile() const
{
	return m_readFile;
}

File* Serializer::getWriteFile() const
{
	return m_writeFile;
}

void Serializer::setErrorDesc(const char* _errorDesc)
{
	m_errorDesc = _errorDesc;
}
