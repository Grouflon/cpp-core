#pragma once

class Resource;

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
