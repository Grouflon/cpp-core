template <typename T>
void ClassDesc::addMember(const char* _name, uint32 _address, T* _value)
{
	addMember(_name, _address, getType(_value));
}

template <typename T>
void ClassDesc::addArrayMember(const char* _name, uint32 _address, T* _value, size_t _elementCount)
{
	addArrayMember(_name, _address, getType(_value), _elementCount);
}


template <typename T>
void ClassDesc::addVectorMember(const char* _name, uint32 _address, std::vector<T>* _value)
{
	addArrayMember(_name, _address, getType(_value->data()));
}

template <typename T>
ClassDesc::MemberType ClassDesc::getType(T*) const
{
	return TYPE_UNKNOWN;
}
