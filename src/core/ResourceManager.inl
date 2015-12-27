template <class T, typename... Args>
T* ResourceManager::createResource(Args... _args)
{
	T* resource = new T(_args...);
	registerResource(resource);
	return resource;
}
