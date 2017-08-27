#include "core/Fbx.h"

#include <cstring>
#include "core/Assert.h"

#define FBX_BUFFER_SIZE 256

namespace fbx {

void skipBlanks(const char** _cursor)
{
	while (**_cursor == ' ' || **_cursor == '\t' || **_cursor == '\r')
	{
		++(*_cursor);
	}
}

void skipCommas(const char** _cursor)
{
	while (**_cursor == ',')
	{
		++(*_cursor);
	}
}

void skipNumber(const char** _cursor)
{
	while (**_cursor != '\0' && (**_cursor == '-' || **_cursor == '.' || (**_cursor >= '0' && **_cursor <= '9')))
	{
		++(*_cursor);
	}
}

void skipLine(const char** _cursor)
{
	while (**_cursor != '\n')
	{
		if (**_cursor == '\0') return;

		++(*_cursor);
	}
	++(*_cursor);
}

void skipComments(const char** _cursor)
{
	while (**_cursor == ';')
	{
		skipLine(_cursor);
	}
}

bool isValidSymbolCharacter(char c)
{
	return (
		(c >= 'A' && c <= 'Z') ||
		(c >= 'a' && c <= 'z') ||
		(c >= '0' && c <= '9')
	);
}

bool tryEnterSymbol(const char* _name, const char** _cursor)
{
	size_t nameLength = strlen(_name);

	skipBlanks(_cursor);
	if (strncmp(*_cursor, _name, nameLength) == 0 && *(*_cursor + nameLength) == ':')
	{
		*_cursor += nameLength + 1;
		return true;
	}
	else
	{
		return false;	
	}
}

bool tryEnterObject(const char** _cursor)
{
	skipBlanks(_cursor);
	if (**_cursor == '{')
	{
		skipLine(_cursor);
		return true;
	}
	else
	{
		return false;
	}
}

void exitObject(const char** _cursor)
{
	int level = 1;
	while (**_cursor != '\0' && (level > 0 || **_cursor != '\n'))
	{
		if (**_cursor == '{') ++level;
		else if (**_cursor == '}') --level;

		++(*_cursor);
	}
	++(*_cursor);
}

bool isObjectEnd(const char** _cursor)
{
	skipBlanks(_cursor);
	return **_cursor == '}';
}

Value* readNumber(const char** _cursor)
{
	if (**_cursor != '-' && **_cursor != '.' && (**_cursor < '0' || **_cursor > '9'))
		return nullptr;

	// CREATE VALUE
	Value* value = new Value;
	value->type = FBX_NUMBER;
	float* number = new float;
	// TODO: use strtof
	*number = static_cast<float>(atof(*_cursor));
	value->payload = number;

	skipNumber(_cursor);

	return value;
}

Value* readString(const char** _cursor)
{
	skipBlanks(_cursor);
	if (**_cursor != '"')
		return nullptr;

	++*_cursor;

	char buffer[FBX_BUFFER_SIZE];
	int size = 0;
	while (**_cursor != '\0' && **_cursor != '"')
	{
		if (size < FBX_BUFFER_SIZE - 1)
		{
			buffer[size] = **_cursor;
			++size;
		}
		++*_cursor;
	}

	if (**_cursor != '"')
		return nullptr;

	buffer[size] = '\0';
	++*_cursor;

	// CREATE VALUE
	Value* value = new Value;
	value->type = FBX_STRING;
	char* str = new char[size + 1];
	strcpy(str, buffer);
	value->payload = str;

	return value;
}

bool readValue(const char** _cursor, Node* _node)
{
	skipBlanks(_cursor);

	Value* value = readNumber(_cursor);
	if (!value) value = readString(_cursor);

	if (!value)
		return false;

	// GET PARENT
	Value** attach = &_node->valueStart;
	while (*attach != nullptr)
	{
		attach = &(*attach)->next;
	}

	*attach = value;
	++_node->valueCount;
	return true;
}

Node::Node()
{
	name = nullptr;
	next = nullptr;
	valueStart = nullptr;
	valueCount = 0;
	subStart = nullptr;
	subCount = 0;
}

Node::~Node()
{
	delete[] name;

	Value* value = valueStart;
	while (value)
	{
		Value* next = value->next;
		delete value;
		value = next;
	}

	Node* node = subStart;
	while (node)
	{
		Node* next = node->next;
		delete node;
		node = next;
	}
}

Node* Node::getNodeAt(const char* _symbolName) const
{
	Node* result = nullptr;

	Node* currentNode = subStart;

	while (currentNode)
	{
		if (strcmp(currentNode->name, _symbolName) == 0)
		{
			result = currentNode;
			break;
		}
		currentNode = currentNode->next;
	}

	return result;
}

Value* Node::getValueAt(unsigned int _index) const
{
	if (_index >= valueCount)
		return nullptr;

	Value* value = valueStart;
	while (_index > 0)
	{
		value = value->next;
		--_index;
	}
	return value;
}

Value::Value()
{
	type = FBX_UNKNOWN;
	payload = nullptr;
	next = nullptr;
}

Value::~Value()
{
	switch (type)
	{
	case FBX_NUMBER:
		{
			delete static_cast<float*>(payload);
		} break;

	case FBX_STRING:
		{
			delete[] static_cast<char*>(payload);
		} break;

	default: break;
	}
}

const char* Value::getString() const
{
	ASSERT(type == FBX_STRING);
	return static_cast<char*>(payload);
}

float Value::getNumber() const
{
	ASSERT(type == FBX_NUMBER);
	return *static_cast<float*>(payload);
}

bool ReadNode(const char** _cursor, Node* _scope)
{
	skipComments(_cursor);
	skipBlanks(_cursor);

	if (!isValidSymbolCharacter(**_cursor))
	{
		skipLine(_cursor);
		return false;
	}



	// GET A VALID NAME
	char buffer[FBX_BUFFER_SIZE];
	int size = 0;
	while (isValidSymbolCharacter(**_cursor))
	{
		if (size < FBX_BUFFER_SIZE - 1)
		{
			buffer[size] = **_cursor;
			++size;
		}

		++*_cursor;
	}
	buffer[size] = '\0';
	if (**_cursor != ':')
	{
		skipLine(_cursor);
		return false;
	}

	// SKIP SEMICOLON
	++*_cursor;

	// GET PARENT
	Node** attach = &_scope->subStart;
	while (*attach != nullptr)
	{
		attach = &(*attach)->next;
	}

	// CREATE NODE
	Node* node = new Node;
	*attach = node;
	++_scope->subCount;
	node->name = new char[size + 1];
	strcpy(node->name, buffer);

	skipBlanks(_cursor);

	
	while (readValue(_cursor, node))
	{
		skipBlanks(_cursor);

		if (**_cursor == '\n')
		{
			skipLine(_cursor);
			skipBlanks(_cursor);
		}

		skipCommas(_cursor);
	}

	if (**_cursor == '{')
	{
		skipLine(_cursor);
		skipBlanks(_cursor);
		while (**_cursor != '\0' && **_cursor != '}')
		{
			ReadNode(_cursor, node);
			skipBlanks(_cursor);
		}
		skipLine(_cursor);
	}
	return true;
}

void Read(const char* _buffer, Node* _out)
{
	const char* cursor = _buffer;

	while (*cursor != '\0')
	{
		ReadNode(&cursor, _out);
	}
}

} // namespace Fbx
