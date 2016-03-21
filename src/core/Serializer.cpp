#include "stdafx.h"
#include "core/Serializer.h"

#include "core/Assert.h"
#include "core/FileHandle.h"

Serializer::Serializer()
	: m_reading(false)
	, m_writing(false)
	, m_readFile(nullptr)
	, m_writeFile(nullptr)
	
{
}

Serializer::~Serializer()
{
}

bool Serializer::beginRead(const FileHandle* _file)
{
	if (m_reading || m_writing)
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
	m_reading = true;
	return true;
}

bool Serializer::beginWrite(FileHandle* _file)
{
	if (m_reading || m_writing)
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
	m_writing = true;
	return true;
}

bool Serializer::end()
{
	m_readFile = nullptr;
	m_writeFile = nullptr;
	m_reading = false;
	m_writing = false;
	return true;
}

bool Serializer::isReading() const
{
	return m_reading;
}

bool Serializer::isWriting() const
{
	return m_writing;
}

const char* Serializer::getErrorDesc()
{
	const char* errorDesc = m_errorDesc.c_str();
	m_errorDesc.resize(0);
	return errorDesc;
}

const FileHandle* Serializer::getReadFile() const
{
	return m_readFile;
}

FileHandle* Serializer::getWriteFile() const
{
	return m_writeFile;
}

void Serializer::setErrorDesc(const char* _errorDesc)
{
	m_errorDesc = _errorDesc;
}
