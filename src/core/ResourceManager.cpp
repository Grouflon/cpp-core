#include "stdafx.h"
#include "core/ResourceManager.h"

#include "core/Resource.h"

ResourceManager::ResourceManager()
{
}

ResourceManager::~ResourceManager()
{
}

void ResourceManager::registerResource(Resource* resource)
{
#ifdef _DEBUG
	std::vector<Resource*>::iterator it = std::find(m_resources.begin(), m_resources.end(), resource);
	if (it != m_resources.end())
	{
		ASSERT(false) // Check for double registrations. Should never happen
		return;
	}
#endif
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