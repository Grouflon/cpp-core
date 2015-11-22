#pragma once

#include "core/Factory.h"
#include "core/ClassDesc.h"

#define REFLECT_BEGIN(_class) \
private: \
	static ClassDesc*	s_classDesc; \
public: \
	static const ClassDesc* getClassDesc() \
{ \
	ClassDesc* classDesc = g_classSet.getClassDesc(#_class); \
	if (!classDesc) { \
	classDesc = new ClassDesc(#_class); \
	g_classSet.setClassDesc(#_class, classDesc); \
	Factory::registerConstructor<_class>(#_class); \
	_class prototype;

#define REFLECT_END() \
	} \
	return classDesc; \
}

#define REFLECT_AUTO(_memberName) \
	classDesc->addMember(#_memberName, reinterpret_cast<uint32>(&prototype._memberName) - reinterpret_cast<uint32>(&prototype), &prototype._memberName);

#define REFLECT_ARRAY_AUTO(_memberName, _size) \
	classDesc->addArrayMember(#_memberName, reinterpret_cast<uint32>(&prototype._memberName) - reinterpret_cast<uint32>(&prototype), prototype._memberName, _size);

// TODO-MAYBE: typed reflect macros (ex: REFLECT_INT8)
// not sure this is useful, AUTO seems to work all the time