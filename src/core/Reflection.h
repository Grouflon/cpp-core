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
	classDesc->addMember(#_memberName, &prototype._memberName, reinterpret_cast<uint32>(&prototype._memberName) - reinterpret_cast<uint32>(&prototype));

#define REFLECT_INT(_memberName) \
	classDesc->addMember(#_memberName, ClassDesc::TYPE_INT, reinterpret_cast<uint32>(&prototype._memberName) - reinterpret_cast<uint32>(&prototype));