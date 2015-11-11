#pragma once

class Factory
{
public:

	template<typename T>
	static void registerContructor(const char* factoryId);

	static void* create(const char* factoryId);

private:

	template<typename T>
	static T* _constructor();

	static void*(*_getConstructor(const char* factoryId))();

	static std::unordered_map<StringHash, void*(*)()>	s_creatorsMap;
};

#include "core/Factory.inl"