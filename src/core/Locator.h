#pragma once

#include <vector>
#include "core/Types.h"
#include "core/Assert.h"

class Locator
{
public:
	template <class T>
	static void Register(T* _value);

	template <class T>
	static T* Get();

private:
	template <class T>
	static uint32 GetServiceId();

	static std::vector<void*> s_services;
	static uint32 s_nextIndex;
};


template <class T>
void Locator::Register(T* _value)
{
	s_services[GetServiceId<T>()] = _value;
}

template <class T>
T* Locator::Get()
{
	return reinterpret_cast<T*>(s_services[GetServiceId<T>()]);
}

template <class T>
uint32 Locator::GetServiceId()
{
	static uint32 index = s_nextIndex;

	ASSERT(index <= s_services.size());
	if (index == s_services.size())
	{
		s_nextIndex++;
		s_services.resize(s_nextIndex);
	}

	return index;
}
