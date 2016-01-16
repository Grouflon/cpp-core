template <class T, typename... Args>
T* ResourceManager::CreateResource(Args... _args)
{
	return g_resourceManager.createResource<T, Args...>(_args...);
}


template <class T, typename... Args>
T* ResourceManager::createResource(Args... _args)
{
	T* resource = new T(_args...);
	registerResource(resource);
	return resource;
}
