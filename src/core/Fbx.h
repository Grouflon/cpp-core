#pragma once

#include <cstdlib>

namespace fbx {

struct Node;
struct List;
struct Value;

enum ValueType
{
	FBX_UNKNOWN,
	FBX_NUMBER,
	FBX_STRING
};

struct Node
{
	Node();
	~Node();

	char* name;
	Node* next;

	Value* valueStart;
	size_t valueCount;

	Node* subStart;
	size_t subCount;

	Node* getNodeAt(const char* _symbolName) const;

	template <typename... Args>
	Node* getNodeAt(const char* _symbolName, Args... _args) const
	{
		return getNodeAt(_symbolName)->getNodeAt(_args...);
	}

	Value* getValueAt(unsigned int _index) const;
};

struct Value
{
	Value();
	~Value();

	const char* getString() const;
	float		getNumber() const;

	ValueType type;
	void* payload;
	Value* next;
};

void Read(const char* _buffer, Node* _out);

} // namespace Fbx