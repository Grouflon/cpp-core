#include "core/ClassDesc.h"

ClassSet	g_classSet;

ClassDesc::ClassDesc(const char* _className)
	: m_name(_className)
{
}

const std::vector<ClassDesc::ClassMember>& ClassDesc::getMembers() const
{
	return m_members;
}

const char* ClassDesc::getName() const
{
	return m_name;
}

void ClassDesc::addMember(const char* _name, uint32 _address, MemberType _type)
{
	m_members.push_back(ClassMember(_name, _address, _type));
}

void ClassDesc::addArrayMember(const char* _name, uint32 _address, MemberType _elementType, size_t _elementCount)
{
	m_members.push_back(ClassMember(_name, _address, TYPE_ARRAY, _elementType, _elementCount));
}

void ClassDesc::addVectorMember(const char* _name, uint32 _address, MemberType _elementType)
{
	m_members.push_back(ClassMember(_name, _address, TYPE_VECTOR, _elementType));
}

ClassDesc::ClassMember::ClassMember(const char* _name, uint32 _address, MemberType _type, MemberType _elementType, size_t _elementCount)
	: name(_name)
	, address(_address)
	, type(_type)
	, elementType(_elementType)
	, elementCount(_elementCount)
{
}

template <> ClassDesc::MemberType ClassDesc::getType(bool*) const			{ return TYPE_BOOL; }
template <> ClassDesc::MemberType ClassDesc::getType(char*) const			{ return TYPE_CHAR; }
template <> ClassDesc::MemberType ClassDesc::getType(int8*) const			{ return TYPE_INT8; }
template <> ClassDesc::MemberType ClassDesc::getType(int16*) const			{ return TYPE_INT16; }
template <> ClassDesc::MemberType ClassDesc::getType(int32*) const			{ return TYPE_INT32; }
template <> ClassDesc::MemberType ClassDesc::getType(int64*) const			{ return TYPE_INT64; }
template <> ClassDesc::MemberType ClassDesc::getType(uint8*) const			{ return TYPE_UINT8; }
template <> ClassDesc::MemberType ClassDesc::getType(uint16*) const			{ return TYPE_UINT16; }
template <> ClassDesc::MemberType ClassDesc::getType(uint32*) const			{ return TYPE_UINT32; }
template <> ClassDesc::MemberType ClassDesc::getType(uint64*) const			{ return TYPE_UINT64; }
template <> ClassDesc::MemberType ClassDesc::getType(float*) const			{ return TYPE_FLOAT; }
template <> ClassDesc::MemberType ClassDesc::getType(double*) const			{ return TYPE_DOUBLE; }
template <> ClassDesc::MemberType ClassDesc::getType(std::string*) const	{ return TYPE_STRING; }

ClassSet::~ClassSet()
{
	for (auto& pair : m_classDescs) delete pair.second;
}

ClassDesc* ClassSet::getClassDesc(const char* _className)
{
	return m_classDescs[_className];
}

void ClassSet::setClassDesc(const char* _className, ClassDesc* _classDesc)
{
	ClassDesc*& classDesc = m_classDescs[_className];
	if (classDesc)
	{
		delete classDesc;
	}
	classDesc = _classDesc;
}

ClassDesc* GetClassDesc(const char* _className)
{
	return g_classSet.getClassDesc(_className);
}
