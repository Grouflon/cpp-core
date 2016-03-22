#pragma once

#include "core/StringHash.h"

class ClassDesc
{
public:
	ClassDesc(const char* _className);

	enum MemberType
	{
		TYPE_BOOL,
		TYPE_CHAR,
		TYPE_INT8,
		TYPE_INT16,
		TYPE_INT32,
		TYPE_INT64,
		TYPE_UINT8,
		TYPE_UINT16,
		TYPE_UINT32,
		TYPE_UINT64,
		TYPE_FLOAT,
		TYPE_DOUBLE,

		TYPE_STRING,

		TYPE_ARRAY,

		TYPE_VECTOR,

		TYPE_UNKNOWN
	};

	struct ClassMember
	{
		ClassMember(const char* _name, uint32 _address, MemberType _type, MemberType _elementType = TYPE_UNKNOWN, size_t _elementCount = 0);
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
	void addVectorMember(const char* _name, uint32 _address, MemberType _elementType);

	template <typename T>
	void addMember(const char* _name, uint32 _address, T* _value);

	template <typename T>
	void addArrayMember(const char* _name, uint32 _address, T*, size_t _elementCount);

	template <typename T>
	void addVectorMember(const char* _name, uint32 _address, std::vector<T>*);

private:
	template <typename T>
	MemberType getType(T*) const;

	const char*					m_name;
	std::vector<ClassMember>	m_members;
};

template <> ClassDesc::MemberType  ClassDesc::getType(bool*) const;
template <> ClassDesc::MemberType  ClassDesc::getType(char*) const;
template <> ClassDesc::MemberType  ClassDesc::getType(int8*) const;
template <> ClassDesc::MemberType  ClassDesc::getType(int16*) const;
template <> ClassDesc::MemberType  ClassDesc::getType(int32*) const;
template <> ClassDesc::MemberType  ClassDesc::getType(int64*) const;
template <> ClassDesc::MemberType  ClassDesc::getType(uint8*) const;
template <> ClassDesc::MemberType  ClassDesc::getType(uint16*) const;
template <> ClassDesc::MemberType  ClassDesc::getType(uint32*) const;
template <> ClassDesc::MemberType  ClassDesc::getType(uint64*) const;
template <> ClassDesc::MemberType  ClassDesc::getType(float*) const;
template <> ClassDesc::MemberType  ClassDesc::getType(double*) const;
template <> ClassDesc::MemberType  ClassDesc::getType(std::string*) const;


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

ClassDesc* GetClassDesc(const char* _className);

#include "core/ClassDesc.inl"
