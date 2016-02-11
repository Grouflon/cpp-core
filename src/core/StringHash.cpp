#include "stdafx.h"
#include "core/StringHash.h"

#include "core/Assert.h"
#include "core/HashTools.h"

StringHash::StringHash(const char* str)
{
	m_hash = hashString(str);

#ifdef DEBUG_STRINGHASH
	m_string = g_stringHashRepository.registerStringHash(m_hash, str);
#endif
}

StringHash::~StringHash()
{
}

uint32 StringHash::getHash() const
{
	return m_hash;
}

bool StringHash::operator==(const StringHash& rhs) const
{
	return m_hash == rhs.m_hash;
}

bool StringHash::operator==(uint32 rhs) const
{
	return m_hash == rhs;
}

bool StringHash::operator!=(const StringHash& rhs) const
{
	return m_hash != rhs.m_hash;
}

bool StringHash::operator<(const StringHash& rhs) const
{
	return m_hash < rhs.m_hash;
}

bool StringHash::operator>(const StringHash& rhs) const
{
	return m_hash > rhs.m_hash;
}

bool StringHash::operator<=(const StringHash& rhs) const
{
	return m_hash <= rhs.m_hash;
}

bool StringHash::operator>=(const StringHash& rhs) const
{
	return m_hash >= rhs.m_hash;
}


size_t std::hash<StringHash>::operator()(const StringHash& value) const
{
	return value.getHash();
}

#ifdef DEBUG_STRINGHASH
StringHashRepository g_stringHashRepository;

StringHashRepository::StringHashRepository()
{
}

StringHashRepository::~StringHashRepository()
{
	for (auto pair : m_stringMap)
	{
		delete pair.second;
	}
}

const char* StringHashRepository::registerStringHash(uint32 _hash, const char* _string)
{
	auto it = m_stringMap.find(_hash);
	if (it == m_stringMap.end())
	{
		size_t stringLength = strlen(_string);
		char* string = new char[stringLength + 1];
		memcpy(string, _string, stringLength + 1);
		m_stringMap.insert(std::pair<uint32, char*>(_hash, string));
		return string;
	}
	else
	{
		ASSERT(strcmp(_string, it->second) == 0); // Hash collision !
		return it->second;
	}
}
#endif
