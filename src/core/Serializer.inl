template <typename T>
bool Serializer::serialize(const char* _name, std::vector<T>& _value)
{
	size_t size = _value.size();
	bool result = beginVectorSerialization(_name, size);

	if (!result)
		return false;

	_value.resize(size);

	for (T& element : _value)
	{
		result = result && serialize(nullptr, _value);
	}
	result = result && endVectorSerialization();
	return result;
}


template <typename T>
bool Serializer::serialize(const char* _name, T** _value)
{
	return serialize(_name, _value, (*_value)->getClassDesc());
}

template <typename T>
bool Serializer::serialize(const char* _name, T* _value)
{
	return serialize(_name, _value, _value->getClassDesc());
}