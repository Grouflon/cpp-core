#include "stdafx.h"
#include "core/Serializer.h"
#include "core/Serializable.h"

Serializer::Serializer(File* file, Mode mode)
{
	m_file = file;
	m_mode = mode;

	// TODO: assert if file is not opened
}

Serializer::~Serializer()
{
}