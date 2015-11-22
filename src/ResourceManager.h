#pragma once

class Resource;

#ifdef _DEBUG
#define DEBUG_CHECK_DOUBLE_REGISTRATION 1
#else
#define DEBUG_CHECK_DOUBLE_REGISTRATION 0
#endif

class ResourceManager
{
public:

	ResourceManager();
	~ResourceManager();

	void registerResource(Resource* resource);
	void flushResources();

private:
	std::vector<Resource*> m_resources;
};

static ResourceManager g_resourceManager;
