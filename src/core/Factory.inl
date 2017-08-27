template<typename T>
void Factory::registerConstructor(const char* factoryId)
{
	s_creatorsMap[factoryId] = reinterpret_cast<void*(*)()>(&_constructor<T>);
}

template<typename T>
T* Factory::_constructor()
{
	return new T();
}