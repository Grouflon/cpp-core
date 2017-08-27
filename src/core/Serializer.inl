template <typename T>
bool Serializer::serialize(const char* _name, std::vector<T>& _value)
{
	size_t size = _value.size();
	bool result = serializeVectorStart(_name, size);

	if (!result)
		return false;

	_value.resize(size);

	for (T& element : _value)
	{
		result = result && serialize(nullptr, element);
	}
	result = result && serializeVectorStop();
	return result;
}


template <typename T>
bool Serializer::serialize(const char* _name, T** _value)
{
	return serialize(_name, reinterpret_cast<void**>(_value), (*_value)->GetClassDesc());
}

template <typename T>
bool Serializer::serialize(const char* _name, T* _value)
{
	return serialize(_name, _value, _value->GetClassDesc());
}