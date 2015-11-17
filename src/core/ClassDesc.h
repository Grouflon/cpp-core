#pragma once


class ClassDesc
{
public:
	ClassDesc(const char* _className);

	enum MemberType
	{
		TYPE_INT,
		TYPE_FLOAT,
		TYPE_REFLECTIVE
	};

	struct ClassMember
	{
		ClassMember(const char* _name, MemberType _type, uint32 _address);
		const char* name;
		MemberType	type;
		uint32		address;
	};

	const std::vector<ClassMember>& getMembers() const;
	const char*						getName() const;

	void addMember(const char* _name, MemberType _type, uint32 _address);

	template <typename T>
	void addMember(const char* _name, T*, uint32 _address);


private:
	const char*					m_name;
	std::vector<ClassMember>	m_members;
};

template <>
void ClassDesc::addMember(const char* _name, int*, uint32 _address);

template <>
void ClassDesc::addMember(const char* _name, float*, uint32 _address);


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
