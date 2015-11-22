#include "stdafx.h"
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
	m_members.push_back(ClassMember(_name, _address, _elementType, _elementCount));
}

ClassDesc::ClassMember::ClassMember(const char* _name, uint32 _address, MemberType _type)
	: name(_name)
	, address(_address)
	, type(_type)
	, elementType(TYPE_UNKNOWN)
	, elementCount(0)
{
}

ClassDesc::ClassMember::ClassMember(const char* _name, uint32 _address, MemberType _elementType, size_t _elementCount)
	: name(_name)
	, address(_address)
	, type(TYPE_ARRAY)
	, elementType(_elementType)
	, elementCount(_elementCount)
{

}

template <> ClassDesc::MemberType ClassDesc::getType(int*) const	{ return TYPE_INT; }
template <> ClassDesc::MemberType ClassDesc::getType(char*) const	{ return TYPE_CHAR; }
template <> ClassDesc::MemberType ClassDesc::getType(float*) const	{ return TYPE_FLOAT; }

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

ClassDesc* getClassDesc(const char* _className)
{
	return g_classSet.getClassDesc(_className);
}
