#include "stdafx.h"
#include "core/Factory.h"

std::unordered_map<StringHash, void*(*)()> Factory::s_creatorsMap;

void* Factory::create(const char* factoryId)
{
	return _getConstructor(factoryId)();
}

void*(* Factory::_getConstructor(const char* factoryId))()
{
	auto it = s_creatorsMap.find(factoryId);
	if (it != s_creatorsMap.end())
	{
		return it->second;
	}
	return nullptr;
}