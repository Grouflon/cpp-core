#include "core/ResourceManager.h"

#include "core/Assert.h"
#include "core/Resource.h"

ResourceManager::ResourceManager()
{
}

ResourceManager::~ResourceManager()
{
	flushResources();
}

void ResourceManager::FlushResources()
{
	g_resourceManager.flushResources();
}

void ResourceManager::registerResource(Resource* resource)
{
	m_resources.push_back(resource);
}

void ResourceManager::flushResources()
{
	std::vector<Resource*>::iterator it = m_resources.begin();
	while (it != m_resources.end())
	{
		Resource* resource = *it;
		if (resource->getUseCount() == 0)
		{
			delete resource;
			it = m_resources.erase(it);
			continue;
		}
		++it;
	}
}