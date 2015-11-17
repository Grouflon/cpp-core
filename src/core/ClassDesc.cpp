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

template <>
void ClassDesc::addMember(const char* _name, int*, uint32 _address)
{
	addMember(_name, TYPE_INT, _address);
}

template <>
void ClassDesc::addMember(const char* _name, float*, uint32 _address)
{
	addMember(_name, TYPE_FLOAT, _address);
}

void ClassDesc::addMember(const char* _name, MemberType _type, uint32 _address)
{
	m_members.push_back(ClassMember(_name, _type, _address));
}

ClassDesc::ClassMember::ClassMember(const char* _name, MemberType _type, uint32 _address)
	: name(_name)
	, type(_type)
	, address(_address)
{
}

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

#include "core/ClassDesc.inl"
