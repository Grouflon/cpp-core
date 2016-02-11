#pragma once

#include <vector>

class Resource;

class ResourceManager
{
public:

	ResourceManager();
	~ResourceManager();

	template <class T, typename... Args>
	static T* CreateResource(Args... _args);

	static void FlushResources();

	template <class T, typename... Args>
	T* createResource(Args... _args);
	void flushResources();

private:
	void registerResource(Resource* resource);

	std::vector<Resource*> m_resources;
};

static ResourceManager g_resourceManager;

#include "core/ResourceManager.inl"
