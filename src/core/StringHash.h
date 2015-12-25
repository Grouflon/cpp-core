#pragma once

#include <unordered_map>

#include "core/Types.h"

#ifdef _DEBUG
#define DEBUG_STRINGHASH
#endif

class StringHash
{
public:
	StringHash(const char* str);
	~StringHash();

	uint32 getHash() const;

	bool operator==(const StringHash& rhs) const;
	bool operator==(uint32 rhs) const;
	bool operator!=(const StringHash& rhs) const;
	bool operator< (const StringHash& rhs) const;
	bool operator> (const StringHash& rhs) const;
	bool operator<=(const StringHash& rhs) const;
	bool operator>=(const StringHash& rhs) const;

private:
	uint32		m_hash;
#ifdef DEBUG_STRINGHASH
	const char*	m_string;
#endif
};

// TODO: automatic debug strings destroyer
extern std::unordered_map<uint32, char*> g_stringHashes;

template <typename T>
class HashMap : public std::unordered_map<StringHash, T> {};

namespace std {
template <> struct hash<StringHash>		{ size_t operator()(const StringHash& value) const; };
} // namespace std
