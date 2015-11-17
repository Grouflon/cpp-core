#include "stdafx.h"
#include "core/StringHash.h"

#include "core/HashTools.h"

std::unordered_map<uint32, char*> g_stringHashes;

StringHash::StringHash(const char* str)
{
	m_hash = hashString(str);

#ifdef DEBUG_STRINGHASH
	auto it = g_stringHashes.find(m_hash);
	if (it == g_stringHashes.end())
	{
		size_t stringLength = strlen(str);
		char* string = new char[stringLength + 1];
		memcpy(string, str, stringLength + 1);
		g_stringHashes.insert(std::pair<uint32, char*>(m_hash, string));
		m_string = string;
	}
	else
	{
		m_string = it->second;
		ASSERT(strcmp(str, m_string) == 0); // Hash collision !
	}
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

