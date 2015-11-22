#pragma once


class ClassDesc
{
public:
	ClassDesc(const char* _className);

	enum MemberType
	{
		TYPE_INT,
		TYPE_CHAR,
		TYPE_FLOAT,
		TYPE_ARRAY,
		TYPE_UNKNOWN
	};

	struct ClassMember
	{
		ClassMember(const char* _name, uint32 _address, MemberType _type);
		ClassMember(const char* _name, uint32 _address, MemberType _elementType, size_t _elementCount); // C Array element
		const char* name;
		uint32		address;
		MemberType	type;
		MemberType	elementType;
		size_t		elementCount;
	};

	const std::vector<ClassMember>& getMembers() const;
	const char*						getName() const;

	void addMember(const char* _name, uint32 _address, MemberType _type);
	void addArrayMember(const char* _name, uint32 _address, MemberType _elementType, size_t _elementCount);

	template <typename T>
	void addMember(const char* _name, uint32 _address, T* _value);

	template <typename T>
	void addArrayMember(const char* _name, uint32 _address, T*, size_t _elementCount);

	

private:
	template <typename T>
	MemberType getType(T*) const;

	const char*					m_name;
	std::vector<ClassMember>	m_members;
};

template <> ClassDesc::MemberType  ClassDesc::getType(int*) const;
template <> ClassDesc::MemberType  ClassDesc::getType(char*) const;
template <> ClassDesc::MemberType  ClassDesc::getType(float*) const;


class ClassSet
{
public:
	~ClassSet();

	ClassDesc* getClassDesc(const char* _className);
	void setClassDesc(const char* _className, ClassDesc* _classDesc);

private:
	std::unordered_map<StringHash, ClassDesc*> m_classDescs;
};
extern ClassSet	g_classSet;

ClassDesc* getClassDesc(const char* _className);

#include "core/ClassDesc.inl"
